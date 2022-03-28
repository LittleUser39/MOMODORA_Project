#pragma once
#include "CGameObject.h"
class CBossWarp : public CGameObject
{
	public:
		CBossWarp();
		~CBossWarp();

		virtual CBossWarp* Clone();

		virtual void update();
		virtual void render();

		virtual void OnCollisionEnter(CCollider* other);
};




