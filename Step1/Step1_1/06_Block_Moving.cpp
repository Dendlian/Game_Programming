#include<iostream>
#include<time.h>
#include<stdio.h>
#include <Windows.h>
#include <conio.h> //Ű �Է�ó���� �ϴ� �������

using namespace std;

void Keyboard(bool* playing, int* x, int* y);
void Draw(HANDLE hOP, int x, int y, char* str, WORD color);

int main()
{
	HANDLE hOP; // �ڵ鰪 ��������
	hOP = GetStdHandle(STD_OUTPUT_HANDLE);

	// Ŀ�� �����
	CONSOLE_CURSOR_INFO curInfo;
	curInfo.bVisible = false;
	curInfo.dwSize = 1;
	SetConsoleCursorInfo(hOP, &curInfo);

	bool isPlaying = true;
	int x = 10, y = 10;

	cout << "x��ǥ : " << x << endl; 
	cout << "y��ǥ : " << y << endl;
	Draw(hOP, x * 2, y, (char*)"A", BACKGROUND_RED);

	while (isPlaying)
	{
		if (_kbhit())		// Ű ���� Ȯ�� : Ű �Է��� �ִ� ��� ���ۿ� ���� ���ܼ� true�� ��ȯ�ȴ�.
		{
			Keyboard(&isPlaying, &x, &y); // Ű���� �Լ� ȣ��
			system("cls");
			cout << "x��ǥ : " << x << endl;
			cout << "y��ǥ : " << y << endl;
			Draw(hOP, x * 2, y, (char*)"A", BACKGROUND_RED);
			while (_kbhit()) _getch();	// Ű�� �� ���� ������ ���ۿ� ���� ��� ���� �ְ� �Ǽ� �� ������ getch() �Լ��� �̿��ؼ� ����.
										// getch() �Լ��� �Էµ� Ű���� ���� ������ �ٷ� ������ ���� ���� ex) keyValue = getch();
		}
	}

	return 0;
	system("pause");
}


void Keyboard(bool* playing, int* x, int* y)
{
	if (GetAsyncKeyState(VK_RIGHT) & 0x8000) // ������ ����Ű
		(*x)++;
	else if (GetAsyncKeyState(VK_LEFT) & 0x8000) // ���� ����Ű
		(*x)--;
	else if (GetAsyncKeyState(VK_UP) & 0x8000) // ���� ����Ű
		(*y)--;
	else if (GetAsyncKeyState(VK_DOWN) & 0x8000) // ���� ����Ű
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
	// ������Ʈ �Ӽ� -> ���� �Ӽ� -> ��� -> �������� -> ��Ƽ����Ʈ �������� ���
}
