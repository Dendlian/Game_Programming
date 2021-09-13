#include<iostream>
#include<vector>
#include<time.h>
#include<windows.h>

using namespace std;

/*
	- push_back(���ڰ�) : ����(���� ����)�� �ڷ� ����
	- pop_back() : ������ ������ �ڷ� ����
	- size() : ���Ϳ� �� �ִ� �ڷ��� ������ ��ȯ
	- begin() : ������ ù��° ���� �ּҰ�
		// ex) begin() + 3 : ������ ù��° �����κ��� 3ĭ ���� �ּڰ� (4��° �ڷ��� �ּҰ�)
	- end() : ������ ������ ���� �ּҰ�
	- insert(�ڷḦ ���� ��ġ �ּҰ�, ���� ��) : Ư�� ��ġ�� ���� ����
	- insert(�ڷḦ ���� ��ġ �ּҰ�, ����, ���� ��) : Ư�� ��ġ�� ���� ������ŭ ���� ����
	- erase(�ڷḦ ���� ��ġ �ּҰ�) : Ư�� ��ġ�� ���� ����
	- clear() : ���� ��ü�� ����
	- empty() : ���Ͱ� ����ִ��� Ȯ��
*/

int main()
{
	// ���� : �ڷḦ ��� �ڷᱸ�� (�ߺ� �����͵� ���)
	// �迭�ϰ� ��������� ��ũ�� ����� �߰��� �ڷᱸ��
	// vector<���� �ڷ���> ���� �̸�;
	vector<int>vecInt;

	cout << vecInt.empty() << endl;		// true(1)

	vecInt.push_back(3);
	vecInt.push_back(2);
	vecInt.push_back(4);
	vecInt.push_back(7);

	cout << vecInt.empty() << endl;		// false(0)

	// ���� ���ͷ����� : ������ �ּҰ��� �ӽ÷� ���� ����
	//vector<int>::iterator iter;
	//for (iter = vecInt.begin(); iter != vecInt.end(); iter++)
	//{
	//	cout << (*iter) << endl;
	//}
	//[begin]3[+1]2[+2]4[+3]7[end]

	cout << *vecInt.begin() << endl;
	cout << *(vecInt.end() - 1) << endl;

	// vecInt[3] => *(vecInt.begin()+3)
	vecInt.insert(vecInt.begin() + 2, 10);		// 3 2 10 4 7
	vecInt.insert(vecInt.begin() + 2, 3, 5);	// 3 2 5 5 5 10 4 7

	// �ε����� ���Ϳ� �����ϴ� ���
	for (int i = 0; i < vecInt.size(); i++)
	{
		cout << vecInt[i] << endl;
	}
	cout << endl;

	vecInt.clear();
	cout << vecInt.empty() << endl;		// true (1)

	system("pause");
	return 0;

}