#pragma once
#include "Monobehaviour.h"

class Start : public Monobehaviour
{
public:
	Start();
	~Start();

public:
	// Monobehaviour을(를) 통해 상속됨
	virtual void Init() override;
	virtual void Update(float dt) override;
	virtual void Render(HDC hdc, float dt) override;
	virtual void Release() override;

public:
	bool		GetIsStart() { return m_IsStart; }
	void		SetIsStart(bool isStart) { m_IsStart = isStart; }

private:
	bool		m_IsStart;
};
