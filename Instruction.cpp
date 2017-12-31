#include "stdafx.h"
#include "Instruction.h"
#include "Errors.h"

/**/
/*
Instruction::ParseInstruction(string &a_buff)

NAME

Instruction::ParseInstruction(string &a_buff)

SYNOPSIS

Instruction::InstructionType Instruction::ParseInstruction(string &a_buff)
a_buff            --> instruction line to parse.

DESCRIPTION

This function receives an isntruction to be parsed.

RETURNS

Returns the instruction type.

AUTHOR

Philip Glazman

DATE

12/18/2017

*/
/**/
Instruction::InstructionType 
Instruction::ParseInstruction(string &a_buff)
{
	// Reassigning values to the variables so that past instruction values do not interfere.
	m_Label = "";
	m_OperandValue = 0;
	m_Operand = "";
	m_OpCode = "";
	m_instruction = "";
	m_IsNumericOperand = true;
	m_NumOpCode = 0;

	// Return an ST_Empty instruction type if there is no instruction.
	if ( a_buff.empty() ) 
		return ST_Empty;


	// Remove any comments because they're not necessary for reading the instruction set.
	if ( a_buff.find(";") != string::npos )
	{
		// If the entire instruction line is after the comment, return instruction type as ST_Comment.
		if ( a_buff.at(0) == ';' )
			return ST_Comment;

		// Remove the comment. Not necessary for parsing the instruction.
		a_buff.erase(a_buff.find(";"), a_buff.length());
	}

	// Using istringstream to parse a_buff.
	m_instruction = a_buff;
	istringstream line(m_instruction);
	string ibuff;
	
	// Stack to push the parsed line onto. Stack is being used because its quick to determine the size and get the last value pushed onto it.
	stack<string> instruction;

	// While some string is in the instruction buffer, push the instruction onto the stack.
	while (line)
	{

		if ( !ibuff.empty() )
		{
			instruction.push(ibuff);
		}
		line >> ibuff;
	}

	// If the stack size is 1, get OP Code.
	if ( instruction.size() == 1 )
	{
		m_OpCode = instruction.top();
		instruction.pop();
		
		// If END, indicates there are no more additional statements to translate.
		if (m_OpCode == "end")
			return ST_End;
	}


	// Else if stack size is 2, get OP Code and Operand.
	else if ( instruction.size() == 2 )
	{

		m_Operand = instruction.top();
		
		// Check if the operand is an integer. If so, then assign it to m_OperandValue. Else, set the m_IsNumericOperand flag to false. This is important for OpCodes like "ds".
		try 
		{
			m_OperandValue = stoi(instruction.top());
		}
		catch (invalid_argument&) 
		{
			m_IsNumericOperand = false;
		}

		instruction.pop();

		m_OpCode = instruction.top();
		instruction.pop();
	}

	// Else if the stack size is 3, get Label, OP Code, and Operand.
	else if ( instruction.size() == 3 )
	{ 
		m_Operand = instruction.top();
		try 
		{
			m_OperandValue = stoi(instruction.top());
		}
		catch (invalid_argument&) 
		{
			m_IsNumericOperand = false;
		}
		
		instruction.pop();
		
		m_OpCode = instruction.top();
		instruction.pop();
		
		m_Label = instruction.top();
		instruction.pop();
	}
	
	// If the stack size is greater than there, there's a problem with the instruction.
	
	else if (instruction.size() > 3)
	{
		Errors::RecordError(string("Instruction contains more than a label, op code, and operand"));
		return ST_Error;
	}

	// Comply with case sensitivity - make OP Code and Label lowercase
	transform(m_OpCode.begin(), m_OpCode.end(), m_OpCode.begin(), ::tolower);
	transform(m_Label.begin(), m_Label.end(), m_Label.begin(), ::tolower);

	// Check to see what the parsed OpCode is and return the instruction type. Check the value and see if it is a machine code, and assembly code, or neither.
	if ( find( machine_OpCodes.begin(), machine_OpCodes.end(), m_OpCode ) != machine_OpCodes.end() )
	{
		m_NumOpCode = distance(machine_OpCodes.begin(), find(machine_OpCodes.begin(), machine_OpCodes.end(), m_OpCode)) + 1;
		return ST_MachineLanguage;
	}
	else if ( find(assem_OpCodes.begin(), assem_OpCodes.end(), m_OpCode) != assem_OpCodes.end() )
	{
		return ST_AssemblerInstr;
	}
	else 
	{
		Errors::RecordError(string("OpCode is illegal."));
		return ST_Error;
	}

};

/**/
/*
Instruction::LocationNextInstruction(int a_loc)

NAME

Instruction::LocationNextInstruction(int a_loc)

SYNOPSIS

int Instruction::LocationNextInstruction(int a_loc)
a_loc            --> location of the instruction.

DESCRIPTION

This function returns the location of the next instruction so it can be loaded in the symbol table for later use. 
If OpCode is "org" or "dis", increment the location and add the operand value. 
Else, just increment the location.

RETURNS

Returns location of next instruction.

AUTHOR

Philip Glazman

DATE

12/18/2017

*/
/**/
int
Instruction::LocationNextInstruction(int a_loc) 
{
	return (m_OpCode == "org" || m_OpCode == "ds") ? a_loc + m_OperandValue : ++a_loc;
};