#include "console.h"


void GotoXY(int x, int y)
{
	HANDLE hout;
	COORD Cur;
	hout = GetStdHandle(STD_OUTPUT_HANDLE);
	Cur.X = x;
	Cur.Y = y;
	SetConsoleCursorPosition(hout, Cur);
}

void SetColor(int color, int bgcolor)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (bgcolor << 4) | color);
}

void FullScreen()
{
	SetConsoleDisplayMode(GetStdHandle(STD_OUTPUT_HANDLE), CONSOLE_FULLSCREEN_MODE, NULL);
}

void NoScrollBarFullScreen()
{
	SetConsoleDisplayMode(GetStdHandle(STD_OUTPUT_HANDLE), CONSOLE_FULLSCREEN, 0);
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO cs_buf;
	GetConsoleScreenBufferInfo(handle, &cs_buf);
	COORD pos;
	pos.X = cs_buf.srWindow.Right - cs_buf.srWindow.Left + 1;
	pos.Y = cs_buf.srWindow.Bottom - cs_buf.srWindow.Top + 1;
	SetConsoleScreenBufferSize(handle, pos);
}

bool operator==(const POINT& leftValue, const POINT& rightValue)
{
	if (leftValue.x == rightValue.x && leftValue.y == rightValue.y)
	{
		return true;
	}
	return false;
}



POINT operator+(const POINT &leftValue, const POINT& rightValue)
{
	return POINT{ leftValue.x + rightValue.x , leftValue.y + rightValue.y };
}

POINT operator-(const POINT& leftValue, const POINT& rightValue)
{
	return POINT{ leftValue.x - rightValue.x , leftValue.y - rightValue.y };
}

POINT operator+=(POINT& leftValue, const POINT& rightValue)
{
	leftValue.x = leftValue.x + rightValue.x;
	leftValue.y = leftValue.y + rightValue.y;
	return leftValue;
}


RECT GetWindowRect()
{
	RECT windowRect;
	HWND hWnd = GetConsoleWindow();

	GetClientRect(hWnd, &windowRect);

	return windowRect;
}

void HideCursor()
{
	CONSOLE_CURSOR_INFO cursorInfo;
	cursorInfo.dwSize = 1;
	cursorInfo.bVisible = FALSE;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);

	DWORD prev_mode;
	GetConsoleMode(GetStdHandle(STD_INPUT_HANDLE), &prev_mode);
	SetConsoleMode(GetStdHandle(STD_INPUT_HANDLE), ENABLE_EXTENDED_FLAGS |
		(prev_mode & ~ENABLE_QUICK_EDIT_MODE));
}


void AwesomeTitle(std::wstring* titles, int titleLength) {
	using namespace std;

	RECT windowRect = GetWindowRect();

	int maxLength = 0;

	for (int i = 0; i < titleLength; i++) {
		int currentLength = titles[i].length();
		if (currentLength > maxLength) {
			maxLength = currentLength;
		}
	}


	POINT curPos;
	curPos.x = 0;//windowRect.bottom/10 - maxLength/2;// 65;//windowRect.bottom/2;
	curPos.y = 5;// windowRect.right / 10 - maxLength / 2;// 5;//windowRect.right/2;



	//cout<<curPos.x<<"/"<<curPos.y<<endl;

	GotoXY(curPos.x, curPos.y);

	int	oldMode = _setmode(_fileno(stdout), _O_U8TEXT);

	int count = maxLength - 1;
	while (count >= 0) {
		for (int j = 0; j < titleLength; j++) {
			for (int i = count; i < maxLength; i++) {
				if (titles[j].length() <= i) {
					break;
				}
				wcout << titles[j][i];
			}
			wcout << endl;
			GotoXY(curPos.x, WhereCursor().Y);
		}
		Sleep(10);
		GotoXY(curPos.x, curPos.y);
		count--;
	}
	//UINTcurrentCP=GetConsoleOutputCP();
	//SetConsoleOutputCP(CP_UTF8);

	for (int i = 0; i < titleLength; i++) {
		wcout << titles[i] << endl;
		GotoXY(curPos.x, WhereCursor().Y);
	}

	Sleep(500);
	GotoXY(curPos.x, curPos.y);

	for (int i = 0; i < Color::Length; i++) {
		for (int j = 0; j < titleLength; j++) {
			wcout << titles[j] << endl;
			GotoXY(curPos.x, WhereCursor().Y);
		}
		GotoXY(curPos.x, curPos.y);
		Sleep(150);
		SetColor(i, Color::Black);
	}
	system("cls");
	GotoXY(curPos.x, curPos.y);
	Sleep(1000);

	for (int i = 0; i < titleLength; i++) {
		wcout << titles[i] << endl;
		GotoXY(curPos.x, WhereCursor().Y);
	}

	_setmode(_fileno(stdout), oldMode);
	//SetConsoleOutputCP(currentCP);
	SetColor(Color::White, Color::Black);

}

int Random(int x, int y)
{
	return rand() % x + y;
}





//getcursorposition
COORD WhereCursor(void)
{
	CONSOLE_SCREEN_BUFFER_INFO info;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &info);
	return info.dwCursorPosition;
}
