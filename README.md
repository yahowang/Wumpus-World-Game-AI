# Wumpus World Game AI
This is an AI project for Wumpus World for CS 171 at University of California Irvine. 
Wumpus World is a partially observable, deterministic, sequential, static, discrete, and single-agent world.

The Wumpus World is a cave consisting of rooms connected by passageways. Lurking
somewhere in the cave is the terrible wumpus, a beast that eats anyone who enters its room.
The wumpus can be shot by an agent, but the agent has only one arrow. Some rooms contain
bottomless pits that will trap anyone who wanders into these rooms (except for the wumpus,
which is too big to fall in). The only mitigating feature of this bleak environment is the
possibility of finding a heap of gold. A concrete definition of the game is given by this PEAS
description:

1) Performance Measure
The performance measure of an agent is an integer score calculated based on the following:
  Start at 0 points
  -1 point for each action taken
  -10 for using the arrow (additional to the -1 point)
  -1000 points for falling into a pit or being eaten by the wumpus
  +1000 for climbing out of the cave with the gold
  
The game ends either when the agent dies, when the agent climbs out of the cave, or when
the agent’s score goes below -1000.
