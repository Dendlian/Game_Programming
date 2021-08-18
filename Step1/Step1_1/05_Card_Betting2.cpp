#include<iostream>
#include<time.h>
#include<Windows.h>
using namespace std;

enum E_SHAPE {E_SPADE, E_DIA, E_HEART, E_CLOVER, E_MAX};
enum E_SELECT {E_QUIT, E_HIGH, E_LOW, E_SEVEN};

// ���̷ο� ����
// 52���� ��Ŀī�带 ���
// ���� ���� �� 5���� ī�带 ����
// ���� 1���� 7���� 'ũ��', '�۴�', '����'�� ���ߴ� ����

typedef struct tagCard
{
	char*	 szShape;
	int		 nNumber;
}Card;


void InitCards(Card* cards);				// ��ü ī�� �ʱ�ȭ
void Suffle(Card* cards);					// ī�� ����
void Print(Card* cards);					// ��ü ī�� ���
void Print(tagCard* caeds, int index);		// �÷��� ī�� ���

void Play(Card* cards, int* money, int* index, bool* playing);
int Betting(int Money);

int main() 
{
	srand(time(NULL));
	rand();

	Card stCards[52];
	bool isPlaying = true;
	int nMymoney = 10000;
	int nCurrIndex = 5;

	InitCards(stCards);
	Suffle(stCards);
	Print(stCards);
	
	// system("pause");

	while (isPlaying)
	{
		system("cls");
		Print(stCards, nCurrIndex);
		if (nMymoney < 100)
		{
			// ���� ���� ����
			cout << "Not enough Money!";
			isPlaying = false;
		}
		else if (nCurrIndex > 42)
		{
			// �� ī��� ��ü (�ٽ� ����)
			Suffle(stCards);
			nCurrIndex = 5;
			cout << "Restart : Card reloading..." << endl;
			system("pause");
		}
		else
		{
			// �÷���
			Play(stCards, &nMymoney, &nCurrIndex, &isPlaying);
			Sleep(2000);
		}
	}
	system("pasue");
	return 0;
}



void InitCards(Card* cards)
{
	for (E_SHAPE i = E_SPADE; i < E_MAX; i = (E_SHAPE)(i + 1)) 
	{
		for (int j = 0; j < 13; j++) 
		{
			switch (i)
			{
			case E_SPADE:
				cards[i * 13 + j].szShape = (char*)"��";
				break;
			case E_DIA:
				cards[i * 13 + j].szShape = (char*)"��";
				break;
			case E_HEART:
				cards[i * 13 + j].szShape = (char*)"��";
				break;
			case E_CLOVER:
				cards[i * 13 + j].szShape = (char*)"��";
				break;
			}
			cards[i * 13 + j].nNumber = j + 1;
		}
	}
}
void Suffle(Card* cards)
{
	for (int i = 1; i < 1000; i++)
	{
		int nSrc = rand() % 52;
		int nDest = rand() % 52;

		Card stTemp = cards[nSrc];
		cards[nSrc] = cards[nDest];
		cards[nDest] = stTemp;
	}
}
void Print(Card* cards)
{
	for (int i = 0; i < 52; i++) 
	{
		switch (cards[i].nNumber)
		{
		case 1:
			cout << cards[i].szShape << "A" << "\t";
			break;
		case 11:
			cout << cards[i].szShape << "J" << "\t";
			break;
		case 12:
			cout << cards[i].szShape << "Q" << "\t";
			break;
		case 13:
			cout << cards[i].szShape << "K" << "\t";
			break;
		default : 
			cout << cards[i].szShape << cards[i].nNumber << "\t";
			break;
		}
		if (i % 13 == 12)cout << endl;
	}
}
void Print(Card* cards, int index)
{
	for (int i = index - 5; i < index; i++)
		cout << cards[i].szShape << cards[i].nNumber << "\t";
	cout << "\t ( ? )" << endl;
}
void Play(Card* cards, int* money, int* index, bool* playing)
{
	int						nSelect;
	E_SELECT				eSelect;
	int						nBet;
	cout << "My Money : " << *money << endl;
	cout << "1. HIGH  2. LOW  3.SEVEN (0. END GAME) : ";
	cin >> nSelect;

	eSelect = (E_SELECT)nSelect;

	switch (eSelect)
	{
	case E_QUIT:
		cout << "Finish The Game!" << endl;
		*playing = false;
		break;
	case E_HIGH:
		nBet = Betting(*money);
		if (cards[*index].nNumber > 7) // ��
		{
			cout << "Betting Success! : ";
			*money += nBet;
		}
		else // ��
		{
			cout << "Betting Failure! : ";
			*money -= nBet;
		}
		cout << cards[*index].szShape << cards[*index].nNumber << endl;
		break;
	case E_LOW:
		nBet = Betting(*money);
		if (cards[*index].nNumber < 7) // ��
		{
			cout << "Betting Success! : ";
			*money += nBet;
		}
		else // ��
		{
			cout << "Betting Failure! : ";
			*money -= nBet;
		}
		cout << cards[*index].szShape << cards[*index].nNumber << endl;
		break;
	case E_SEVEN:
		nBet = Betting(*money);
		if (cards[*index].nNumber == 7) // ��
		{
			cout << "Betting Success! : ";
			*money += nBet*2;
		}
		else // ��
		{
			cout << "Betting Failure! : ";
			*money -= nBet;
		}
		cout << cards[*index].szShape << cards[*index].nNumber << endl;
		break;
	}
	*index += 6;
}
int Betting(int Money)
{
	int nBet = 0;
	while (nBet<100 || nBet>Money)
	{
		cout << "Bet the Cash. (100 ~ All-in) : ";
		cin >> nBet;
	}
	return nBet;
}