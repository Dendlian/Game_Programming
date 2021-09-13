#include "Base.h"
#include "Color.h"

void Keyboard(bool* playing, int* x, int* y, int blockX[100], int blockY[100]);
void Draw(HANDLE hOP, int x, int y, char* str, WORD color);

// 게임 함수
void InitBlock(int blockX[100], int blockY[100]);
void InitMonster(int monsterX[3], int monsterY[3], int blockX[100], int blockY[100]);
void PrintMap(HANDLE hOP, int blockX[100], int blockY[100], int monsterX[3], int monsterY[3], int*x, int *y, int *life);



int main()
{
	// 핸들값 가져오기
	HANDLE hOP;
	hOP = GetStdHandle(STD_OUTPUT_HANDLE);

	// 커서 숨기기
	CONSOLE_CURSOR_INFO curInfo;
	curInfo.bVisible = false;
	curInfo.dwSize = 1;
	SetConsoleCursorInfo(hOP, &curInfo);

	// 콘솔창의 크기 지정
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
	Draw(hOP, x * 2, y, (char*)"☆", BG_YELLOW);


	while (isPlaying)
	{
		if (_kbhit())		// 키 버퍼 확인 : 키 입력이 있는 경우 버퍼에 값이 생겨서 true가 반환된다.
		{
			Keyboard(&isPlaying, &x, &y, blockX, blockY); // 키보드 함수 호출
			system("cls");

			Draw(hOP, x * 2, y, (char*)"●", BACKGROUND_RED);
			PrintMap(hOP, blockX, blockY, monsterX, monsterY, &x,  &y, &Life);
			
			while (_kbhit()) _getch();	// 키를 한 번만 눌러도 버퍼에 값이 계속 남아 있게 되서 그 값들을 getch() 함수를 이용해서 비운다.
										// getch() 함수는 입력된 키보드 값을 변수로 바로 저장할 때도 사용됨 ex) keyValue = getch();
		}
	}

	return 0;
	system("pause");
}


void Keyboard(bool* playing, int* x, int* y, int blockX[100], int blockY[100])
{
	bool cantgo = 0;
	if (GetAsyncKeyState(VK_RIGHT)&0x8000) // 오른쪽 방향키
	{
		for (int i = 0; i < 100; i++) 
		{
			if (blockX[i] == (*x) + 1 && blockY[i] == (*y))cantgo = 1;
		}
		if ((*x) < 24 && cantgo==0)(*x)++;
		cantgo = 0;
	}
	else if (GetAsyncKeyState(VK_LEFT)&0x8000) // 왼쪽 방향키
	{
		for (int i = 0; i < 100; i++)
		{
			if (blockX[i] == (*x) -1 && blockY[i] == (*y))cantgo = 1;
		}
		if ((*x) > 0 && cantgo == 0)(*x)--;
		cantgo = 0;
	}
	else if (GetAsyncKeyState(VK_UP) & 0x8000) // 위쪽 방향키
	{
		for (int i = 0; i < 100; i++)
		{
			if (blockX[i] == (*x) && blockY[i] == (*y)-1)cantgo = 1;
		}
		if ((*y) > 0 && cantgo == 0)(*y)--;
		cantgo = 0;
	}
	else if (GetAsyncKeyState(VK_DOWN) & 0x8000) // 아래쪽 방향키
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
	for (int i = 0; i < 100; i++)Draw(hOP, blockX[i] * 2, blockY[i], (char*)"■", BG_YELLOW);
	for (int i = 0; i < *life; i++)cout << "♥";

	for (int i = 0; i < 3; i++)
	{
		if (*x == monsterX[i] && *y == monsterY[i])
		{
			monsterX[i] = 50;
			monsterY[i] = 50;
			(*life)--;
		}
		else if(monsterX[i]!=50 && monsterY[i]!=50)
			Draw(hOP, monsterX[i] * 2, monsterY[i], (char*)"◈", BACKGROUND_RED);
	}
}