//
//      Implementation of the Error class.
//
#include "stdafx.h"
#include "Errors.h"

// Initializes error reports.

queue<string> Errors::m_ErrorMsgs;

/**/
/*
Errors::InitErrorReporting()

NAME

Errors::InitErrorReporting()

SYNOPSIS

void Errors::InitErrorReporting()

DESCRIPTION

This function empties the error queue in order to remove any junk.

RETURNS

Returns nothing

AUTHOR

Philip Glazman

DATE

12/19/2017

*/
/**/
void
Errors::InitErrorReporting()
{
	while (!m_ErrorMsgs.empty()) m_ErrorMsgs.pop();
}

/**/
/*
Errors::RecordError(string &a_emsg)

NAME

Errors::RecordError(string &a_emsg)

SYNOPSIS

void Errors::RecordError(string &a_emsg)
a_emsg            --> Error message to push to the queue.

DESCRIPTION

This function pushes a string error message to the queue.

RETURNS

Returns nothing.

AUTHOR

Philip Glazman

DATE

12/18/2017

*/
/**/
void
Errors::RecordError(string &a_emsg)
{
	m_ErrorMsgs.push(a_emsg);
}

/**/
/*
Errors::DisplayErrors()

NAME

Errors::DisplayErrors()

SYNOPSIS

void Errors::DisplayErrors()

DESCRIPTION

This function outputs any error messages in the queue.
It changes the attributes of the console in order to print the error message in red text color.

RETURNS

Returns nothing.

AUTHOR

Philip Glazman

DATE

12/18/2017

*/
/**/
void
Errors::DisplayErrors()
{
	// Get details about the console window.
	HANDLE Console = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO Info;
	GetConsoleScreenBufferInfo(Console, &Info);
	WORD Attributes = Info.wAttributes;

	// Set the text color to red.
	SetConsoleTextAttribute(Console, FOREGROUND_RED | FOREGROUND_INTENSITY);
	
	// While there are any error messages, print them to the screen.
	while (!m_ErrorMsgs.empty())
	{
		cout << setw(15) << right << m_ErrorMsgs.front() << endl;
		m_ErrorMsgs.pop();
	}

	// Return the console window to normal settings.
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Attributes);
}