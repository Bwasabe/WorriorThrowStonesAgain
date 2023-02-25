#include "Enemy.h"
#include "global.h"

Enemy::Enemy()
	: Character()
	, m_TargetObj{}
	, m_fAngle(0)
{
}

Enemy::Enemy(POINT pos, std::vector<LPCTSTR> imageFilePath, float scale, int hp, int atk, int def, float speed,float animSpeed , TAG tag, Character* target)
	: Character(pos, imageFilePath, scale, hp, atk, def, speed, animSpeed, tag)
	, m_TargetObj(target)
	, m_fAngle(0)
{
}

Enemy::~Enemy()
{
}

void Enemy::Init()
{
	Character::Init();
}

void Enemy::Render(HDC hdc, float dt)
{
	Character::Render(hdc, dt);
}

void Enemy::Update(float dt)
{
	Character::Update(dt);

	SetAngle();

	EnemyMove(dt);
}

void Enemy::Release()
{
	Character::Release();
}

void Enemy::Damage(int damage)
{
	g_pEngine->m_SoundManager->EnemyHitSound();

	Character::Damage(damage);
	
}

void Enemy::Dead() {
	g_pEngine->m_SpawnManager->SetScore(g_pEngine->m_SpawnManager->GetScore() + 100 );
	g_pEngine->m_SpawnManager->SetEnemySpeed(g_pEngine->m_SpawnManager->GetEnemySpeed() + 1.0f);
	Character::Dead();
}

void Enemy::UpdateCol()
{
	m_Collision.left = m_Pos.x + m_Size.width * 0.2 + 5;
	m_Collision.right = m_Collision.left + m_Size.width * 0.45;
	m_Collision.top = m_Pos.y + m_Size.height * 0.2 + 5;
	m_Collision.bottom = m_Collision.top + m_Size.height * 0.45;

	/*HDC hdc = GetDC(g_pEngine->GetWndHandle());
	Rectangle(hdc, m_Collision.left, m_Collision.top, m_Collision.right, m_Collision.bottom);*/
}


void Enemy::EnemyMove(float dt)
{
	m_Pos.x += cosf(m_fAngle) * m_Speed * dt;
	m_Pos.y += sinf(m_fAngle) * m_Speed * dt;
}

void Enemy::SetAngle()
{
	//POINT dir = m_TargetObj->GetPos() - m_Pos;
	float x = m_TargetObj->GetPos().x - m_Pos.x;
	float y = m_TargetObj->GetPos().y - m_Pos.y;

	m_fAngle = atan2(y, x);
}
