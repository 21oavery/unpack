#include <stdio.h>
#include "libob.c"

#ifndef NULL
#define NULL ((void *) 0)
#endif

void *getKern() {
    void *ptr;
    SAB;
    SAB;
    // Get peb
#ifdef _LP64
    __asm__("movq %%fs:0x60, %0":"=r"(ptr));
#else
    __asm__("movl %%fs:0x30, %0":"=r"(ptr));
#endif
    // Get peb_ltr_data
    ptr = ((char *) ptr) + (4 + 2 * sizeof(void *));
    ptr = *((void **) ptr);
    // Get InMemoryOrderModuleList
    ptr = ((char *) ptr) + (8 + 3 * sizeof(void *));
    ptr = *((void **) ptr);
    // Get third item (kernal32.dll) base address
    SAB;
    SAB;
    return ***((char ****) ptr) + (4 * sizeof(void *));
}

static char strLookup[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz.";

char _access(unsigned int offset) {
    SAB;
    offset ^= 0xfeedfeed;
    return strData[offset - 17];
}

#define access(x) _access(((x) + 17) ^ 0xfeedfeed)

void memcpy(restrict void *src, restrict void *dst, unsigned int len) {
    for (unsigned int i = 0; i < len; i++) {
        ((char *) dst)[i] = ((char *) src)[i];
    }
}

int streq(const void *a, const void *b) {
    unsigned int i = 0;
    while (1) {
        char r = ((char *) a)[i];
        if (r != ((char *) b)[i]) return 0;
        if (!r) return 1;
    }
}

void *getFunct(void *dll) {
    // Get start of new exe header
    void *ptr = ((char *) dll) + 60;
    ptr = ((char *) dll) + *((long *) ptr);
    // Get export table
    ptr = ((char *) ptr) + 120;
    unsigned long extRel = *((unsigned long *) ptr);
    // Find the section the export table is located in
    ptr = 

__attribute__((section(".text.startup"))) void _start() {
    void *kern = getKern();
}
