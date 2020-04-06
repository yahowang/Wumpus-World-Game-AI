// ======================================================================
// FILE:        MyAI.cpp
//
// AUTHOR:      Abdullah Younis
//
// DESCRIPTION: This file contains your agent class, which you will
//              implement. You are responsible for implementing the
//              'getAction' function and any helper methods you feel you
//              need.
//
// NOTES:       - If you are having trouble understanding how the shell
//                works, look at the other parts of the code, as well as
//                the documentation.
//
//              - You are only allowed to make changes to this portion of
//                the code. Any changes to other portions of the code will
//                be lost when the tournament runs your code.
// ======================================================================

#include "MyAI.hpp"

MyAI::MyAI() : Agent()
{
	// ======================================================================
	// YOUR CODE BEGINS
	// ======================================================================
	for (int i = 0; i < 11; ++i)
	{
		std::vector<Cell> Column;
		for (int j = 0; j < 11; ++j)
		{
			Cell cell{};
			if (i == 0)
				cell.W_avail = false;
			if (j == 0)
				cell.S_avail = false;
			Column.push_back(cell);
		}
		worldMap.push_back(Column);
	}

	worldMap[0][0].visited = true;
	// ======================================================================
	// YOUR CODE ENDS
	// ======================================================================
}
	
Agent::Action MyAI::getAction
(
	bool stench,
	bool breeze,
	bool glitter,
	bool bump,
	bool scream
)
{
	// ======================================================================
	// YOUR CODE BEGINS
	// ======================================================================
	// This is only for checking at the initial position


	worldMap[0][0].visited = true;

	if (action_future.size())
		return ExecuteAction();

	if (positionX == 0 && positionY == 0 && !go_home)
	{
		if (breeze)
		{
			climb();
			return ExecuteAction();
		}

		worldMap[0][1].PL = -1;
		worldMap[1][0].PL = -1;

		if (scream)
			no_more_wumpus(1,0);

		if (stench && !wumpus_dead)
		{	
			if (arrow)
			{	
				_shootEast();
				return ExecuteAction();		
			}
			else
			{
				for (int i = 0; i < 11; ++i)
					for (int j = 0; j < 11; ++j)
						worldMap[i][j].WL = -1;
				worldMap[0][1].WL = 1;
			}
		}

		chooseMove();
		return ExecuteAction();
	}

	if (go_home)
	{
		time_to_go_home();
		return ExecuteAction();
	}

	if (glitter)
	{
		grab();
		return ExecuteAction();
	}

	if (bump)
	{
		hit_wall();
		chooseMove();
		return ExecuteAction();
	}

	int wumpusCounter = 0;

	if ((!breeze && !stench) || (!breeze && stench && wumpus_dead)) 
	{
		auto current = worldMap[positionX][positionY];

		if (current.N_avail && !worldMap[positionX][positionY + 1].visited)
		{
			worldMap[positionX][positionY + 1].PL = -1;
			worldMap[positionX][positionY + 1].WL = -1;
		}

		if (current.S_avail && !worldMap[positionX][positionY - 1].visited)
		{
			worldMap[positionX][positionY - 1].PL = -1;
			worldMap[positionX][positionY - 1].WL = -1;
		}

		if (current.E_avail && !worldMap[positionX + 1][positionY].visited)
		{
			worldMap[positionX + 1][positionY].PL = -1;
			worldMap[positionX + 1][positionY].WL = -1;
		}

		if (current.W_avail && !worldMap[positionX - 1][positionY].visited)
		{
			worldMap[positionX - 1][positionY].PL = -1;
			worldMap[positionX - 1][positionY].WL = -1;
		}
	}

	if ((breeze && !stench) || (breeze && stench && wumpus_dead)) 
	{
		auto current = worldMap[positionX][positionY];

		if (current.N_avail && !worldMap[positionX][positionY + 1].visited)
		{
			if (worldMap[positionX][positionY + 1].PL != -1)
				++worldMap[positionX][positionY + 1].PL;
			worldMap[positionX][positionY + 1].WL = -1;
		}	
		if (current.S_avail && !worldMap[positionX][positionY - 1].visited)
		{
			if (worldMap[positionX][positionY - 1].PL != -1)
				++worldMap[positionX][positionY - 1].PL;
			worldMap[positionX][positionY - 1].WL = -1;
		}
		if (current.E_avail && !worldMap[positionX + 1][positionY].visited)
		{
			if (worldMap[positionX + 1][positionY].PL != -1)
				++worldMap[positionX + 1][positionY].PL;
			worldMap[positionX + 1][positionY].WL = -1;
		}
		if (current.W_avail && !worldMap[positionX - 1][positionY].visited)
		{
			if (worldMap[positionX - 1][positionY].PL != -1)
				++worldMap[positionX - 1][positionY].PL;
			worldMap[positionX - 1][positionY].WL = -1;
		}
	}

	if (!breeze && stench && !wumpus_dead)
	{
		auto current = worldMap[positionX][positionY];

		if (current.N_avail && !worldMap[positionX][positionY + 1].visited)
		{
			worldMap[positionX][positionY + 1].PL = -1;
			if (worldMap[positionX][positionY + 1].WL != -1)
			{
				++worldMap[positionX][positionY + 1].WL;
				++wumpusCounter;
			}
		}
		if (current.S_avail && !worldMap[positionX][positionY - 1].visited)
		{
			worldMap[positionX][positionY - 1].PL = -1;
			if (worldMap[positionX][positionY - 1].WL != -1)
			{
				++worldMap[positionX][positionY - 1].WL;
				++wumpusCounter;
			}
		}
		if (current.E_avail && !worldMap[positionX + 1][positionY].visited)
		{
			worldMap[positionX + 1][positionY].PL = -1;
			if (worldMap[positionX + 1][positionY].WL != -1)
			{
				++worldMap[positionX + 1][positionY].WL;
				++wumpusCounter;
			}
		}
		if (current.W_avail && !worldMap[positionX - 1][positionY].visited)
		{
			worldMap[positionX - 1][positionY].PL = -1;
			if (worldMap[positionX - 1][positionY].WL != -1)
			{
				++worldMap[positionX - 1][positionY].WL;
				++wumpusCounter;
			}
		}
	}

	if (breeze && stench && !wumpus_dead)
	{
		auto current = worldMap[positionX][positionY];

		if (current.N_avail && !worldMap[positionX][positionY + 1].visited)
		{
			if (worldMap[positionX][positionY + 1].PL != -1)
				++worldMap[positionX][positionY + 1].PL;
			if (worldMap[positionX][positionY + 1].WL != -1)
			{
				++worldMap[positionX][positionY + 1].WL;
				++wumpusCounter;
			}
		}
		if (current.S_avail && !worldMap[positionX][positionY - 1].visited)
		{
			if (worldMap[positionX][positionY - 1].PL != -1)
				++worldMap[positionX][positionY - 1].PL;
			if (worldMap[positionX][positionY - 1].WL != -1)
			{
				++worldMap[positionX][positionY - 1].WL;
				++wumpusCounter;
			}
		}
		if (current.E_avail && !worldMap[positionX + 1][positionY].visited)
		{
			if (worldMap[positionX + 1][positionY].PL != -1)
				++worldMap[positionX + 1][positionY].PL;
			if (worldMap[positionX + 1][positionY].WL != -1)
			{
				++worldMap[positionX + 1][positionY].WL;
				++wumpusCounter;
			}
		}
		if (current.W_avail && !worldMap[positionX - 1][positionY].visited)
		{
			if (worldMap[positionX - 1][positionY].PL != -1)
				++worldMap[positionX - 1][positionY].PL;
			if (worldMap[positionX - 1][positionY].WL != -1)
			{
				++worldMap[positionX - 1][positionY].WL;
				++wumpusCounter;
			}
		}
	}

	if (arrow)
	{
		shootWumpus(wumpusCounter);
		if (action_future.size())
			return ExecuteAction();
	}

	chooseMove();
	return ExecuteAction();

	// ======================================================================
	// YOUR CODE ENDS
	// ======================================================================
}
// ======================================================================
// YOUR CODE BEGINS
// ======================================================================

