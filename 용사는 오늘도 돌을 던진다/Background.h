#pragma once
#include "BObject.h"

class Background : public Object
{
public:
	Background();
	Background(POINT pos, std::vector<LPCTSTR> imageFilePath, float scale);
	~Background();

public:
	virtual void		Render(HDC hdc, float dt) override;

};
