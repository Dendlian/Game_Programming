#include <iostream>
#include <time.h>
using namespace std;

/*
 // ���ھ߱� ���� : 1~9������ ������ ������ ���� 3���� ���ߴ� ����
 ��Ʈ����ũ : ��ġ�� ���� ��� ����
 �� : ���ڴ� ������ ��ġ�� �ٸ�
 �ƿ� : ���ڿ� ��ġ ��� �ش� ����
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