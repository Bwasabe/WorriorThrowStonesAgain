#include "ColManager.h"
#include "console.h"

ColManager::ColManager()
{
}

ColManager::~ColManager()
{
}

//void ColManager::Init()
//{
//}
//
//void ColManager::Update(float dt)
//{
//}
//
//void ColManager::Release()
//{
//}

void ColManager::RegisterObject(Character* obj)
{
	m_ColObjList.push_back(obj);
}

bool ColManager::IsCollision(Character* targetObject, TAG hitTags)
{
	//bool isHit(false);
	RECT tempRect;
	RECT* targetRect = targetObject->GetCol();
	for (size_t i = 0; i < m_ColObjList.size(); ++i) {
		RECT* enemyRect = m_ColObjList[i]->GetCol();
		if ((int)(m_ColObjList[i]->GetTag() & hitTags) != 0 && IntersectRect(&tempRect, enemyRect, targetRect) ) {
			//m_ColObjList[i]->Attack(&targetObject);
			return true;
		}
	}
	return false;
}

//void ColManager::Render(HDC hdc, float dt)
//{
//}
