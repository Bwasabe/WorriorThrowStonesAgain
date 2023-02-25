#pragma once

#include "console.h"
class Monobehaviour
{
public:
	Monobehaviour() = default;
	virtual ~Monobehaviour() = default;

public:
	virtual void Init() = 0;
	virtual void Update(float dt) = 0;
	virtual void Render(HDC hdc, float dt) = 0;
	virtual void Release() = 0;

public:
	int			GetID() { return m_Id; }
	void		SetId(int id) { m_Id = id; }

private:
	int			m_Id;
};
