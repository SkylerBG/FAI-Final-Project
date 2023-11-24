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
	State newState = *this;
	if (list == 0 && mL1.size() == 1)
	{
		if (mR1.mPosition == 0 && mR1.mBox == "nothing")
		{
			newState.mR1.mBox = mL1.at(0);
			newState.mL1.pop_back();
		}
		else if (mR2.mPosition == 0 && mR2.mBox == "nothing")
		{
			newState.mR2.mBox = mL1.at(0);
			newState.mL1.pop_back();
		}
	}
	else if (list == 1 && mL2.size() == 1)
	{
		if (mR1.mPosition == 1 && mR1.mBox == "nothing")
		{
			newState.mR1.mBox = mL2.at(0);
			newState.mL2.pop_back();
		}
		else if (mR2.mPosition == 1 && mR2.mBox == "nothing")
		{
			newState.mR2.mBox = mL2.at(0);
			newState.mL2.pop_back();
		}
	}
	newState.action = "Pick-Up";
	return newState;
}

RobotStacking::State RobotStacking::State::PutDown(int list)
{
	State newState = *this;
	if (list == 0 && mL1.size() == 0)
	{
		if (mR1.mPosition == 0 && mR1.mBox != "nothing")
		{
			newState.mL1.push_back(newState.mR1.mBox);
			newState.mR1.mBox = "nothing";
		}
		else if (mR2.mPosition == 0 && mR2.mBox != "nothing")
		{
			newState.mL1.push_back(newState.mR2.mBox);
			newState.mR2.mBox = "nothing";
		}
	}
	else if (list == 1 && mL2.size() == 0)
	{
		if (mR1.mPosition == 1 && mR1.mBox != "nothing")
		{
			newState.mL2.push_back(newState.mR1.mBox);
			newState.mR2.mBox = "nothing";
		}
		else if (mR2.mPosition == 1 && mR2.mBox != "nothing")
		{
			newState.mL2.push_back(newState.mR2.mBox);
			newState.mR2.mBox = "nothing";
		}
	}
	newState.action = "Put-Down";
	return newState;
}

RobotStacking::State RobotStacking::State::Stack(int list)
{
	State newState = *this;
	if (list == 0 && mL1.size() > 0)
	{
		if (mR1.mPosition == 0 && mR1.mBox != "nothing")
		{
			newState.mL1.push_back(newState.mR1.mBox);
			newState.mR1.mBox = "nothing";
		}
		else if (mR2.mPosition == 0 && mR2.mBox != "nothing")
		{
			newState.mL1.push_back(newState.mR2.mBox);
			newState.mR2.mBox = "nothing";
		}
	}
	else if (list == 1 && mL2.size() > 0)
	{
		if (mR1.mPosition == 1 && mR1.mBox != "nothing")
		{
			newState.mL2.push_back(newState.mR1.mBox);
			newState.mR1.mBox = "nothing";
		}
		else if (mR2.mPosition == 1 && mR2.mBox != "nothing")
		{
			newState.mL2.push_back(newState.mR2.mBox);
			newState.mR2.mBox = "nothing";
		}
	}
	newState.action = "Stack";
	return newState;
}

RobotStacking::State RobotStacking::State::Unstack(int list)
{
	State newState = *this;
	if (list == 0 && mL1.size() > 1)
	{
		if (mR1.mPosition == 0 && mR1.mBox == "nothing")
		{
			newState.mR1.mBox = mL1.at(mL1.size() - 1);
			newState.mL1.pop_back();
		}
		else if (mR2.mPosition == 0 && mR2.mBox == "nothing")
		{
			newState.mR2.mBox = mL1.at(mL1.size() - 1);
			newState.mL1.pop_back();
		}
	}
	else if (list == 1 && mL2.size() > 1)
	{
		if (mR1.mPosition == 1 && mR1.mBox == "nothing")
		{
			newState.mR1.mBox = mL2.at(mL2.size() - 1);
			newState.mL2.pop_back();
		}
		else if (mR2.mPosition == 1 && mR2.mBox == "nothing")
		{
			newState.mR2.mBox = mL2.at(mL2.size() - 1);
			newState.mL2.pop_back();
		}
	}
	newState.action = "Unstack";
	return newState;
}

RobotStacking::State RobotStacking::State::Move(int currentPosition, int newPosition)
{
	State newState = *this;
	if (mR1.mPosition == currentPosition)
	{
		newState.mR1.mPosition = newPosition;
		newState.mR2.mPosition = currentPosition;
	}
	else if (mR2.mPosition == currentPosition)
	{
		newState.mR2.mPosition = newPosition;
		newState.mR1.mPosition = currentPosition;
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

std::string RobotStacking::State::toString()
{
	std::string returnString;
	returnString += "mL1: {";
	for (std::string x : mL1)
	{
		returnString += x + ", ";
	}
	returnString += "}\n";

	returnString += "mL2: {";
	for (std::string x : mL2)
	{
		returnString += x + ", ";
	}
	returnString += "}\n";

	returnString += "mR1 (" + std::to_string(mR1.mPosition) + "): " + mR1.mBox + "\n";
	returnString += "mR2 (" + std::to_string(mR2.mPosition) + "): " + mR2.mBox + "\n";
	returnString += "action: " + action + "\n";
	return returnString;
}