#include "StateMachine.h"

void we::StateMachine::AddState(StateRef newState, bool isReplacing)
{
	// copy the state over
	m_newState = std::move(newState);

	m_isAdding	= true;
	m_isReplacing = isReplacing;
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
				m_states.pop();
			}
			else
			{
				m_states.top()->Pause();
			}
		}

		m_states.push(std::move(m_newState));
		m_states.top()->Init();
		
		m_isAdding = false;
	}

	// Remove state
	if (m_isRemoving && !m_states.empty())
	{
		m_states.pop();

		if (!m_states.empty())
		{
			m_states.top()->Resume();
		}

		m_isRemoving = false;
	}
}

bool we::StateMachine::isEmpty()
{
	return m_states.empty();
}

we::StateRef& we::StateMachine::GetActiveState()
{
	return m_states.top();
}


