#include "RobotStacking.hpp"

#include <iostream>
#include <string>
#include <vector>

int InPlaceInLists(std::vector<std::string> currentStateList, std::vector<std::string> goalStateList);
std::vector<RobotStacking::State> SolveForBox(RobotStacking::State currentState, RobotStacking::State goalState, int whichBox, int whichList);

int main()
{
	RobotStacking::DataContainer mData = RobotStacking::DataContainer();
	std::vector<std::string> initialL1 = {"b", "e", "c"};
	std::vector<std::string> initialL2 = {"a", "g", "f", "d"};
	RobotStacking::RobotArm initialR1 = RobotStacking::RobotArm(0, "nothing"), initialR2 = RobotStacking::RobotArm(1, "nothing");
	RobotStacking::State currentState = RobotStacking::State(initialL1, initialL2, initialR1, initialR2);

	std::vector<std::string> goalL1 = {"a", "b", "c", "d"};
	std::vector<std::string> goalL2 = {"e", "f", "g"};
	RobotStacking::RobotArm goalR1 = RobotStacking::RobotArm(0, "nothing"), goalR2 = RobotStacking::RobotArm(1, "nothing");
	RobotStacking::State goalState = RobotStacking::State(goalL1, goalL2, goalR1, goalR2);

	mData.AddState(currentState);
	while (currentState != goalState)
	{
		int inPlaceL1 = InPlaceInLists(currentState.mL1, goalState.mL1);
		int inPlaceL2 = InPlaceInLists(currentState.mL2, goalState.mL2);

		//both lists are solved so put the robot arms in the correct spot
		if (inPlaceL1 == currentState.mL1.size() && inPlaceL2 == currentState.mL2.size())
		{

		}
		
		//Only save the shortest moves
		std::vector<RobotStacking::State> nextL1BoxSolved = SolveForBox(currentState, goalState, inPlaceL1, 0);
		std::vector<RobotStacking::State> nextL2BoxSolved = SolveForBox(currentState, goalState, inPlaceL2, 1);
		if (nextL1BoxSolved.size() > 0 && nextL1BoxSolved.size() < nextL2BoxSolved.size())
		{
			mData.AddStates(nextL1BoxSolved);
		}
		else if (nextL2BoxSolved.size() > 0 && nextL2BoxSolved.size() < nextL1BoxSolved.size())
		{
			mData.AddStates(nextL2BoxSolved);
		}

		currentState = mData.GetState(mData.GetStates().size() - 1);
	}

	system("pause");
	return 0;
}

//Get how many places are solved in a list
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

std::pair<int, int> FindWhereBoxIsInState(RobotStacking::State aState, std::string boxName)
{
	for (int i = 0; i < aState.mL1.size(); i++)
	{
		if (aState.mL1[i] == boxName)
		{
			return { 0, i };
		}
	}

	for (int i = 0; i < aState.mL2.size(); i++)
	{
		if (aState.mL2[i] == boxName)
		{
			return { 1, i };
		}
	}

	if (aState.mR1.mBox == boxName)
	{
		return { 2, 0 };
	}

	if (aState.mR2.mBox == boxName)
	{
		return { 3, 0 };
	}

	return { -1, -1 };
}