Agent::Action MyAI::ExecuteAction()
{
	Action action = action_future.front();
	action_future.pop();
	_change_facing(action);
	worldMap[positionX][positionY].WL = -1;
	worldMap[positionX][positionY].PL = -1;
	return action;
}

void MyAI::no_more_wumpus(int x, int y)
{
	wumpus_dead = true;
	if (worldMap[x][y].N_avail)
	{
		worldMap[x][y+1].WL = -1;
		if ((worldMap[x][y+1].N_avail && !worldMap[x][y+2].visited) || (worldMap[x][y+1].E_avail && !worldMap[x+1][y+1].visited) || (worldMap[x][y+1].W_avail && !worldMap[x-1][y+1].visited))
		{
			if (worldMap[x][y+1].visited)
				stench_visited_cell.push_back(std::pair<int, int> {x, y+1});
			worldMap[x][y+1].visited = false;
		}
	}

	if (worldMap[x][y].S_avail)
	{
		worldMap[x][y-1].WL = -1;
		if ((worldMap[x][y-1].S_avail && !worldMap[x][y-2].visited) || (worldMap[x][y-1].E_avail && !worldMap[x+1][y-1].visited) || (worldMap[x][y-1].W_avail && !worldMap[x-1][y-1].visited))
		{
			if (worldMap[x][y-1].visited)
				stench_visited_cell.push_back(std::pair<int, int> {x, y-1});
			worldMap[x][y-1].visited = false;
		}
	}

	if (worldMap[x][y].E_avail)
	{
		worldMap[x+1][y].WL = -1;
		if ((worldMap[x+1][y].S_avail && !worldMap[x+1][y-1].visited) || (worldMap[x+1][y].E_avail && !worldMap[x+2][y].visited) || (worldMap[x+1][y].N_avail && !worldMap[x+1][y+1].visited))
		{
			if (worldMap[x+1][y].visited)
				stench_visited_cell.push_back(std::pair<int, int> {x+1, y});
			worldMap[x+1][y].visited = false;
		}
	}

	if (worldMap[x][y].W_avail)
	{
		worldMap[x-1][y].WL = -1;
		if ((worldMap[x-1][y].S_avail && !worldMap[x-1][y-1].visited) || (worldMap[x-1][y].W_avail && !worldMap[x-2][y].visited) || (worldMap[x-1][y].N_avail && !worldMap[x-1][y+1].visited))
		{
			if (worldMap[x-1][y].visited)
				stench_visited_cell.push_back(std::pair<int, int> {x-1, y});
			worldMap[x-1][y].visited = false;
		}
	}
	worldMap[0][0].visited = true;
}

