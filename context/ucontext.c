// #pragma ARM
#include "ucontext.h"

extern int flag;
extern int memPC;

int r;
int r0, r1, r2, r3, r4, r5, r6, r7, r8, r9, r10, r11, r12, r13, r14, r15;

int getcontext(ucontext_t *context)
{
	//__asm ("MOV SR, r" );   ;  SR = status register no MSP 430
	/*__asm (
			"MRS %[r], CPSR\n\t"
			: [r] "=&r" (r)
			:
	);   // CPSR = Current Program Status Register no ARM
	context->uc_mcontext.regCPSR = r;*/

	//__asm("MOV R4, r");               No ARM:  MOV dst, src   MSP430: MOV src, dst
	//context->uc_mcontext.regR4 = r;

	__asm(
		"MOV %[r], %[r0]"
		: [r] "=&r"(r)
		: [r0] "m"(r0));
	context->uc_mcontext.regR0 = r;

	__asm(
		"MOV %[r], %[r1]"
		: [r] "=&r"(r)
		: [r1] "m"(r1));
	context->uc_mcontext.regR1 = r;

	__asm(
		"MOV %[r], %[r2]"
		: [r] "=&r"(r)
		: [r2] "m"(r2));
	context->uc_mcontext.regR2 = r;

	__asm(
		"MOV %[r], %[r3]"
		: [r] "=&r"(r)
		: [r3] "m"(r3));
	context->uc_mcontext.regR3 = r;

	__asm(
		"MOV %[r], %[r4]"
		: [r] "=&r"(r)
		: [r4] "m"(r4));
	context->uc_mcontext.regR4 = r;

	__asm(
		"MOV %[r], %[r5]"
		: [r] "=&r"(r)
		: [r5] "m"(r5));
	context->uc_mcontext.regR5 = r;

	__asm(
		"MOV %[r], %[r6]"
		: [r] "=&r"(r)
		: [r6] "m"(r6));
	context->uc_mcontext.regR6 = r;

	__asm(
		"MOV %[r], %[r7]"
		: [r] "=&r"(r)
		: [r7] "m"(r7));
	context->uc_mcontext.regR7 = r;

	__asm(
		"MOV %[r], %[r8]"
		: [r] "=&r"(r)
		: [r8] "m"(r8));
	context->uc_mcontext.regR8 = r;

	__asm(
		"MOV %[r], %[r9]"
		: [r] "=&r"(r)
		: [r9] "m"(r9));
	context->uc_mcontext.regR9 = r;

	__asm(
		"MOV %[r], %[r10]"
		: [r] "=&r"(r)
		: [r10] "m"(r10));
	context->uc_mcontext.regR10 = r;

	__asm(
		"MOV %[r], %[r11]"
		: [r] "=&r"(r)
		: [r11] "m"(r11));
	context->uc_mcontext.regR11 = r;

	__asm(
		"MOV %[r], %[r12]"
		: [r] "=&r"(r)
		: [r12] "m"(r12));
	context->uc_mcontext.regR12 = r;

	__asm(
		"MOV %[r], %[r13]"
		: [r] "=&r"(r)
		: [r13] "m"(r13)); // ARM SP register
	context->uc_mcontext.regR13 = r;

	//__asm("MOV r, LR");            // ARM LR register
	//context->uc_mcontext.reg14 = r;

	__asm(
		"MOV %[r], %[r15]"
		: [r] "=&r"(r)
		: [r15] "m"(r15)); // ARM PC register
	context->uc_mcontext.regR15 = r;

	// asm
	// (
	// "MOV PC, r"
	// );
	// if(!flag)
	// context->uc_mcontext.regPC = r; // Com salvamento em ASM

	context->uc_mcontext.regPC = memPC;

	return 0;
}

int setcontext(ucontext_t *context)
{

	/*r = context->uc_mcontext.regCPSR;
	//MSR     CPSR_c, xxxx      sets the control bits
    //MSR     CPSR_f, xxxx      sets the flag bits
    //MSR     CPSR_cxsf, xxxx   sets everything

	__asm("MSR CPSR_f, r1");
	//__asm("MSR CPSR_c, r1");*/

	r = context->uc_mcontext.regR4;
	__asm(
		"MOV %[r4], %[r]"
		: [r4] "=&r"(r4)
		: [r] "m"(r));

	r = context->uc_mcontext.regR5;
	__asm(
		"MOV %[r5], %[r]"
		: [r5] "=&r"(r5)
		: [r] "m"(r));

	r = context->uc_mcontext.regR6;
	__asm(
		"MOV %[r6], %[r]"
		: [r6] "=&r"(r6)
		: [r] "m"(r));

	r = context->uc_mcontext.regR7;
	__asm(
		"MOV %[r7], %[r]"
		: [r7] "=&r"(r7)
		: [r] "m"(r));

	r = context->uc_mcontext.regR8;
	__asm(
		"MOV %[r8], %[r]"
		: [r8] "=&r"(r8)
		: [r] "m"(r));

	r = context->uc_mcontext.regR9;
	__asm(
		"MOV %[r9], %[r]"
		: [r9] "=&r"(r9)
		: [r] "m"(r));

	r = context->uc_mcontext.regR10;
	__asm(
		"MOV %[r10], %[r]"
		: [r10] "=&r"(r10)
		: [r] "m"(r));

	r = context->uc_mcontext.regR11;
	__asm(
		"MOV %[r11], %[r]"
		: [r11] "=&r"(r11)
		: [r] "m"(r));

	r = context->uc_mcontext.regR12;
	__asm(
		"MOV %[r12], %[r]"
		: [r12] "=&r"(r12)
		: [r] "m"(r));

	r = context->uc_mcontext.regR13;
	__asm(
		"MOV %[r13], %[r]"
		: [r13] "=&r"(r13)
		: [r] "m"(r));

	r = context->uc_mcontext.regR14;
	__asm(
		"MOV %[r14], %[r]"
		: [r14] "=&r"(r14)
		: [r] "m"(r));

	r = context->uc_mcontext.regR15;
	__asm(
		"MOV %[r15], %[r]"
		: [r15] "=&r"(r15)
		: [r] "m"(r));

	///////////////////////////////////////////////////////////////////
	if (!context->initialized)
	{
		r = (int)context->uc_stack.ss_sp;
		__asm(
			"MOV %[r13], %[r]"
			: [r13] "=&r"(r13)
			: [r] "m"(r));

		r = (int)(context->func);
		context->initialized = 1;
		__asm(
			"MOV %[r15], %[r]"
			: [r15] "=&r"(r15)
			: [r] "m"(r));
	}

	else
	{
		flag = 1;
		r = context->uc_mcontext.regSP;
		__asm(
			"MOV %[r13], %[r]"
			: [r13] "=&r"(r13)
			: [r] "m"(r));

		r = context->uc_mcontext.regPC;
		__asm(
			"MOV %[r15], %[r]"
			: [r15] "=&r"(r15)
			: [r] "m"(r));
	}

	return 0;
}

/////////////////////////////////////////////////////////////////////////

//void makecontext(ucontext_t *context, int start_routine, int n_parms, char* parm)
void makecontext(ucontext_t *context, int start_routine, int n_parms, char *parm)
{
	context->func = start_routine;
}

int swapcontext(ucontext_t *saida, ucontext_t *entrada)
{
	getcontext(saida);
	setcontext(entrada);

	return 0;
}
