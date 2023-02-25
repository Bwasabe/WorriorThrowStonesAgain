#pragma once

#include "Monobehaviour.h"
#include "BImage.h"

class Object : public Monobehaviour
{
public:
	Object();
	Object(POINT pos, std::vector<LPCTSTR> imageFilePath, float scale, float animSpeed);
	virtual ~Object();

public:
	virtual void		Init() override;
	virtual void		Render(HDC hdc, float dt) override;
	virtual void		Update(float dt) override{}
	virtual void		Release() override;

public:
	std::vector<BImage>			GetImage() { return m_Images; }
	OBJECTSIZE		GetSize() { return m_Size; }
	POINT			GetPos() { return m_Pos; }

public:
	void			SetPos(POINT pos) { m_Pos = pos; }
protected:
 	std::vector<LPCTSTR>	m_ImageFilePath;

	std::vector<BImage>		m_Images;

	POINT		m_Pos;

	OBJECTSIZE	m_Size;

protected:
	float		m_AnimSpd;
	float		m_AnimTimer;

	int			m_AnimCount;

	float		m_Scale;
};
