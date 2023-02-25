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

	wsprintf(str, TEXT("��Ŭ���� ������ �����մϴ�"));
	TextOut(hdc, rect.right/2 - 170, rect.bottom/2 + 100, str, wcslen(str));

	wsprintf(str, TEXT("���۹�� : wasd�� �����̰� ���콺 ��Ŭ������ ������ ���� ������ �׿���������!"));
	TextOut(hdc, rect.right / 2 - 200, rect.bottom / 2 - 400, str, wcslen(str));

	wsprintf(str, TEXT("�Ʒ����� ���� ��ų�� ���� ������ Ȯ���ϼ���"));
	TextOut(hdc, rect.right / 2 - 200, rect.bottom / 2 - 300, str, wcslen(str));

	wsprintf(str, TEXT("SpaceBar : ���� ����(��Ÿ�� : 3��)"));
	TextOut(hdc, rect.right / 2 - 170, rect.bottom / 2 - 250, str, wcslen(str));

	wsprintf(str, TEXT("ȿ�� : 0.5�ʵ��� �̵��ӵ��� 2��� �������ϴ�"));
	TextOut(hdc, rect.right / 2 - 170, rect.bottom / 2 - 230, str, wcslen(str));

	wsprintf(str, TEXT("E : ������ ������(��Ÿ�� : 10��)"));
	TextOut(hdc, rect.right / 2 - 170, rect.bottom / 2 - 180, str, wcslen(str));

	wsprintf(str, TEXT("ȿ�� : 3�ʵ��� �Ѿ��� �������� �����ϴ�"));
	TextOut(hdc, rect.right / 2 - 170, rect.bottom / 2 - 160, str, wcslen(str));

	/*WCHAR str3[128];

	wsprintf(str, TEXT("SpaceBar : �뽬(��Ÿ�� : 3��)"));
	TextOut(hdc, rect.right / 2 - 170, rect.bottom / 2 - 300, str, wcslen(str));*/


	SetBkMode(hdc, mode);
}

void Start::Release()
{
}
