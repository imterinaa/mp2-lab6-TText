#define HOME	75
#define DOWN	80
#define NEXT	77
#define UP	72
#define ESC	27
#define INS	82
#define DEL	83
#define ENTER	13
#define TAB 9


#include "TText.h"
#include "TLink.h"
#include <Windows.h>
#include <conio.h>

void clrscr(void);
void clreol(void);
void gotoxy(int x, int y);

TMemory TLink::mem;

int LinkCount = 180;

int main() {
	TLink::InitMem(LinkCount);
	//TLink::PrintFree();
	TText text;
	TLink tmp;
	
	char s;
	char buf[80];
	bool flag = false;
	bool f = true;
	cout << "\nR - read from file\n";
	

		cout << "input: ";
	
		s = _getch();
		cout << s << endl;
		switch (s) {
		case 'R': cout << "read from file:\n "; flag = true; text.Read("file.txt"); text.Print(); break;
		
		}
		cout << "   to show functions - TAB" << endl;


	while (true) {

		cout << "input: ";

		s = _getch();
		cout << s << endl;

		switch (s) {
		case TAB: cout << "r - read\np - print\ns - save\nc - clear console \nf - print free\nDEL - clear memory\n" <<
			"^ - go to previous link\n< - go to first link\nv - go to next link\n> - go to down link\n1 - insert next line\n2 - insert next section\n" <<
			"3 - insert down line\n4 - insert down section\n5 - delete next link\n6 - delete down link\n"; break;
		case 'r': text.Read("file.txt");
			if (text.GetpFirst() == NULL) { cout << "Reading error\n"; }
			else { flag = true; cout << "Successful reading\n"; }; break;
		case 'p': text.Print(); break;
		
		case 'c': clrscr(); cout << "TAB - show functions\n"; break;
		case DEL: if (flag) { TLink::MemCleaner(text); flag = false; cout << "Memory was cleared\n"; }
				  else cout << "There is nothing to clear\n"; break;
		case 's': text.Write("file2.txt"); break;
		case 'f': TLink::PrintFree(); break;
		case ESC: if (flag) { TLink::MemCleaner(text); } return 0;
		case UP : text.GoPrevLink(); text.Print(); break;
		case DOWN: text.GoNextLink(); text.Print(); break;
		case NEXT: text.GoDownLink(); text.Print(); break;
		case HOME : text.GoFirstLink(); text.Print(); break;
		case '1': cout << "Enter your line: "; cin >> buf; text.InsNextLine(buf); text.Print();  break;
		case '2': cout << "Enter your line: "; cin >> buf; text.InsNextSection(buf); text.Print();  break;
		case '3': cout << "Enter your line: "; cin >> buf; text.InsDownLine(buf); text.Print();  break;
		case '4': cout << "Enter your line: "; cin >> buf; text.InsDownSection(buf); text.Print(); break;
		case '5': text.DelNext(); text.Print(); break;
		case '6': text.DelDown(); text.Print();  break;
		default: cout << "Input error\n";
		}
	}
}




void clrscr(void)
{
	HANDLE Console = GetStdHandle(STD_OUTPUT_HANDLE);
	if (!Console) return;

	CONSOLE_SCREEN_BUFFER_INFO buf;
	GetConsoleScreenBufferInfo(Console, &buf);

	DWORD Count;

	COORD zpos;
	zpos.X = 0;
	zpos.Y = 0;

	FillConsoleOutputCharacter(Console, ' ', buf.dwSize.X * buf.dwSize.Y, zpos, &Count);
	SetConsoleCursorPosition(Console, zpos);
}

void clreol(void)
{
	HANDLE Console = GetStdHandle(STD_OUTPUT_HANDLE);
	if (!Console)return;

	CONSOLE_SCREEN_BUFFER_INFO buf;
	GetConsoleScreenBufferInfo(Console, &buf);

	WORD Attr;
	DWORD Count;

	COORD zpos = buf.dwCursorPosition;

	zpos.X = buf.dwCursorPosition.X + 1;
	zpos.Y = buf.dwCursorPosition.Y;

	FillConsoleOutputCharacter(Console, ' ', buf.dwSize.X - buf.dwCursorPosition.X - 1, zpos, &Count);
	SetConsoleCursorPosition(Console, buf.dwCursorPosition);
}

void gotoxy(int x, int y)
{
	HANDLE Console = GetStdHandle(STD_OUTPUT_HANDLE);
	if (!Console)return;

	COORD pos;
	pos.X = x;
	pos.Y = y;

	SetConsoleCursorPosition(Console, pos);
}
