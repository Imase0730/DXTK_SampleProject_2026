//--------------------------------------------------------------------------------------
// File: GameContext.h
//
// シーンへ渡すゲームコンテキストクラス
//
// Date: 2026.3.3
// Author: Hideyasu Imase
//--------------------------------------------------------------------------------------
#pragma once

#include "StepTimer.h"
#include "DeviceResources.h"
#include "ImaseLib/DebugFont.h"

// 各シーンに渡す共通リソースを記述してください
class GameContexts
{
private:

	// ステップタイマー
	DX::StepTimer* m_timer;

	// デバイスリソース
	DX::DeviceResources* m_deviceResources;

	// キーボードステートトラッカー
	DirectX::Keyboard::KeyboardStateTracker* m_keyboardTracker;

	// マウスステートトラッカー
	DirectX::Mouse::ButtonStateTracker* m_mouseButtonTracker;

	// コモンステート
	DirectX::CommonStates* m_states;

	// デバッグ用文字列表示へのポインタ
	Imase::DebugFont* m_debugFont;

public:

	// コンストラクタ
	GameContexts()
		: m_timer{ nullptr }
		, m_deviceResources{ nullptr }
		, m_keyboardTracker{ nullptr }
		, m_mouseButtonTracker{ nullptr }
		, m_states{ nullptr }
		, m_debugFont{ nullptr }
	{
	}

	// ------------------------------------------ //
	// ステップタイマー	
	// ------------------------------------------ //

	// ステップタイマーを設定する関数
	void SetStepTimerStates(DX::StepTimer* timer) { m_timer = timer; }

	// ステップタイマーを取得する関数
	DX::StepTimer* GetStepTimer() { return m_timer; }

	// ------------------------------------------ //
	// デバイスリソース	
	// ------------------------------------------ //

	// デバイスリソースを設定する関数
	void SetDeviceResources(DX::DeviceResources* deviceResources) { m_deviceResources = deviceResources; }

	// デバイスリソースを取得する関数
	DX::DeviceResources* GetDeviceResources() { return m_deviceResources; }

	// ------------------------------------------ //
	// キーボードトラッカー	
	// ------------------------------------------ //

	// キーボードトラッカーを設定する関数
	void SetKeyboardTracker(DirectX::Keyboard::KeyboardStateTracker* tracker) { m_keyboardTracker = tracker; }

	// キーボードトラッカーを取得する関数
	DirectX::Keyboard::KeyboardStateTracker* GetKeyboardTracker() { return m_keyboardTracker; }

	// ------------------------------------------ //
	// マウスボタンラッカー	
	// ------------------------------------------ //

	// マウスボタントラッカーを設定する関数
	void SetMouseButtonTracker(DirectX::Mouse::ButtonStateTracker* tracker) { m_mouseButtonTracker = tracker; }

	// マウスボタントラッカーを取得する関数
	DirectX::Mouse::ButtonStateTracker* GetMouseButtonTracker() { return m_mouseButtonTracker; }

	// ------------------------------------------ //
	// コモンステート	
	// ------------------------------------------ //

	// コモンステートを設定する関数
	void SetCommonStates(DirectX::CommonStates* states) { m_states = states; }

	// コモンステートを取得する関数
	DirectX::CommonStates* GetCommonStates() { return m_states; }

	// ------------------------------------------ //
	// デバッグフォント	
	// ------------------------------------------ //

	// デバッグフォントを設定する関数
	void SetDebugFont(Imase::DebugFont* debugFont) { m_debugFont = debugFont; }

	// デバッグフォントを取得する関数
	Imase::DebugFont* GetDebugFont() { return m_debugFont; }

};

