#include "SceneManager.h"

SceneManager::SceneManager()
	: m_CameraShakeDuration(0.1)
	, m_IsCameraShake(false)
	, m_CameraShakeStrength{}
	, m_CameraShakeTimer(0)
{
}

SceneManager::~SceneManager()
{
}

void SceneManager::Init()
{
	for (size_t i = 0; i < m_MonoList.size(); ++i) {
		m_MonoList[i]->Init();
	}
}

void SceneManager::Update(float dt)
{
	CheckCameraShake(dt);
	for (size_t i = 0; i < m_MonoList.size(); ++i) {
		m_MonoList[i]->Update(dt);
	}
}

void SceneManager::Render(HDC hdc, float dt)
{
	for (size_t i = 0; i < m_MonoList.size(); ++i) {
		m_MonoList[i]->Render(hdc, dt);
	}
}

void SceneManager::Release()
{
	for (size_t i = 0; i < m_MonoList.size(); ++i) {
		m_MonoList[i]->Release();
	}
}

void SceneManager::RegisterObject(Monobehaviour* obj)
{
	m_MonoList.push_back(obj);
}

void SceneManager::DeleteObject(Monobehaviour* obj)
{
	m_MonoList.erase(m_MonoList.begin() + obj->GetID());
	for (UINT i = 0; i < m_MonoList.size(); ++i) {
		m_MonoList[i]->SetId(i);
	}
}

void SceneManager::CameraShake(POINT strength)
{
	for (UINT i = 0; i < m_MonoList.size(); ++i) {
		Object* o = dynamic_cast<Object*>(m_MonoList[i]);

		m_CameraShakeStrength = strength;
		if (o != nullptr) {
			o->SetPos(o->GetPos() + strength);
		}
	}
}

void SceneManager::CheckCameraShake(float dt)
{
	if (!m_IsCameraShake)return;

	m_CameraShakeTimer += dt;

	if (m_CameraShakeTimer >= m_CameraShakeDuration) {
		m_IsCameraShake = false;
		m_CameraShakeTimer = 0.0f;
		CameraShake({ -m_CameraShakeStrength.x ,-m_CameraShakeStrength.y });
	}
}


