#include <stdio.h>

void xpx() {
    puts("hi");
}

void d() {
#ifdef _LP64
    __asm__("movq 16(%%rbp), %%rax\n"
            "inc %%rax\n"
            "movq %%rax, 16(%%rbp)\n"
            :::"%rax");
#else
    __asm__("movl 8(%%ebp), %%eax\n"
            "inc %%eax\n"
            "movl %%eax, 8(%%ebp)\n"
            :::"%eax");
#endif
}

int main(int argc, char **argv) {
    d();
    __asm__(".ascii \"\\45\"");
    xpx();
}
