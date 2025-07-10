#include "subnet.h"

int amountOfIPs(CIDRBlock *block) {
    return pow(2,32 - block->prefixLength);
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
    block->prefixLength = atoi(prefix);

    printf("%d\n", block->prefixLength);
    printf("%s\n", block->IPAddress->ipStrValue);
    free(prefix);
    
    return EXIT_SUCCESS;

}

int generateSubnetMasks(CIDRBlock *block) {
    block->subnetMask = generateMask(block->prefixLength);
    block->wildcardMask = generateMask(32 - (block->prefixLength));   
    
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


    return EXIT_SUCCESS;
}

int destroyCIDRBlock(CIDRBlock *block){ 
    free(block->IPAddress->ipStrValue);
    free(block->IPAddress);
    free(block);
    return EXIT_SUCCESS;
}