#include<iostream>
using namespace std;

/*
 // Ŭ���������� ���
   - �θ� Ŭ�����κ��� �ڽ� Ŭ������ ���� �Ǵ� �Լ��� �����ִ� �ý���

 // virtual function (���� �Լ�)
   - C++�� '������'�̶�� Ư���� �����ϱ� ���� virtua�� Ű���带 ����
   - �θ� Ŭ���� ������ virtual�� ����� �ڽ� Ŭ�������� �� ���� ����
   - ���� �� ���Ǹ� ���� �ʰ� ȣ���� �Ѵٸ� �θ��� �Լ��� ȣ���� �ǰ� �� ���Ǹ� ���ڸ� �� ���ǵ� �ڽ��� Ŭ������ ȣ��
*/

class cWeapon		// �θ� Ŭ����
{
private:	// ���ΰ��� : �ش� Ŭ���� ���ο����� ���� ����
	
protected:	// ��ȣ�� ���� : �ش� Ŭ���� ���� �� ��ӹ��� �ڽ� Ŭ�������� ���� ����	
	int			m_nAttDamage;
	int			m_nDuarability;

public:		// �������� : �ܺ� ��𼭵� ���� ����
	virtual void Attack()
	{
		cout << "Attack!!" << endl;
	}
	virtual void Defence()
	{
		cout << "Defence!!" << endl;
	}
};

class cSword : public cWeapon
{
public:
	void Attack() override // virtual ���� �ڽ� Ŭ������ �����Ǹ� �� �� ǥ�÷� override�� �����ϰ� �����ݷ� �̱���
	{
		cout << "Sword Attack!!" << endl;
	}
	void Defence() override
	{
		cout << "Sword Defence!!" << endl;
	}
};

class cGun : public cWeapon
{
public:
	void Attack() override
	{
		cout << "Gun Attack!!" << endl;
	}
	void Defence() override
	{
		cout << "Gun Defence!!" << endl;
	}
};

int main()
{
	cWeapon* pWeapon = new cWeapon;

	pWeapon->Attack();
	pWeapon->Defence();
	delete pWeapon;

	pWeapon = new cSword;
	pWeapon->Attack();
	pWeapon->Defence();
	delete pWeapon;

	system("pause");
	return 0;
}