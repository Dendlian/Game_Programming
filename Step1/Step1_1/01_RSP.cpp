#include <iostream>
#include <time.h>
using namespace std;

// Rock Paper Scissors Game

int main()
{
	int nCom, nPlayer;
	int cCom = 0;
	int cPlayer = 0;
	while (1)
	{
		cout << "1.ROCK 2.SCISSORS 3.PAPER : ";
		cin >> nPlayer;
		nCom = rand() % 3;
		if (nCom == nPlayer)
			cout << "DRAW" << endl << endl;
		else if ((nCom + 1) % 3 == nPlayer)
		{
			cout << "You Win" << endl;
			cPlayer++;
			cout << "Computer : You =" << cCom << " : " << cPlayer << endl << endl;
		}
		else
		{
			cout << "You Lose" << endl;
			cCom++;
			cout << "Computer : You =" << cCom << " : " << cPlayer << endl << endl;
		}

		if (cCom == 3 || cPlayer == 3)break;
	}
	if (cCom == 3)cout << "Defeat" << endl; // 3ÆÇ 3¼±½ÂÁ¦
	else cout << "Victory" << endl;

	system("pause");
	return 0;
}