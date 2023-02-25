#pragma once
#include "SceneManager.h"
#include "ColManager.h"
#include "EnemySpawnManager.h"
#include "Player.h"
#include "SoundManager.h"

class BEngine : public Monobehaviour
{
public:
	BEngine();
	~BEngine();

public:
	HWND		GetWndHandle() { return m_hWnd; }
	HINSTANCE	GetInstanceHandle() { return m_hInstance; }

public:
	// Monobehaviour을(를) 통해 상속됨
	virtual void Init() override;
	virtual void Update(float dt) override;
	virtual void Render(HDC hdc, float dt) override;
	virtual void Release() override;

public:
	void		MainLoop();
private:
	void		RenderingFPS(UINT fps, float dt);

public:
	void		RegisterObject(Monobehaviour* obj);

	void		RegisterPlayer(Player* player) { m_Player = player; }

	void		RegisterSpawnManager(std::vector<LPCTSTR>imageFilePath, float spawnDuration);
public:
	float		GetTimeScale() { return m_TimeScale; }
	void		SetTimeScale(float timeScale) { m_TimeScale = timeScale; }

	bool		GetIsStop() { return m_IsStop; }
	void		SetIsStop(bool isStop) { m_IsStop = isStop; }

private:
	LARGE_INTEGER		m_liPrevCount;
	LARGE_INTEGER		m_liCurcount;
	LARGE_INTEGER		m_liFrequency;

	float				m_fDT;			//프레임간 시간값(FrameDeltaTime)
	float				m_fAcc;			//1초 체크를 위한 누적 시간
	UINT				m_iCallCount;	//함수 호출 횟수 체크
	UINT				m_iFPS;

private:
	HWND				m_hWnd;
	HINSTANCE			m_hInstance;

private:
	float				m_TimeScale;

	bool				m_IsStop;
public:
	SceneManager*		m_SceneManager;
	ColManager*			m_ColManager;
	EnemySpawnManager*	m_SpawnManager;

	SoundManager*		m_SoundManager;
	Player*				m_Player;
};