void MyAI::chooseMove()
{
	auto current = worldMap[positionX][positionY];
	
	std::vector<Orientation> avail_orientation;

	if (current.E_avail)
	{
		auto neighbor = worldMap[positionX + 1][positionY];
		if (!neighbor.visited && neighbor.WL < 1 && neighbor.PL < 1)
			avail_orientation.push_back(East);
	}

	if (current.N_avail)
	{
		auto neighbor = worldMap[positionX][positionY + 1];
		if (!neighbor.visited && neighbor.WL < 1 && neighbor.PL < 1)
			avail_orientation.push_back(North);
	}

	if (current.W_avail)
	{
		auto neighbor = worldMap[positionX - 1][positionY];
		if (!neighbor.visited && neighbor.WL < 1 && neighbor.PL < 1)
			avail_orientation.push_back(West);
	}

	if (current.S_avail)
	{
		auto neighbor = worldMap[positionX][positionY - 1];
		if (!neighbor.visited && neighbor.WL < 1 && neighbor.PL < 1)
			avail_orientation.push_back(South);
	}
	
	Orientation current_facing_orientation = _facingOrientation();

	if (std::find(avail_orientation.begin(), avail_orientation.end(), current_facing_orientation) != avail_orientation.end())
	{
		_moveTo(current_facing_orientation);
		return;
	}

	
	if (avail_orientation.size())
	{
	/*	
		Orientation first;
		Orientation second;
		Orientation third;
		if (current_facing_orientation == North)
		{
			// T
			first = West;
			second = East;
			third = South;
		}
		if (current_facing_orientation == South)
		{
			// T
			first = East;
			second = West;
			third = North;
		}
		if (current_facing_orientation == West)
		{
			// F
			first = North;
			second = South;
			third = East;
		}
		if (current_facing_orientation == East)
		{
			// T
			first = South;
			second = North;
			third = West;
		}
		if (std::find(avail_orientation.begin(), avail_orientation.end(), first) != avail_orientation.end())
		{
			_moveTo(first);
			return;
		}
		if (std::find(avail_orientation.begin(), avail_orientation.end(), second) != avail_orientation.end())
		{
			_moveTo(second);
			return;
		}
		_moveTo(third);
*/
		_moveTo(avail_orientation.at(0));
		return;
	}

	if (positionX == 0 && positionY == 0)
	{
		climb();
		return;
	}

	int currentX = positionX;
	int currentY = positionY;

	bool home = true;
	std::vector<Orientation> copy_past = orientation_past;
	std::reverse(copy_past.begin(), copy_past.end());

	for (auto past : copy_past)
	{
		if (past == North)
		{
			if (
					(worldMap[currentX][currentY-1].W_avail && _check_unvisited_save_cell(currentX-1, currentY-1))
					||
					(worldMap[currentX][currentY-1].S_avail && _check_unvisited_save_cell(currentX, currentY-2))
					||
					(worldMap[currentX][currentY-1].E_avail && _check_unvisited_save_cell(currentX+1, currentY-1)))
			{
				--currentY;
				home = false;
				break;
			}
			--currentY;
		}

		if (past == South)
		{
			if (
					(worldMap[currentX][currentY+1].W_avail && _check_unvisited_save_cell(currentX-1, currentY+1)) 
					|| 
					(worldMap[currentX][currentY+1].N_avail && _check_unvisited_save_cell(currentX, currentY+2)) 
					|| 
			   		(worldMap[currentX][currentY+1].E_avail && _check_unvisited_save_cell(currentX+1, currentY+1)))
			{
			
				++currentY;
				home = false;
				break;
			}
			++currentY;
		}

		if (past == East)
		{
			if (
					(worldMap[currentX-1][currentY].W_avail && _check_unvisited_save_cell(currentX-2, currentY)) 
					|| 
					(worldMap[currentX-1][currentY].S_avail && _check_unvisited_save_cell(currentX-1, currentY-1))
					|| 
					(worldMap[currentX-1][currentY].N_avail && _check_unvisited_save_cell(currentX-1, currentY+1)))
			{
				--currentX;
				home = false;
				break;
			}
			--currentX;
		}


		if (past == West)
		{
			if (
					(worldMap[currentX+1][currentY].N_avail && _check_unvisited_save_cell(currentX+1, currentY+1))
					|| 
					(worldMap[currentX+1][currentY].S_avail && _check_unvisited_save_cell(currentX+1, currentY-1)) 
					|| 
					(worldMap[currentX+1][currentY].E_avail && _check_unvisited_save_cell(currentX+2, currentY)))
			{
				++currentX;
				home = false;
				break;
			}
			++currentX;
		}
	}
		
	if (home)
	{
		go_home = true;
		time_to_go_home();
		return;
	}
	

	std::vector<Orientation> combination;

	int delta_x = positionX - currentX;
	int delta_y = positionY - currentY;


	if (delta_y <= 0)
		for (int j = 0; j < -delta_y; ++j)
			combination.push_back(North);

	if (delta_x <= 0)
		for (int i = 0; i < -delta_x; ++i)
			combination.push_back(East);

	if (delta_y > 0)
		for (int j = 0; j < delta_y; ++j)
			combination.push_back(South);


	if (delta_x > 0)
		for (int i = 0; i < delta_x; ++i)
			combination.push_back(West);

	std::vector<std::vector<Orientation>> optimals = _find_optimal_paths_to(currentX, currentY, combination);
/*
	if (optimals.size())
	{
		int	opt_index = 0;
		for (int o_i = 0; o_i < optimals.size(); ++o_i)
		{	
			if (_cost(optimals.at(o_i)) < _cost(optimals.at(opt_index)))	
				opt_index = o_i;
		}
		_modify_past(optimals.at(opt_index), currentX, currentY);}
*/
	moveBack();
}

