////�� ������ ������ �������� �����������, 
////���۱��� �ִ� �̹����� ���� ���� �ֽ��ϴ�.
//
//#include "Player.h"
//#include "global.h"
//#include "ColManager.h"
//#include "Bullet.h"
//#include "BInput.h"
//#include "Background.h"
//
//#include "resource.h"
//using namespace std;
//
//int main() {
//	srand((UINT)time(NULL));
//	HideCursor();
//	NoScrollBarFullScreen();
//
//	vector<LPCTSTR> playerImageVec = {
//	TEXT("Sprites/enemy_knight_4_idle_1.bmp"),
//	TEXT("Sprites/enemy_knight_4_idle_2.bmp"),
//	TEXT("Sprites/enemy_knight_4_idle_3.bmp"),
//	TEXT("Sprites/enemy_knight_4_idle_4.bmp")
//	};
//
//
//
//
//	//vector<LPCTSTR> backgroundVec = {
//	//	TEXT("Sprites/TX Tileset Grass.bmp")
//	//};
//
//	//Background background({ 0,0 }, backgroundVec, 1);
//
//	vector<LPCTSTR> stoneImageVec = {
//		TEXT("Sprites/Stone.bmp")
//	};
//
//	//Character testChar({100,100}, backgroundVec, 1, 10, 0, 0, 0, TAG::ENEMY);
//
//	vector<LPCTSTR> enemyImageVec = {
//		TEXT("Sprites/evil_102_idle_1.bmp"),
//		TEXT("Sprites/evil_102_idle_2.bmp"),
//		TEXT("Sprites/evil_102_idle_3.bmp"),
//		TEXT("Sprites/evil_102_idle_4.bmp")
//	};
//
//	BEngine basicEngine;
//	RECT rect;
//	GetClientRect(basicEngine.GetWndHandle(), &rect);
//	Player player({ rect.right / 2,rect.bottom / 2 }, playerImageVec, 1.5, 400, 10, 10, 10, 0.3f, TAG::DEFAULT);
//
//	player.PlayerInit(0.5f, KEYSTATE::KEY_PUSH, stoneImageVec);
//
//	//basicEngine.RegisterObject(&background);
//
//	basicEngine.RegisterSpawnManager(enemyImageVec, 100.0f);
//	basicEngine.RegisterPlayer(&player);
//	basicEngine.RegisterObject(&player);
//
//	basicEngine.m_SoundManager->PlayingBGM();
//	_getch();
//
//}