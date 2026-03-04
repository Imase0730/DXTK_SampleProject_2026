//--------------------------------------------------------------------------------------
// File: SceneA.h
//
// サンプルシーンクラス
//
// Date: 2026.2.24
// Author: Hideyasu Imase
//--------------------------------------------------------------------------------------
#pragma once

#include "ImaseLib/SceneManager.h"
#include "GameContext.h"

class SceneA : public Imase::Scene<GameContext>
{
public:
	
	// コンストラクタ
	SceneA(Imase::SceneManager<GameContext>* sceneManager);

	// 更新処理
	void Update(float elapsedTime) override;

	// 描画処理
	void Render() override;

	// デバイスに依存するリソースを作成する関数
	void CreateDeviceDependentResources() override;

	// ウインドウサイズに依存するリソースを作成する関数
	void CreateWindowSizeDependentResources() override;

	// デバイスロストした時に呼び出される関数
	void OnDeviceLost() override;

private:

	// スプライトバッチ
	std::unique_ptr<DirectX::SpriteBatch> m_spriteBatch;

	// シェーダーリソースビュー
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_texture;

};

