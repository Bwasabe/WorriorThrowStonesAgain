#pragma once

#include "Character.h"

class ColManager
{
public:
	ColManager();
	~ColManager();


//public:
//	// Monobehaviour을(를) 통해 상속됨
//	virtual void Init() override;
//	virtual void Update(float dt) override;
//	virtual void Render(HDC hdc, float dt) override;
//	virtual void Release() override;

public:
	void	RegisterObject(Character* obj);
	bool	IsCollision(Character* targetObject, TAG hitTags);

private:
	std::vector<Character*> m_ColObjList;




};