void MyAI::moveNorth()
{
	if (facing == left) _turnRight();
	if (facing == down) _turnBack();
	if (facing == right) _turnLeft();
	action_future.push(FORWARD);
	orientation_past.push_back(North);
	worldMap[positionX][++positionY].visited = true;
}

void MyAI::moveSouth()
{
	if (facing == up) _turnBack();
	if (facing == left) _turnLeft();
	if (facing == right) _turnRight();
	action_future.push(FORWARD);
	orientation_past.push_back(South);
	worldMap[positionX][--positionY].visited = true;
}

void MyAI::moveEast()
{
	if (facing == up) _turnRight();
	if (facing == left) _turnBack();
	if (facing == down) _turnLeft();
	action_future.push(FORWARD);
	orientation_past.push_back(East);
	worldMap[++positionX][positionY].visited = true;
}

void MyAI::moveWest()
{
	if (facing == up) _turnLeft();
	if (facing == down) _turnRight();
	if (facing == right) _turnBack();
	action_future.push(FORWARD);
	orientation_past.push_back(West);
	worldMap[--positionX][positionY].visited = true;
}

void MyAI::moveBack()
{
	Orientation orientation = orientation_past.back();
	orientation_past.pop_back();
	if (orientation == West)	moveEast();
	if (orientation == East)	moveWest();
	if (orientation == North)	moveSouth();
	if (orientation == South)	moveNorth();
	orientation_past.pop_back();
}

