/*
* Assembler main program.
*/
#include "stdafx.h"     // This must be present if you use precompiled headers which you will use.
#include <stdio.h>

#include "Assembler.h"

void splitOutput()
{
	cout << "-----------------------------------------------------------------------" << endl;
	cout << "Please Enter to continue...";
	cin.get();
	cout << "-----------------------------------------------------------------------" << endl;
}


int main(int argc, char *argv[])
{
	Assembler assem(argc, argv);

	// Establish the location of the labels:
	assem.PassI();
	
	// Display the symbol table.
	assem.DisplaySymbolTable();

	splitOutput();


	// Output the symbol table and the translation.
	assem.PassII();

	splitOutput();

	// Run the emulator on the VC3600 program that was generated in Pass II.
	assem.RunEmulator();

	cin.ignore();
	splitOutput();
	
	// Terminate indicating all is well.  If there is an unrecoverable error, the 
	// program will terminate at the point that it occurred with an exit(1) call.
	return 0;
}