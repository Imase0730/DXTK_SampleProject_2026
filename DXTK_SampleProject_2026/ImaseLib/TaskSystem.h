#pragma once
#include <vector>
#include <memory>
//--------------------------------------------------------------------------------------
// File: TaskSystem.h
//
// シーンシステムクラス
//
// Date: 2026.4.3
// Author: Hideyasu Imase
//--------------------------------------------------------------------------------------
#include <functional>
#include <cstdint>

namespace Imase
{
    class Task;

    class TaskSystem
    {
    private:
        struct PendingAdd
        {
            Task* parent;
            std::unique_ptr<Task> child;
        };

        std::unique_ptr<Task> m_root;

        uint64_t m_nextID = 1;

        // ペンディング処理
        std::vector<PendingAdd> m_pendingAdd;

        // 親変更ペンディング
        struct PendingChangeParent
        {
            Task* task;
            Task* newParent;
        };

        std::vector<PendingChangeParent> m_pendingChangeParent;

    public:
        TaskSystem();
        ~TaskSystem();

        //--------------------------------
        void Update(float dt);
        void Render();

        //--------------------------------
        // ペンディング登録
        //--------------------------------
        void RequestAddChild(Task* parent, std::unique_ptr<Task> child);
        void RequestChangeParent(Task* t, Task* newParent);

        //--------------------------------
        Task* GetRoot() { return m_root.get(); }
    };
}
