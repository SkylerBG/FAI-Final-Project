cmake_minimum_required(VERSION 3.16)
project(RobotStacking
		LANGUAGES CXX
		VERSION 1.0.0)

file(GLOB RobotStacking_SRC CONFIGURE_DEPENDS "*.h" "*.hpp" "*.cpp")

add_executable(RobotStacking ${RobotStacking_SRC})