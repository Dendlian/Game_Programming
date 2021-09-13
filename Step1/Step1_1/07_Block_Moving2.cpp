#include<iostream>
#include<time.h>
#include<windows.h>
#include<conio.h>
#include"COLOR.h"

using namespace std;

void Keyboard(bool* playing, int puzzle[5][5], int* x, int* y);
void Draw(HANDLE hOP, int x, int y, char* str, WORD color);

//게임 함수들
void InitPuzzle(int puzzle[5][5]);											// 퍼즐 초기화 함수
void Print(HANDLE hOP, int puzzle[5][5], int x, int y);						// 화면에 퍼즐을 그려주는 함수
void DrawBlock(HANDLE hOP, int x, int y, char* str, WORD color);			// 퍼즐을 블록별로 그려주는 함수
void Swap(int* prevBlock, int* currBlock);									// 두 블록을 교체해주는 함수
bool Check(int puzzle[5][5]);


int main() 
{
	system("mode con:lines=25 cols=48"); // 콘솔창의 가로 세로 크기 지정 (세로 : Lines, 가로 : Cols)
	srand(time(NULL));
	rand();

	HANDLE hOP; // 핸들값 가져오기
	hOP = GetStdHandle(STD_OUTPUT_HANDLE);

	// 커서 숨기기
	CONSOLE_CURSOR_INFO curInfo;
	curInfo.bVisible = false;
	curInfo.dwSize = 1;
	SetConsoleCursorInfo(hOP, &curInfo);

	bool isPlaying = true;
	int nPuzzle[5][5];
	int nX = 4, nY = 4; // 처음 빈 칸의 인덱스 번호

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
	if (GetAsyncKeyState(VK_RIGHT) & 0x800 && *x < 4)				// 오른쪽 방향키
	{
		Swap(&puzzle[*y][*x], &puzzle[*y][*x + 1]); // 블록을 swap하고 포인터로 넘겨준 후 &를 붙혀주고 주솟값으로 반환
		(*x)++;
	}
	else if (GetAsyncKeyState(VK_LEFT) & 0x800 && *x > 0)
	{
		Swap(&puzzle[*y][*x], &puzzle[*y][*x - 1]);					// 왼쪽 방향키
		(*x)--;
	}
	else if (GetAsyncKeyState(VK_UP) & 0x800 && *y > 0)				// 위쪽 방향키
	{
		Swap(&puzzle[*y][*x], &puzzle[*y-1][*x]);
		(*y)--;
	}
	else if (GetAsyncKeyState(VK_DOWN) & 0x800 && *y < 4)			// 아래쪽 방향키
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

	for (int i = 0; i < 999; i++) // 빈칸으로 시작하기 때문에 스왑에서 제외하고 전체 횟수를 짝수로 설정 (홀수로 설정시 정상적인 셔플 불가)
	{
		int nDestX = rand() % 5;
		int nDestY = rand() % 5;

		int nSrcX = rand() % 5;
		int nSrcY = rand() % 5;

		if ((nDestX == 4 && nDestY == 4) || (nSrcX == 4 && nSrcY == 4) || nDestX == nSrcX && nDestY == nSrcY) // 스왑을 할 필요가 없는 경우
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
			
			// itoa : 정수값을 문자 형식으로 변형해주는 함수
			if (j == x && i == y) // 빈칸 블럭 itoa(저장공간, 임시로 문자를 받을 공간, 10진수)
				DrawBlock(hOP, 10 + j * 6, 5 + i * 3, (char*)"■", BG_WHITE | FG_BLACK);
			else
				DrawBlock(hOP, 10 + j * 6, 5 + i * 3, itoa(puzzle[i][j],szTemp,10), BG_WHITE | FG_BLACK);
		}
	}
}


void DrawBlock(HANDLE hOP, int x, int y, char* str, WORD color)
{
	Draw(hOP, x + 0, y + 0, str, color);
	Draw(hOP, x + 2, y + 0, (char*)"■", color);
	Draw(hOP, x + 0, y + 1, (char*)"■", color);
	Draw(hOP, x + 2, y + 1, (char*)"■", color);
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

/*오류잡기
1. 프로젝트 구성 -> 구성속성 -> 고급 -> 문자집합 = 멀티바이트 문자 집합 사용
2. C / C++ -> 일반 -> SDL감사 = 아니오
*/