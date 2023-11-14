#include "RobotStacking.hpp"

#include <iostream>
#include <string>
#include <vector>

int InPlaceInLists(std::vector<std::string> currentStateList, std::vector<std::string> goalStateList);

int main()
{
	RobotStacking::DataContainer mData = RobotStacking::DataContainer();
	std::vector<std::string> initialL1 = {"b", "e", "c"};
	std::vector<std::string> initialL2 = {"a", "g", "f", "d"};
	std::string initialR1 = "", initialR2 = "";
	RobotStacking::DataContainer::State currentState = RobotStacking::DataContainer::State(initialL1, initialL2, initialR1, initialR2);

	std::vector<std::string> goalL1 = {"a", "b", "c", "d"};
	std::vector<std::string> goalL2 = {"e", "f", "g"};
	std::string goalR1 = "", goalR2 = "";
	RobotStacking::DataContainer::State goalState = RobotStacking::DataContainer::State(goalL1, goalL2, goalR1, goalR2);

	mData.AddState(currentState);
	while (currentState != goalState)
	{
		int inPlaceL1 = InPlaceInLists(currentState.mL1, goalState.mL1);
		int inPlaceL2 = InPlaceInLists(currentState.mL2, goalState.mL2);
		
		//Do shortest moves
		
	}

	system("pause");
	return 0;
}

int InPlaceInLists(std::vector<std::string> currentStateList, std::vector<std::string> goalStateList)
{
	int inPlaceInList = 0;
	for (int i = 0; i < currentStateList.size(); i++)
	{
		if (i >= goalStateList.size() || currentStateList[i] != goalStateList[i])
			break;
		inPlaceInList++;
	}
	return inPlaceInList;
}