/*
	Class to parse and provide information about instructions.
*/
#pragma once

class Instruction {

public:

	Instruction() { };
	~Instruction() { };

	// Codes to indicate the type of instruction we are processing.
	enum InstructionType {
		ST_MachineLanguage, // A machine language instruction.
		ST_AssemblerInstr,	// Assembler Language instruction.
		ST_Comment,			// Comment or blank line.
		ST_End,				// End instruction.
		ST_Error,			// Error instruction.
		ST_Empty			// Empty instruction.
	};

	// Parse the Instruction.
	InstructionType ParseInstruction(string &a_buff);

	// Compute the location of the next instruction.
	int LocationNextInstruction(int a_loc);

	// Return label.
	inline string getLabel() { return m_Label; };

	// Determine if a label is blank.
	inline bool isLabel() { return !m_Label.empty(); };
	
	// Return Number of OpCode.
	inline int getOpCodeNum() { return m_NumOpCode; };

	// Return OpCode.
	inline string &getOpCode() { return m_OpCode; };

	// Determine if Operand exists.
	inline bool isOperand() { return !m_Operand.empty(); };

	// Return Operand.
	inline string getOperand() { return m_Operand; };

	// Return Operand Value
	inline int getOperandValue() { return m_OperandValue; };

private:


	// The elemements of a instruction
	string m_Label;            // The label.
	string m_OpCode;       // The symbolic op code.
	string m_Operand;      // The operand.


	string m_instruction;    // The original instruction.

							 // Derived values.
	int m_NumOpCode;     // The numerical value of the op code.
	InstructionType m_type; // The type of instruction.

	bool m_IsNumericOperand;// == true if the operand is numeric.
	int m_OperandValue;   // The value of the operand if it is numeric.
	
	// Ordered vector of machine OpCodes and assembly OpCodes
	vector<string> machine_OpCodes {"add","sub","mult","div","load","store","read","write","b","bm","bz","bp","halt"};
	vector<string> assem_OpCodes { "dc","ds","org","end" };
};

