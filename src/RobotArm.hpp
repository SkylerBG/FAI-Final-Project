#ifndef ROBOT_ARM_HPP
#define ROBOT_ARM_HPP

#include <string>

namespace RobotStacking
{
	class RobotArm
	{
	public:
		RobotArm(int aPosition, std::string aBox = "nothing");

		void operator=(const RobotArm otherArm);
		bool operator==(RobotArm otherArm);
		bool operator!=(RobotArm otherArm);

		std::string mBox = "";
		int mPosition = 0;
	};
}

#endif