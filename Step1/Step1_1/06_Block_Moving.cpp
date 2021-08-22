#include<iostream>
#include<time.h>
#include<stdio.h>
#include <Windows.h>
#include <conio.h> //키 입력처리를 하는 헤더파일

using namespace std;

void Keyboard(bool* playing, int* x, int* y);
void Draw(HANDLE hOP, int x, int y, char* str, WORD color);

int main()
{
	HANDLE hOP; // 핸들값 가져오기
	hOP = GetStdHandle(STD_OUTPUT_HANDLE);

	// 커서 숨기기
	CONSOLE_CURSOR_INFO curInfo;
	curInfo.bVisible = false;
	curInfo.dwSize = 1;
	SetConsoleCursorInfo(hOP, &curInfo);

	bool isPlaying = true;
	int x = 10, y = 10;

	cout << "x좌표 : " << x << endl; 
	cout << "y좌표 : " << y << endl;
	Draw(hOP, x * 2, y, (char*)"A", BACKGROUND_RED);

	while (isPlaying)
	{
		if (_kbhit())		// 키 버퍼 확인 : 키 입력이 있는 경우 버퍼에 값이 생겨서 true가 반환된다.
		{
			Keyboard(&isPlaying, &x, &y); // 키보드 함수 호출
			system("cls");
			cout << "x좌표 : " << x << endl;
			cout << "y좌표 : " << y << endl;
			Draw(hOP, x * 2, y, (char*)"A", BACKGROUND_RED);
			while (_kbhit()) _getch();	// 키를 한 번만 눌러도 버퍼에 값이 계속 남아 있게 되서 그 값들을 getch() 함수를 이용해서 비운다.
										// getch() 함수는 입력된 키보드 값을 변수로 바로 저장할 때도 사용됨 ex) keyValue = getch();
		}
	}

	return 0;
	system("pause");
}


void Keyboard(bool* playing, int* x, int* y)
{
	if (GetAsyncKeyState(VK_RIGHT) & 0x8000) // 오른쪽 방향키
		(*x)++;
	else if (GetAsyncKeyState(VK_LEFT) & 0x8000) // 왼쪽 방향키
		(*x)--;
	else if (GetAsyncKeyState(VK_UP) & 0x8000) // 왼쪽 방향키
		(*y)--;
	else if (GetAsyncKeyState(VK_DOWN) & 0x8000) // 왼쪽 방향키
		(*y)++;
	else if (GetAsyncKeyState(VK_ESCAPE) & 0x8000) // ESC
		*playing = false;
}

void Draw(HANDLE hOP, int x, int y, char* str, WORD color)
{
	DWORD dwCharsWritten;
	COORD cdFill = { x, y };

	FillConsoleOutputAttribute(hOP, color, strlen(str), cdFill, &dwCharsWritten);
	WriteConsoleOutputCharacter(hOP, str, strlen(str), cdFill, &dwCharsWritten);
	// 프로젝트 속성 -> 구성 속성 -> 고급 -> 문자집합 -> 멀티바이트 문자집합 사용
}
