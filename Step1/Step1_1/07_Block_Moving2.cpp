#include<iostream>
#include<time.h>
#include<windows.h>
#include<conio.h>
#include"COLOR.h"

using namespace std;

void Keyboard(bool* playing, int puzzle[5][5], int* x, int* y);
void Draw(HANDLE hOP, int x, int y, char* str, WORD color);

//���� �Լ���
void InitPuzzle(int puzzle[5][5]);											// ���� �ʱ�ȭ �Լ�
void Print(HANDLE hOP, int puzzle[5][5], int x, int y);						// ȭ�鿡 ������ �׷��ִ� �Լ�
void DrawBlock(HANDLE hOP, int x, int y, char* str, WORD color);			// ������ ��Ϻ��� �׷��ִ� �Լ�
void Swap(int* prevBlock, int* currBlock);									// �� ����� ��ü���ִ� �Լ�
bool Check(int puzzle[5][5]);


int main() 
{
	system("mode con:lines=25 cols=48"); // �ܼ�â�� ���� ���� ũ�� ���� (���� : Lines, ���� : Cols)
	srand(time(NULL));
	rand();

	HANDLE hOP; // �ڵ鰪 ��������
	hOP = GetStdHandle(STD_OUTPUT_HANDLE);

	// Ŀ�� �����
	CONSOLE_CURSOR_INFO curInfo;
	curInfo.bVisible = false;
	curInfo.dwSize = 1;
	SetConsoleCursorInfo(hOP, &curInfo);

	bool isPlaying = true;
	int nPuzzle[5][5];
	int nX = 4, nY = 4; // ó�� �� ĭ�� �ε��� ��ȣ

	InitPuzzle(nPuzzle);
	Print(hOP, nPuzzle, nX, nY);

	while (isPlaying)
	{
		if (_kbhit())
		{
			system("cls");

			Keyboard(&isPlaying, nPuzzle, &nX, &nY);
			Print(hOP, nPuzzle, nX, nY);
			isPlaying = !Check(nPuzzle);

			if (isPlaying == false)
			{
				cout << "Congratulation!! Game Clear!" << endl;
				system("pause");
			}
			while (_kbhit())_getch();
		}
	}

	return 0;
	system("pause");
}
// 2*3 + 6*2 - 8/4
// (2*3) + (6*2) - (8/4)

void Keyboard(bool* playing, int puzzle[5][5], int* x, int* y)
{
	if (GetAsyncKeyState(VK_RIGHT) & 0x800 && *x < 4)				// ������ ����Ű
	{
		Swap(&puzzle[*y][*x], &puzzle[*y][*x + 1]); // ����� swap�ϰ� �����ͷ� �Ѱ��� �� &�� �����ְ� �ּڰ����� ��ȯ
		(*x)++;
	}
	else if (GetAsyncKeyState(VK_LEFT) & 0x800 && *x > 0)
	{
		Swap(&puzzle[*y][*x], &puzzle[*y][*x - 1]);					// ���� ����Ű
		(*x)--;
	}
	else if (GetAsyncKeyState(VK_UP) & 0x800 && *y > 0)				// ���� ����Ű
	{
		Swap(&puzzle[*y][*x], &puzzle[*y-1][*x]);
		(*y)--;
	}
	else if (GetAsyncKeyState(VK_DOWN) & 0x800 && *y < 4)			// �Ʒ��� ����Ű
	{
		Swap(&puzzle[*y][*x], &puzzle[*y+1][*x]);
		(*y)++;
	}
	else if (GetAsyncKeyState(VK_ESCAPE) & 0x8000)					// ESC
		*playing = false;
}

void Draw(HANDLE hOP, int x, int y, char* str, WORD color)
{
	DWORD dwCharsWritten;
	COORD cdFill = { x,y };

	FillConsoleOutputAttribute(hOP, color, strlen(str), cdFill, &dwCharsWritten);
	WriteConsoleOutputCharacter(hOP, str, strlen(str), cdFill, &dwCharsWritten);
}

void InitPuzzle(int puzzle[5][5])
{
	for (int i = 0; i < 5; i++) for (int j = 0; j < 5; j++) puzzle[i][j] = i * 5 + j;
	puzzle[0][0] = 24;
	puzzle[4][4] = 0;

	for (int i = 0; i < 999; i++) // ��ĭ���� �����ϱ� ������ ���ҿ��� �����ϰ� ��ü Ƚ���� ¦���� ���� (Ȧ���� ������ �������� ���� �Ұ�)
	{
		int nDestX = rand() % 5;
		int nDestY = rand() % 5;

		int nSrcX = rand() % 5;
		int nSrcY = rand() % 5;

		if ((nDestX == 4 && nDestY == 4) || (nSrcX == 4 && nSrcY == 4) || nDestX == nSrcX && nDestY == nSrcY) // ������ �� �ʿ䰡 ���� ���
		{
			i--;
			continue;
		}

		int nTemp = puzzle[nDestY][nDestX];
		puzzle[nDestY][nDestX] = puzzle[nSrcY][nSrcX];
		puzzle[nSrcY][nSrcX] = nTemp;
	}
}



void Print(HANDLE hOP, int puzzle[5][5], int x, int y)
{
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			char* szTemp = new char;
			
			// itoa : �������� ���� �������� �������ִ� �Լ�
			if (j == x && i == y) // ��ĭ �� itoa(�������, �ӽ÷� ���ڸ� ���� ����, 10����)
				DrawBlock(hOP, 10 + j * 6, 5 + i * 3, (char*)"��", BG_WHITE | FG_BLACK);
			else
				DrawBlock(hOP, 10 + j * 6, 5 + i * 3, itoa(puzzle[i][j],szTemp,10), BG_WHITE | FG_BLACK);
		}
	}
}


void DrawBlock(HANDLE hOP, int x, int y, char* str, WORD color)
{
	Draw(hOP, x + 0, y + 0, str, color);
	Draw(hOP, x + 2, y + 0, (char*)"��", color);
	Draw(hOP, x + 0, y + 1, (char*)"��", color);
	Draw(hOP, x + 2, y + 1, (char*)"��", color);
}

void Swap(int* prevBlock, int* currBlock)
{
	int nTemp = *prevBlock;
	*prevBlock = *currBlock;
	*currBlock = nTemp;
}

bool Check(int puzzle[5][5])
{
	bool isComplete = false;

	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			if (i == 4 && j == 4) isComplete = true;
			if (puzzle[i][j] != j + 1 + i * 5) break;

		}
	}
	return isComplete;

}

/*�������
1. ������Ʈ ���� -> �����Ӽ� -> ��� -> �������� = ��Ƽ����Ʈ ���� ���� ���
2. C / C++ -> �Ϲ� -> SDL���� = �ƴϿ�
*/