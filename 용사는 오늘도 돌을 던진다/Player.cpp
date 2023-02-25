#include "Player.h"
#include "Global.h"
#include "BInput.h"
Player::Player()
	: Character()
	, m_NextDir{}
{
}

Player::Player(POINT pos, std::vector<LPCTSTR> imageFilePath, float scale, float speed, int hp, int atk, int def, float animSpeed, TAG tag)
	: Character(pos, imageFilePath, scale, hp, atk, def, speed, animSpeed, tag)
	, m_NextDir{}
	, m_DashColTime(3.0f)
	, m_DashColTimer(3.0f)
	, m_SkillEColTime(10.0f)
	, m_SkillEColTimer(10.0f)
	, m_SkillEDuration(3.0f)
{
}

Player::~Player()
{
}

void Player::PlayerInit(float duration, KEYSTATE keyState, std::vector<LPCTSTR> luciferFilePath)
{
	m_DashDuration = duration;
	m_CurrentKeyState = keyState;
	m_LuciferFilePaths = luciferFilePath;
}

void Player::Init()
{
	Character::Init();

	m_BulletImageFilePaths = {
		TEXT("Sprites/Stone.bmp")
	};

}

void Player::Update(float dt)
{
	Character::Update(dt);

	PlayerMove(dt);

	PlayerAttack();

	BulletIsValid();

	CheckEnemyHit();

	PlayerDash(dt);

	PlayerSkillE(dt);
}



void Player::Render(HDC hdc, float dt)
{
	Character::Render(hdc, dt);


	int mode = SetBkMode(hdc, TRANSPARENT);

	WCHAR str[128];

	wsprintf(str, TEXT("순간가속 남은 쿨타임 : %d 초"), (int)ceil(m_DashColTime - m_DashColTimer));
	TextOut(hdc, 90, 90, str, wcslen(str));

	WCHAR str2[128];

	wsprintf(str2, TEXT("돌덩이 세마리 남은 쿨타임 : %d 초"), (int)ceil(m_SkillEColTime - m_SkillEColTimer));
	TextOut(hdc, 90, 130, str2, wcslen(str2));

	SetBkMode(hdc, mode);
}

void Player::Release()
{
	Character::Release();
}

void Player::Dead()
{
	Character::Dead();

	//PlayerDeath();

}

void Player::PlayerMove(float dt)
{
	m_NextDir = {0,0};
	if (GetAsyncKeyState('w') & 0x8000 || GetAsyncKeyState('W') & 0x8000) {
		m_NextDir += { 0, -(int)(m_Speed * dt) };
	}
	if (GetAsyncKeyState('s') & 0x8000 || GetAsyncKeyState('S') & 0x8000) {
		m_NextDir += { 0, (int)(m_Speed* dt) };
	}
	if (GetAsyncKeyState('d') & 0x8000 || GetAsyncKeyState('D') & 0x8000) {
		m_NextDir += { (int)(m_Speed* dt), 0 };
	}
	if (GetAsyncKeyState('a') & 0x8000 || GetAsyncKeyState('A') & 0x8000) {
		m_NextDir += { -(int)(m_Speed * dt), 0 };
	}
	m_Pos += m_NextDir;


	RECT rect;
	GetClientRect(g_pEngine->GetWndHandle(), &rect);

	if (m_Pos.x < rect.left) {
		m_Pos.x = rect.left;
	}
	if (m_Pos.x + m_Size.width > rect.right) {
		m_Pos.x = rect.right - m_Size.width;
	}
	if (m_Pos.y < rect.top) {
		m_Pos.y = rect.top;
	}
	if (m_Pos.y + m_Size.height > rect.bottom) {
		m_Pos.y = rect.bottom - m_Size.height;
	}
}

void Player::PlayerAttack()
{
	BInput::GetInstance()->KeyCheck(VK_LBUTTON, m_Input.dwMouseLB);

	if (m_Input.dwMouseLB == m_CurrentKeyState) {
		g_pEngine->m_SceneManager->SetIsCameraShake(true);
		g_pEngine->m_SceneManager->SetCameraShakeDuration(0.05f);
		g_pEngine->m_SceneManager->CameraShake({3,1/*rand()%5 + 3 , rand() % 3  + 1*/});
		g_pEngine->m_SoundManager->PlayerThrowSound();


		POINT point;
		GetCursorPos(&point);
		ScreenToClient(g_pEngine->GetWndHandle(), &point);

		float x = point.x - m_Pos.x + m_Size.width / 4;
		float y = point.y - m_Pos.y + m_Size.height / 4;

		float fAngle = atan2(y, x);
		if (m_IsSkillE) {
			for (int i = -10; i < 11; i += 10) {
				Bullet* bullet = new Bullet({ m_Pos.x + m_Size.width / 4, m_Pos.y + m_Size.height / 4 }, fAngle + (i*Deg2Rad), m_BulletImageFilePaths, 0.6f, 0, 10, 0, 500, 0, TAG::BULLET);

				g_pEngine->RegisterObject(bullet);

				m_Bullets.push_back(bullet);
			}
		}
		else {
			Bullet* bullet = new Bullet({ m_Pos.x + m_Size.width / 4, m_Pos.y + m_Size.height / 4 }, fAngle, m_BulletImageFilePaths, 0.6f, 0, 10, 0, 500, 0, TAG::BULLET);

			g_pEngine->RegisterObject(bullet);

			m_Bullets.push_back(bullet);
		}
		
	}
}

