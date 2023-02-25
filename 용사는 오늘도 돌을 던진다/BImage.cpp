#include "BImage.h"

DWORD BImage::m_TransparentColor = RGB(255, 0, 255);

BImage::BImage() : m_BitmapHandle(nullptr) {
	memset(&m_BitmapInfo, 0, sizeof(m_BitmapInfo));
}

BImage::BImage(LPCTSTR strLoadfile) : BImage() {
	this->Load(strLoadfile);
}

BImage::~BImage() {
	if (!this->IsEmpty()) {
		DeleteObject(m_BitmapHandle);
	}
}

bool BImage::IsEmpty() {
	return m_BitmapHandle == nullptr;
}

bool BImage::Load(LPCTSTR strLoadFile) {
	m_BitmapHandle = (HBITMAP)LoadImage(GetModuleHandle(nullptr),
		strLoadFile, IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION | LR_LOADFROMFILE | LR_DEFAULTSIZE);

	if (this->IsEmpty())return false;

	GetObject(m_BitmapHandle, sizeof(m_BitmapInfo), &m_BitmapInfo);

	return true;
}

bool BImage::Load(HBITMAP bitmapHandle) {
	if (bitmapHandle == nullptr)return false;

	if (this->IsEmpty()) {
		DeleteObject(m_BitmapHandle);
	}
	m_BitmapHandle = bitmapHandle;

	GetObject(m_BitmapHandle, sizeof(m_BitmapInfo), &m_BitmapInfo);

	return true;
}

void BImage::Release() {
	if (!this->IsEmpty()) {
		DeleteObject(m_BitmapHandle);
	}
}

HBITMAP BImage::GetBitmapHandle() {
	return m_BitmapHandle;
}

const BITMAP& BImage::GetBitmapInfo() {
	return m_BitmapInfo;
}

void BImage::DrawBitmap(HDC hdc, int x, int y, int width, int height, int alpha, IMAGE_TYPE type) {
	if (width == 0)
		width = m_BitmapInfo.bmWidth;
	if (height == 0)
		height = m_BitmapInfo.bmHeight;

	this->drawBitmapByCropping(hdc, x, y, width, height, 0, 0, m_BitmapInfo.bmWidth, m_BitmapInfo.bmHeight, alpha, type);
}

void BImage::drawBitmapByCropping(HDC hdc, int x, int y, int width, int height, int sx, int sy, int swidth, int sheight, int alpha, IMAGE_TYPE type)
{
	HDC hMemDC;
	hMemDC = CreateCompatibleDC(hdc);

	HBITMAP hOldBitmap = (HBITMAP)SelectObject(hMemDC, m_BitmapHandle);

	switch (type)
	{
	case IMAGE_TYPE::MAGENTA_IMAGE:
	{
		GdiTransparentBlt(hdc, x, y, width, height, hMemDC, sx, sy, swidth, sheight, GetTransparentColor());
	}
		break;
	case IMAGE_TYPE::TRANSPARENT_IMAGE:
	{
		BLENDFUNCTION bf;
		bf.SourceConstantAlpha = alpha;
		bf.BlendOp = AC_SRC_OVER;
		bf.BlendFlags = 0;
		bf.AlphaFormat = 0;

		GdiAlphaBlend(hdc, x, y, width, height, hMemDC, sx, sy, swidth, sheight, bf);
	}
		break;
	default:
		break;
	}


	SelectObject(hMemDC, hOldBitmap);

	DeleteDC(hMemDC);
}

void BImage::SetTransParentColor(DWORD color) {
	m_TransparentColor = color;
}

DWORD BImage::GetTransparentColor() {
	return m_TransparentColor;
}
