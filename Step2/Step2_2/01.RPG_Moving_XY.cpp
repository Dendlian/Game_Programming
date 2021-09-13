#include"Base.h"
/*
// 열거문 - enum
   - enum은 여러가지 상태값을 문자로 표현 가능 (가독성이 증가)
   - 값을 순차적으로 증가시키며 관리 (값을 임의로 넣는 경우 임의로 정해준 값부터 뒤쪽으로 1씩 증가)
   - 열거문으로 선언된 변수에 설정된 값에 대한 제한을 거는 것이 가능
   enum class E_NUMBERS {EN_ZERO, EN_ONE, EN_TWO, EN_THREE, EN_TEN=10, EN_ELEVEN};
*/

// 캐릭터의 상태값
enum E_STATE {E_IDLE=0, E_MOVE_LEFT, E_MOVE_RIGHT, E_MOVE_UP, E_MOVE_DOWN, E_FIGHT, E_STATE_NMAX};

// 전투중 캐릭터의 상태값
enum E_FIGHTING {E_RUNAWAY, E_ATTACK, E_DEFENCE, E_MAGIC, E_F_MAX};

// 몬스터의 종류
enum E_MONTYPE {E_ORC, E_ELF, E_TROLL, E_HUMAN, E_MON_MAX=4};

int main()
{
	srand(time(NULL));
	rand();

	E_STATE eState = E_STATE::E_IDLE; // 캐릭터의 현재 상태
	int nHp = 100; // 캐릭터의 체력
	int nCoordX = 0, nCoordY = 0; // 캐릭터의 현재 위치
	int nSelect; // 행동을 입력받기 위한 변수

	// 몬스터의 수 만큼 배열 할당
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