void MyAI::shootWumpus(int wumpusCounter)
{
	auto current = worldMap[positionX][positionY];
	if (     current.N_avail && !worldMap[positionX][positionY + 1].visited && (worldMap[positionX][positionY + 1].WL > 1 || (worldMap[positionX][positionY + 1].WL == 1 && wumpusCounter == 1)))
	{
		//if (worldMap[positionX][positionY + 1].PL != 2)
		{
			no_more_wumpus(positionX, positionY + 1);
			_shootNorth();
		}
	}
	if (current.S_avail && !worldMap[positionX][positionY - 1].visited && (worldMap[positionX][positionY - 1].WL > 1 || (worldMap[positionX][positionY - 1].WL == 1  && wumpusCounter == 1)))
	{
		//if (worldMap[positionX][positionY - 1].PL != 2)
		{
			no_more_wumpus(positionX, positionY - 1);
			_shootSouth();
		}
	}
	if (current.E_avail && !worldMap[positionX + 1][positionY].visited && (worldMap[positionX + 1][positionY].WL > 1 || (worldMap[positionX + 1][positionY].WL == 1  && wumpusCounter == 1)))
	{
		//if (worldMap[positionX + 1][positionY].PL != 2)
		{
			no_more_wumpus(positionX + 1, positionY);
			_shootEast();
		}
	}
	if (current.W_avail && !worldMap[positionX - 1][positionY].visited && (worldMap[positionX - 1][positionY].WL > 1 || (worldMap[positionX - 1][positionY].WL == 1  && wumpusCounter == 1)))
	{
		//if (worldMap[positionX - 1][positionY].PL != 2)
		{
			no_more_wumpus(positionX - 1, positionY);
			_shootWest();
		}
	}
	worldMap[positionX][positionY].visited = true;
}

void MyAI::climb()
{
	action_future.push(CLIMB);
}

void MyAI::grab()
{
	action_future.push(GRAB);
	go_home = true;
}

void MyAI::hit_wall()
{
	if (facing == right)
	{	
		worldMap[positionX--][positionY].visited = false;
		dimentionX = positionX;
		for (int j = 0; j < 11; ++j)
			_avail_mark_off(dimentionX, j, std::vector<Orientation>{East});
	}
	if (facing == up)
	{
		worldMap[positionX][positionY--].visited = false;
		dimentionY = positionY;
		for (int i = 0; i < 11; ++i)
			_avail_mark_off(i, dimentionY, std::vector<Orientation>{North});
	}
	if (facing == left)
		positionX++;
	if (facing == down)
		positionY++;
	orientation_past.pop_back();
}

