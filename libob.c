#pragma once

#define SAB do {rmStack();__asm__(".ascii \"\\45\"");} while (0)
#define PAD __asm__(".ascii \"\\45\"");

void rmStack() {
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
