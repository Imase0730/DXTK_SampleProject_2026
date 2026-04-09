#pragma once

#include "../ImaseLib/TaskSystem.h"

class CollisionManager
{
private:

	// タスクシステムへのポインタ
	Imase::TaskSystem* m_system = nullptr;

public:

	// 更新
	void Update();

	// 矩形同士の衝突判定
	bool IsColliding(RECT a, RECT b);

};
