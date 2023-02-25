#pragma once
#include "Enemy.h"
class Bullet : public Character
{
public:
	Bullet();
	Bullet(POINT pos, float m_fAngle, std::vector<LPCTSTR> imageFilePath, float scale, int hp, int atk, int def, float speed, float animSpeed, TAG tag = TAG::BULLET);
	~Bullet();

public:
	virtual void		Init()override;
	virtual void		Update(float dt) override;
	virtual void		Release() override;

private:
	void		BulletMove(float dt);

	void		CheckHit();
public:
	bool		IsValid();

private:
	float		m_fAngle;


};