void MyAI::time_to_go_home()
{
	if (stench_visited_cell.size())
	{
		for (auto cell : stench_visited_cell)
			worldMap[cell.first][cell.second].visited = true;
		stench_visited_cell.clear();
	}
	
	for (int i = 0; i < positionX; ++i)
		for (int j = 0; j < positionY; ++j)
			if (worldMap[i][j].WL < 1 && worldMap[i][j].PL == -1)
				worldMap[i][j].visited = true;

	if (!_find_optimal_home)
	{
		std::vector<Orientation> combination;
		for (int i = 0; i < positionY; ++i)
			combination.push_back(South);
		for (int j = 0; j < positionX; ++j)
			combination.push_back(West);
		
		std::vector<std::vector<Orientation>> optimals = _find_optimal_paths_to(0,0, combination);
	
		if (optimals.size())
		{
			_find_optimal_home = true;
			int	opt_index = 0;
			for (int o_i = 0; o_i < optimals.size(); ++o_i)
			{
				if (_cost(optimals.at(o_i)) < _cost(optimals.at(opt_index)))
					opt_index = o_i;
			}

			_modify_past(optimals.at(opt_index),0,0);
		}
	}

	if (orientation_past.size())
		moveBack();
	else
		climb();
}

std::vector<std::vector<MyAI::Orientation>> MyAI::_find_optimal_paths_to(int x, int y, std::vector<MyAI::Orientation> combination)
{
	std::vector<Orientation> true_path;
	std::vector<std::vector<Orientation>> optimals;
	
	std::vector<int> int_combination;
	for (auto o: combination)
	{
		int_combination.push_back(_orientationToInt(o));
	}
		
	do
	{
		true_path.clear();
		int currentX = positionX;
		int currentY = positionY;

		for (auto orientation : int_combination)
		{
			if (orientation == 3)
			{
				if (!worldMap[currentX][currentY - 1].visited)
					break;
				else
					{true_path.push_back(South);}
				currentY--;
			}
			if (orientation == 1)
			{
				if (!worldMap[currentX][currentY + 1].visited)
					break;
				else
					{true_path.push_back(North);}
				currentY++;
			}
			if (orientation == 4)
			{
				if (!worldMap[currentX - 1][currentY].visited)
					break;
				else
					{true_path.push_back(West);}
				currentX--;
			}
			if (orientation == 2)
			{
				if (!worldMap[currentX + 1][currentY].visited)
					break;
				else
					{true_path.push_back(East);}
				currentX++;
			}
		}		
		if (true_path.size() == int_combination.size() && currentX == x && currentY == y)
			optimals.push_back(true_path);

	}while(std::next_permutation(int_combination.begin(), int_combination.end()));
	return optimals;
}

int MyAI::_orientationToInt(Orientation o)
{
	if (o == North) return 1;
	if (o == East) return 2;
	if (o == South) return 3;
	return 4;
}

int MyAI::_cost(std::vector<Orientation> optimal)
{
	Direction temp_facing = facing;
	int cost = 0;
	for (auto orientation: optimal)
	{
		if (orientation == West)
		{
			if (temp_facing == up)		cost += 2;
			if (temp_facing == right)	cost += 3;
			if (temp_facing == left)	cost += 1;
			if (temp_facing == down)	cost += 2;
			temp_facing = left;
		}
		if (orientation == South)
		{
			if (temp_facing == up)		cost += 3;
			if (temp_facing == right)	cost += 2;
			if (temp_facing == left)	cost += 2;
			if (temp_facing == down)	cost += 1;
			temp_facing = down;
		}
		
		if (orientation == North)
		{
			if (temp_facing == up)		cost += 1;
			if (temp_facing == right)	cost += 2;
			if (temp_facing == left)	cost += 2;
			if (temp_facing == down)	cost += 3;
			temp_facing = up;
		}

		if (orientation == East)
		{
			if (temp_facing == up)		cost += 2;
			if (temp_facing == right)	cost += 1;
			if (temp_facing == left)	cost += 3;
			if (temp_facing == down)	cost += 2;
			temp_facing = right;
		}
	}
	return cost;
}