std::vector<RobotStacking::State> SolveForBox(RobotStacking::State currentState, RobotStacking::State goalState, int whichBox, int whichList)
{
	std::vector<RobotStacking::State> statesToSolve;

	std::string boxToMove = currentState.GetBoxInState(whichList, whichBox);
	std::pair<int, int> boxInGoalState = FindWhereBoxIsInState(goalState, boxToMove);
	std::cout << "Box To Move: " << boxToMove << " is at {" << boxInGoalState.first << ", " << boxInGoalState.second << "} in the goal state" << std::endl;
	system("pause");
	
	while (currentState.mR1.mBox != boxToMove && currentState.mR2.mBox != boxToMove)
	{
		if (whichList == 0)
		{
			if (currentState.mR1.mPosition == 0)
			{
				if (currentState.mR1.mBox != "nothing")
				{
					if (currentState.mR2.mBox != "nothing")
					{
						if (currentState.mL2.size() > 1)
						{
							currentState = currentState.Stack(1);
						}
						else
						{
							currentState = currentState.PutDown(1);
						}
						statesToSolve.push_back(currentState);
					}
					currentState = currentState.Move(0, 1);
				}
				else
				{
					if (currentState.mL1.size() > 1)
					{
						currentState = currentState.Unstack(0);
					}
					else
					{
						currentState = currentState.PickUp(0);
					}
				}
			}
			else if (currentState.mR2.mPosition == 0)
			{
				if (currentState.mR2.mBox != "nothing")
				{
					if (currentState.mR1.mBox != "nothing")
					{
						if (currentState.mL2.size() > 1)
						{
							currentState = currentState.Stack(1);
						}
						else
						{
							currentState = currentState.PutDown(1);
						}
						statesToSolve.push_back(currentState);
					}
					currentState = currentState.Move(0, 1);
				}
				else
				{
					if (currentState.mL2.size() > 1)
					{
						currentState = currentState.Unstack(0);
					}
					else
					{
						currentState = currentState.PickUp(0);
					}
				}
			}
		}
		else if (whichList == 1)
		{
			if (currentState.mR1.mPosition == 1)
			{
				if (currentState.mR1.mBox != "nothing")
				{
					if (currentState.mR2.mBox != "nothing")
					{
						if (currentState.mL1.size() > 1)
						{
							currentState = currentState.Stack(0);
						}
						else
						{
							currentState = currentState.PutDown(0);
						}
						statesToSolve.push_back(currentState);
					}
					currentState = currentState.Move(1, 0);
				}
				else
				{
					if (currentState.mL2.size() > 1)
					{
						currentState = currentState.Unstack(1);
					}
					else
					{
						currentState = currentState.PickUp(1);
					}
				}
			}
			else if (currentState.mR2.mPosition == 1)
			{
				if (currentState.mR2.mBox != "nothing")
				{
					if (currentState.mR1.mBox != "nothing")
					{
						if (currentState.mL1.size() > 1)
						{
							currentState = currentState.Stack(0);
						}
						else
						{
							currentState = currentState.PutDown(0);
						}
						statesToSolve.push_back(currentState);
					}
					currentState = currentState.Move(1, 0);
				}
				else
				{
					if (currentState.mL2.size() > 1)
					{
						currentState = currentState.Unstack(1);
					}
					else
					{
						currentState = currentState.PickUp(1);
					}
				}
			}
		}
		statesToSolve.push_back(currentState);
	}
	std::cout << currentState.toString() << std::endl;
	system("pause");
	while ((boxInGoalState.second == 0 && currentState.mL1.size() > boxInGoalState.first) || 
		(boxInGoalState.second == 1 && currentState.mL2.size() > boxInGoalState.first))
	{
		if (boxInGoalState.second == 0)
		{
			if (currentState.mR1.mBox != boxToMove)
			{
				if (currentState.mR1.mPosition == 0)
				{
					if (currentState.mR1.mBox == "nothing")
					{
						if (currentState.mL1.size() > 1)
						{
							currentState = currentState.Unstack(0);
						}
						else
						{
							currentState = currentState.PickUp(0);
						}
					}
					else
					{
						currentState = currentState.Move(0, 1);
					}
				}
				else if (currentState.mR1.mPosition == 1)
				{
					if (currentState.mR1.mBox == "nothing")
					{
						currentState = currentState.Move(1, 0);
					}
					else
					{
						if (currentState.mL2.size() > 0)
						{
							currentState = currentState.Stack(1);
						}
						else
						{
							currentState = currentState.PutDown(1);
						}
					}
				}
			}
			else if (currentState.mR2.mBox != boxToMove)
			{
				if (currentState.mR2.mPosition == 0)
				{
					if (currentState.mR2.mBox == "nothing")
					{
						if (currentState.mL1.size() > 1)
						{
							currentState = currentState.Unstack(0);
						}
						else
						{
							currentState = currentState.PickUp(0);
						}
					}
					else
					{
						currentState = currentState.Move(0, 1);
					}
				}
				else if (currentState.mR2.mPosition == 1)
				{
					if (currentState.mR2.mBox == "nothing")
					{
						currentState = currentState.Move(1, 0);
					}
					else
					{
						if (currentState.mL2.size() > 0)
						{
							currentState = currentState.Stack(1);
						}
						else
						{
							currentState = currentState.PutDown(1);
						}
					}
				}
			}
		}
		else if (boxInGoalState.second == 1)
		{
			if (currentState.mR1.mBox != boxToMove)
			{
				if (currentState.mR1.mPosition == 1)
				{
					if (currentState.mR1.mBox == "nothing")
					{
						if (currentState.mL2.size() > 1)
						{
							currentState = currentState.Unstack(1);
						}
						else
						{
							currentState = currentState.PickUp(1);
						}
					}
					else
					{
						currentState = currentState.Move(1, 0);
					}
				}
				else if (currentState.mR1.mPosition == 0)
				{
					if (currentState.mR1.mBox == "nothing")
					{
						currentState = currentState.Move(0, 1);
					}
					else
					{
						if (currentState.mL1.size() > 0)
						{
							currentState = currentState.Stack(0);
						}
						else
						{
							currentState = currentState.PutDown(0);
						}
					}
				}
			}
			else if (currentState.mR2.mBox != boxToMove)
			{
				if (currentState.mR2.mPosition == 1)
				{
					if (currentState.mR2.mBox == "nothing")
					{
						if (currentState.mL2.size() > 1)
						{
							currentState = currentState.Unstack(1);
						}
						else
						{
							currentState = currentState.PickUp(1);
						}
					}
					else
					{
						currentState = currentState.Move(1, 0);
					}
				}
				else if (currentState.mR2.mPosition == 0)
				{
					if (currentState.mR2.mBox == "nothing")
					{
						currentState = currentState.Move(0, 1);
					}
					else
					{
						if (currentState.mL1.size() > 0)
						{
							currentState = currentState.Stack(0);
						}
						else
						{
							currentState = currentState.PutDown(0);
						}
					}
				}
			}
		}
	}
	std::cout << currentState.toString() << std::endl;
	system("pause");



	return statesToSolve;
}