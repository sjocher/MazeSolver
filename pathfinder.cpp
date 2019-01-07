#include "image.h"
#include "deque.hpp"
#include <iostream>
#include <string>

//state specification
struct state
{
	int row;
	int column;
	int depth;
};
//prototype

bool checkColor(Image<Pixel> inputMaze);
bool redCounter(Image<Pixel> inputMaze);
struct state findStartPoint(Image<Pixel> inputMaze);
bool breadth_first_search(Image<Pixel> inputMaze, struct state start, std::string outputFile);

//pathfinder function
int main(int argc, char *argv[])
{
	// TODO
	if (argc == 3)
	{
		std::string inputFile = argv[1];
		std::string outputFile = argv[2];
		try {
			Image<Pixel> input = readFromFile(inputFile);
			if (checkColor(input))
			{
				if (redCounter(input))
				{
					struct state start = findStartPoint(input);
					if (breadth_first_search(input, start, outputFile))
					{
						std::cout << "Solution Found";
						return EXIT_SUCCESS;
					}
					else
					{
						std::cout << "No Solution Found";
						return EXIT_SUCCESS; //not entirely sure if applicable
					}
				}
				else
				{
					std::cerr << "Error : More then one starting point\n";
					return EXIT_FAILURE;
				}
			}
			else
			{
				std::cerr << "Error : Maze continues invalid pixels\n";
				return EXIT_FAILURE;
			}
		}
		catch (std::exception &ex)
		{
			std::cerr << ex.what() << std::endl;
		}
	}
	else
	{
		std::cerr << "Error : Incorrect Command Line Inputs\n";
		return EXIT_FAILURE;
	}
}

bool checkColor(Image<Pixel> inputMaze)
{
	for (int i = 0; i<inputMaze.width(); i++)
	{
		for (int j = 0; j < inputMaze.height(); j++)
		{
			if (inputMaze(i, j) == BLACK || inputMaze(i, j) == WHITE || inputMaze(i, j) == RED)
			{
				continue;
			}
			else
			{
				return false;
			}
		}
	}
	return true;
}

bool redCounter(Image<Pixel> inputMaze)
{
	int redCounter = 0;
	for (int i = 0; i < inputMaze.width(); i++)
	{
		for (int j = 0; j < inputMaze.height(); j++)
		{
			if (inputMaze(i, j) == RED)
			{
				redCounter++;
			}
		}
	}
	if (redCounter == 0 || redCounter >= 2)
	{
		return false;
	}
	else
	{
		return true;
	}
}

struct state findStartPoint(Image<Pixel> inputMaze)
{
	state start;
	for (int i = 0; i < inputMaze.width(); i++)
	{
		for (int j = 0; j < inputMaze.height(); j++)
		{
			if (inputMaze(i, j) == RED)
			{
				start.column = i;
				start.row = j;
				start.depth = 0;
			}
		}
	}
	return start;
}

bool goalCheck(Image<Pixel> inputMaze, struct state position)
{
	if (position.column == 0 || position.column == inputMaze.width() - 1)
	{
		return true;
	}
	else if (position.row == 0 || position.row == inputMaze.height() - 1)
	{

		return true;
	}
	else
	{
		return false;
	}
}

bool validPosition(Image<Pixel> inputMaze, struct state position)
{
	if (inputMaze(position.column, position.row) != WHITE)
	{
		return false;
	}
	return true;
}

bool breadth_first_search(Image<Pixel> inputMaze, struct state start, std::string outputFile)
{
	int depth = 0;
	start;
	for (int i = 0; i < inputMaze.width(); i++)
	{
		for (int j = 0; j < inputMaze.height(); j++)
		{
			if (inputMaze(i, j) == RED)
			{
				start.column = i;
				start.row = j;
				start.depth = 0;
			}
		}
	}
	start.depth = depth;
	if (start.column == 0 || start.row == 0 || start.column == inputMaze.width() - 1 || start.row == inputMaze.height() - 1) {
		inputMaze(start.column, start.row) = GREEN;
		writeToFile(inputMaze, outputFile);
		return true;
	}
	Deque<state> frontier;
	Image<Pixel> explored(inputMaze);
	frontier.pushBack(start);
	while (!frontier.isEmpty()) {
		state pos = frontier.front();
		frontier.popFront();
		explored(pos.column, pos.row) = BLACK;
		std::cout << depth << std::endl;
		if (pos.column == 0 || pos.row == 0 || pos.column == inputMaze.width() - 1 || pos.row == inputMaze.height() - 1) {
			inputMaze(pos.column, pos.row) = GREEN;
			writeToFile(inputMaze, outputFile);
			return true;
		}
		//image(pos.x, pos.y) = BLUE;
		Deque<state> newMoves;
		state left;
		left.column = pos.column - 1;
		left.row = pos.row;
		left.depth = depth;
		if (inputMaze(left.column, left.row) == WHITE) {
			//if valid move, add to the new deque
			newMoves.pushBack(left);
		}
		state right;
		if (pos.column + 1 < inputMaze.width()) {
			right.column = pos.column + 1;
		}
		else {
			right.column = pos.column;
		}
		right.row = pos.row;
		right.depth = depth;
		if (inputMaze(right.column, right.row) == WHITE) {
			//if valid move, add to the new deque
			newMoves.pushBack(right);
		}
		state up;
		up.column = pos.column;
		if (pos.row + 1 < inputMaze.height()) {
			up.row = pos.row + 1;
		}
		else {
			up.row = pos.row;
		}
		up.depth = depth;
		if (inputMaze(up.column, up.row) == WHITE) {
			//if valid move, add to the new deque
			newMoves.pushBack(up);
		}
		state down;
		down.column = pos.column;
		down.row = pos.row - 1;
		down.depth = depth;
		if (inputMaze(down.column, down.row) == WHITE) {
			//if valid move, add to the new deque
			newMoves.pushBack(down);
		}
		while (!newMoves.isEmpty()) {
			state checkState = newMoves.front();
			newMoves.popFront();
			if (explored(checkState.column, checkState.row) != BLACK) {
				explored(checkState.column, checkState.row) = BLACK;
				frontier.pushBack(checkState);
			}
		}
		depth++;
	}
	writeToFile(inputMaze, outputFile);
	return false;
}
