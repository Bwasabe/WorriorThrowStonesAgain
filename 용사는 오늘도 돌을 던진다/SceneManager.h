#pragma once
#include "BObject.h"

class SceneManager : public Monobehaviour
{
public:
	SceneManager();
	~SceneManager();

public:
	// Monobehaviour을(를) 통해 상속됨
	virtual void Init() override;
	virtual void Update(float dt) override;
	virtual void Render(HDC hdc, float dt) override;
	virtual void Release() override;

public:
	void		RegisterObject(Monobehaviour* obj);
	void		DeleteObject(Monobehaviour* obj);
	
	void		CameraShake(POINT strength);

	void		CheckCameraShake(float dt);
public:
	int			GetListSize() { return m_MonoList.size(); }
	
	bool		GetIsCameraShake() { return m_IsCameraShake; }
	void		SetIsCameraShake(bool isCameraShake) { m_IsCameraShake = isCameraShake; }

	float		GetCameraShakeDuration() { return m_CameraShakeDuration; }
	void		SetCameraShakeDuration(float duration) { m_CameraShakeDuration = duration; }
private:
	POINT		m_CameraShakeStrength;

	float		m_CameraShakeDuration;
	float		m_CameraShakeTimer;

	bool		m_IsCameraShake;
private:
	std::vector<Monobehaviour*>		m_MonoList;


};


