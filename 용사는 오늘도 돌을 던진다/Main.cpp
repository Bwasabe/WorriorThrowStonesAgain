//이 게임은 교육용 목적으로 만들어졌으며, 
//저작권이 있는 이미지가 있을 수도 있습니다.

#include "Player.h"
#include "global.h"
#include "ColManager.h"
#include "Bullet.h"
#include "BInput.h"
#include "Background.h"
#include "Start.h"
using namespace std;

int main() {
	srand((UINT)time(NULL));
	HideCursor();
	NoScrollBarFullScreen();


	BEngine basicEngine;
	
	Start start;

	TInputState startInput;

	basicEngine.RegisterObject(&start);
	while (true) {
		BInput::GetInstance()->KeyCheck(VK_LBUTTON, startInput.dwMouseLB);
		basicEngine.MainLoop();
		if (startInput.dwMouseLB == KEYSTATE::KEY_PUSH) {
			break;
		}
	}
	basicEngine.m_SceneManager->DeleteObject(&start);

	vector<LPCTSTR> stoneImageVec = {
		TEXT("Sprites/Stone.bmp")
	};

	vector<LPCTSTR> enemyImageVec = {
		TEXT("Sprites/evil_102_idle_1.bmp"),
		TEXT("Sprites/evil_102_idle_2.bmp"),
		TEXT("Sprites/evil_102_idle_3.bmp"),
		TEXT("Sprites/evil_102_idle_4.bmp")
	};


	vector<LPCTSTR> playerImageVec = {
		TEXT("Sprites/enemy_knight_4_idle_1.bmp"),
		TEXT("Sprites/enemy_knight_4_idle_2.bmp"),
		TEXT("Sprites/enemy_knight_4_idle_3.bmp"),
		TEXT("Sprites/enemy_knight_4_idle_4.bmp")
	};



	RECT rect;
	GetClientRect(basicEngine.GetWndHandle(), &rect);
	Player player({ rect.right / 2,rect.bottom / 2 }, playerImageVec, 1.5, 400, 10, 10, 10, 0.3f, TAG::DEFAULT);

	player.PlayerInit(0.5f, KEYSTATE::KEY_PUSH, stoneImageVec);

	//basicEngine.RegisterObject(&background);

	basicEngine.RegisterSpawnManager(enemyImageVec, 1.0f);
	basicEngine.RegisterPlayer(&player);
	basicEngine.RegisterObject(&player);


	basicEngine.m_SoundManager->PlayingBGM();
	while (true) {
		basicEngine.MainLoop();

		if (basicEngine.m_Player->GetIsDead()) {
			break;
		}

		//if (GetAsyncKeyState('H') & 0x8000 || GetAsyncKeyState('h') & 0x8000) {
		//	static int randomX = 0;
		//	float value = randomX * Deg2Rad;
		//	//TODO: 중앙 위치를 가져와서 밑에 오브젝트의 pos를 설정해 줄 것
		//	//POINT playerPos;
		//	//GetClientRect(g_pEngine->GetWndHandle(),&rect);

		//	Character* testObj = new Character({ (int)(cos(value) * 300) + player.GetPos().x/*rect.right / 2*/,(int)(sin(value) * 300) + player.GetPos().y/*rect.bottom / 2*/ }, stoneImageVec, 0.5f, 10, 10, 0, 0, 0, TAG::ENEMY);
		//	basicEngine.RegisterObject(testObj);
		//	basicEngine.m_ColManager->RegisterObject(testObj);
		//	randomX += 5;
		//	randomX %= 361;

		//}
	}

	system("cls");
	RECT windowRect = {0,0,0,0};
	HDC hdc = GetDC(basicEngine.GetWndHandle());


	FillRect(hdc, &windowRect, (HBRUSH)GetStockObject(WHITE_BRUSH));


	Object endPlayer({0,0}, playerImageVec, 1, 100);

	endPlayer.Update(0.1);

	_getch();
}