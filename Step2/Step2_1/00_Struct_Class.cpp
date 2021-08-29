#include<iostream>
#include<time.h>
#include<windows.h>

using namespace std;

// 구조체는 기본값이 public, 클래스는 기본값이 private
struct tagPlayer // 스스로 생각하거나 행동하지 않는 오브젝트를 표현할 때 사용하는 것을 지향
{
	int a;
public: // 외부에서도 사용 가능
	int b;
private: // 외부에서 접근 불가
	int c;
};

// 함수 구현은 구조체도 가능하지만 보통 클래스 내부에 함수를 구현

class cPlayer // 특정 행동을 할 수 있는 오브젝트를 표현할 때 사용하는 것을 지향
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