#pragma once

template<typename T>
class Singleton
{
public:
	// data������ ���� �Ҵ��� �ϴ� ���
	static T* Get() 
	{// data������ ���� �Ҵ��� �ϴ� ���
		//static T instance;
		//return &instance;
		if (instance == nullptr) { instance = new T(); }
		return instance;
	}
	static void Delete() { delete instance; }


private:
	// static ���� TMI
	/* ram->Data / stack + heap �������� ����
	 stack-> ��������
	 heap -> �����Ҵ�
	 Data -> ��������, static -> ���α׷� �����Ҷ� �Ҵ� ������ ����
	 static-> Ư�� �������� ��� / ����-> ��� ������Ʈ */
	// �����Ϳ� instance�� �ؼ� data������ �Ҵ�� ����
	static T* instance;

};

template<typename T>
T* Singleton<T>::instance = nullptr;

// tamplate -> cpp / h�� ������ ���� (TMI)
// �������� ����
// ���α׷� ���� -> ��ó����(�ּ����� / #) -> ������(C++ -> Assembly / ������ -> ����(2����))
// -> ��Ŀ (���⼭ tamplate����) -> ����