#pragma once

#include "../ImaseLib/TaskSystem.h"

class CollisionManager
{
private:

	// タスクシステムへのポインタ
	Imase::TaskSystem* m_system;

public:

	// 更新
	void Update();

};
