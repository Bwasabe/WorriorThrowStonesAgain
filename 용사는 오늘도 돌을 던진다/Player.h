#pragma once

#include "Bullet.h"
#include "BInput.h"

class Player : public Character
{
public:
	Player();
	Player(POINT pos, std::vector<LPCTSTR> imageFilePath, float scale, float speed, int hp, int atk,int def,float animSpeed, TAG tag);
	~Player();

	void PlayerInit(float duration, KEYSTATE keyState, std::vector<LPCTSTR> luciferFilePath);
public:
	// Object을(를) 통해 상속됨
	virtual void		Init()override;
	virtual void		Update(float dt) override;
	virtual void		Render(HDC hdc, float dt)override;
	virtual void		Release() override;

	virtual void		Dead()override;

public:
	POINT				GetDir() { return m_NextDir; }

	RECT				GetNonMonsterZone() { return m_NonMonsterZone; }

private:
	void				PlayerMove(float dt);
	void				PlayerAttack();
	void				PlayerDash(float dt);

	void				PlayerSkillE(float dt);

	void				PlayerDeath();
private:
	void				BulletIsValid();

	void				CheckEnemyHit();

	void				DeleteAll();


protected:
	virtual void		UpdateCol()	override;

private:
	POINT					m_NextDir;

	RECT					m_NonMonsterZone;

private:
	float					m_DashTimer;
	float					m_DashDuration;

	float					m_DashColTime;
	float					m_DashColTimer;

	bool					m_IsDash;
	bool					m_IsCanDash;

private:
	float					m_SkillEDuration;
	float					m_SkillETimer;

	float					m_SkillEColTime;
	float					m_SkillEColTimer;

	bool					m_IsSkillE;
	bool					m_IsCanSkillE;
private:

private:
	std::vector<Bullet*>	m_Bullets;
	std::vector<LPCTSTR>	m_BulletImageFilePaths;

	std::vector<LPCTSTR>	m_LuciferFilePaths;
private:
	TInputState				m_Input;

	KEYSTATE				m_CurrentKeyState;
};
