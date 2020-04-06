// ======================================================================
// FILE:        MyAI.hpp
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

#ifndef MYAI_LOCK
#define MYAI_LOCK

#include "Agent.hpp"
#include<vector>
#include<queue>
#include<map>
#include<algorithm>
#include<iostream>

class MyAI : public Agent
{
public:
	MyAI ( void );
	
	Action getAction
	(
		bool stench,
		bool breeze,
		bool glitter,
		bool bump,
		bool scream
	);
	
	// ======================================================================
	// YOUR CODE BEGINS
	// ======================================================================

private:
	enum Direction{								// This is used for labeling what direction out agent is facing at
		up,
		down,
		left,
		right,
	};

	enum Orientation{							// This is the absolute orientation depends on the world
		North,
		South,
		East,
		West,
	};

	struct Cell									// A Cell represents a position in the world
	{
		Cell(){}								// Constructor
		bool visited = false;					// if the cell has been visited

		bool N_avail = true;					// if the agent is allowed to move North from the cell; it is for boundary checking
		bool W_avail = true;					// if the agent is allowed to move West from the cell; it is for boundary checking
		bool S_avail = true;					// if the agent is allowed to move South from the cell; it is for boundary checking
		bool E_avail = true;					// if the agent is allowed to move East from the cell; it is for boundary checking
		
		int WL = 0;								// tri-nary label for deciding if a wumpus is in the cell.
												// WL = -1: absolutely no wumpus;
												// WL = 0: unchecked yet;
												// WL > 0: possible wumpus

		int PL = 0;								// tri-nary label for deciding if a pit is in the cell.
												//PL = -1 : absolutely no pit;
												//PL = 0 : unchecked yet;
												//PL > 0 : possible pit
	};

	std::vector<std::vector<Cell>> worldMap;	// the 2D world map
	std::queue<Action>  action_future; 		 	// stores what actions will happen in the future
	std::vector<Orientation> orientation_past;	// records orientation movements


	void no_more_wumpus(int x, int y);			// call this function right when you are sure the wumpus is going to be killed, x, y is where wumpus is.
												// It sets wumpus_dead = true and sets WL in every Cell to be -1.

	void chooseMove();							// provides a valid move and stacks the move to action_future

	void moveNorth();							// stacks a series of actions to action_future to produce a "move to North" move
	void moveSouth();							// stacks a series of actions to action_future to produce a "move to South" move
	void moveEast();							// stacks a series of actions to action_future to produce a "move to East" move
	void moveWest();							// stacks a series of actions to action_future to produce a "move to West" move
	void moveBack();							// stacks a series of actions to action_future to produce a "move one step Back" move

	void shootWumpus(int wumpusCounter);							// keeps tracking the position of the wumpus and will shoot it if possible
 	void climb();								// stacks CLIMB to action_future
	void grab();								// stacks GRAB to action_future
	void hit_wall();							// call this when the agent hits any wall
												// It sets false to the avail flag in the cells corresponding to the positionX or positionY and corrects the position.

	Action ExecuteAction();						// return an Action from action_future
	void time_to_go_home();						// initializes go home procedure and starts to move Back.

	int positionX = 0;				   			// current agent's x position
	int positionY = 0;				   			// current agent's y position
	int dimentionX = 0;				   			// agent's feeling of world x dimention
	int dimentionY = 0;				   			// agent's felling of world y dimention
	Direction facing = right;					// records what direction our agent is facing at

	bool go_home = false;			   			// if agent  wants to go home or not
	bool arrow = true;				   			// if arrow is available
	bool wumpus_dead = false;		   			// if wumpus is dead

	Orientation _facingOrientation();			// helper function. Converts current facing to current Orientation

	int _orientationToInt(Orientation o);		// helper function. Converts the given Orientation to int
	void _avail_mark_off(int X, int Y, std::vector<Orientation> mark_where);	// helper function. Disabling the given orientation in cell in position X and position Y
	void _moveTo(Orientation o);				// helper function. Moves to the given Orientation
	void _change_facing(Action action); 		// helper function. Feeds with TURN_RIGHT or TURN_LEFT to change agent's facing.
	void _shootNorth();							// helper function. Shoot the arrow at Orientation::North
	void _shootSouth();							// helper function. Shoot the arrow at Orientation::South
	void _shootEast();							// helper function. Shoot the arrow at Orientation::East
	void _shootWest();							// helper function. Shoot the arrow at Orientation::West
	bool _check_unvisited_save_cell(int x, int y);	// helper function. Checks if the given position is an unvisited safe cell.
	void _turnLeft();							// helper function. Stacks a series of actions to action_future to produce a "turn right" move
	void _turnRight();							// helper function. Stacks a series of actions to action_future to produce a "turn left" move
	void _turnBack();							// helper function. Stacks a series of actions to action_future to produce a "turn back" move
	std::vector<std::vector<Orientation>> _find_optimal_paths_to(int x, int y, std::vector<Orientation> combination);
	int _cost(std::vector<Orientation> optimal);// helper function. Returns the cost of an optimal path.
	void _modify_past(std::vector<Orientation> new_past, int dest_x, int dest_y);// helper function. Overrides the orientation_past to the new_past
	bool _find_optimal_home = false;			// helper variable. Determines if there is an optimal path to home
	Direction _directions[4] = {up,left,down,right};										// an array of Direction for changing facing
	std::map<Direction, int> _facing_index = {{up, 0}, {left, 1}, {down, 2}, {right, 3}};	// a map of std::pair<Direction, int> for changing facing
	std::vector<std::pair<int, int>> stench_visited_cell;	// a vector of visited cells that are stenchy.
	// ======================================================================
	// YOUR CODE ENDS
	// ======================================================================
};

#endif
