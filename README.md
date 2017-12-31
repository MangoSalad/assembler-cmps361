# Assembler and Emulator for VC-3600 Computer
This is an assembler and emulator that is designed to run a vc3600 computer. This was a school project for cmps361 at Ramapo College of NJ.

## VC-3600 Assembly Language
### Symbolic Op Codes
  - 01 ADD
  - 02 SUB
  - 03 MULT
  - 04 DIV
  - 05 LOAD
  - 06 STORE
  - 07 READ
  - 08 WRITE
  - 09 B        
  - 10 BM
  - 11 BZ
  - 12 BP
  - 13 HALT
### Assembly Language Instructions
 - DC - define constant. The constant is a decimal integer placed in the operand field.
 - DS - define storage. The operand specifies the number of words of storage to be set aside.
 - ORG -define origin. The operand specifies the address at which the translation of the next instruction will be generated,
 - END – indicates that there are no additional statements to translate.
 
## Class Definitions
 - stdafx.h - precompiled headers include file.
 - stdafx.cpp - supports precompiled headers.

 - Assem.cpp - the main program that launches the assembler.

 - Assembler.h - definition of the assembler class.
 - Assembler.cpp - implementation of the assembler class.

 - FileAccess.h - definition of the class to perform file access.
 - FileAccess.cpp - implementation of the class to perform file access.

 - Instruction.h - the definition of the class to manipulate instructions. Includes error handling.

 - SymTab.h - the definition of the class the manage the symbol table. 
 - SymTab.cpp - implementation of the class to manage the symbol table.

 - Errors.h - the definition of the class to perform error reporting.
 - Errors.cpp - the implementation of the class to perform error reporting.

 - Emulator.h - the definition for the emulator class.
