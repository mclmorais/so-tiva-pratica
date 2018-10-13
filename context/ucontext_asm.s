    .syntax unified
    .arch armv7-m

.text

.set P_ucontext_t           , 0
.set stack_t_Pss_sp         , 1 * 4
.set stack_t_ss_size        , 2 * 4
.set stack_t_ss_flags       , 3 * 4
.set mcontext_t_regPC       , 4 * 4  //; // program counter
.set mcontext_t_regSP       , 5 * 4  //	int ; // stack pointer
.set mcontext_t_regCPSR     , 6 * 4  //; // status register
.set mcontext_t_regR0       , 7 * 4
.set mcontext_t_regR1       , 8 * 4
.set mcontext_t_regR2       , 9 * 4
.set mcontext_t_regR3       ,10 * 4
.set mcontext_t_regR4       ,11 * 4
.set mcontext_t_regR5       ,12 * 4
.set mcontext_t_regR6       ,13 * 4
.set mcontext_t_regR7       ,14 * 4
.set mcontext_t_regR8       ,15 * 4
.set mcontext_t_regR9       ,16 * 4
.set mcontext_t_regR10      ,17 * 4
.set mcontext_t_regR11      ,18 * 4
.set mcontext_t_regR12      ,19 * 4
.set mcontext_t_regR13      ,20 * 4
.set mcontext_t_regR14      ,21 * 4
.set mcontext_t_regR15      ,22 * 4
.set ucontext_t_func        ,23 * 4
.set ucontext_t_initialized ,24 * 4
.set ucontext_t_arg         ,25 * 4


.global get_context_asm
get_context_asm:

