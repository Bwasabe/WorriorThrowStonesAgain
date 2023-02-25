#include "EnemySpawnManager.h"
#include "global.h"

EnemySpawnManager::EnemySpawnManager()
	: m_SpawnDuration(0)
	, m_CurrentDT(0)
	, m_Level(1)
	, m_Score(0)
	, m_ScoreTimer(0)
	, m_EnemySpeed(0.0f)

{
}

EnemySpawnManager::EnemySpawnManager(std::vector<LPCTSTR> imageFilepath ,float spawnDuration)
	: m_SpawnDuration(spawnDuration)
	, m_ImageFilePath(imageFilepath)
	, m_CurrentDT(0)
	, m_Level(1)
	, m_Score(0)
	, m_ScoreTimer(0)
	, m_EnemySpeed(50.0f)
{
}

EnemySpawnManager::~EnemySpawnManager()
{
}

void EnemySpawnManager::Init()
{
}

void EnemySpawnManager::Update(float dt)
{
	SpawnTimer(dt);
	DeleteEnemy();
	ScorePerTime(dt);
}

void EnemySpawnManager::Render(HDC hdc, float dt)
{
	

	int mode = SetBkMode(hdc, TRANSPARENT);

	WCHAR str[128];

	wsprintf(str, TEXT("score : %d"), m_Score);
	TextOut(hdc, 90, 70, str, wcslen(str));

	SetBkMode(hdc, mode);

}

void EnemySpawnManager::Release()
{
}

void EnemySpawnManager::SpawnTimer(float dt)
{
	m_CurrentDT += dt;

	if (m_CurrentDT >= m_SpawnDuration) {
		m_CurrentDT = 0;

		SpawnMonster();
	}
}

void EnemySpawnManager::SpawnMonster()
{
	RECT rect;
	GetClientRect(g_pEngine->GetWndHandle(), &rect);

	int random = rand() % 4;

	POINT spawnPos{0,0};

	RECT nonMonsterZone = g_pEngine->m_Player->GetNonMonsterZone();
	
	switch (random)
	{
	case 0:
		spawnPos.x = rand() % nonMonsterZone.left;
		spawnPos.y = rand() % nonMonsterZone.bottom;
		break;
	case 1:
		spawnPos.x = rand() % (rect.right - nonMonsterZone.left) + nonMonsterZone.left;
		spawnPos.y = rand() % nonMonsterZone.top;
		break;
	case 2:
		spawnPos.x = rand() % nonMonsterZone.right;
		spawnPos.y = rand() % (rect.bottom - nonMonsterZone.bottom) + nonMonsterZone.bottom;
		break;
	case 3:
		spawnPos.x = rand() % (rect.right - nonMonsterZone.right) + nonMonsterZone.right;
		break;
	}

	// 적의 약간 속도의 오차를 만들어줌
	float randomSpeed = rand() % 100 * 0.01f * m_EnemySpeed;
	Enemy* enemy = new Enemy(spawnPos, m_ImageFilePath, 1.5f, 40, 10, 0, 200.0f + randomSpeed , 0.3f,TAG::ENEMY, g_pEngine->m_Player);

	g_pEngine->RegisterObject(enemy);

	RegisterEnemy(enemy);
}

void EnemySpawnManager::ScorePerTime(float dt)
{
	m_ScoreTimer += dt;

	if (m_ScoreTimer >= 0.1f) {
		m_Score++;
		m_ScoreTimer = 0.0f;
	}
}

void EnemySpawnManager::RegisterEnemy(Enemy* enemy)
{
	m_EnemyList.push_back(enemy);
}

void EnemySpawnManager::DeleteEnemy()
{
	for (UINT i = 0; i < m_EnemyList.size(); ++i) {
		// 에네미의 GetCol이 true일 경우 데미지 주고 false, Dead일경우에 딜리트
		//std::cout << m_EnemyList[i]->GetIsDead();
		if (m_EnemyList[i]->GetIsDead()) {
			g_pEngine->m_SceneManager->DeleteObject(m_EnemyList[i]);

			delete m_EnemyList[i];
			m_EnemyList.erase(m_EnemyList.begin() + i);
		}
	}
}

void EnemySpawnManager::DeleteAll()
{
	for (UINT i = 0; i < m_EnemyList.size(); ++i) {
		g_pEngine->m_SceneManager->DeleteObject(m_EnemyList[i]);

		delete m_EnemyList[i];
		m_EnemyList.erase(m_EnemyList.begin() + i);
	}
}

bool EnemySpawnManager::IsEnemyCol(Character* character)
{
	bool isHit(false);
	RECT rt;
	for (UINT i = 0; i < m_EnemyList.size(); ++i) {
		if (IntersectRect(&rt, character->GetCol(), m_EnemyList[i]->GetCol()))
		{
			m_EnemyList[i]->Damage(character->GetAtk());
			character->Damage(m_EnemyList[i]->GetAtk());

			isHit = true;
		}
	}
	return isHit;
}

// 불렛하고 에네미하고 맞았는지 체크
