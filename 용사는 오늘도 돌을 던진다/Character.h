#pragma once

#include "BObject.h"
class Character : public Object
{
public:
	Character();
	Character(POINT pos, std::vector<LPCTSTR> imageFilePath, float scale, int hp, int atk, int def,float speed,float animSpeed, TAG tag);
	virtual ~Character();


public:
	virtual void	Attack(Character* hitObject);
	virtual void	Damage(int damage);
	virtual void	Dead();

public:
	virtual void	Update(float dt)override;
public:
	virtual void	Init() override;

public:
	TAG				GetTag() { return m_Tag; }

	RECT*			GetCol() { return &m_Collision; }
	void			SetCol(RECT rect) { m_Collision = rect; }

	void			SetIsDamaged(bool isDamage) { m_IsDamaged = isDamage; }
	bool			GetIsDamaged() { return m_IsDamaged; }

	int				GetAtk() { return m_Atk; }
	void			SetAtk(int atk) { m_Atk = atk	; }

	void			SetIsDead(bool isDead) { m_IsDead = isDead; }
	bool			GetIsDead() { return m_IsDead; }
protected:
	virtual void	UpdateCol();

	virtual void	UpdateDamaged();
protected:
	int		m_Hp;

	int		m_Atk;

	int		m_Def;

	float	m_Speed;

protected:
	bool	m_IsDead;

	bool	m_IsDamaged;
private:
	TAG m_Tag;

protected:
	RECT m_Collision;
};
