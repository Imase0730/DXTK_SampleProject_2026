//--------------------------------------------------------------------------------------
// File: SceneFactory.cpp
//
// シーン生成関数
//
// Date: 2026.3.21
// Author: Hideyasu Imase
//--------------------------------------------------------------------------------------
#include "pch.h"
#include "SceneFactory.h"
#include "SceneA.h"
#include "SceneB.h"

// シーンを生成する関数
Imase::ScenePtr<SceneId, GameContext> CreateScene(const SceneId& id)
{
	if (id == SceneId::SceneA)
	{
		return std::make_unique<SceneA>();
	}

	if (id == SceneId::SceneB)
	{
		return std::make_unique<SceneB>();
	}

	return nullptr;
}