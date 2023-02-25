#pragma once

#include "Enemy.h"
#include "Bullet.h"

class EnemySpawnManager : public Monobehaviour
{
public:
	EnemySpawnManager();
	EnemySpawnManager(std::vector<LPCTSTR> imageFilePath , float spawnDuration);
	~EnemySpawnManager();

public:
	// Monobehaviour을(를) 통해 상속됨
	virtual void Init() override;
	virtual void Update(float dt) override;
	virtual void Render(HDC hdc, float dt) override;
	virtual void Release() override;

private:
	void		SpawnTimer(float dt);

	void		SpawnMonster();

	void		ScorePerTime(float dt);
public:
	int			GetLevel() { return m_Level; }
	void		SetLevel(int level) { m_Level = level; }

	int			GetScore() { return m_Score; }
	void		SetScore(int score) { m_Score = score; }

	float		GetEnemySpeed() { return m_EnemySpeed; }
	void		SetEnemySpeed(float speed) { m_EnemySpeed = speed; }
public:
	void		RegisterEnemy(Enemy* enemy);

	void		DeleteEnemy();

	void		DeleteAll();

	bool		IsEnemyCol(Character* character);
private:
	std::vector<Enemy*> m_EnemyList;

	std::vector<LPCTSTR> m_ImageFilePath;

private:
	int			m_Score;

	float		m_ScoreTimer;

private:
	float		m_EnemySpeed;

private:
	int			m_Level;

	float		m_CurrentDT;
	float		m_SpawnDuration;
};

