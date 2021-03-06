#include "SupaSyC/Common.h"

static ConsoleColor sConsoleColor;

ConsoleColor GetConsoleColor()
{ return sConsoleColor; }

void ResetConsoleColor()
{ SetConsoleColor(ConsoleColor_Reset); }

#if _WIN32
#define OpenFile WinApiOpenFile // Since windows has there own function named 'OpenFile' just change the name
#include <windows.h>
#undef OpenFile

static HANDLE sStdOutHandle = null;

void SetConsoleColor(ConsoleColor c)
{
	if (c == sConsoleColor)
		return;
	sConsoleColor = c;

	if (!sStdOutHandle)
		sStdOutHandle = GetStdHandle(STD_OUTPUT_HANDLE);

	SetConsoleTextAttribute(sStdOutHandle, sConsoleColor);
}
#else
void SetConsoleColor(ConsoleColor c)
{
	sConsoleColor = c;
}
#endif