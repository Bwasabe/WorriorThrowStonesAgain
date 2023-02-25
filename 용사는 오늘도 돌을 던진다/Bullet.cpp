#include "Bullet.h"
#include "global.h"
Bullet::Bullet()
	: Character()
	, m_fAngle(0)
{
}

Bullet::Bullet(POINT pos, float fAngle, std::vector<LPCTSTR> imageFilePath, float scale, int hp, int atk, int def, float speed, float animSpeed, TAG tag)
	: Character(pos, imageFilePath, scale, hp, atk, def, speed, animSpeed, tag)
	, m_fAngle(fAngle)
{


}

Bullet::~Bullet()
{
}

void Bullet::Init()
{
	Character::Init();
}

void Bullet::Update(float dt)
{
	BulletMove(dt);

	Character::Update(dt);

	CheckHit();
}

void Bullet::Release()
{
	Character::Release();
}


void Bullet::BulletMove(float dt)
{
	m_Pos.x += cosf(m_fAngle) * m_Speed * dt;
	m_Pos.y += sinf(m_fAngle) * m_Speed * dt;
}

void Bullet::CheckHit()
{
	g_pEngine->m_SpawnManager->IsEnemyCol(this);
}

bool Bullet::IsValid()
{
	RECT rect;
	GetClientRect(g_pEngine->GetWndHandle(), &rect);
	return PtInRect(&rect, m_Pos);
}



