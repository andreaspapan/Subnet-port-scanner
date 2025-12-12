#ifndef subnet
#define subnet

#include "../ip/ip.h"

typedef struct CIDRBlock{
    int prefixLength;
    IPv4 *subnetMask;
    IPv4 *wildcardMask;
    IPv4 *IPAddress;
    IPv4 *networkAddress;
    IPv4 *broadcastAddress;
    IPv4 **hostIPs;

} CIDRBlock;


int amountOfHostIPs(CIDRBlock *block);
int CIDRParser(CIDRBlock *block, char *CIDR);
int generateSubnetMasks(CIDRBlock *block);
int generateAddresses(CIDRBlock *block);
int initCIDRBlock(CIDRBlock **block, char *CIDR);
int generateHostIPs(CIDRBlock *block);
int destroyCIDRBlock(CIDRBlock *block);

#endif