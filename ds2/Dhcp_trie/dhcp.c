/*******************************************************************************
* NAME: Dhcp                                                                   *
*                                                                              *
* AUTHOR: Dor Yadidi                                                           *
* DATE UPDATED:  7.01.18                                                       *
*******************************************************************************/

#include <stddef.h> /* size_t */
#include <assert.h> /* assert */
#include <stdlib.h> /* free malloc */
#include "dhcp.h"

#define BITS_IN_CHAR 8
#define TOTAL_BITS 32
#define NO_FREE_ADDRESSES 0
#define LEAF_DEPTH 0

typedef enum {ZERO, ONE, NUMBER_OF_CHILDREN} direction_e;

typedef struct trie_node_s trie_node_t;

struct trie_node_s
{
	trie_node_t *children[NUMBER_OF_CHILDREN];
	size_t number_of_free_addresses;
};

struct dhcp_s
{
	trie_node_t *root;
	size_t cidr_mask;
	ip_address_t network_ip;
};

typedef union {
	ip_address_t curr_ip;
	unsigned int ip_to_int;
} ip_to_int_t;

/****************************Functions Decelerations***************************/

static trie_node_t *DHCPCreateNode(size_t number_of_free_addresses);
static status CreateConstIP(dhcp_t *dhcp);
static void CastIPLittleEndian(ip_address_t dest, const ip_address_t src);
static void RecursiveDhcpDestroy(trie_node_t *root);
static trie_node_t *ReserveAddress(trie_node_t *node, size_t trie_depth,
                                   ip_address_t ip_to_reserve, status *stat);
static status FindFreeAddres(trie_node_t *node, ip_to_int_t *out_ip, size_t trie_depth);
static size_t UpdateNumOfFree(trie_node_t *node, size_t trie_depth);
static trie_node_t *RecursiveFreeAddress(trie_node_t *node, ip_to_int_t *ip_to_free,
	                                    size_t trie_depth, status *result_state);
/*************************************************************************/

static trie_node_t *DHCPCreateNode(size_t number_of_free_addresses)
{
	trie_node_t *node = (trie_node_t *)malloc(sizeof(trie_node_t));

	if (NULL == node)
	{
		return (NULL);
	}

	node->children[ZERO] = NULL;
	node->children[ONE] = NULL;
	node->number_of_free_addresses = number_of_free_addresses;

	return (node);
}

static status CreateConstIP(dhcp_t *dhcp)
{
	status stat = SUCCESS;
	ip_address_t network = {0, 0, 0, 0};
	ip_address_t broadcast = {255, 255, 255, 255};
	ip_address_t gateway = {255, 255, 255, 254};

	ReserveAddress(dhcp->root, dhcp->cidr_mask, network, &stat);

	if (SUCCESS != stat)
	{
		return (FAIL);
	}

	ReserveAddress(dhcp->root, dhcp->cidr_mask, broadcast, &stat);

	if (SUCCESS != stat)
	{
		return (FAIL);
	}

	ReserveAddress(dhcp->root, dhcp->cidr_mask, gateway, &stat);

	if (SUCCESS != stat)
	{
		return (FAIL);
	}

	return (SUCCESS);
}


static trie_node_t *ReserveAddress(trie_node_t *node, size_t trie_depth,
                                   ip_address_t ip_to_reserve, status *stat)
{
	ip_to_int_t ip_int;
	int direction = 0;

	CastIPLittleEndian(ip_int.curr_ip, ip_to_reserve);

	direction = (ip_int.ip_to_int >> (trie_depth - 1)) & 1;

	if (LEAF_DEPTH == trie_depth)
	{
		*stat = SUCCESS;
		--node->number_of_free_addresses;
		return (node);
	}

	if (1 == trie_depth && node->children[direction] != NULL)
	{
		*stat = FAIL;
		return (node);
	}

	if (NULL == node->children[direction])
	{
		node->children[direction] = DHCPCreateNode(1 << (trie_depth - 1));

		if (NULL == node->children[direction])
		{
			*stat = MEMORY_ALLOCATION_FAIL;

			if (NULL == node->children[!direction])
			{
				free(node);
				node = NULL;
				return (NULL);
			}

			return (node);
		}
	}

	node->children[direction] = ReserveAddress(node->children[direction],
                                           trie_depth - 1, ip_to_reserve, stat);

	if (MEMORY_ALLOCATION_FAIL == *stat)
	{
		if (!node->children[!direction])
		{
			free(node);
			return (NULL);
		}
	}

	--node->number_of_free_addresses;

	return (node);
}

static void CastIPLittleEndian(ip_address_t dest, const ip_address_t src)
{
	dest[0] = src[3];
	dest[1] = src[2];
	dest[2] = src[1];
	dest[3] = src[0];
}

/*********************************Create***************************************/

dhcp_t *DhcpCreate(const ip_address_t network_ip, const size_t cidr_mask)
{
	dhcp_t *dhcp = (dhcp_t *)malloc(sizeof(dhcp_t));
	const size_t cidr = TOTAL_BITS - cidr_mask;

	assert(network_ip && cidr_mask);

	if (NULL == dhcp)
	{
		return (NULL);
	}

	dhcp->root = DHCPCreateNode(1 << cidr);

	if (NULL == dhcp->root)
	{
		free(dhcp);
		dhcp = NULL;
		return (NULL);
	}

	dhcp->cidr_mask = cidr;

	CastIPLittleEndian(dhcp->network_ip, network_ip);

	if(CreateConstIP(dhcp) != SUCCESS)
	{
		DhcpDestroy(dhcp);
		return (NULL);
	}

	return (dhcp);
}

