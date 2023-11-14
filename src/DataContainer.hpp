
#include <string>
#include <vector>

namespace RobotStacking
{
	class DataContainer
	{
	public:
		struct State
		{
			State(std::vector<std::string> aL1, std::vector<std::string> aL2, std::string aR1, std::string aR2)
			{
				mL1 = aL1;
				mL2 = aL2;
				mR1 = aR1;
				mR2 = aR2;
				action = "NOOP";
			}

			bool operator==(State otherState)
			{
				return (mL1 == otherState.mL1 &&
						mL2 == otherState.mL2 &&
						mR1 == otherState.mR1 &&
						mL2 == otherState.mL2);
			}

			bool operator!=(State otherState)
			{
				return !(*this == otherState);
			}

			std::string mR1, mR2, action;
			std::vector<std::string> mL1, mL2;
		};

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
			if (aIndex > 0 && aIndex < states.size())
			{
				return states.at(aIndex);
			}
		}

		std::vector<State> GetStates()
		{
			return states;
		}

	private:
		std::vector<State> states;
	};
}