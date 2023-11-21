#include "RobotArm.hpp"

RobotStacking::RobotArm::RobotArm(int aPosition, std::string aBox)
{
	mPosition = aPosition;
	mBox = aBox;
}

void RobotStacking::RobotArm::operator=(const RobotArm otherArm)
{
	mBox = otherArm.mBox;
	mPosition = otherArm.mPosition;
}

bool RobotStacking::RobotArm::operator==(RobotArm otherArm)
{
	return (mBox == otherArm.mBox &&
		mPosition == otherArm.mPosition);
}

bool RobotStacking::RobotArm::operator!=(RobotArm otherArm)
{
	return !(*this == otherArm);
}