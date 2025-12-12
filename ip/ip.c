#include "ip.h"

int initIP(IPv4 **ipv4){
    *ipv4 = (IPv4 *)malloc(sizeof(IPv4));
    if((*ipv4) == NULL) {
        perror("Could not allocate memory for the IP");
        return EXIT_FAILURE;
    }
    (*ipv4)->ipStrValue = NULL;
    return EXIT_SUCCESS;

}

IPv4 *generateMask(int prefixLength,bool type){
    IPv4 *ipAddr;
    int res = initIP(&ipAddr);
    if(res == 1){
        return NULL;
    }
    if(type == true){ // Subnet mask
        (ipAddr->ipIntValue) = htonl((~0U << (32 - prefixLength)));
    } else {  // Wildcard mask
        ipAddr->ipIntValue = htonl((1U << (32 - prefixLength)) - 1);
    }

    struct in_addr conversionAddr;
    conversionAddr.s_addr = ipAddr->ipIntValue;
    //ipAddr->ipStrValue = strdup(inet_ntoa(conversionAddr));
    ipAddr->ipStrValue = malloc(strlen((inet_ntoa(conversionAddr)))+1);
    strcpy(ipAddr->ipStrValue,inet_ntoa(conversionAddr));

    return ipAddr;
}

IPv4 *generateAddress(IPv4 *subnetMask, IPv4 *ipCIDR, bool type){
    IPv4 *ipAddr;
    int res = initIP(&ipAddr);
    if(res == 1){
        return NULL;
    }
    if(type == true){ // Network address
        (ipAddr->ipIntValue) = htonl(ntohl(subnetMask->ipIntValue) & ntohl(ipCIDR->ipIntValue));
    } else {  // Broadcast address
        ipAddr->ipIntValue = htonl(ntohl(ipCIDR->ipIntValue) | ~ntohl(subnetMask->ipIntValue));
    }

    struct in_addr conversionAddr;
    conversionAddr.s_addr = ipAddr->ipIntValue;
    //ipAddr->ipStrValue = strdup(inet_ntoa(conversionAddr));
    ipAddr->ipStrValue = malloc(strlen((inet_ntoa(conversionAddr)))+1);
    strcpy(ipAddr->ipStrValue,inet_ntoa(conversionAddr));

    return ipAddr;
}

int destroyIP(IPv4 *ipv4){
    free(ipv4->ipStrValue);
    free(ipv4);
    return EXIT_SUCCESS;
}
