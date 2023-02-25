#pragma once
#include "Character.h"
class Enemy : public Character
{
public:
	Enemy();
	Enemy(POINT pos, std::vector<LPCTSTR> imageFilePath, float scale, int hp, int atk, int def, float speed,float animSpeed, TAG tag, Character* target);
	~Enemy();

public:

	virtual void		Init() override;
	virtual void		Render(HDC hdc, float dt) override;
	virtual void		Update(float dt) override;
	virtual void		Release() override;

public:
	virtual void		Damage(int damage)override;
	virtual void		Dead()override;
	virtual void		UpdateCol()override;
private:
	void				EnemyMove(float dt);

	void				SetAngle();

private:
	Character*			m_TargetObj;

private:
	float				m_fAngle;

};

