//--------------------------------------------------------------------------------------
// File: SceneFactory.h
//
// シーン生成関数
//
// Date: 2026.3.21
// Author: Hideyasu Imase
//--------------------------------------------------------------------------------------
#pragma once

#include "ImaseLib/SceneManager.h"
#include "GameContext.h"
#include "SceneId.h"

// シーンを生成する関数
extern Imase::ScenePtr<SceneId, GameContext> CreateScene(const SceneId& id);
