#include "subnet.h"

int amountOfHostIPs(CIDRBlock *block) {
    return pow(2,32 - block->prefixLength)-2;
}

int CIDRParser(CIDRBlock *block, char *CIDR) {
    char *ptrTraversal = CIDR;
    char *IP = calloc(1, sizeof(char));
    char *prefix = calloc(1, sizeof(char));
    bool prefixFound = false;

    while(*ptrTraversal != '\0') {
        if(*ptrTraversal == '/') {
            prefixFound = true;
            ptrTraversal++;
            continue;
        }
        else if(prefixFound){
            int prefixLength = strlen(prefix);
            char *temp = realloc(prefix, prefixLength + 2);
            if(temp == NULL) {
                perror("Failled to allocate memory for the prefix");
                return EXIT_FAILURE;
            }
            *(temp + prefixLength) = *ptrTraversal;
            *(temp + prefixLength + 1) = '\0';
            prefix = temp;
        }
        else {
            int IPLength = strlen(IP);
            char *temp = realloc(IP, IPLength + 2);
            if(temp == NULL) {
                perror("Failled to allocate memory for the IP address");
                return EXIT_FAILURE;
            }
            *(temp+ IPLength) = *ptrTraversal;
            *(temp+ IPLength + 1) = '\0';
            IP = temp;
        }
        ptrTraversal++;
    }

    block->IPAddress->ipStrValue = IP;
    block->IPAddress->ipIntValue = inet_addr(IP);
    block->prefixLength = atoi(prefix);

    printf("%d\n", block->prefixLength);
    printf("%s\n", block->IPAddress->ipStrValue);
    free(prefix);
    
    return EXIT_SUCCESS;

}

int generateSubnetMasks(CIDRBlock *block) {
    block->subnetMask = generateMask((block)->prefixLength,1);
    block->wildcardMask = generateMask((block)->prefixLength,0);
    if(block->subnetMask == NULL | block->wildcardMask == NULL) {
        perror("Couldn't generate masks\n");
        return EXIT_FAILURE;
    }
    
    return EXIT_SUCCESS;
}

int generateAddresses(CIDRBlock *block){
    block->networkAddress = generateAddress(block->subnetMask,block->IPAddress,1);
    block->broadcastAddress = generateAddress(block->subnetMask,block->IPAddress,0);
    if(block->networkAddress == NULL | block->broadcastAddress == NULL) {
        perror("Couldn't generate addresses\n");
        return EXIT_FAILURE;
    }
    
    return EXIT_SUCCESS;
}

int generateHostIPs(CIDRBlock *block){
    (block->hostIPs) = (IPv4 **)malloc((amountOfHostIPs(block))*sizeof(IPv4 *));
    for(int i = 0; i<amountOfHostIPs(block);i++){
        initIP(&(block->hostIPs[i]));
        uint32_t network = ntohl(block->networkAddress->ipIntValue);
        uint32_t resultIP = (i+1)+network;
        block->hostIPs[i]->ipIntValue = htonl(resultIP);

        struct in_addr conversionAddr;
        conversionAddr.s_addr = block->hostIPs[i]->ipIntValue;
        block->hostIPs[i]->ipStrValue = strdup(inet_ntoa(conversionAddr));
    }
    return EXIT_SUCCESS;
}

int initCIDRBlock(CIDRBlock **block, char *CIDR){
    *block = (CIDRBlock *)malloc(sizeof(CIDRBlock));
    if((*block) == NULL) {
        perror("Failled to initialize CIDRBlock");
        return EXIT_FAILURE;
    }
    initIP(&((*block)->IPAddress));
    CIDRParser(*block, CIDR);
    generateSubnetMasks(*block);
    generateAddresses(*block);
    generateHostIPs(*block);

    return EXIT_SUCCESS;
}

int destroyCIDRBlock(CIDRBlock *block){ 
    destroyIP(block->IPAddress);
    destroyIP(block->subnetMask);
    destroyIP(block->wildcardMask);
    destroyIP(block->networkAddress);
    destroyIP(block->broadcastAddress);
    for(int i = 0; i<amountOfHostIPs(block); i++){
        destroyIP(block->hostIPs[i]);
    }
    free(block->hostIPs);
    free(block);
    return EXIT_SUCCESS;
}
