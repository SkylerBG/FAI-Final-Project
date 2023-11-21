#include "State.hpp"

RobotStacking::State::State()
{

}

RobotStacking::State::State(std::vector<std::string> aL1, std::vector<std::string> aL2, RobotArm aR1, RobotArm aR2)
{
	mL1 = aL1;
	mL2 = aL2;
	mR1 = aR1;
	mR2 = aR2;
	action = "NOOP";
}

std::string RobotStacking::State::GetBoxInState(int list, int boxIndex)
{
	switch (list)
	{
	case 0:
		if (boxIndex < mL1.size())
			return mL1[boxIndex];
	case 1:
		if(boxIndex < mL2.size())
			return mL2[boxIndex];
	case 2:
		return mR1.mBox;
	case 3:
		return mR2.mBox;
	default:
		break;
	}
	return "";
}

RobotStacking::State RobotStacking::State::PickUp(int list)
{

	action = "Pick-Up";
}

RobotStacking::State RobotStacking::State::PutDown(int list)
{

	action = "Put-Down";
}

RobotStacking::State RobotStacking::State::Stack(int list)
{

	action = "Stack";
}

RobotStacking::State RobotStacking::State::Unstack(int list)
{

	action = "Unstack";
}

RobotStacking::State RobotStacking::State::Move(int currentPosition, int newPosition)
{
	State newState = *this;
	if (mR1.mPosition == currentPosition)
	{
		mR1.mPosition = newPosition;
		mR2.mPosition = currentPosition;
	}
	else if (mR2.mPosition == currentPosition)
	{
		mR2.mPosition = newPosition;
		mR1.mPosition = currentPosition;
	}
	newState.action = "Move";
	return newState;
}

RobotStacking::State RobotStacking::State::NoOp()
{
	State newState = *this;
	newState.action = "NOOP";
	return newState;
}


void RobotStacking::State::operator=(const State otherState)
{
	mL1 = otherState.mL1;
	mL2 = otherState.mL2;
	mR1 = otherState.mR1;
	mR2 = otherState.mR2;
	action = otherState.action;
}

bool RobotStacking::State::operator==(State otherState)
{
	return (mL1 == otherState.mL1 &&
		mL2 == otherState.mL2 &&
		mR1 == otherState.mR1 &&
		mR2 == otherState.mR2);
}

bool RobotStacking::State::operator!=(State otherState)
{
	return !(*this == otherState);
}