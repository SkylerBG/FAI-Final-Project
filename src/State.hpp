#ifndef STATE_HPP
#define STATE_HPP

#include "RobotArm.hpp"

#include <string>
#include <vector>

namespace RobotStacking
{
	class State
	{
		friend class RobotArm;

	public:
		State();
		State(std::vector<std::string> aL1, std::vector<std::string> aL2, RobotArm aR1 = RobotArm(0), RobotArm aR2 = RobotArm(1));
		std::string GetBoxInState(int list, int boxIndex);


		State PickUp(int list);
		State PutDown(int list);
		State Stack(int list);
		State Unstack(int list);
		State Move(int currentPosition, int newPosition);
		State NoOp();

		void operator=(const State otherState);
		bool operator==(State otherState);
		bool operator!=(State otherState);

		RobotArm mR1 = RobotArm(0), mR2 = RobotArm(1);
		std::string action;
		std::vector<std::string> mL1, mL2;
	};
}

#endif