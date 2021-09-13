#include<iostream>
using namespace std;

/*
 // 클래스에서의 상속
   - 부모 클래스로부터 자식 클래스로 변수 또는 함수를 몰려주는 시스템

 // virtual function (가상 함수)
   - C++는 '다형성'이라는 특성을 지원하기 위해 virtuaㅣ 키워드를 제공
   - 부모 클래스 내에서 virtual로 선언된 자식 클래스에서 재 정의 가능
   - 만약 재 정의를 하지 않고 호출을 한다면 부모의 함수가 호출이 되고 재 정의를 했자면 재 정의된 자식의 클래스를 호출
*/

class cWeapon		// 부모 클래스
{
private:	// 개인공간 : 해당 클래스 내부에서만 접근 가능
	
protected:	// 보호된 공간 : 해당 클래스 내부 및 상속받은 자식 클래스에서 접근 가능	
	int			m_nAttDamage;
	int			m_nDuarability;

public:		// 자유공간 : 외부 어디서든 접근 가능
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
	void Attack() override // virtual 사용시 자식 클래스의 재정의를 한 후 표시로 override를 기입하고 세미콜론 미기입
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