//	push     {lr}
  str.w       r0,  [r0,#mcontext_t_regR0]
  str.w       r1,  [r0,#mcontext_t_regR1]
  str.w       r2,  [r0,#mcontext_t_regR2]
  str.w       r3,  [r0,#mcontext_t_regR3]
  str.w       r4,  [r0,#mcontext_t_regR4]
  str.w       r5,  [r0,#mcontext_t_regR5]
  str.w       r6,  [r0,#mcontext_t_regR6]
  str.w       r7,  [r0,#mcontext_t_regR7]
  str.w       r8,  [r0,#mcontext_t_regR8]
  str.w       r9,  [r0,#mcontext_t_regR9]
  str.w       r10, [r0,#mcontext_t_regR10]
  str.w       r11, [r0,#mcontext_t_regR11]
  str.w       r12, [r0,#mcontext_t_regR12]
  str.w       r13, [r0,#mcontext_t_regR13]
  str.w       r14, [r0,#mcontext_t_regR14]
  push	  {r3}
  //mov	      r3, #regR15
//    mov       r3, r15
    mov         r3, pc //r15
    //add       r3, #6
  str.w       r3,  [r0,#mcontext_t_regR15]
  pop       {r3}
//	pop     {pc}
    bx        lr //; return


.global set_context_asm
set_context_asm:


//    push    {lr}
  LDR	 r1 ,  [r0 ,#mcontext_t_regR1]
    LDR  r2 ,  [r0 ,#mcontext_t_regR2]
    LDR  r3 ,  [r0 ,#mcontext_t_regR3]
    LDR  r4 ,  [r0 ,#mcontext_t_regR4]
    LDR  r5 ,  [r0 ,#mcontext_t_regR5]
    LDR  r6 ,  [r0 ,#mcontext_t_regR6]
    LDR  r7 ,  [r0 ,#mcontext_t_regR7]
    LDR  r8 ,  [r0 ,#mcontext_t_regR8]
    LDR  r9 ,  [r0 ,#mcontext_t_regR9]
    LDR  r10,  [r0 ,#mcontext_t_regR10]
    LDR  r11,  [r0 ,#mcontext_t_regR11]
    LDR  r12,  [r0 ,#mcontext_t_regR12]
//    LDR  r13,  [r0 ,#mcontext_t_regR13]
    LDR  r14,  [r0 ,#mcontext_t_regR14]

  LDR	 r1 ,  [r0 ,#ucontext_t_initialized]
  CMP  r1 , 0
  BNE  inicializado

    // ainda não inicializado
    mov  r1,   #1
  STR  r1 ,  [r0 ,#ucontext_t_initialized]
  LDR	 r1 ,  [r0 ,#mcontext_t_regR1]
  ldr  R13,  [r0 ,#stack_t_Pss_sp]
    LDR  r15,  [r0 ,#ucontext_t_func]
//	pop     {pc}
    bx     lr

inicializado:
  LDR	 r1 ,  [r0 ,#mcontext_t_regR1]
    LDR  r13,  [r0 ,#mcontext_t_regR13]
//    LDR  r15,  [r0 ,#mcontext_t_regR15]
    LDR  r15,  [r0 ,#mcontext_t_regR14]
//	pop     {pc}
    bx     lr
//	.end


////////////////////////  SWAP BEG /////////////////////
.global swap_context_asm
swap_context_asm:

  str.w       r0,  [r0,#mcontext_t_regR0]
  str.w       r1,  [r0,#mcontext_t_regR1]
  str.w       r2,  [r0,#mcontext_t_regR2]
  str.w       r3,  [r0,#mcontext_t_regR3]
  str.w       r4,  [r0,#mcontext_t_regR4]
  str.w       r5,  [r0,#mcontext_t_regR5]
  str.w       r6,  [r0,#mcontext_t_regR6]
  str.w       r7,  [r0,#mcontext_t_regR7]
  str.w       r8,  [r0,#mcontext_t_regR8]
  str.w       r9,  [r0,#mcontext_t_regR9]
  str.w       r10, [r0,#mcontext_t_regR10]
  str.w       r11, [r0,#mcontext_t_regR11]
  str.w       r12, [r0,#mcontext_t_regR12]
  str.w       r13, [r0,#mcontext_t_regR13]
  str.w       r14, [r0,#mcontext_t_regR14]
  push        {r3}
  mov         r3,  pc
  str.w       r3,  [r0,#mcontext_t_regR15]
  pop         {r3}
///////////////////////  end get   beg set

  //LDR	 r1 ,  [r1 ,#mcontext_t_regR1]
    ldr  r2 ,  [r1 ,#mcontext_t_regR2]
    ldr  r3 ,  [r1 ,#mcontext_t_regR3]
    ldr  r4 ,  [r1 ,#mcontext_t_regR4]
    ldr  r5 ,  [r1 ,#mcontext_t_regR5]
    ldr  r6 ,  [r1 ,#mcontext_t_regR6]
    ldr  r7 ,  [r1 ,#mcontext_t_regR7]
    ldr  r8 ,  [r1 ,#mcontext_t_regR8]
    ldr  r9 ,  [r1 ,#mcontext_t_regR9]
    ldr  r10,  [r1 ,#mcontext_t_regR10]
    ldr  r11,  [r1 ,#mcontext_t_regR11]
    ldr  r12,  [r1 ,#mcontext_t_regR12]
    ldr  r14,  [r1 ,#mcontext_t_regR14]

    ldr	 r0 ,  [r1 ,#ucontext_t_initialized]
    cmp  r0 , 0
    bne  inicializado1

    // ainda não inicializado
    mov  r0,   #1
    STR  r0 ,  [r1 ,#ucontext_t_initialized]
    ldr  R13,  [r1 ,#stack_t_Pss_sp]
    ldr  r0,   [r1 ,#ucontext_t_arg]
    LDR  r15,  [r1 ,#ucontext_t_func]
    bx     lr

inicializado1:
    LDR  r13,  [r1 ,#mcontext_t_regR13]
    LDR  r15,  [r1 ,#mcontext_t_regR14]
    bx     lr

////////////////////////  SWAP END /////////////////////


