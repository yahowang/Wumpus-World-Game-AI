# Wumpus World Game AI
This is an AI tournament project for Wumpus World for CS 171 at University of California Irvine.

My team was ranked top 10 among 150+ teams.

Wumpus World is a partially observable, deterministic, sequential, static, discrete, and single-agent world.

The Wumpus World is a cave consisting of rooms connected by passageways. Lurking
somewhere in the cave is the terrible wumpus, a beast that eats anyone who enters its room.
The wumpus can be shot by an agent, but the agent has only one arrow. Some rooms contain
bottomless pits that will trap anyone who wanders into these rooms (except for the wumpus,
which is too big to fall in). The only mitigating feature of this bleak environment is the
possibility of finding a heap of gold. A concrete definition of the game is given by this PEAS
description:

## Performance Measure
The performance measure of an agent is an integer score calculated based on the following:
 * Start at 0 points
 * -1 point for each action taken
 * -10 for using the arrow (additional to the -1 point)
 * -1000 points for falling into a pit or being eaten by the wumpus
 * +1000 for climbing out of the cave with the gold

The game ends either when the agent dies, when the agent climbs out of the cave, or when the agent’s score goes below -1000.

## Environment
The environment can be classified as partially observable, deterministic, sequential, static,
discrete, and single agent.
* An NxM grid of rooms, where 4 ≤ 𝑁, 𝑀 ≤ 10.
* The agent always starts in the bottom left square (1, 1), facing to the right.
* The locations of the gold and the wumpus are chosen randomly, with a uniform distribution, from the squares other than the start square.
* Each square other than the start can be a pit, with a 20% probability.
* The agent dies a miserable death if it enters a square containing a pit or a live wumpus.

## Actuators
* The agent can move **FORWARD**, **TURN_LEFT** by 90 degrees, or **TURN_RIGHT** by 90
degrees.
* The action **GRAB** can be used to pick up the gold if it is in the same square as the agent.
* The action **SHOOT** can be used to fire an arrow in a straight line in the direction the agent is facing. The arrow continues until it either hits and kills the wumpus or hits a wall. The agent has only one arrow, so only the first shoot action has any effect.
* The action **CLIMB** can be used to climb out of the cave, but only from square (1, 1).

## Sensors
* In the square containing the wumpus and in the directly (not diagonally) adjacent squares, the agent will perceive a **STENCH**.
* In the squares directly adjacent to a pit, the agent will perceive a **BREEZE**.
* In the square where the gold is, the agent will perceive a **GLITTER**.
* When an agent walks into a wall, it will perceive a **BUMP**.
* When the wumpus is killed, it emits a woeful **SCREAM** that can be perceived anywhere in the cave. This percept will only be sensed on the turn immediately after the wumpus's death.


