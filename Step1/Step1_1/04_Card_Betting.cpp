#include <iostream>
#include <time.h>
using namespace std;

/*
ī�� : 1~12�� ���� ī��
1. ī�� 2���� �����ϰ� ���õǰ� �ø���� ��������.
ex) 7~10 (ī�� 1���� ������ �ǰ� ��� ������� ���µ��� �ʴ´�.)
2. �⺻ ���� 200
3. �������� : 100ȸ�� / ��ž : �º� / �߰� ���� : ����-ī�� �߰� ����
=> �º� : ������ ī�尡 ���� ���µ� �� ���� ������ ī���� �¸�
=> �߰� ���� : ���� ���� ���� ī�� �߿� �� ���� ���µȴ�.
*/

int main() 
{
	// �÷��̾��� �� �ݾ�, ���� �ݾ�, ī�� 12��, ���� Ƚ��, ���� ����
	srand(time(NULL));
	rand();
	int M_total = 10000;
	int card[12] = { 1,2,3,4,5,6,7,8,9,10,11,12 };

	int U_select;
	
	int c_temp = 0;
	int rn1;
	int rn2;
	
	int game = 1;

	while (1) { // n��° ����
		
		system("cls");
		int M_bet = 200;
		int C_bet = 0;

		for (int i = 0; i < 100; i++)
		{
			rn1 = rand() % 12;
			rn2 = rand() % 12;
			c_temp = card[rn1];
			card[rn1] = card[rn2];
			card[rn2] = c_temp;
		}

		if (card[0] > card[1]) {
			c_temp = card[0];
			card[0] = card[1];
			card[1] = c_temp;
		}
	
		while (1) { // n��° ���� �� n��° ����
			cout << endl << "Total Cash : " << M_total << endl;
			cout << "===============================================" << endl;
			cout << "Betting Cash : " << M_bet << endl;
			cout << "Open Card  : " << card[0] << " ~ " << card[1] << endl;
			cout << "Answer Card : ? " << endl;
			cout << "1.Stop	 2.Add Betting  3.Give-up : ";
			cin >> U_select;

			if (U_select == 3) {
				M_bet /= 2;
				M_total -= M_bet;
				cout << endl<< "You give-up the game." << endl << "Answer Card : " << card[2] << endl;
				break;
			}
			else if (U_select == 1) {
				if (card[0] < card[2] && card[2] < card[1]) {
					M_total += M_bet;
					cout << endl << "You Win!" << endl << "Answer Card : " << card[2] << endl;
					break;
				}
				else {
				
					M_total -= M_bet;
					cout << endl << "You Lose!" << endl << "Answer Card : " << card[2] << endl;
					break;
				}
			}
			else if (U_select == 2) {
				if (C_bet > 3) cout << "You can't add anymore!" << endl;
				else {
					C_bet++;
					M_bet *= 2;
					system("cls");
					cout << "Plus Open Card : ";
					for (int i = 0; i < C_bet; i++) cout << card[i + 3] << " ";
					cout << endl;
				}
			}
		}
		cout << "Continue? (1.YES  2.NO)";
		cin >> game;
		if (game == 2)break;
	}
	system("pause");
}