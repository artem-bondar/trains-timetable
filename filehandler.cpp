#include "filehandler.h"
#include "interface.h"
#include "finder.h"

void FileHandler::tryToOpenFile(const string* filename) {
	file.open(filename[0] + filename[1]);
	if (file.is_open())
	{
		print(text.openSuccess + filename[1] + text.whiteSpaces[5] + text.whiteSpaces[3] + text.whiteSpaces[3], WHITE, GREEN);
	}
	else
	{
		file.open(filename[0] + filename[1] + text.txt);
		if (file.is_open())
		{
			print(text.openSuccess + filename[1] + text.txt + text.whiteSpaces[5] + text.whiteSpaces[3] + text.whiteSpaces[3], WHITE, GREEN);
		}
		else
			throw true;
	}
}

void FileHandler::doOutput(const string &target, char* argv[]) const  {
	if (!target.size())
	{
		GetConsoleScreenBufferInfo(hStdOut, &csbi);
		SetConsoleCursorPosition(hStdOut, { 0, csbi.dwCursorPosition.Y - 1 });
	}
	if (target.size())
	{
		string output = argv[0];
		output = output.substr(0, output.find_last_of(text.backslash) + 1);
		ofstream fout(output + target);
		fout << finder.result;
		fout.close();
		print(text.saved, WHITE, GREEN);
		cout << text.whiteSpaces[5];
	}
	else
	{
		DWORD binBuffer;
		COORD start;
		GetConsoleScreenBufferInfo(hStdOut, &csbi);
		start = csbi.dwCursorPosition;
		COORD newConsoleSize = { csbi.dwSize.X, (short)finder.result.getSize() + start.Y * 2};
		SetConsoleScreenBufferSize(hStdOut, newConsoleSize);
		cout << finder.result;
		GetConsoleScreenBufferInfo(hStdOut, &csbi);
		for (short i = 0; i < csbi.dwCursorPosition.Y - start.Y + 1; i++)
			FillConsoleOutputAttribute(hStdOut, (WORD)((WHITE << 4) | BLUE), csbi.dwSize.X - 1, { start.X, start.Y + i}, &binBuffer);
		cout << text.whiteSpaces[3] << text.whiteSpaces[5];
	}
}