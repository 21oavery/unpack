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

__attribute__((section(".text.startup"))) void _start() {
    void *kern = getKern();
}
