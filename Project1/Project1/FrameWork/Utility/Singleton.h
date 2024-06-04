#pragma once

template<typename T>
class Singleton
{
public:
	// data영역에 많은 할당을 하는 방법
	static T* Get() 
	{// data영역에 많은 할당을 하는 방법
		//static T instance;
		//return &instance;
		if (instance == nullptr) { instance = new T(); }
		return instance;
	}
	static void Delete() { delete instance; }


private:
	// static 설명 TMI
	/* ram->Data / stack + heap 영역으로 존재
	 stack-> 지역변수
	 heap -> 동적할당
	 Data -> 전역변수, static -> 프로그램 시작할때 할당 끝날때 해제
	 static-> 특정 영역에서 사용 / 전역-> 모든 프로젝트 */
	// 포인터에 instance를 해서 data영역에 할당양 적게
	static T* instance;

};

template<typename T>
T* Singleton<T>::instance = nullptr;

// tamplate -> cpp / h를 나누면 터짐 (TMI)
// 컴파일은 가능
// 프로그램 시작 -> 전처리기(주석삭제 / #) -> 컴파일(C++ -> Assembly / 어셈블어 -> 기계어(2진법))
// -> 링커 (여기서 tamplate터짐) -> 실행