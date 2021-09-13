#include "Base.h"
#include "Color.h"

void Keyboard(bool* playing, int* x, int* y, int blockX[100], int blockY[100]);
void Draw(HANDLE hOP, int x, int y, char* str, WORD color);

// ���� �Լ�
void InitBlock(int blockX[100], int blockY[100]);
void InitMonster(int monsterX[3], int monsterY[3], int blockX[100], int blockY[100]);
void PrintMap(HANDLE hOP, int blockX[100], int blockY[100], int monsterX[3], int monsterY[3], int*x, int *y, int *life);



int main()
{
	// �ڵ鰪 ��������
	HANDLE hOP;
	hOP = GetStdHandle(STD_OUTPUT_HANDLE);

	// Ŀ�� �����
	CONSOLE_CURSOR_INFO curInfo;
	curInfo.bVisible = false;
	curInfo.dwSize = 1;
	SetConsoleCursorInfo(hOP, &curInfo);

	// �ܼ�â�� ũ�� ����
	system("mode con:lines=25 cols=50");

	int Life = 5;
	int blockX[100];
	int blockY[100];
	int monsterX[3];
	int monsterY[3];
	InitBlock(blockX, blockY);
	InitMonster(monsterX, monsterY, blockX, blockY);

	bool isPlaying = true;
	int x = 0, y = 24;
	Draw(hOP, x * 2, y, (char*)"��", BG_YELLOW);


	while (isPlaying)
	{
		if (_kbhit())		// Ű ���� Ȯ�� : Ű �Է��� �ִ� ��� ���ۿ� ���� ���ܼ� true�� ��ȯ�ȴ�.
		{
			Keyboard(&isPlaying, &x, &y, blockX, blockY); // Ű���� �Լ� ȣ��
			system("cls");

			Draw(hOP, x * 2, y, (char*)"��", BACKGROUND_RED);
			PrintMap(hOP, blockX, blockY, monsterX, monsterY, &x,  &y, &Life);
			
			while (_kbhit()) _getch();	// Ű�� �� ���� ������ ���ۿ� ���� ��� ���� �ְ� �Ǽ� �� ������ getch() �Լ��� �̿��ؼ� ����.
										// getch() �Լ��� �Էµ� Ű���� ���� ������ �ٷ� ������ ���� ���� ex) keyValue = getch();
		}
	}

	return 0;
	system("pause");
}


void Keyboard(bool* playing, int* x, int* y, int blockX[100], int blockY[100])
{
	bool cantgo = 0;
	if (GetAsyncKeyState(VK_RIGHT)&0x8000) // ������ ����Ű
	{
		for (int i = 0; i < 100; i++) 
		{
			if (blockX[i] == (*x) + 1 && blockY[i] == (*y))cantgo = 1;
		}
		if ((*x) < 24 && cantgo==0)(*x)++;
		cantgo = 0;
	}
	else if (GetAsyncKeyState(VK_LEFT)&0x8000) // ���� ����Ű
	{
		for (int i = 0; i < 100; i++)
		{
			if (blockX[i] == (*x) -1 && blockY[i] == (*y))cantgo = 1;
		}
		if ((*x) > 0 && cantgo == 0)(*x)--;
		cantgo = 0;
	}
	else if (GetAsyncKeyState(VK_UP) & 0x8000) // ���� ����Ű
	{
		for (int i = 0; i < 100; i++)
		{
			if (blockX[i] == (*x) && blockY[i] == (*y)-1)cantgo = 1;
		}
		if ((*y) > 0 && cantgo == 0)(*y)--;
		cantgo = 0;
	}
	else if (GetAsyncKeyState(VK_DOWN) & 0x8000) // �Ʒ��� ����Ű
	{
		for (int i = 0; i < 100; i++)
		{
			if (blockX[i] == (*x) && blockY[i] == (*y)+1)cantgo = 1;
		}
		if ((*y) < 24 && cantgo == 0)(*y)++;
		cantgo = 0;
	}
	else if (GetAsyncKeyState(VK_ESCAPE) & 0x8000) // ESC
		*playing = false;
}

void Draw(HANDLE hOP, int x, int y, char* str, WORD color)
{
	DWORD dwCharsWritten;
	COORD cdFill = { x, y };

	FillConsoleOutputAttribute(hOP, color, strlen(str), cdFill, &dwCharsWritten);
	WriteConsoleOutputCharacter(hOP, str, strlen(str), cdFill, &dwCharsWritten);
}

void InitBlock(int blockX[100], int blockY[100])
{
	for (int i = 0; i < 100; i++)
	{
		int nX = rand() % 25;
		int nY = 1 + rand() % 24;
		blockX[i] = nX;
		blockY[i] = nY;
	}
}

void InitMonster(int monsterX[3], int monsterY[3], int blockX[100], int blockY[100])
{
	bool block = 0;
	int count = 0;
	while(1)
	{
		int nX = rand() % 25;
		int nY = 1 + rand() % 24;
		for (int j = 0; j < 100; j++)
		{
			if (nX == blockX[j] && nY == blockY[j])
			{
				block = 1;
				break;
			}
		}
		if (block == 0) 
		{
			monsterX[count] = nX;
			monsterY[count] = nY;
			count++;
		}
		block = 0;
		if (count == 3)break;
	}

}


void PrintMap(HANDLE hOP, int blockX[100], int blockY[100], int monsterX[3], int monsterY[3], int* x, int* y, int *life)
{
	for (int i = 0; i < 100; i++)Draw(hOP, blockX[i] * 2, blockY[i], (char*)"��", BG_YELLOW);
	for (int i = 0; i < *life; i++)cout << "��";

	for (int i = 0; i < 3; i++)
	{
		if (*x == monsterX[i] && *y == monsterY[i])
		{
			monsterX[i] = 50;
			monsterY[i] = 50;
			(*life)--;
		}
		else if(monsterX[i]!=50 && monsterY[i]!=50)
			Draw(hOP, monsterX[i] * 2, monsterY[i], (char*)"��", BACKGROUND_RED);
	}
}