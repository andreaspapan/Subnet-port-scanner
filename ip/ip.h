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
    uint32_t ipIntValue;
    in_addr_t ipAddr;

} IPv4;

int initIP(IPv4 **ipv4);
int destroyIP(IPv4 *ipv4);
IPv4 *generateMask(int prefixLength);

#endif