/*******************************Destroy****************************************/

static void RecursiveDhcpDestroy(trie_node_t *root)
{
	if (NULL == root)
	{
		return;
	}

	RecursiveDhcpDestroy(root->children[ZERO]);
	RecursiveDhcpDestroy(root->children[ONE]);
	free(root);
	root = NULL;
}

void DhcpDestroy(dhcp_t *dhcp)
{
	assert(dhcp != NULL);

	if (NULL != dhcp->root)
	{
		RecursiveDhcpDestroy(dhcp->root);
	}

	free(dhcp);
	dhcp = NULL;
}

/***********************************Count**************************************/

size_t DhcpCountFree(const dhcp_t *dhcp)
{
	assert(dhcp != NULL);

	return (dhcp->root->number_of_free_addresses);
}

/***********************************Allocate***********************************/

static status FindFreeAddres(trie_node_t *node, ip_to_int_t *out_ip, size_t trie_depth)
{
	status stat;
	int direction = (out_ip->ip_to_int >> (trie_depth - 1)) & 1;

	if (LEAF_DEPTH == trie_depth)
	{
		--node->number_of_free_addresses;
		return (SUCCESS);
	}

	for (	; direction < NUMBER_OF_CHILDREN; ++direction)
	{
		if (NULL == node->children[direction])
		{
			node->children[direction] = DHCPCreateNode(1 << (trie_depth - 1));

			if (NULL == node->children[direction])
			{
				return (MEMORY_ALLOCATION_FAIL);
			}
		}

		if (NO_FREE_ADDRESSES != node->children[direction]->number_of_free_addresses)
		{
			stat = FindFreeAddres(node->children[direction],
                                               out_ip, trie_depth - 1);

			if (MEMORY_ALLOCATION_FAIL == stat)
			{
				return (MEMORY_ALLOCATION_FAIL);
			}

			if (SUCCESS == stat)
			{
				out_ip->ip_to_int &= ~(1 << (trie_depth - 1));
				out_ip->ip_to_int |= direction << (trie_depth - 1);

				--node->number_of_free_addresses;

				return (SUCCESS);
			}
		}
	}

	out_ip->ip_to_int = 0;

	return (FAIL);
}

status DhcpAllocIP(dhcp_t *dhcp, ip_address_t out_ip, const ip_address_t suggested_ip)
{
	status stat;
	ip_to_int_t int_out_ip;
	assert(dhcp && out_ip);

	int_out_ip.ip_to_int = 0;

	if (NULL != suggested_ip)
	{
		CastIPLittleEndian(int_out_ip.curr_ip, suggested_ip);
	}

	stat = FindFreeAddres(dhcp->root, &int_out_ip, dhcp->cidr_mask);
	int_out_ip.ip_to_int |=
		(*(unsigned int *)dhcp->network_ip >> dhcp->cidr_mask) << dhcp->cidr_mask;

	CastIPLittleEndian(out_ip, int_out_ip.curr_ip);

	return (stat);
}

/************************************Free**************************************/

static size_t UpdateNumOfFree(trie_node_t *node, size_t trie_depth)
{
	if (NULL != node->children[ZERO])
	{
		if (NULL == node->children[ONE])
		{
			return (
			node->children[ZERO]->number_of_free_addresses + (1 << (trie_depth - 1)));
		}

		return (node->children[ZERO]->number_of_free_addresses +
				node->children[ONE]->number_of_free_addresses);

	}

	if (NULL != node->children[ONE])
	{
		return (
			node->children[ONE]->number_of_free_addresses + (1 << (trie_depth - 1)));
	}

	return (1 << trie_depth);
}

static trie_node_t *RecursiveFreeAddress(trie_node_t *node, ip_to_int_t *ip_to_free,
                                size_t trie_depth, status *result_state)
{
	int direction = (ip_to_free->ip_to_int >> (trie_depth - 1)) & 1;

	if (LEAF_DEPTH == trie_depth)
	{
		free(node);
		node = NULL;
		return (NULL);
	}

	if (NULL == node->children[direction])
	{
		*result_state = FAIL;
		return (node);
	}

	node->children[direction] =
		RecursiveFreeAddress(node->children[direction],
					ip_to_free, trie_depth - 1, result_state);

	if (*result_state != SUCCESS)
	{
		return (node);
	}

	if (NULL == node->children[ZERO] && NULL == node->children[ONE])
	{
		free(node);
		node = NULL;
		return (NULL);
	}

	node->number_of_free_addresses = UpdateNumOfFree(node, trie_depth);

	return (node);
}

status DhcpFreeIP(dhcp_t *dhcp, const ip_address_t ip_to_free)
{
	status result_state = SUCCESS;
	ip_to_int_t int_ip_to_free;
	assert(dhcp && ip_to_free);

	CastIPLittleEndian(int_ip_to_free.curr_ip, ip_to_free);
	RecursiveFreeAddress(dhcp->root, &int_ip_to_free, dhcp->cidr_mask, &result_state);

	return (result_state);
}
