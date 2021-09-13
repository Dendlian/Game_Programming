#include"Base.h"
/*
// ���Ź� - enum
   - enum�� �������� ���°��� ���ڷ� ǥ�� ���� (�������� ����)
   - ���� ���������� ������Ű�� ���� (���� ���Ƿ� �ִ� ��� ���Ƿ� ������ ������ �������� 1�� ����)
   - ���Ź����� ����� ������ ������ ���� ���� ������ �Ŵ� ���� ����
   enum class E_NUMBERS {EN_ZERO, EN_ONE, EN_TWO, EN_THREE, EN_TEN=10, EN_ELEVEN};
*/

// ĳ������ ���°�
enum E_STATE {E_IDLE=0, E_MOVE_LEFT, E_MOVE_RIGHT, E_MOVE_UP, E_MOVE_DOWN, E_FIGHT, E_STATE_NMAX};

// ������ ĳ������ ���°�
enum E_FIGHTING {E_RUNAWAY, E_ATTACK, E_DEFENCE, E_MAGIC, E_F_MAX};

// ������ ����
enum E_MONTYPE {E_ORC, E_ELF, E_TROLL, E_HUMAN, E_MON_MAX=4};

int main()
{
	srand(time(NULL));
	rand();

	E_STATE eState = E_STATE::E_IDLE; // ĳ������ ���� ����
	int nHp = 100; // ĳ������ ü��
	int nCoordX = 0, nCoordY = 0; // ĳ������ ���� ��ġ
	int nSelect; // �ൿ�� �Է¹ޱ� ���� ����

	// ������ �� ��ŭ �迭 �Ҵ�
	int nMonHp[E_MON_MAX];
	int nMonX[E_MON_MAX];
	int nMonY[E_MON_MAX];

	for (int i = 0; i < E_MON_MAX; i++)
	{
		nMonHp[i] = 100;
		nMonX[i] = 5 + i * 5;
		nMonY[i] = 0;
	}

	while (1)
	{
		system("cls");
		cout << "Curren Location : X(" << nCoordX << ") Y(" << nCoordY << ")" << endl;

		if (eState == E_IDLE)
			cout << "SELECT (0.STAY  1.LEFT  2.RIGHT  3.UP  4.DOWN) :";
		else if (eState == E_FIGHT)
			cout << "SEKECT (0.RUN  1.ATTACK  2.MAGIC  3.DEFENCE) : ";

		cin >> nSelect;

		cout << ".";
		Sleep(500);
		cout << ".";
		Sleep(500);
		cout << ".";
		Sleep(500);

		if (eState == E_IDLE)
		{
			switch (nSelect)
			{
			case E_IDLE:
				cout << "STAY FOR NEXT TURN!" << endl;
				break;
			case E_MOVE_LEFT:
				cout << "MOVE LEFT!" << endl;
				nCoordX--;
				break;
			case E_MOVE_RIGHT:
				cout << "MOVE RIGHT!" << endl;
				nCoordX++;
				break;
			case E_MOVE_UP:
				cout << "MOVE UP!" << endl;
				nCoordY--;
				break;
			case E_MOVE_DOWN:
				cout << "MOVE DOWN!" << endl;
				nCoordY++;
				break;
			default:
				cout << "WRONG INPUT! STAY FOR NEXT TURN!" << endl;
				break;
			}
			Sleep(2000);
		}
		else if (eState == E_FIGHT)
		{
			switch (nSelect)
			{
			case E_RUNAWAY:
			{
				int nRand = rand() % 2;
				if (nRand == 0)
				{
					cout << "Successfully Escape!" << endl;
					nCoordX += 1;
				}
				else
				{
					cout << "FAIL!" << endl;
				}
			}
				break;
			case E_ATTACK:
				cout << "ATTACK!" << endl;
				break;
			case E_MAGIC:
				cout << "MAGIC!!" << endl;
				break;
			case E_DEFENCE:
				cout << "DEFENCE!" << endl;
				break;
			default:
				cout << "WRONG INPUT! STAY FOR NEXT TURN!" << endl;
				break;
			}
		}
		

		for (int i = 0; i < E_MON_MAX; i++)
		{
			if (nCoordX == nMonX[i] && nCoordY == nMonY[i])
			{
				switch (i)
				{
				case E_ORC:
					cout << "You bump into ORC!" << endl;
					Sleep(1000);
					break;
				case E_ELF:
					cout << "You bump into ELF!" << endl;
					Sleep(1000);
					break;
				case E_TROLL:
					cout << "You bump into TROLL!" << endl;
					Sleep(1000);
					break;
				case E_HUMAN:
					cout << "You bump into HUMAN!" << endl;
					Sleep(1000);
					break;
				}
				eState = E_FIGHT;
			}
		}
	}
	system("pause");
	return 0;
}