#include<iostream>
#include<time.h>
#include<Windows.h> // Delay
//#include<tchar.h>

using namespace std;

void InitTable(int* table);
void ShowTable(int* table);
void HideTable(int* table);
void UserSelect(int* userTable, int* comTable);
void ComSelect(int* userTalbe, int* comTable);
int CheckBingo(int* table);

int main()
{
	// 랜덤 초기화
	srand(time(NULL));
	rand();

	// 테이블 배열과 빙고 변수 선언
	int nUserTable[25];
	int nUserBingo = 0;

	int nComTable[25];
	int nComBingo = 0;

	// 게임 진행 변수 선언
	bool isPlaying = true;
	bool isMyturn = true;

	while (isPlaying)
	{
		// 게임진행

		// 게임 플레이
		InitTable(nUserTable);
		InitTable(nComTable);

		while (nUserBingo < 3 && nComBingo < 3)
		{
			system("cls");
			//nUserBingo < 3 && nComTable < 3

			// 빙고 확인
			nUserBingo = CheckBingo(nUserTable);
			nComBingo = CheckBingo(nComTable);

			// 테이블 확인
			HideTable(nComTable);
			cout << "Computer Bingo : " << nComBingo << endl << endl;
			ShowTable(nUserTable);
			cout << "User Bingo : " << nUserBingo << endl;
			
			if (nUserBingo >= 3 && nComBingo >= 3) 
			{
				cout << "DRAW : DOUBLE THREE BINGO!" << endl;
				break;
			}
			else if (nUserBingo >= 3) 
			{
				cout << "VICTORY : YOU WIN!" << endl;
				break;
			}
			else if (nComBingo >= 3) 
			{
				cout << "DEFEAT : YOU LOSE!" << endl;
				break;
			}

			// 번호 선택
			if (isMyturn)
			{
				UserSelect(nUserTable, nComTable);
				isMyturn = false;
			}
			else
			{
				ComSelect(nUserTable, nComTable);
				isMyturn = true;
			}
		}

		nUserBingo = 0;
		nComBingo = 0;

		// 게임종료 선택
		cout << "0.End game, 1.New game : ";
		cin >> isPlaying;
	}
	system("pause");
	return 0;
}

void InitTable(int* table)
{
	for (int i = 0; i < 25; i++) table[i] = i + 1;

	int nSrc;
	int nDest;
	int nTemp;

	for (int i = 0; i < 250; i++)
	{
		nSrc = rand() % 25;
		nDest = rand() % 25;

		nTemp = table[nSrc];
		table[nSrc] = table[nDest];
		table[nDest] = nTemp;
	}
}

void ShowTable(int* table)
{
	cout << "====================================" << endl;
	for (int i = 0; i < 25; i++)
	{
		cout << "| " << table[i] << "\t";
		if (i % 5 == 4)
		{
			cout << endl;
			cout << "====================================" << endl;
		}

	}
}

void HideTable(int* table)
{
	cout << "====================================" << endl;
	for (int i = 0; i < 25; i++)
	{
		if (table[i] == 0)
			cout << "| 0\t";
		else
			cout << "| ?\t";
		if (i % 5 == 4) 
		{
			cout << endl;
			cout << "====================================" << endl;
		}
	}
}

void UserSelect(int* userTable, int* comTable)
{
	int nSelect;

	cout << "Choose Number(1~25) : ";
	cin >> nSelect;

	// 테이블 전제를 검사
	for (int i = 0; i < 25; i++)
	{
		if (nSelect == userTable[i])
		{
			// 0 => 테이블에서 이미 선택된 숫자를의미
			userTable[i] = 0;

			// 컴퓨터 테이블도 똑같은 숫자를 처리
			for (int j = 0; j < 25; j++)
			{
				if (nSelect == comTable[j])
				{
					comTable[j] = 0;
					break;
				}
			}
			break;
		}
		// 선택한 숫자를 찾지 못한 경우
		if (i == 24)
		{
			cout << "Wrong Number!" << endl;
			Sleep(1000);
		}
	}
}

void ComSelect(int* userTable, int* comTable)
{
	int nIndex;
	int nSelect;

	cout << "Computer Select";
	Sleep(100);
	cout << ".";
	Sleep(100);
	cout << ".";
	Sleep(100);
	cout << "." << endl;
	

	while (1) // 이전에 선택된 적이 없는 칸(배열의 Index)을 선택한다.
	{
		
		nIndex = rand() % 3000;
		nIndex %= 25;
		nSelect = comTable[nIndex];

		if (nSelect != 0) // 숫자가 남은 칸을 찾았으면
		{
			for (int i = 0; i < 25; i++)
			{
				if (nSelect == userTable[i])
				{
					userTable[i] = 0;
					cout << "Computer Select : " << nSelect << endl;
					Sleep(2000);
					break;
				}
			}
			comTable[nIndex] = 0; // 컴퓨터 테이블에서도 선택된 숫자를 처리한다.
			
			break;
		}
		
	}
}


int CheckBingo(int* table)
{
	int nBingo = 0;

	// 가로 검사
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			if (table[i * 5 + j] == 0) // 한 칸씩 선택 유무 확인
			{
				if (j == 4) nBingo++; // 제일 마지막 칸까지 선택이 되어 있는 경우
			}
			else break;
		}
	}
	// 세로 검사
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			if (table[i + j * 5] == 0) // 한 칸씩 선택 유무 확인
			{
				if (j == 4) nBingo++; // 제일 마지막 칸까지 선택이 되어 있는 경우
			}
			else break;
		}
	}

	// 왼쪽 사선
	for (int i = 0; i < 5; i++)
	{
		if (table[i * 6] == 0) // 한 칸씩 선택 유무 확인
		{
			if (i == 4) nBingo++; // 제일 마지막 칸까지 선택이 되어 있는 경우
		}
		else break;
	}

	// 오른쪽 사선
	for (int i = 1; i < 5; i++)
	{
		if (table[i * 4] == 0) // 한 칸씩 선택 유무 확인
		{
			if (i == 4) nBingo++; // 제일 마지막 칸까지 선택이 되어 있는 경우
		}
		else break;
	}

	return nBingo;
}


/* 컴퓨터의 지능 플레이
<우선순위 TABLE>
[3] [0] [0] [0] [4]
[0] [3] [0] [3] [1]
[1] [1] [5] [1] [x]
[0] [3] [0] [3] [1]
[3] [0] [0] [0] [4]
// 우선순위를 정해줌으로서 컴퓨터가 더 지능적으로 플레이 할 수 있음
*/

/*
 <rand 함수의 한계> 
 : Sleep을 사용하게 되면(?) rand를 무수히 돌려도 절대 안나오는 숫자가 발생하여 플레이가 중간에 끊김
 : 따라서 범위를 더 크게 만들고 다시 25로 나누는 절차를 진행
*/