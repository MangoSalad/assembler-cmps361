//
//      Implementation of the Emulator class.
//
#include "stdafx.h"
#include "Emulator.h"

/**/
/*
Emulator::insertMemory(int a_location, int a_contents)

NAME

Emulator::insertMemory(int a_location, int a_contents)

SYNOPSIS

bool Emulator::insertMemory(int a_location, int a_contents)
a_location            --> Location to insert into memory.
a_contents			  --> Contents to insert into memory.

DESCRIPTION

This function inserts into m_memory specified contents at a specific location address. 
This function creates a table to reflect memory of a VC3600 computer.

RETURNS

Returns a boolean to confirm if the insertion was completed successfully.

AUTHOR

Philip Glazman

DATE

12/18/2017

*/
/**/
bool
Emulator::insertMemory(int a_location, int a_contents) 
{
	// If location is out of bounds, then return that location cannot be added.
	if (a_location >= MEMSZ)
	{
		return false;
	}
	else
	{
		m_memory[a_location] = a_contents;
		return true;
	}
}

/**/
/*
Emulator::runProgram()

NAME

Emulator::runProgram()

SYNOPSIS

bool Emulator::runProgram()

DESCRIPTION

This function simulates the VC3600 computer by processing each symbolic operation code by reading through the memory table.

RETURNS

Returns a boolean to confirm that the emulator has run successfully.

AUTHOR

Philip Glazman

DATE

12/18/2017

*/
/**/
bool
Emulator::runProgram()
{
	int address; //address is last 4 digits of word
	int input;

	// Program starts at 100.
	for (int loc = 100; loc < MEMSZ; loc++)
	{
		if (m_memory[loc] != 0)
		{
			address = m_memory[loc] % 10000;

			// Get number of OpCode.
			switch (m_memory[loc] / 10000)
			{
				// Add.
				case 1:
					accumulator += m_memory[address];
					break;
				// Subtract.
				case 2:
					accumulator -= m_memory[address];
					break;
				// Multiply.
				case 3:
					accumulator *= m_memory[address];
					break;
				// Divide.
				case 4:
					accumulator /= m_memory[address];
					break;
				// Load.
				case 5:
					accumulator = m_memory[address];
					break;
				// Store.
				case 6:
					m_memory[address] = accumulator;
					break;
				// Read.
				case 7:
					cout << "?";
					cin >> input;
					m_memory[address] = input;
					break;
				// Write.
				case 8:
					cout << m_memory[address] << endl;
					break;
				// Branch.
				case 9:
					loc = address;
					break;
				// Branch Minus.
				case 10:
					if (accumulator < 0)
						loc = address;
					break;
				// Branch Zero.
				case 11:
					if (accumulator == 0)
						loc = address;
					break;
				// Branch Positive.
				case 12:
					if (accumulator > 0)
						loc = address;
					break;
				// Halt.
				case 13:
					return true;
				// Error.
				default:
					cout << "..." << endl;
			}
		}
	}
	return true;
}