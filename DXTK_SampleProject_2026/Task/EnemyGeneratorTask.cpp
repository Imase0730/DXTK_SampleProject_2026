//--------------------------------------------------------------------------------------
// File: EnemyGeneratorTask.cpp
//
// 敵生成タスク
//
// Date: 2026.4.5
// Author: Hideyasu Imase
//--------------------------------------------------------------------------------------
#include "pch.h"
#include "EnemyGeneratorTask.h"
#include "EnemyTask.h"

using namespace DirectX;

// コンストラクタ
EnemyGeneratorTask::EnemyGeneratorTask(
    const GameContext& gameContext,
    DirectX::SpriteBatch& spriteBatch,
    ID3D11ShaderResourceView* pTexture
)
    : m_gameContext(gameContext)
    , m_spriteBatch(spriteBatch)
    , m_pTexture(pTexture)
{
    // タグを設定
    SetTag(L"EnemyGenerator");
}

// 更新
bool EnemyGeneratorTask::Update(float elapsedTime)
{

    return true;
}