void MyAI::_modify_past(std::vector<Orientation> new_past, int dest_x, int dest_y)
{
	if (_find_optimal_home)
		orientation_past.clear();
	else
	{		
		int currentX = positionX;
		int currentY = positionY;
		int pop_num = 0;
		std::vector<Orientation> rev_orientation_past = orientation_past;
		std::reverse(rev_orientation_past.begin(), rev_orientation_past.end());

		for (auto orientation: rev_orientation_past)
		{
			pop_num++;
			if (orientation == West)
				currentX++;
			if (orientation == East)
				currentX--;
			if (orientation == North)
				currentY--;
			if (orientation == South)
				currentY++;
			if (currentX == dest_x && currentY == dest_y)
				break;
		}

		for (int i = 0; i < pop_num; ++i)
			orientation_past.pop_back();
	}

	std::reverse(new_past.begin(), new_past.end());
	for (auto o:new_past)
	{
		if (o == West)
			orientation_past.push_back(East);
		if (o == South)
			orientation_past.push_back(North);
		if (o == North)
			orientation_past.push_back(South);
		if (o == East)
			orientation_past.push_back(West);
	}
}

MyAI::Orientation MyAI::_facingOrientation()
{
	if (facing == up) return North;
	if (facing == right) return East;
	if (facing == down) return South;
	if (facing == left) return West;
}

void MyAI::_avail_mark_off(int X, int Y, std::vector<Orientation> mark_where)
{
	for (auto orientation:mark_where)
	{
		if (orientation == North)	worldMap[X][Y].N_avail = false;
		if (orientation == South)	worldMap[X][Y].S_avail = false;
		if (orientation == East)	worldMap[X][Y].E_avail = false;
		if (orientation == West)	worldMap[X][Y].W_avail = false;
	}
}

void MyAI::_moveTo(Orientation o)
{
	if (o == North) moveNorth();
	if (o == East) moveEast();
	if (o == South) moveSouth();
	if (o == West) moveWest();
}

void MyAI::_shootNorth()
{
	if (facing == left) _turnRight();
	if (facing == down) _turnBack();
	if (facing == right) _turnLeft();
	arrow = false;
	action_future.push(SHOOT);
}

void MyAI::_shootSouth()
{
	if (facing == up) _turnBack();
	if (facing == left) _turnLeft();
	if (facing == right) _turnRight();
	arrow = false;
	action_future.push(SHOOT);
}

void MyAI::_shootEast()
{
	if (facing == up) _turnRight();
	if (facing == left) _turnBack();
	if (facing == down) _turnLeft();
	arrow = false;
	action_future.push(SHOOT);
}

void MyAI::_shootWest()
{
	if (facing == up) _turnLeft();
	if (facing == down) _turnRight();
	if (facing == right) _turnBack();
	arrow = false;
	action_future.push(SHOOT);
}

bool MyAI::_check_unvisited_save_cell(int x, int y)
{
	return (!worldMap[x][y].visited) && (worldMap[x][y].PL < 1) && (worldMap[x][y].WL < 1);
}

void MyAI::_turnLeft()
{
	action_future.push(TURN_LEFT);
}

void MyAI::_turnRight()
{
	action_future.push(TURN_RIGHT);
}

void MyAI::_turnBack()
{
	action_future.push(TURN_LEFT);
	action_future.push(TURN_LEFT);
}

void MyAI::_change_facing(Agent::Action action)
{
	int old_index = _facing_index.at(facing);
	if (action == TURN_RIGHT)
	{
		if (old_index == 0)
			facing = _directions[3];
		else
			facing = _directions[--old_index];
	}
	if (action == TURN_LEFT)
	{
		if (old_index == 3)
			facing = _directions[0];
		else
			facing = _directions[++old_index];
	}
}
// ======================================================================
// YOUR CODE ENDS
// ======================================================================
