#include<iostream>
#include<time.h>
#include<windows.h>

using namespace std;

// ����ü�� �⺻���� public, Ŭ������ �⺻���� private
struct tagPlayer // ������ �����ϰų� �ൿ���� �ʴ� ������Ʈ�� ǥ���� �� ����ϴ� ���� ����
{
	int a;
public: // �ܺο����� ��� ����
	int b;
private: // �ܺο��� ���� �Ұ�
	int c;
};

// �Լ� ������ ����ü�� ���������� ���� Ŭ���� ���ο� �Լ��� ����

class cPlayer // Ư�� �ൿ�� �� �� �ִ� ������Ʈ�� ǥ���� �� ����ϴ� ���� ����
{
private:
	int a;
public:
	int Function();
};

int cPlayer::Function()
{
	return 30;
}

int main()
{
	tagPlayer p1;
	cPlayer p2;

	system("pause");
	return 0;
}