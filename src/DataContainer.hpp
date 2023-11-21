#ifndef DATACONTAINER_HPP
#define DATACONTAINER_HPP

#include "State.hpp"
#include "RobotArm.hpp"

#include <string>
#include <vector>

namespace RobotStacking
{
	class DataContainer
	{
	public:
		void AddState(State aState)
		{
			states.push_back(aState);
		}

		void AddStates(std::vector<State> aStates)
		{
			for(State aState : aStates)
				states.push_back(aState);
		}

		State GetState(int aIndex)
		{
			if (aIndex >= 0 && aIndex < states.size())
			{
				return states.at(aIndex);
			}
			return State();
		}

		std::vector<State> GetStates()
		{
			return states;
		}

	private:
		std::vector<State> states;
	};
}

#endif