#include "ip.h"

int initIP(IPv4 **ipv4){
    *ipv4 = (IPv4 *)malloc(sizeof(IPv4));
    return EXIT_SUCCESS;
}

IPv4 *generateMask(int prefixLength){
    return NULL;
}