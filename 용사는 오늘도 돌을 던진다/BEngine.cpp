#include "BEngine.h"
#include <iostream>
BEngine* g_pEngine = nullptr;

BEngine::BEngine()
	: m_liPrevCount{}
	, m_liCurcount{}
	, m_liFrequency{}
	, m_fDT(0.0f)
	, m_fAcc(0.0f)
	, m_iCallCount(0)
	, m_iFPS(0)
	, m_TimeScale(1.0f)
	, m_IsStop(false)
{
	g_pEngine = this;
	m_SceneManager = new SceneManager;
	m_ColManager = new ColManager;

	m_SoundManager = new SoundManager;
	m_hWnd = GetConsoleWindow();
	m_hInstance = (HINSTANCE)GetWindowLong(m_hWnd, GWL_HINSTANCE);

	//현재 카운트
	QueryPerformanceCounter(&m_liPrevCount);

	//초당 카운트 횟수
	QueryPerformanceFrequency(&m_liFrequency);
}

BEngine::~BEngine()
{
}

void BEngine::Init()
{
	m_SceneManager->Init();
}

void BEngine::Update(float dt)
{
	if (m_SceneManager) {
		m_SceneManager->Update(dt);
	}

	if (m_SpawnManager) {
		m_SpawnManager->Update(dt);
	}
}

void BEngine::Render(HDC hdc, float dt)
{
	HDC hMemdc;
	RECT windowRect;
	HBITMAP hBitmap;

	GetClientRect(m_hWnd, &windowRect);

	hMemdc = CreateCompatibleDC(hdc);

	hBitmap = CreateCompatibleBitmap(hdc, windowRect.right, windowRect.bottom);

	HBITMAP hOldBitmap = (HBITMAP)SelectObject(hMemdc, hBitmap);

	FillRect(hMemdc, &windowRect, (HBRUSH)GetStockObject(WHITE_BRUSH));

	if (m_SceneManager)m_SceneManager->Render(hMemdc, dt);

	if (m_SpawnManager)m_SpawnManager->Render(hMemdc, dt);

	BitBlt(hdc, 0, 0, windowRect.right, windowRect.bottom, hMemdc, 0, 0, SRCCOPY);

	SelectObject(hMemdc, hOldBitmap);
	DeleteObject(hBitmap);
	DeleteDC(hMemdc);

}

void BEngine::Release()
{
	SAFE_DELETE(m_SceneManager);
	SAFE_DELETE(m_ColManager);
	SAFE_DELETE(m_SpawnManager);
	SAFE_DELETE(m_SoundManager);
}

void BEngine::MainLoop()
{
	QueryPerformanceCounter(&m_liCurcount);
	m_fDT = (float)(m_liCurcount.QuadPart - m_liPrevCount.QuadPart) / (float)(m_liFrequency.QuadPart);

	m_liPrevCount = m_liCurcount;

	m_iCallCount++;

	m_fAcc += m_fDT;

	if (m_fAcc >= 1.0f) {
		m_iFPS = m_iCallCount;
		m_iCallCount = 0;
		m_fAcc = 0.0f;

		RenderingFPS(m_iFPS, m_fDT);
	}

	HDC hdc = GetDC(m_hWnd);

	Update(m_fDT * m_TimeScale);

	Render(hdc, m_fDT * m_TimeScale);

	ReleaseDC(m_hWnd, hdc);
}

void BEngine::RenderingFPS(UINT fps, float dt)
{
	static TCHAR szTemp[256];
	swprintf_s(szTemp, TEXT("게임 속도 FPS: %d, 프레임간 간격: %f"), fps, dt);
	//wsprintf(szTemp, TEXT("게임속도 FPS : %d"), frameCount);
	SetConsoleTitleW(szTemp);
}

void BEngine::RegisterObject(Monobehaviour* obj)
{
	obj->Init();
	obj->SetId(m_SceneManager->GetListSize());
	m_SceneManager->RegisterObject(obj);
}

void BEngine::RegisterSpawnManager(std::vector<LPCTSTR> imageFilePath, float spawnDuration)
{
	m_SpawnManager = new EnemySpawnManager(imageFilePath, spawnDuration);
}
