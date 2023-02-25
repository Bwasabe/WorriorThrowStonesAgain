#pragma once
#include "console.h"
#include "MonoSingleton.h"
enum KEYSTATE {
	KEY_FREE = 0,
	KEY_PUSH,
	KEY_UP,
	KEY_DOWN,
	KEY_HOLD
};

struct TInputState {
	DWORD dwKeyUp;
	DWORD dwKeyDown;
	DWORD dwKeyLeft;
	DWORD dwKeyRight;

	DWORD dwKeyLShift;

	DWORD dwKeyE;

	DWORD dwKeySpace;

	DWORD dwMouseLB;
	DWORD dwMouseRB;

};

class BInput : public MonoSingleton<BInput>
{
public:
	BInput();
	~BInput();

public:
	void	KeyCheck(DWORD dwCheckKey, DWORD& dwStateKey);
};


