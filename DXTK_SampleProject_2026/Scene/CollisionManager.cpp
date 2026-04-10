#include "pch.h"
#include "CollisionManager.h"
#include "../Task/PlayerTask.h"
#include "../Task/EnemyTask.h"
#include "../Task/BulletTask.h"
#include "../Task/GameTypes.h"

// 矩形同士の衝突判定
bool CollisionManager::IsColliding(RECT a, RECT b)
{
    if ( (a.right >= b.left)
      && (a.left <= b.right)
      && (a.bottom >= b.top)
      && (a.top <= b.bottom)
       )
    {
        return true;
    }
    return false;
}

// プレイヤーの弾と敵の当たり判定
void CollisionManager::PlayerBulletVsEnemy(Imase::TaskSystem& taskSystem)
{
    // 弾のリスト
    std::vector<Imase::Task*> bullets = taskSystem.FindByTag(L"Bullet");

    // 敵のリスト
    std::vector<Imase::Task*> enemies = taskSystem.FindByTag(L"Enemy");

    for (auto* bullet : bullets)
    {
        BulletTask* b = dynamic_cast<BulletTask*>(bullet);
        for (auto* enemy : enemies)
        {
            EnemyTask* e = dynamic_cast<EnemyTask*>(enemy);
            // プレイヤーの発射した弾
            if (b->GetFaction() == Faction::Player)
            {
                // 矩形同士の衝突判定を行う
                if (IsColliding(b->GetBoundingRect(), e->GetBoundingRect()))
                {
                    // 弾と敵を消す
                    b->Kill();
                    e->Kill();
                }
            }
        }
    }
}

// 敵の弾とプレイヤーの当たり判定
void CollisionManager::EnemyBulletVsPlayer(Imase::TaskSystem& taskSystem)
{
    // 弾のリスト
    std::vector<Imase::Task*> bullets = taskSystem.FindByTag(L"Bullet");

    // プレイヤーのリスト
    std::vector<Imase::Task*> players = taskSystem.FindByTag(L"Player");

    // プレイヤーがいない
    if (players.size() == 0) return;

    PlayerTask* player = dynamic_cast<PlayerTask*>(players[0]);
    for (auto* bullet : bullets)
    {
        BulletTask* b = dynamic_cast<BulletTask*>(bullet);
        // 敵の発射した弾
        if (b->GetFaction() == Faction::Enemy)
        {
            // 矩形同士の衝突判定を行う
            if (IsColliding(b->GetBoundingRect(), player->GetBoundingRect()))
            {
                // 弾消去
                b->Kill();
                // プレイヤー死亡
                player->Kill();
                return;
            }
        }
    }
}

// 当たり判定
void CollisionManager::Check(Imase::TaskSystem& taskSystem)
{
    // プレイヤーの弾と敵の当たり判定
    PlayerBulletVsEnemy(taskSystem);

    // 敵の弾とプレイヤーの当たり判定
    EnemyBulletVsPlayer(taskSystem);
}
