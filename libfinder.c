#define NULL ((void *) 0)

void *getDLList() {
    void *ptr;
    // Get peb
#ifdef _LP64
    __asm__("movq fs:0x60, %0":"=r"(ptr));
#else
    __asm__("movl fs:0x30, %0":"=r"(ptr));
#endif
    // Get peb_ltr_data
    ptr = ((char *) ptr) + (4 + 2 * sizeof(void *));
    ptr = *((void *) ptr);
    // Get InMemoryOrderModuleList and return
    ptr = ((char *) ptr) + (8 + 3 * sizeof(void *));
    return ptr;
}

void *getDLL(void *head, int index) {
    void *ptr = *((void **) head);
    while (index) {
        if (ptr == head) return NULL;
        ptr = *((void **)
