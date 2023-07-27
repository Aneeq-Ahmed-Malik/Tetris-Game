# Tetris Game built in C++

## Commands for compilation and running the Game

* g++ -c main.cpp
* g++ main.o -o sfml-app -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio
* ./sfml-app

### _Some description of gameplay_

* Score as Much as you can by completing the rows, max of 4 rows can be destroyed at a time
* Game is over when you get to the top
* After each minute level increments and the grid shrinks by one row
* Number of Suggestions reduce with increase in level
* Bomb falls at random instances
* If bomb falls on different color tile 4 tiles in its radius are destroyed
* If bomb falls on same color tile, All tiles are destroyed
* Press the down Key to speed up the falling process of block
* Press Spacebar to instantly bring down the block
* _Shadow_ of block helps to play the game
* Different sounds are embedded such as bomb fall and bomb exploding sounds, for better gameplay!


### All of the above aspects are shown in this video

[Tertris_Gameplay.webm](https://github.com/Aneeq-Ahmed-Malik/Tetris-Game/assets/140415409/ab7333ae-6dd9-4129-82dd-a1c1ecd9792a)
