#include "Start.h"
#include "global.h"

Start::Start()
	: m_IsStart(false)
{
}

Start::~Start()
{
}

void Start::Init()
{
}

void Start::Update(float dt)
{
}

void Start::Render(HDC hdc, float dt)
{
	RECT rect;
	GetClientRect(g_pEngine->GetWndHandle(), &rect);

	//RECT boxRect{ 100, 50, 100,400};

	//Rectangle(hdc, boxRect.left, boxRect.top, boxRect.right, boxRect.bottom);

	FillRect(hdc, &rect, (HBRUSH)GetStockObject(WHITE_BRUSH));

	int mode = SetBkMode(hdc, TRANSPARENT);

	WCHAR str[128];

	wsprintf(str, TEXT("좌클릭을 누르면 시작합니다"));
	TextOut(hdc, rect.right/2 - 170, rect.bottom/2 + 100, str, wcslen(str));

	wsprintf(str, TEXT("조작방법 : wasd로 움직이고 마우스 좌클릭으로 공격을 날려 적들을 죽여버리세요!"));
	TextOut(hdc, rect.right / 2 - 200, rect.bottom / 2 - 400, str, wcslen(str));

	wsprintf(str, TEXT("아래에서 각종 스킬에 대한 정보를 확인하세요"));
	TextOut(hdc, rect.right / 2 - 200, rect.bottom / 2 - 300, str, wcslen(str));

	wsprintf(str, TEXT("SpaceBar : 순간 가속(쿨타임 : 3초)"));
	TextOut(hdc, rect.right / 2 - 170, rect.bottom / 2 - 250, str, wcslen(str));

	wsprintf(str, TEXT("효과 : 0.5초동안 이동속도가 2배로 빨라집니다"));
	TextOut(hdc, rect.right / 2 - 170, rect.bottom / 2 - 230, str, wcslen(str));

	wsprintf(str, TEXT("E : 돌덩이 세마리(쿨타임 : 10초)"));
	TextOut(hdc, rect.right / 2 - 170, rect.bottom / 2 - 180, str, wcslen(str));

	wsprintf(str, TEXT("효과 : 3초동안 총알이 세갈래로 나갑니다"));
	TextOut(hdc, rect.right / 2 - 170, rect.bottom / 2 - 160, str, wcslen(str));

	/*WCHAR str3[128];

	wsprintf(str, TEXT("SpaceBar : 대쉬(쿨타임 : 3초)"));
	TextOut(hdc, rect.right / 2 - 170, rect.bottom / 2 - 300, str, wcslen(str));*/


	SetBkMode(hdc, mode);
}

void Start::Release()
{
}
