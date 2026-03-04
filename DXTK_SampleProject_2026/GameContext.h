//--------------------------------------------------------------------------------------
// File: GameContext.h
//
// シーンへ渡すゲームコンテキストクラス
//
// Date: 2026.3.3
// Author: Hideyasu Imase
//--------------------------------------------------------------------------------------
#pragma once

#include "Common/StepTimer.h"
#include "Common/DeviceResources.h"
#include "ImaseLib/DebugFont.h"

// 各シーンに渡す共通リソースを記述してください
struct GameContext
{
	// ステップタイマー
	DX::StepTimer& timer;

	// デバイスリソース
	DX::DeviceResources& deviceResources;

	// キーボードステートトラッカー
	DirectX::Keyboard::KeyboardStateTracker& keyboardTracker;

	// マウスステートトラッカー
	DirectX::Mouse::ButtonStateTracker& mouseButtonTracker;

	// コモンステート
	DirectX::CommonStates& commonStates;

	// デバッグ用文字列表示へのポインタ
	Imase::DebugFont& debugFont;
};

