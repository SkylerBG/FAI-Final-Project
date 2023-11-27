#include "RobotStacking.hpp"

#include <iostream>
#include <string>
#include <vector>

#include <chrono>

std::vector<std::string> GetLocationListFromString(std::string listString);
int InPlaceInLists(std::vector<std::string> currentStateList, std::vector<std::string> goalStateList);
std::vector<RobotStacking::State> SolveForBox(RobotStacking::State currentState, RobotStacking::State goalState, int whichBox, int whichList);

int main()
{
	std::cout << "Robot Stacking\n";
	bool goAgain = true;
	while (goAgain)
	{
		std::string list;

		std::cout << "Enter Initial State Boxes in Location 1 from bottom to top and seperated by spaces: \n";
		std::getline(std::cin, list);
		std::vector<std::string> initialL1 = GetLocationListFromString(list);

		std::cout << "Enter Initial State Boxes in Location 2 from bottom to top and seperated by spaces: \n";
		std::getline(std::cin, list);
		std::vector<std::string> initialL2 = GetLocationListFromString(list);
		int armPosition = 0;
		std::string armBox;
		std::cout << "Enter the Initial Position and Initial Box held in Robot Arm 1 seperated by a space (if nothing is held write nothing): \n";
		std::cin >> armPosition;
		std::getline(std::cin, armBox);
		armPosition--;
		armBox = armBox.substr(armBox.find_first_of(" ")+1, armBox.size());
		RobotStacking::RobotArm initialR1 = RobotStacking::RobotArm(armPosition, armBox);

		armPosition = 1;
		std::cout << "Enter the Initial Position and Initial Box held in Robot Arm 2 seperated by a space (if nothing is held write nothing): \n";
		std::cin >> armPosition;
		std::getline(std::cin, armBox);
		armPosition--;
		armBox = armBox.substr(armBox.find_first_of(" ")+1, armBox.size());
		RobotStacking::RobotArm initialR2 = RobotStacking::RobotArm(armPosition, armBox);
		RobotStacking::State currentState = RobotStacking::State(initialL1, initialL2, initialR1, initialR2);

		std::cout << std::endl;
		std::cout << "Enter Goal State Boxes in Location 1 from bottom to top and seperated by spaces: \n";
		std::getline(std::cin, list);
		std::vector<std::string> goalL1 = GetLocationListFromString(list);

		std::cout << "Enter Goal State Boxes in Location 2 from bottom to top and seperated by spaces: \n";
		std::getline(std::cin, list);
		std::vector<std::string> goalL2 = GetLocationListFromString(list);

		std::cout << "Enter the Goal Position and Goal Box held in Robot Arm 1 seperated by a space (if nothing is held write nothing): \n";
		std::cin >> armPosition;
		std::getline(std::cin, armBox);
		armPosition--;
		armBox = armBox.substr(armBox.find_first_of(" ") + 1, armBox.size());
		RobotStacking::RobotArm goalR1 = RobotStacking::RobotArm(armPosition, armBox);

		std::cout << "Enter the Goal Position and Goal Box held in Robot Arm 2 seperated by a space (if nothing is held write nothing): \n";
		std::cin >> armPosition;
		std::getline(std::cin, armBox);
		armPosition--;
		armBox = armBox.substr(armBox.find_first_of(" ") + 1, armBox.size());
		RobotStacking::RobotArm goalR2 = RobotStacking::RobotArm(armPosition, armBox);
		RobotStacking::State goalState = RobotStacking::State(goalL1, goalL2, goalR1, goalR2);

		auto start = std::chrono::system_clock::now();
		RobotStacking::DataContainer mData = RobotStacking::DataContainer();
		mData.AddState(currentState);
		while (currentState != goalState)
		{
			int inPlaceL1 = InPlaceInLists(currentState.mL1, goalState.mL1);
			int inPlaceL2 = InPlaceInLists(currentState.mL2, goalState.mL2);

			//both lists are solved so put the robot arms in the correct spot
			if (inPlaceL1 == goalState.mL1.size() && inPlaceL2 == goalState.mL2.size())
			{
				if (currentState.mR1.mBox != goalState.mR1.mBox)
				{
					std::string wantedBox = goalState.mR1.mBox;
					if (currentState.mR2.mBox == wantedBox)
					{
						if (currentState.mR2.mPosition == 0)
						{
							if (currentState.mL1.size() > 0)
							{
								currentState = currentState.Stack(0);
							}
							else
							{
								currentState = currentState.PutDown(0);
							}
							mData.AddState(currentState);
							currentState = currentState.Move(0, 1);
							mData.AddState(currentState);
							if (currentState.mL1.size() > 1)
							{
								currentState = currentState.Unstack(0);
							}
							else
							{
								currentState = currentState.PickUp(0);
							}
							mData.AddState(currentState);
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
							mData.AddState(currentState);
							currentState = currentState.Move(1, 0);
							mData.AddState(currentState);
							if (currentState.mL2.size() > 1)
							{
								currentState = currentState.Unstack(1);
							}
							else
							{
								currentState = currentState.PickUp(1);
							}
							mData.AddState(currentState);
						}

					}
					else if (currentState.mL1.at(currentState.mL1.size() - 1) == wantedBox)
					{
						if (currentState.mR1.mPosition != 0)
						{
							currentState = currentState.Move(1, 0);
							mData.AddState(currentState);
						}
						if (currentState.mL1.size() > 1)
						{
							currentState = currentState.Unstack(0);
						}
						else
						{
							currentState = currentState.PickUp(0);
						}
						mData.AddState(currentState);
					}
					else if (currentState.mL2.at(currentState.mL2.size() - 1) == wantedBox)
					{
						if (currentState.mR1.mPosition != 1)
						{
							currentState = currentState.Move(0, 1);
							mData.AddState(currentState);
						}
						if (currentState.mL2.size() > 1)
						{
							currentState = currentState.Unstack(1);
						}
						else
						{
							currentState = currentState.PickUp(1);
						}
						mData.AddState(currentState);
					}
				}

				if (currentState.mR2.mBox != goalState.mR2.mBox)
				{
					std::string wantedBox = goalState.mR2.mBox;
					if (currentState.mR1.mBox == wantedBox)
					{
						if (currentState.mR1.mPosition == 0)
						{
							if (currentState.mL1.size() > 0)
							{
								currentState = currentState.Stack(0);
							}
							else
							{
								currentState = currentState.PutDown(0);
							}
							mData.AddState(currentState);
							currentState = currentState.Move(0, 1);
							mData.AddState(currentState);
							if (currentState.mL1.size() > 1)
							{
								currentState = currentState.Unstack(0);
							}
							else
							{
								currentState = currentState.PickUp(0);
							}
							mData.AddState(currentState);
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
							mData.AddState(currentState);
							currentState = currentState.Move(1, 0);
							mData.AddState(currentState);
							if (currentState.mL2.size() > 1)
							{
								currentState = currentState.Unstack(1);
							}
							else
							{
								currentState = currentState.PickUp(1);
							}
							mData.AddState(currentState);
						}

					}
					else if (currentState.mL1.at(currentState.mL1.size() - 1) == wantedBox)
					{
						if (currentState.mR2.mPosition != 0)
						{
							currentState = currentState.Move(1, 0);
							mData.AddState(currentState);
						}
						if (currentState.mL1.size() > 1)
						{
							currentState = currentState.Unstack(0);
						}
						else
						{
							currentState = currentState.PickUp(0);
						}
						mData.AddState(currentState);
					}
					else if (currentState.mL2.at(currentState.mL2.size() - 1) == wantedBox)
					{
						if (currentState.mR2.mPosition != 1)
						{
							currentState = currentState.Move(0, 1);
							mData.AddState(currentState);
						}
						if (currentState.mL2.size() > 1)
						{
							currentState = currentState.Unstack(1);
						}
						else
						{
							currentState = currentState.PickUp(1);
						}
						mData.AddState(currentState);
					}
				}

				if (currentState.mR1.mPosition != goalState.mR1.mPosition)
				{
					currentState = currentState.Move(0, 1);
					mData.AddState(currentState);
				}
				break;
			}

			//Only save the shortest moves
			std::vector<RobotStacking::State> nextL1BoxSolved = (goalState.mL1.size() > 0) ? SolveForBox(currentState, goalState, inPlaceL1, 0) : std::vector<RobotStacking::State>();
			std::vector<RobotStacking::State> nextL2BoxSolved = (goalState.mL2.size() > 0) ? SolveForBox(currentState, goalState, inPlaceL2, 1) : std::vector<RobotStacking::State>();
			if (nextL1BoxSolved.size() > 0 && (nextL2BoxSolved.size() == 0 || nextL1BoxSolved.size() <= nextL2BoxSolved.size()))
			{
				mData.AddStates(nextL1BoxSolved);
			}
			else if (nextL2BoxSolved.size() > 0 && (nextL1BoxSolved.size() == 0 || nextL2BoxSolved.size() < nextL1BoxSolved.size()))
			{
				mData.AddStates(nextL2BoxSolved);
			}

			currentState = mData.GetState(mData.GetStates().size() - 1);
		}
		auto end = std::chrono::system_clock::now();
		std::chrono::duration<double> computationTime = end - start;

		std::cout << "Computation took: " << computationTime.count() << " s\nFor: "
			<< mData.GetStates().size()-1 << " states" << std::endl;

		char seeStates = -1;
		std::cout << "Do you want to see the states? (Y/N) ";
		std::cin >> seeStates;
		seeStates = std::toupper(seeStates);
		if (seeStates == 'Y')
		{
			int stateCounter = 0;
			for (RobotStacking::State state : mData.GetStates())
			{
				std::cout << "\nSTATE " << stateCounter << ": \n" << state.toString() << std::endl;
				stateCounter++;
				system("pause");
			}
		}

		char again = -1;
		std::cout << "Do you want to do it again? (Y/N) ";
		std::cin >> again;
		std::cin.clear();
		std::cin.ignore(10000, '\n');
		again = std::toupper(again);
		goAgain = (again == 'Y') ? true : false;
	}
	return 0;
}