void Player::PlayerDash(float dt)
{
	BInput::GetInstance()->KeyCheck(VK_SPACE, m_Input.dwKeySpace);

	if (m_IsCanDash) {

		if (m_Input.dwKeySpace == KEYSTATE::KEY_PUSH) {
			m_DashTimer = 0.0f;
			m_DashColTimer = 0.0f;

			m_IsDash = true;
			m_IsCanDash = false;

			m_Speed = 800.0f;
		}
	}
	else if(!m_IsDash){
		m_DashColTimer += dt;

		if (m_DashColTimer >= m_DashColTime) {
			m_DashColTimer = m_DashColTime;
			m_IsCanDash = true;
		}
	}

	if (m_IsDash) {
		m_DashTimer += dt;

		if (m_DashTimer >= m_DashDuration) {
			m_DashTimer = 0.0f;

			m_IsDash = false;

			m_Speed = 400.0f;
		}
	}
}

void Player::PlayerSkillE(float dt)
{
	BInput::GetInstance()->KeyCheck(VK_TAB, m_Input.dwKeyE);
	//BInput::GetInstance()->KeyCheck('e', m_Input.dwKeyE);

	if (m_IsCanSkillE) {

		if (m_Input.dwKeyE == KEYSTATE::KEY_PUSH) {
			m_SkillETimer = 0.0f;
			m_SkillEColTimer = 0.0f;

			m_IsSkillE = true;
			m_IsCanSkillE = false;
		}
	}
	else if (!m_IsSkillE) {
		m_SkillEColTimer += dt;

		if (m_SkillEColTimer >= m_SkillEColTime) {
			m_SkillEColTimer = m_SkillEColTime;

			m_IsCanSkillE = true;
		}
	}

	if (m_IsSkillE) {
		m_SkillETimer += dt;

		if (m_SkillETimer >= m_SkillEDuration) {
			m_SkillETimer = 0.0f;

			m_IsSkillE = false;
		}
	}
}

void Player::PlayerDeath()
{
	//cls를 한 후, 
	Sleep(1000);

	RECT rect;
	GetClientRect(g_pEngine->GetWndHandle(), &rect);

	
	m_Pos = { (rect.right- m_Size.width)/2,(rect.bottom - m_Size.height)/2 };

	g_pEngine->m_SpawnManager->DeleteAll();

	DeleteAll();

	g_pEngine->MainLoop();

	g_pEngine->SetTimeScale(0);

	Object* lucifer = new Object({ m_Pos.x + m_Size.width, m_Pos.y + m_Size.height * 2 }, m_LuciferFilePaths, 1.0f, 0.8f);

}

void Player::BulletIsValid()
{
	for (UINT i = 0; i < m_Bullets.size(); ++i) {
		if (!m_Bullets[i]->IsValid() || m_Bullets[i]->GetIsDead()) {
			g_pEngine->m_SceneManager->DeleteObject(m_Bullets[i]);

			//SAFE_DELETE(m_Bullets[i]);
			delete m_Bullets[i];
			m_Bullets.erase(m_Bullets.begin() + i);
		}
	}
}

void Player::CheckEnemyHit()
{
	if (g_pEngine->m_SpawnManager->IsEnemyCol(this)) {
		//exit(0);
	}
}

void Player::DeleteAll()
{
	for (UINT i = 0; i < m_Bullets.size(); ++i) {
		g_pEngine->m_SceneManager->DeleteObject(m_Bullets[i]);
		
		delete m_Bullets[i];
		m_Bullets.erase(m_Bullets.begin() + i);
	}
}

void Player::UpdateCol()
{
	//GotoXY(236, 66);
	//std::cout << std::endl;
	m_Collision.left = m_Pos.x + m_Size.width * 0.2 + 7;
	m_Collision.right = m_Collision.left + m_Size.width * 0.4;
	m_Collision.top = m_Pos.y + m_Size.height * 0.2 + 7;
	m_Collision.bottom = m_Collision.top + m_Size.height * 0.4;

	m_NonMonsterZone = { m_Collision.left - 200 ,m_Collision.top - 200,m_Collision.right + 200, m_Collision.bottom + 200 };
	/*HDC hdc = GetDC(g_pEngine->GetWndHandle());
	Rectangle(hdc, m_Collision.left, m_Collision.top, m_Collision.right, m_Collision.bottom);*/
}
