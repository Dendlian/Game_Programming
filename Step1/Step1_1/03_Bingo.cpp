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
	// ���� �ʱ�ȭ
	srand(time(NULL));
	rand();

	// ���̺� �迭�� ���� ���� ����
	int nUserTable[25];
	int nUserBingo = 0;

	int nComTable[25];
	int nComBingo = 0;

	// ���� ���� ���� ����
	bool isPlaying = true;
	bool isMyturn = true;

	while (isPlaying)
	{
		// ��������

		// ���� �÷���
		InitTable(nUserTable);
		InitTable(nComTable);

		while (nUserBingo < 3 && nComBingo < 3)
		{
			system("cls");
			//nUserBingo < 3 && nComTable < 3

			// ���� Ȯ��
			nUserBingo = CheckBingo(nUserTable);
			nComBingo = CheckBingo(nComTable);

			// ���̺� Ȯ��
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

			// ��ȣ ����
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

		// �������� ����
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

	// ���̺� ������ �˻�
	for (int i = 0; i < 25; i++)
	{
		if (nSelect == userTable[i])
		{
			// 0 => ���̺��� �̹� ���õ� ���ڸ��ǹ�
			userTable[i] = 0;

			// ��ǻ�� ���̺� �Ȱ��� ���ڸ� ó��
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
		// ������ ���ڸ� ã�� ���� ���
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
	

	while (1) // ������ ���õ� ���� ���� ĭ(�迭�� Index)�� �����Ѵ�.
	{
		
		nIndex = rand() % 3000;
		nIndex %= 25;
		nSelect = comTable[nIndex];

		if (nSelect != 0) // ���ڰ� ���� ĭ�� ã������
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
			comTable[nIndex] = 0; // ��ǻ�� ���̺����� ���õ� ���ڸ� ó���Ѵ�.
			
			break;
		}
		
	}
}


int CheckBingo(int* table)
{
	int nBingo = 0;

	// ���� �˻�
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			if (table[i * 5 + j] == 0) // �� ĭ�� ���� ���� Ȯ��
			{
				if (j == 4) nBingo++; // ���� ������ ĭ���� ������ �Ǿ� �ִ� ���
			}
			else break;
		}
	}
	// ���� �˻�
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			if (table[i + j * 5] == 0) // �� ĭ�� ���� ���� Ȯ��
			{
				if (j == 4) nBingo++; // ���� ������ ĭ���� ������ �Ǿ� �ִ� ���
			}
			else break;
		}
	}

	// ���� �缱
	for (int i = 0; i < 5; i++)
	{
		if (table[i * 6] == 0) // �� ĭ�� ���� ���� Ȯ��
		{
			if (i == 4) nBingo++; // ���� ������ ĭ���� ������ �Ǿ� �ִ� ���
		}
		else break;
	}

	// ������ �缱
	for (int i = 1; i < 5; i++)
	{
		if (table[i * 4] == 0) // �� ĭ�� ���� ���� Ȯ��
		{
			if (i == 4) nBingo++; // ���� ������ ĭ���� ������ �Ǿ� �ִ� ���
		}
		else break;
	}

	return nBingo;
}


/* ��ǻ���� ���� �÷���
<�켱���� TABLE>
[3] [0] [0] [0] [4]
[0] [3] [0] [3] [1]
[1] [1] [5] [1] [x]
[0] [3] [0] [3] [1]
[3] [0] [0] [0] [4]
// �켱������ ���������μ� ��ǻ�Ͱ� �� ���������� �÷��� �� �� ����
*/

/*
 <rand �Լ��� �Ѱ�> 
 : Sleep�� ����ϰ� �Ǹ�(?) rand�� ������ ������ ���� �ȳ����� ���ڰ� �߻��Ͽ� �÷��̰� �߰��� ����
 : ���� ������ �� ũ�� ����� �ٽ� 25�� ������ ������ ����
*/