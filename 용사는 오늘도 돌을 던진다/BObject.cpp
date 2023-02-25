#include "BObject.h"

Object::Object()
	: m_Scale(1.0f)
	, m_Pos{}
	, m_Size{}
	, m_ImageFilePath({})
	, m_AnimSpd(0)
	, m_AnimCount(0)
	, m_AnimTimer(0.0f)
{
}

Object::Object(POINT pos, std::vector<LPCTSTR> imageFilePath, float scale, float animSpeed)
	: m_Scale(scale)
	, m_Size{}
	, m_Pos(pos)
	, m_ImageFilePath(imageFilePath)
	, m_AnimSpd(animSpeed)
	, m_AnimCount(0)
	, m_AnimTimer(0.0f)
{
}


Object::~Object()
{

}

void Object::Init()
{
	for (size_t i = 0; i < m_ImageFilePath.size(); ++i) {
		m_Images.push_back(BImage(m_ImageFilePath[i]));
	}
	for (size_t i = 0; i < m_ImageFilePath.size(); ++i) {
		m_Images[i].Load(m_ImageFilePath[i]);
	}
	m_Size.width = m_Images[0].GetBitmapInfo().bmWidth * m_Scale;
	m_Size.height = m_Images[0].GetBitmapInfo().bmHeight * m_Scale;

}

void Object::Render(HDC hdc, float dt)
{
	if (m_ImageFilePath.empty())return;
	//m_Images[0].DrawBitmap(hdc, m_Pos.x, m_Pos.y, m_Size.width, m_Size.height);

	m_AnimTimer += dt;
	if (m_AnimTimer >= m_AnimSpd) {
		m_AnimTimer = 0.0f;
		m_AnimCount = (m_AnimCount+1) % m_ImageFilePath.size();

	}
	m_Images[m_AnimCount].DrawBitmap(hdc, m_Pos.x, m_Pos.y, m_Size.width, m_Size.height, 255, IMAGE_TYPE::MAGENTA_IMAGE);

	/*for (size_t i = 0; i < m_ImageFilePath.size(); ++i) {
		m_Images[i].DrawBitmap(hdc, m_Pos.x, m_Pos.y, m_Size.width, m_Size.height, 255, IMAGE_TYPE::MAGENTA_IMAGE);
		Sleep(dt);
	}*/
}

void Object::Release() {
	for (UINT i = 0; i < m_ImageFilePath.size(); ++i) {
		m_Images[i].Release();
	}
}
