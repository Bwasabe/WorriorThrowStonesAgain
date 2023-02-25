#ifndef BIMAGE_H
#define BIMAGE_H

#include "console.h"
#include "Enum.h"

class BImage
{
public:
	BImage();
	BImage(LPCTSTR strLoadFile);
	~BImage();

private:
	HBITMAP			m_BitmapHandle;			//��Ʈ�� �ڵ�
	BITMAP			m_BitmapInfo;			//��Ʈ�� ���� ���� ����
	static DWORD	m_TransparentColor;		//����ó�� �� ���󺯼�

public:
	bool			Load(LPCTSTR strLoadFile);
	bool			Load(HBITMAP bitmapHandle);
	void			Release();

public:
	void			DrawBitmap(HDC hdc, int x, int y, int width = 0, int height = 0, int alpha = 255, IMAGE_TYPE type = IMAGE_TYPE::MAGENTA_IMAGE );

public:
	void			drawBitmapByCropping(HDC hdc, int x, int y, int width, int height,
		int sx, int sy, int swidth, int sheight, int alpha, IMAGE_TYPE type);

public:
	bool			IsEmpty();
	HBITMAP			GetBitmapHandle();
	const BITMAP&	GetBitmapInfo();

public:
	static void		SetTransParentColor(DWORD color);
	static DWORD	GetTransparentColor();

};



#endif // !BIMAGE_H