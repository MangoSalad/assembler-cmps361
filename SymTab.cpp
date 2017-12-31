//
//		Implementation of the symbol table class.
//
#include "stdafx.h"
#include "SymTab.h"
#include "Errors.h"

/**/
/*
SymbolTable::AddSymbol(string &a_symbol, int a_loc)

NAME

SymbolTable::AddSymbol(string &a_symbol, int a_loc)

SYNOPSIS

void SymbolTable::AddSymbol(string &a_symbol, int a_loc)
a_symbol		 --> Symbol to be added.
a_loc            --> Location of the symbol to be added.

DESCRIPTION

This function loads the symbol table by calling it with a symbol and location.

RETURNS

Returns nothing.

AUTHOR

Philip Glazman

DATE

12/16/2017

*/
/**/
void
SymbolTable::AddSymbol( string &a_symbol, int a_loc )
{
	// If the symbol is already in the symbol table, record it as multiply defined.
	map<string, int>::iterator st;

	st = m_symbolTable.find(a_symbol);
	
	if ( st != m_symbolTable.end() ) 
	{
		st->second = multiplyDefinedSymbol;
		return;
	}

	// Record the location in the symbol table.
	m_symbolTable[a_symbol] = a_loc;
}

/**/
/*
SymbolTable::DisplaySymbolTable()

NAME

SymbolTable::DisplaySymbolTable()

SYNOPSIS

void SymbolTable::DisplaySymbolTable()

DESCRIPTION

This function displays the Symbol Table.
It will print Symbol #, Symbol, and Location to standard output.s

RETURNS

Returns nothing.

AUTHOR

Philip Glazman

DATE

12/16/2017

*/
/**/
void
SymbolTable::DisplaySymbolTable() 
{
	int symbolNum = 0;
	cout << setw(15) << "Symbol #" << setw(15) << "Symbol" << setw(15) << "Location" << endl;
	
	// Iterate through the Symbol Table.
	map<string, int>::iterator it;
	for ( it = m_symbolTable.begin(); it != m_symbolTable.end(); it++ )
	{
		cout << setw(15) <<right << symbolNum <<" "<< setw(15) << right << it->first << " " << setw(15) << right << it->second << endl;
		symbolNum++;
	}
}

/**/
/*
SymbolTable::LookupSymbol(string &a_symbol, int &a_loc)

NAME

SymbolTable::LookupSymbol(string &a_symbol, int &a_loc)

SYNOPSIS

bool SymbolTable::LookupSymbol(string &a_symbol, int &a_loc)
a_symbol		 --> Symbol to look for.
a_loc            --> Location of the symbol to find.

DESCRIPTION

This function returns a boolean value to check if the symbol is in the Symbol Table.

RETURNS

Returns boolean.

AUTHOR

Philip Glazman

DATE

12/16/2017

*/
/**/
bool
SymbolTable::LookupSymbol(string &a_symbol, int &a_loc)
{
	map<string, int>::iterator st;
	st = m_symbolTable.find(a_symbol);

	if (st != m_symbolTable.end())
	{
		a_loc = m_symbolTable[a_symbol];
		return true;
	}
	else
	{
		Errors::RecordError(string("Could not find symbol in Symbol Table."));
		return false;
	}
}

/**/
/*
SymbolTable::LookupLocation(string &a_symbol)

NAME

SymbolTable::LookupLocation(string &a_symbol)

SYNOPSIS

int SymbolTable::LookupLocation(string &a_symbol)
a_symbol		 --> Symbol to look for.

DESCRIPTION

This function returns the location of the smybol to look for.

RETURNS

Returns location of symbol in table.

AUTHOR

Philip Glazman

DATE

12/16/2017

*/
/**/
int
SymbolTable::LookupLocation(string &a_symbol)
{
	map<string, int>::iterator st;
	st = m_symbolTable.find(a_symbol);

	if (st != m_symbolTable.end())
	{
		return m_symbolTable[a_symbol];
	}
	else
	{
		Errors::RecordError(string("Could not find symbol in Symbol Table."));
		return 0;
	}
}