std::vector<std::string> GetLocationListFromString(std::string listString)
{
	std::vector<std::string> stack;
	std::string currentBox = "";
	for (char c : listString)
	{
		if (!std::isalpha(c))
		{
			if (!currentBox.empty())
			{
				stack.push_back(currentBox);
				currentBox = "";
			}
		}
		else
		{
			currentBox += c;
		}
	}
	if (!currentBox.empty())
	{
		stack.push_back(currentBox);
	}
	return stack;
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

	std::string boxToMove = goalState.GetBoxInState(whichList, whichBox);
	if (boxToMove == "nothing")
	{
		return statesToSolve;
	}

	//pick up
	std::pair<int, int> boxInCurrentState = FindWhereBoxIsInState(currentState, boxToMove);
	while (currentState.mR1.mBox != boxToMove && currentState.mR2.mBox != boxToMove)
	{
		if (boxInCurrentState.first == 0)
		{
			if (currentState.mR1.mPosition == 0)
			{
				if (currentState.mR1.mBox != "nothing")
				{
					if (currentState.mR2.mBox != "nothing")
					{
						if (currentState.mL2.size() > 0)
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
						if (currentState.mL2.size() > 0)
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
		}
		else if (boxInCurrentState.first == 1)
		{
			if (currentState.mR1.mPosition == 1)
			{
				if (currentState.mR1.mBox != "nothing")
				{
					if (currentState.mR2.mBox != "nothing")
					{
						if (currentState.mL1.size() > 0)
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
						if (currentState.mL1.size() > 0)
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

	//put down
	while ((whichList == 0 && currentState.mL1.size() > whichBox) ||
		(whichList == 1 && currentState.mL2.size() > whichBox))
	{
		if (whichList == 0)
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
		else if (whichList == 1)
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
		statesToSolve.push_back(currentState);
	}

	//put down last one 
	std::vector<std::string> goalList;
	if (whichList == 0)
	{
		goalList = currentState.mL1;
	}
	else
	{
		goalList = currentState.mL2;
	}

	if (currentState.mR1.mBox == boxToMove)
	{
		if (currentState.mR1.mPosition != whichList)
		{
			currentState = currentState.Move(0, 1);
			statesToSolve.push_back(currentState);
		}
		if (goalList.size() > 0)
		{
			currentState = currentState.Stack(whichList);
		}
		else
		{
			currentState = currentState.PutDown(whichList);
		}
	}
	else if (currentState.mR2.mBox == boxToMove)
	{
		if (currentState.mR2.mPosition != whichList)
		{
			currentState = currentState.Move(0, 1);
			statesToSolve.push_back(currentState);
		}
		if (goalList.size() > 0)
		{
			currentState = currentState.Stack(whichList);
		}
		else
		{
			currentState = currentState.PutDown(whichList);
		}
	}
	statesToSolve.push_back(currentState);

	return statesToSolve;
}