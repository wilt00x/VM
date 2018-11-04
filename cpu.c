/* This program is divided into three parties : 
   
   1) The passage of the addresses to the execution
   2) Applying operations by passing addresses
   3) Dump of registers
  This program is a virtual basic and simple cpu, virtual machine.
  ADD,ADD,SUB and MOV operations
 */

// DEVELOPED by wilt00x

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>


// Colors ...
#define RED     "\x1b[31m"
#define GREEN   "\x1b[32m"
#define CYAN    "\x1b[36m"
#define RESET   "\x1b[0m"
#define BOLD    "\033[1m"

// R15 register
int program_counter = 0x00;

// The registers 
int r0              = 0x00;
int r1              = 0x00;
int r2              = 0x00;
int r3              = 0x00;

ssize_t execute_instructions(unsigned char opcode, unsigned char operand1, 
	unsigned char operand2, unsigned char operand3);

void reset_registers();
void dump_registers();
int execute(int instructions[], int size);
int execute(int instructions[], int size)
{
	unsigned char opcode;
	unsigned char operand1;
	unsigned char operand2;
	unsigned char operand3;

	for(program_counter = 0; program_counter < size; program_counter++)
	{
		operand1 = (instructions[program_counter] >> 24) & 0xff;
        operand2 = (instructions[program_counter] >> 16) & 0xff;
        operand3 = (instructions[program_counter] >> 8) & 0xff;

        // get most significant byte (opcode)
        opcode = (instructions[program_counter] >> 24) & 0xff;

		execute_instructions(opcode, operand1, operand2, operand3);
	}

	puts("\n[~] Execution finished\n");

	return 0;
}

ssize_t execute_instructions(unsigned char opcode, unsigned char operand1, 
	unsigned char operand2, unsigned char operand3)
{
	switch(opcode)
	{
		case 0x01:

		switch(operand1) // ADD Operation
		{
			case 0x00:

			r0 = operand2 + operand3;
			printf("ADD R0 : 0x%02x, 0x%02x\n", operand2, operand3);
			break;

			case 0x01:

			r1 = operand2 + operand3;
			printf("ADD R1 : 0x%02x, 0x%02x\n", operand2, operand3);
			break;

			case 0x02:

			r2 = operand2 + operand3;
			printf("ADD R2 : 0x%02x, 0x%02x\n", operand2, operand3);
			break;

			case 0x03:

			r3 = operand2 + operand3;
			printf("ADD R3 : 0x%02x, 0x%02x\n", operand2, operand3);
			break;

			default:
			puts(RED BOLD"[ERROR] : UNKNOWN REGISTER\n"RESET BOLD);
		}
		break;

		case 0x02:

		switch(operand1) // SUB Operation
		{
			case 0x00:

			r0 = operand2 - operand3;
			printf("SUB R0 : 0x%02x, 0x%02x\n", operand2, operand3);
			break;

			case 0x01:

			r1 = operand2 - operand3;
			printf("SUB R1 : 0x%02x, 0x%02x\n", operand2, operand3);
			break;

			case 0x02:

			r2 = operand2 - operand3;
			printf("SUB R2 : 0x%02x, 0x%02x\n", operand2, operand3);
			break;

			case 0x03:

			r3 = operand2 - operand3;
			printf("SUB R3 : 0x%02x, 0x%02x\n", operand2, operand3);
			break;

			default:
			puts(RED BOLD"[ERROR] : UNKNOWN REGISTER\n"RESET BOLD);
		}
		break;

		case 0x03:

		switch(operand1) // MOV Operation
		{
			case 0x00:

			r0 = operand2;
			printf("MOV R0 : 0x%02x\n", operand2);
			break;

			case 0x01:

			r1 = operand2;
			printf("MOV R1 : 0x%02x\n", operand2);
			break;

			case 0x02:

			r2 = operand2;
			printf("MOV R2 : 0x%02x\n", operand2);
			break;

			case 0x03:

			r3 = operand2;
			printf("MOV R3 : 0x%02x\n", operand2);
			break;

			default:
			puts(RED BOLD"[ERROR] : UNKNOWN REGISTER\n"RESET BOLD);
		}
			
			/* default:
			puts(RED BOLD"[ERROR] : UNKNOWN REGISTER\n"RESET BOLD);
			return -1; */
	}

	return 0;
}

void reset_registers()
{
	// Reset operation
	r0 = 0x00;
	r1 = 0x00;
	r2 = 0x00;
	r3 = 0x00;

	program_counter = 0x00;
}

void dump_registers() 
{
	puts("Registers dump : \n");
	printf(GREEN BOLD"R0 : 0x%08x\nR1 : 0x%08x\nR2 : 0x%08x\nR3 : 0x%08x\nPC : 0x%08x\n\n"RESET BOLD, r0, r1, r2, r3, program_counter);
}

int main()
{
	printf(CYAN BOLD"+=======================================\n");
	printf("|                                       \n");
	printf("| A Virtual Machine Developed by wilt00x\n");
	printf("|                                       \n");
	printf("+=======================================\n\n"RESET BOLD);

	// The arguments that will be executed by our virtual machine
	int execArg[] = {
		0x010134F4,
		0x0102D345, 
		0x0202FFB2, 
		0x0303BA00 
	};

	size_t execLen = sizeof(execArg)/4;

	puts("Executing ...\n");
	execute(execArg, execLen); // Exec. ...

	dump_registers(); // Dump registers
	reset_registers(); // Reset any registers

	return 0;
}
