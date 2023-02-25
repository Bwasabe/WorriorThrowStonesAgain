#include "BInput.h"

BInput::BInput()
{
}

BInput::~BInput()
{
}

void BInput::KeyCheck(DWORD dwCheckKey, DWORD& dwStateKey)
{
	if (GetAsyncKeyState(dwCheckKey) & 0x8000) {
		if (dwStateKey == KEY_FREE)
			dwStateKey = KEY_PUSH;
		else
			dwStateKey = KEY_DOWN;
	}
	else {
		if (dwStateKey == KEY_PUSH || dwStateKey == KEY_DOWN)
			dwStateKey = KEY_UP;
		else
			dwStateKey = KEY_FREE;
	}
}
