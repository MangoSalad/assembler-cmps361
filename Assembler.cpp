//
//      Implementation of the Assembler class.
//
#include "stdafx.h"
#include "Assembler.h"
#include "Errors.h"

// Constructor for the assembler.  Note: we are passing argc and argv to the file access constructor.
Assembler::Assembler( int argc, char *argv[] ): m_facc( argc, argv ) {}

// Destructor for the assembler.
Assembler::~Assembler( ) {}

/**/
/*
Assembler::PassI()

NAME

Assembler::PassI()

SYNOPSIS

void Assembler::PassI()

DESCRIPTION

This function performs the first pass in the assembler.
It will read each instruction and get its instruction type. 
If the instruction type is assembly or machine, load the location and symbol into the symbol table.

RETURNS

Returns nothing.

AUTHOR

Philip Glazman

DATE

12/18/2017

*/
/**/
void
Assembler::PassI() 
{
    int loc = 0;        // Tracks the location of the instructions to be generated.

    // Successively process each line of source code.
    for( ; ; ) {

        // Read the next line from the source file.
        string buff; 
        if( ! m_facc.GetNextLine( buff ) ) {

            // If there are no more lines, we are missing an end statement.
            // We will let this error be reported by Pass II.
            return;
        }

        // Parse the line and get the instruction type.
        Instruction::InstructionType st =  m_inst.ParseInstruction( buff );

        // If this is an end statement, there is nothing left to do in pass I.
        // Pass II will determine if the end is the last statement.
		if (st == Instruction::ST_End) {
			return;
		}

        // Labels can only be on machine language and assembler language
        // instructions.  So, skip other instruction types.
        if( st != Instruction::ST_MachineLanguage && st != Instruction::ST_AssemblerInstr ) 
        {
        	continue;
		}
        // If the instruction has a label, record it and its location in the
        // symbol table.
		 if( m_inst.isLabel( ) ) {
		     m_symtab.AddSymbol( m_inst.getLabel( ), loc );
        }
        // Compute the location of the next instruction.
        loc = m_inst.LocationNextInstruction( loc );
    }
}

/**/
/*
Assembler::PassII()

NAME

Assembler::PassII()

SYNOPSIS

void Assembler::PassII()

DESCRIPTION

This function performs the second pass in the assembler.
It will read each instruction, do error reporting after the offending instruction line, and prepare for the emulator. 
Translation of the program occurs here.
Errors are identified here such as illegal operation code, missing end statement, undefined label, syntax errors, and more.

RETURNS

Returns nothing.

AUTHOR

Philip Glazman

DATE

12/18/2017

*/
/**/
void
Assembler::PassII()
{
	// Start collecting errors into the Error Queue.
	Errors::InitErrorReporting();

	// Return to the beginning of the file.
	m_facc.rewind();

	cout << setw(15) <<  "Location " << setw(15) << "Contents " << setw(25) << "Original Statement" << endl;
	
	int loc = 0;		// Tracks the location of the instructions to be generated.

	// Successively process each line of source code.
	for (; ; ) {

		// Read the next line from the source file.
		string buff;
		
		// If file buffer ends without END Statement, record error.
		if (!m_facc.GetNextLine(buff)) {

			Errors::RecordError(string("No END statement included."));
			Errors::DisplayErrors();
			
			break;
		}

		// Parse instruction.
		Instruction::InstructionType st = m_inst.ParseInstruction(buff);

		// If the instruction is a ST_Comment or ST_End, then only print out the Original Statement.
		if ( st == Instruction::ST_Comment || st == Instruction::ST_End )
		{
			cout << setw(55) << right << buff << endl;

			if (st == Instruction::ST_End)
				break;

			Errors::DisplayErrors();
			continue;
		}

		// Length of label and operand must be between 1 and 10. first is a letter, remainder can be letters/numbers.
		if ( m_inst.isLabel() && m_inst.getLabel().length() > 10 && !isalpha(m_inst.getLabel()[0]) )
		{
			Errors::RecordError(string("Labels are from 1 to 10 characters in length and the first character is a letter"));
		}
		if ( m_inst.isOperand() && m_inst.getOperand().length() > 10 && !isalpha(m_inst.getOperand()[0]) )
		{
			Errors::RecordError(string("Operands are from 1 to 10 characters in length and the first character is a letter"));
		}

		// If the instruction is org or ds, print out only the location and original statement.
		if (m_inst.getOpCode() == "org" || m_inst.getOpCode() == "ds")
		{
			cout << setw(15) << right << loc << setw(40) << right << buff << endl;
			loc = m_inst.LocationNextInstruction(loc);

			Errors::DisplayErrors();
			continue;
		}
		
		// If ST_Error, the instruction is illegal.
		if (st == Instruction::ST_Error)
		{
			Errors::RecordError(string("Illegal instructions set."));
		}

		// Build the contents by having the first 2 digits be the OpCode and last 4 digits be the address portion. 
		int content = m_inst.getOpCodeNum() * 10000;

		if ( st == Instruction::ST_MachineLanguage )
		{
			if (m_inst.getOpCode() == "halt")
			{
				content += 0;
			}
			else
			{
				content += m_symtab.LookupLocation(m_inst.getOperand());
			}
		}
		else if ( st == Instruction::ST_AssemblerInstr )
		{
			content += m_inst.getOperandValue();
			if(m_inst.getOperandValue()>9999)
				Errors::RecordError(string("Operand value is out of bounds."));
		}

		string cont = to_string(content);
		while (cont.length() != 6) cont = '0' + cont;

		// Output the location, contents, and original statement as well as any errors.
		cout << setw(15) << right << loc << setw(15) << right << cont << setw(25) << right << buff << endl;
		Errors::DisplayErrors();
		loc = m_inst.LocationNextInstruction(loc);

		if(!m_emul.insertMemory(loc, content))
			Errors::RecordError(string("Insufficient memory."));
	}


}


/**/
/*
Assembler::RunEmulator()

NAME

Assembler::RunEmulator()

SYNOPSIS

void Assembler::RunEmulator()

DESCRIPTION

Runs the emulator.

RETURNS

Returns nothing.

AUTHOR

Philip Glazman

DATE

12/18/2017

*/
/**/
void
Assembler::RunEmulator()
{
	m_emul.runProgram();
}
