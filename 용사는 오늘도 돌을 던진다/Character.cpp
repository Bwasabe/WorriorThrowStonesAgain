#include "Character.h"

Character::Character()
	: Object()
	, m_Atk(0)
	, m_Collision{}
	, m_Def(0)
	, m_Hp(0)
	, m_Speed(0)
	, m_Tag(TAG::DEFAULT)
{
}

Character::Character(POINT pos, std::vector<LPCTSTR> imageFilePath, float scale, int hp, int atk, int def,float speed,float animSpeed, TAG tag)
	: Object(pos,imageFilePath, scale, animSpeed)
	, m_Atk(atk)
	, m_Collision{}
	, m_Def(def)
	, m_Hp(hp)
	, m_Speed(speed)
	, m_Tag(tag)
{
}



Character::~Character()
{
}

void Character::Attack(Character* hitObject) {
	hitObject->Damage(m_Atk);
}

void Character::Damage(int damage)
{

	m_Hp -= damage;

	if (m_Hp <= 0) {
		m_IsDead = true;
		Dead();
	}
	else {
		m_IsDamaged = true;
	}
}

void Character::Dead()
{
	Release();
}

void Character::Update(float dt)
{
	Object::Update(dt);
	UpdateCol();
}

void Character::Init()
{
	Object::Init();

	UpdateCol();
}

void Character::UpdateCol()
{
	m_Collision.left = m_Pos.x;
	m_Collision.right = m_Collision.left + m_Size.width;
	m_Collision.top = m_Pos.y;
	m_Collision.bottom = m_Collision.top + m_Size.height;
}

void Character::UpdateDamaged()
{
	if (m_IsDamaged) {
		m_IsDamaged = false;

	}
}



