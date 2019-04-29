/*******************************************************************************
* NAME: Dhcp                                                                   *
*                                                                              *
* AUTHOR: Dor Yadidi                                                           *
* DATE UPDATED:  3.01.18                                                       *
*******************************************************************************/
#ifndef __DHCP_H__
#define __DHCP_H__

#include <stddef.h>

#include "enum_rd58.h"

typedef struct dhcp_s dhcp_t;
typedef unsigned char ip_address_t[4];

dhcp_t *DhcpCreate(const ip_address_t network_ip, const size_t cidr_mask);
/*******************************************************************************
* Dhcp constractor                                                             *
*                                                                              *
* parameters                                                                   *
*  network_ip - network IP address, not NULL                                   *
*  cidr_mask - network mask in cidr form                                       *
*                                                                              *
* returns                                                                      *
*  Dhcp descriptor pointer                                                     *
*******************************************************************************/

void DhcpDestroy(dhcp_t *dhcp);
/*******************************************************************************
* Frees all memory allocated for Dhcp                                          *
*                                                                              *
* parameters                                                                   *
*  dhcp - dhcp descriptor pointer, not NULL                                    *
*                                                                              *
* returns                                                                      *
*  none                                                                        *
*******************************************************************************/

size_t DhcpCountFree(const dhcp_t *dhcp);
/*******************************************************************************
* Returns the amount of free IP addresess in a dhcp                                          *
*                                                                              *
* parameters                                                                   *
*  dhcp - dhcp descriptor pointer, not NULL                                    *
*******************************************************************************/

status DhcpAllocIP(
	dhcp_t *dhcp, ip_address_t out_ip, const ip_address_t suggested_ip
	);
/*******************************************************************************
* Allocates a new IP address                                                   *
*                                                                              *
* parameters                                                                   *
*  dhcp - dhcp descriptor pointer, not NULL                                    *
*  out_ip - IP pointer for returned allocation, not NULL                       *
*  suggested_ip - minimal IP value for allocation,                             *
                  if NULL any IP will be returned                              *
*                                                                              *
* returns                                                                      *
*  SUCCESS - if allocation is successful                                       *
*  FAIL - if no IP address is found for allocation                             *
*  MEMORY_ALLOCATION_FAIL - if memory allocation failed                        *
*******************************************************************************/

status DhcpFreeIP(dhcp_t *dhcp, const ip_address_t ip_to_free);
/*******************************************************************************
* Frees a IP address for future use                                            *
*                                                                              *
* parameters                                                                   *
*  dhcp - dhcp descriptor pointer, not NULL                                    *
*  ip_to_free - ip to be freed, not NULL                                       *
*                                                                              *
* returns                                                                      *
*  SUCCESS - if ip is freed                                                    *
*  FAIL - if ip is not found                                                   *
*******************************************************************************/
#endif
