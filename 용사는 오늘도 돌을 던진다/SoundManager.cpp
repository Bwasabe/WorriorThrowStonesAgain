#include "SoundManager.h"
#include "console.h"
SoundManager::SoundManager()
{
}

SoundManager::~SoundManager()
{
}

MCI_OPEN_PARMS Openbgm;

// 플레이하는 용도
MCI_PLAY_PARMS Playbgm;

UINT dwID1;

void SoundManager::PlayingBGM()
{
	Openbgm.lpstrElementName = L"funkysuspense.mp3";
	Openbgm.lpstrDeviceType = L"mpegvideo";

	mciSendCommand(0, MCI_OPEN, MCI_OPEN_TYPE | MCI_OPEN_ELEMENT, (DWORD)(LPVOID)&Openbgm);
	dwID1 = Openbgm.wDeviceID;
	mciSendCommand(dwID1, MCI_PLAY, MCI_DGV_PLAY_REPEAT, (DWORD)(LPVOID)&Playbgm);
}

MCI_OPEN_PARMS OpenThrow;

// 플레이하는 용도
MCI_PLAY_PARMS PlayThrowEffect;

UINT dwID2;

void SoundManager::PlayerThrowSound()
{
	mciSendCommand(dwID2, MCI_CLOSE, 0, NULL);
	mciSendCommand(dwID2, MCI_SEEK, MCI_SEEK_TO_START, (DWORD)(LPVOID)&PlayThrowEffect);

	OpenThrow.lpstrElementName = L"zapsplat_foley_wood_bambo_swoosh_through_air_001.mp3";
	OpenThrow.lpstrDeviceType = L"mpegvideo";

	mciSendCommand(0, MCI_OPEN, MCI_OPEN_TYPE | MCI_OPEN_ELEMENT, (DWORD)(LPVOID)&OpenThrow);
	dwID2 = OpenThrow.wDeviceID;
	mciSendCommand(dwID2, MCI_PLAY, MCI_NOTIFY, (DWORD)(LPVOID)&PlayThrowEffect);
}

MCI_OPEN_PARMS OpenEnemyHit;

// 플레이하는 용도
MCI_PLAY_PARMS PlayEnemyHit;

UINT dwID3;

void SoundManager::EnemyHitSound()
{
	mciSendCommand(dwID3, MCI_CLOSE, 0, NULL);
	mciSendCommand(dwID3, MCI_SEEK, MCI_SEEK_TO_START, (DWORD)(LPVOID)&PlayEnemyHit);

	OpenEnemyHit.lpstrElementName = L"impact_stone_rock_hit_floor.mp3";
	OpenEnemyHit.lpstrDeviceType = L"mpegvideo";

	mciSendCommand(0, MCI_OPEN, MCI_OPEN_TYPE | MCI_OPEN_ELEMENT, (DWORD)(LPVOID)&OpenEnemyHit);
	dwID3 = OpenEnemyHit.wDeviceID;
	mciSendCommand(dwID3, MCI_PLAY, MCI_NOTIFY, (DWORD)(LPVOID)&PlayEnemyHit);
}
