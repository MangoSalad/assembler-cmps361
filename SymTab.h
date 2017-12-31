//
//		Symbol table class.
//
#pragma once


class SymbolTable {

public:
	
	SymbolTable() {};
	~SymbolTable() {};

	const int multiplyDefinedSymbol = -999;

	// Add a new symbol to the symbol table.
	void AddSymbol(string &a_symbol, int a_loc);

	// Display the symbol table.
	void DisplaySymbolTable();

	// Lookup a symbol in the symbol table.
	bool LookupSymbol(string &a_symbol, int &a_loc);

	// Lookup location of symbol in the symbol table.
	int LookupLocation(string &a_symbol);

private:

	// This is the actual symbol table.  The symbol is the key to the map.
	map<string, int> m_symbolTable;

};