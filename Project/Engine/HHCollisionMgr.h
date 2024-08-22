#pragma once
#include "singleton.h"

class HHCollider2D;

union COLLIDER_ID
{
	struct
	{
		DWORD LeftID;
		DWORD RightID;
	};
	ULONGLONG ID;
};

class HHCollisionMgr :
	public HHSingleton<HHCollisionMgr>
{
	SINGLE(HHCollisionMgr);
public:
	void Tick();

	void CollisionCheck(UINT _Layer1, UINT _Layer2);
	void CollisionCheckClear() { memset(m_Matrix, 0, sizeof(UINT) * MAX_LAYER); }

private:
	void CollisionBetweenLayer(UINT _Left, UINT _Right);
	bool IsCollision(HHCollider2D* _Left, HHCollider2D* _Right);

	UINT					m_Matrix[MAX_LAYER];
	map<ULONGLONG, bool>	m_mapCollisionInfo;

};
