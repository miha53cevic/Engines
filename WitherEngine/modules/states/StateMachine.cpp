#include "StateMachine.h"

we::StateMachine::StateMachine()
{
    m_isAdding      = false;
    m_isRemoving    = false;
    m_isReplacing   = false;
}

void we::StateMachine::AddState(StateRef newState, bool isReplacing)
{
	// copy the state over
	m_newState = std::move(newState);

	m_isAdding      = true;
	m_isReplacing   = isReplacing;
}

void we::StateMachine::RemoveState()
{
	m_isRemoving = true;
}

void we::StateMachine::ProcessStateChanges()
{
	// Add state
	if (m_isAdding)
	{
		if (!m_states.empty())
		{
			if (m_isReplacing)
			{
				m_states.pop_front();
			}
			else
			{
				m_states.front()->Pause();
			}
		}

		m_states.push_front(std::move(m_newState));
		m_states.front()->Init();
		
		m_isAdding = false;
	}

	// Remove state
	if (m_isRemoving && !m_states.empty())
	{
		m_states.pop_front();

        m_isRemoving = false;

		if (!m_states.empty())
		{
			m_states.front()->Resume();
		}
	}
    else if (m_isRemoving) m_isRemoving = false;
}

bool we::StateMachine::isEmpty()
{
	return m_states.empty();
}

void we::StateMachine::RemoveStateBack()
{
    m_states.pop_back();
}

we::StateRef& we::StateMachine::GetActiveState()
{
	return m_states.front();
}

std::deque<we::StateRef>& we::StateMachine::GetStates()
{
    return m_states;
}


