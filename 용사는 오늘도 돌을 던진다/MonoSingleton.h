#pragma once

template <typename T>
class MonoSingleton
{
protected:
	static T* _instance;
	MonoSingleton() {}
	virtual ~MonoSingleton(){}

public:
	static T* GetInstance();   

	void ReleaseInstance();
};

template <typename T>
T* MonoSingleton<T>::_instance = nullptr;

template <typename T>
T* MonoSingleton<T>::GetInstance() {
	if (_instance == nullptr) {
		_instance = new T;
	}
	return _instance;
}

template <typename T>
void MonoSingleton<T>::ReleaseInstance() {
	if (_instance) {
		delete _instance;
		_instance = nullptr;
	}
}

