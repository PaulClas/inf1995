#ifndef instruction_H
#define instruction_H

#include <avr/io.h>
#include <util/delay.h>

class Instruction
{
public:
    Instruction(){}
    Instruction(uint8_t opcode_, uint8_t operand_);
	uint8_t opcode;
	uint8_t operand;
};
#endif
