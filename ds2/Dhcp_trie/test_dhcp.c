#include <math.h>   /* pow */
#include <stdlib.h> /* malloc free */

#include "test.h"
#include "dhcp.h"

#define BITS_IN_IP 32

TestResult DhcpCreateTest();
TestResult DhcpCountFreeTest();
TestResult DhcpAllocIPBasicTest();
TestResult DhcpAllocIPTest();
TestResult DhcpFreeIPTest();
TestResult DhcpAllocSuggestedIpBasicTest();
TestResult DhcpAllocSuggestedIpTest();

int main()
{
	RUN_TEST(DhcpCreateTest);
	RUN_TEST(DhcpCountFreeTest);
	RUN_TEST(DhcpAllocIPBasicTest);
	RUN_TEST(DhcpAllocIPTest);
	RUN_TEST(DhcpFreeIPTest);
	RUN_TEST(DhcpAllocSuggestedIpBasicTest);
	RUN_TEST(DhcpAllocSuggestedIpTest);

	return (0);
}

TestResult DhcpCreateTest()
{
	ip_address_t network_ip = {192, 168, 1, 0};
	size_t cidr_mask = 24;
	dhcp_t *dhcp = DhcpCreate(network_ip, cidr_mask);
	DhcpDestroy(dhcp);
	return (TEST_PASS);
}

TestResult DhcpCountFreeTest()
{
	ip_address_t network_ip = {192, 168, 1, 0};
	size_t cidr_mask = 24;
	dhcp_t *dhcp = DhcpCreate(network_ip, cidr_mask);

	REQUIRE(DhcpCountFree(dhcp) == pow(2, BITS_IN_IP - cidr_mask) - 3);

	DhcpDestroy(dhcp);

	return (TEST_PASS);
}

TestResult DhcpAllocIPBasicTest()
{
	ip_address_t network_ip = {192, 168, 1, 0};
	size_t cidr_mask = 24;
	dhcp_t *dhcp = DhcpCreate(network_ip, cidr_mask);
	ip_address_t *out_ip = malloc(sizeof(ip_address_t));
	size_t number_of_free_addresses = DhcpCountFree(dhcp);

	DhcpAllocIP(dhcp, *out_ip, NULL);
	REQUIRE(DhcpCountFree(dhcp) == number_of_free_addresses - 1);

	DhcpDestroy(dhcp);
	free(out_ip);

	return (TEST_PASS);
}

static bool AreAllDestinct(ip_address_t *ips, size_t number_of_ips)
{
	size_t i;

	for (i = 0; i < number_of_ips; ++i)
	{
		size_t j;

		for (j = 0; j < i; ++j)
		{
			if (*(int *)ips[i] == *(int *)ips[j])
			{
				return (FALSE);
			}
		}

		++j;

		for (; j < number_of_ips; ++j)
		{
			if (*(int *)ips[i] == *(int *)ips[j])
			{
				return (FALSE);
			}
		}
	}

	return (TRUE);
}

TestResult DhcpAllocIPTest()
{
	ip_address_t network_ip = {192, 168, 1, 0};
	size_t cidr_mask = 24;
	size_t i;
	dhcp_t *dhcp = DhcpCreate(network_ip, cidr_mask);
	size_t number_of_free_addresses = DhcpCountFree(dhcp);
	ip_address_t *out_ips =
		calloc(sizeof(ip_address_t), number_of_free_addresses);

	ip_address_t *out_ip_bad =
		malloc(sizeof(ip_address_t));

	for (i = 0; i < number_of_free_addresses; ++i)
	{
		DhcpAllocIP(dhcp, out_ips[i], NULL);
		REQUIRE(DhcpCountFree(dhcp) == number_of_free_addresses - i - 1);
		/* REQUIRE(192 == out_ips[i][0]);
		REQUIRE(168 == out_ips[i][1]);
		REQUIRE(1 == out_ips[i][2]); */
	}

	REQUIRE(AreAllDestinct(out_ips, number_of_free_addresses));

	REQUIRE(FAIL == DhcpAllocIP(dhcp, *out_ip_bad, NULL));
	REQUIRE(DhcpCountFree(dhcp) == 0);

	DhcpDestroy(dhcp);
	free(out_ips);
	free(out_ip_bad);

	return (TEST_PASS);
}

TestResult DhcpFreeIPTest()
{
	ip_address_t network_ip = {192, 168, 1, 0};
	size_t cidr_mask = 24;
	size_t i;
	dhcp_t *dhcp = DhcpCreate(network_ip, cidr_mask);
	size_t number_of_free_addresses = DhcpCountFree(dhcp);
	ip_address_t *out_ips =
		calloc(sizeof(ip_address_t), number_of_free_addresses);

	for (i = 0; i < number_of_free_addresses; ++i)
	{
		DhcpAllocIP(dhcp, out_ips[i], NULL);
	}

	for (i = 0; i < number_of_free_addresses; ++i)
	{
		DhcpFreeIP(dhcp, out_ips[i]);
		REQUIRE(DhcpCountFree(dhcp) == i + 1);
		REQUIRE(AreAllDestinct(out_ips, number_of_free_addresses - i - 1));
	}

	DhcpDestroy(dhcp);
	free(out_ips);

	return (TEST_PASS);
}

TestResult DhcpAllocSuggestedIpBasicTest()
{
	ip_address_t network_ip = {192, 168, 1, 0};
	ip_address_t suggested_ip = {192, 168, 1, 100};
	size_t cidr_mask = 24;
	dhcp_t *dhcp = DhcpCreate(network_ip, cidr_mask);
	ip_address_t *out_ip = malloc(sizeof(ip_address_t));

	DhcpAllocIP(dhcp, *out_ip, suggested_ip);

	REQUIRE(100 == out_ip[0][3]);

	DhcpDestroy(dhcp);
	free(out_ip);

	return (TEST_PASS);
}

TestResult DhcpAllocSuggestedIpTest()
{
	ip_address_t network_ip = {192, 168, 1, 0};
	unsigned char last_digit = 100;
	size_t i;
	size_t cidr_mask = 24;
	dhcp_t *dhcp = DhcpCreate(network_ip, cidr_mask);

	ip_address_t *out_ips = malloc(sizeof(ip_address_t) * ((256 - last_digit)));

	ip_address_t *suggested_ip = malloc(sizeof(ip_address_t));
	suggested_ip[0][0] = 192;
	suggested_ip[0][1] = 168;
	suggested_ip[0][2] = 1;
	suggested_ip[0][3] = last_digit;

	for (i = 0; i < (unsigned)(255 - last_digit - 1); ++i)
	{
		REQUIRE(SUCCESS == DhcpAllocIP(dhcp, out_ips[i], *suggested_ip));
		REQUIRE(last_digit + i == out_ips[i][3]);
	}

	DhcpDestroy(dhcp);
	free(out_ips);
	free(suggested_ip);

	return (TEST_PASS);
}
