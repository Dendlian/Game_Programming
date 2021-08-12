#include <iostream>
#include <time.h>
using namespace std;

/*
 // 숫자야구 게임 : 1~9까지의 숫자중 랜덤한 숫자 3개를 맞추는 게임
 스트라이크 : 위치와 숫자 모두 동일
 볼 : 숫자는 있지만 위치가 다름
 아웃 : 숫자와 위치 모두 해당 없음
*/

int main()
{
	srand(time(NULL));
	rand();

	int C_num[3];
	int Mnum[3];
	int c_strike = 0;
	int c_ball = 0;
	int c_out = 0;
	int T_count = 1;

	for (int i = 0; i < 3; i++)C_num[i] = rand() % 9 + 1;

	while (1)
	{
		cout << "Input your number (1~9)" << endl << "1st number : ";
		cin >> Mnum[0];
		cout << "2nd Number : ";
		cin >> Mnum[1];
		cout << "3rd Number : ";
		cin >> Mnum[2];

		for (int j = 0; j < 3; j++)
		{
			if (Mnum[j] == C_num[j])c_strike;
			else if (Mnum[j] == C_num[(j + 1) % 3] || Mnum[j] == C_num[(j + 2) % 3])c_ball++;
			else c_out++;
		}
		cout << "Srike : " << c_strike << endl << "Ball : " << c_ball << endl << "Out : " << endl << endl;
		cout << "Count : " << T_count << endl;

		system("pause");
		return 0;
	}

}