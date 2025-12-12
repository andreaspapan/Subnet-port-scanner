#ifndef ip
#define ip

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <inttypes.h>
#include <arpa/inet.h>

typedef struct IPv4 {
    char *ipStrValue;
    in_addr_t ipIntValue;

} IPv4;

int initIP(IPv4 **ipv4);
int destroyIP(IPv4 *ipv4);
IPv4 *generateMask(int prefixLength,bool type);
IPv4 *generateAddress(IPv4 *subnetMask,IPv4 *ipCIDR,bool type);

#endif