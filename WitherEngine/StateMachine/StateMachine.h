#pragma once
#include <deque>

#include "../States/State.h"

namespace we
{
	typedef std::unique_ptr<State> StateRef;

	class StateMachine
	{
	public:
		StateMachine()  = default;
		~StateMachine() = default;

		void AddState(StateRef newState, bool isReplacing = true);
		void RemoveState();

		void ProcessStateChanges();

		bool isEmpty();

		StateRef &GetActiveState();

	private:
		std::deque<StateRef> m_states;
		StateRef m_newState;

		bool m_isAdding;
		bool m_isRemoving;
		bool m_isReplacing;
	};
}