#ifndef _BYTECODE_INTERPRETER_H
#define _BYTECODE_INTERPRETER_H

#include "DEL.h"
#include "Son.h"

#include "Moteur.h"
#include "memoire_24.h"


class BytecodeInterpreter {

	public :
		BytecodeInterpreter();
		void run();
		void dispatch_instruction(uint8_t instruction, uint8_t operande);
		void configTimer1();
		void exec_DBT();
		void exec_ATT(uint8_t operande);
		void exec_DAL(uint8_t operande);
		void exec_DET(uint8_t operande);
		void exec_SGO(uint8_t operande);
		void exec_SAR();
		void exec_MAR();
		void exec_MAV(uint8_t operande);
		void exec_MRE(uint8_t operande);
		void exec_TRD();
		void exec_TRG();
		void exec_FIN();

		
	private :
		// DEL del_;
		Son son_;
		Moteur moteur_;
		Memoire24CXXX mem_;

};
#endif // _BYTECODE_INTERPRETER_H
