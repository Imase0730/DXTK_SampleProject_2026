#include "pch.h"
#include "Task.h"
#include "TaskSystem.h"

namespace Imase
{
    void Task::AddChildInternal(Ptr child)
    {
        if (!m_system) return;

        m_system->RequestAddChild(this, std::move(child));
    }

    void Task::ChangeParent(Task* newParent)
    {
        if (!m_system) return;

        m_system->RequestChangeParent(this, newParent);
    }
}
