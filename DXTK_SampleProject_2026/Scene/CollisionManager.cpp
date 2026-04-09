#include "pch.h"
#include "CollisionManager.h"

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

void CollisionManager::Update()
{
    //// 弾のリスト
    //auto bullets = m_system->FindByTag(L"Bullet");
    //// 敵のリスト
    //auto enemies = m_system->FindByTag(L"Enemy");

    //for (auto* b : bullets)
    //{
    //    for (auto* e : enemies)
    //    {
    //        if (CheckHit(b, e))
    //        {
    //            b->Kill();
    //            e->Kill();
    //        }
    //    }
    //}
}
