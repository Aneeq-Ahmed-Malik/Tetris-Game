/* You don't need to change anything in the driver code/main function except the part(s) where instructed.
 * You are expected to define your functionalities in the "functionality.h" header and call them here in the instructed part(s).
 * The game is started with a small box, you need to create other possible in "pieces.h" file in form of array.
    E.g., Syntax for 2 pieces, each having four coordinates -> int Pieces[2][4];
 * Load the images into the textures objects from img directory.
 * Don't make any changes to the "utils.h" header file except for changing the coordinate of screen or global variables of the game.
 * */

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <time.h>
#include "utils.h"
#include "pieces.h"
#include "functionality.h"
#include <sstream>
#include <string>
#include <fstream>
#include <cstring>

using namespace sf;
int main()
{
    srand(time(0));
    
    RenderWindow window(VideoMode(320, 480), title);
    Texture obj1, obj2, obj3, obj4;
    Font font;
    
//------------------------------Loading Textures from files-----------------------------------//
   
    font.loadFromFile("font/MachineGunk-nyqg.ttf");
    obj1.loadFromFile("img/tiles.png");
    obj2.loadFromFile("img/bg.jpg");
    obj3.loadFromFile("img/frame.png");
	obj4.loadFromFile("img/bomb.png");
	
 
//--------------------------Making different objects of Sprite-------------------------------// 
  
    Sprite sprite(obj1), background(obj2), frame(obj3), shadow(obj1), bomb(obj4); 
    Sprite next_piece1(obj1), next_piece2(obj1), next_piece3(obj1);
	Clock clock, clock1;

//-------------------------Managing Bomb Sound & Game Music----------------------------------//
 
	SoundBuffer buffer;
	Sound sound;
	Music music;
	
	buffer.loadFromFile("Sound/bomb_sound.wav");
	sound.setBuffer(buffer);
	
	music.openFromFile("Sound/game_sound.ogg");
	music.setLoop(true);
	music.setVolume(30);
	music.play();
	
//--------------------------------------------------------------------------------------------//



//-----------------------------Variables used throughout the Game-----------------------------//
 
    int delta_x=0, colorNum[5]={1,2,3,4,5}, shape=4, shad[4][2], pause=0;
    int point_3[4][2], point_4[4][2], point_5[4][2], playing_time, min; 
    float timer=0, delay=0.5, bomb_timer, bomb_delay=0.2, speed = 0.5;
	int scr, highscore=0, new_score, n, bomb_piece[2] = {5, -3};
	int sec, level = 1, new_min=0, shrink = M, bombColor = 4, bomb_flag=0;
      
		//  std::string bombColor[7] = {"Red", "Green","Pink", "Orange", "Cyan", "Blue", "Yellow"};
		
    int r[7] = {255,   0, 255, 255,   0,   0, 255};		// rgb color for bomb
    int g[7] = {  0, 255,   0,  69, 255,   0, 255};		
    int b[7] = {  0,   0, 255,   0, 255, 255,   0};
  
  
//---------------------------------------------------------------------------------------------//



//-------------------------------Different objects of Text Class-------------------------------//     


    Text text("Score", font), score("0", font), over("Game Over", font, 50); 
    Text time_min("00", font, 18), time_sec("00", font, 18), show_level("1", font, 20);
    Text high_score("0", font, 20), text1("   High\nscore", font, 15);
    
    
    //--------------------------Different settings for each text-----------------------//
    
	text.setFillColor(Color::Green);
	text.setPosition(235, 140);
	
	score.setPosition(260, 180);
	
	high_score.setFillColor(Color::Red);
	high_score.setPosition(290, 400);
	
	text1.setFillColor(Color::Green);
	text1.setPosition(235, 390);
	
	show_level.setPosition(235, 100);
	
    over.setStyle(Text::Bold);
    over.setPosition(50, 150);
    
    
//------------------------------------------------------------------------------------------------//    
    


//---------------------------------Reading Highscore from File------------------------------------//


    std::fstream infile("highscore.txt");	// decalring an object and opening the file
    
    while(!infile.eof())	// while the control doesn't reach the end of file
    {
    	infile>>scr;			// reading the score
    	
    	if(scr > highscore)
    		highscore = scr;
    	
    }
    
    infile.close();			// Closing the file
    
    high_score.setString(std::to_string(highscore));		// Updating the highscore text to be displayed



//-------------------------------------------------------------------------------------------------//


	for (int i=0;i<4;i++)		// So that first block isn't a single block
    {
		point_1[i][0] = next_block[4][i] / 2;	// x-axis
        point_1[i][1] = next_block[4][i] % 2;	// y-axis

    }


    while (window.isOpen())		
    {
    
	//---------------------------------Setting the time for Game-----------------------------------//    
	
	
		if (!game_over() && !pause)   	 
    		playing_time = clock1.getElapsedTime().asSeconds();
    		
    	min = playing_time / 60;
    	sec = playing_time % 60;
    	
    	time_min.setString(std::to_string(min) + "  :");	// To show time on screen
    	time_sec.setString(std::to_string(sec));

		time_min.setPosition(250, 450);			
		time_sec.setPosition(280, 450);    	
    	
    //---------------------------------------------------------------------------------------------//	
    	
    	
        float time = clock.getElapsedTime().asSeconds();
        clock.restart();
        timer += time;		
		bomb_timer += time;


    //----------------------------------Event Listening Part---------------------------------------//

        
        Event e;
        
        while (window.pollEvent(e))					// Event is occurring - until the game is in running state
        { 								                  
            if (e.type == Event::Closed)               // If cross/close is clicked/pressed
                window.close();                             // Opened window disposes
           
            if (e.type == Event::KeyPressed)              // If any other key (not cross) is pressed
            {
            	
            	if (e.key.code == Keyboard::Down)		// If down key is pressed; increase speed
            		if(!pause)									
            			delay *= 0.7;
            			
                if (e.key.code == Keyboard::Up)           // If down key is pressed; rotate shape
                {
                	if(!pause)
                    	rotation(shrink);                      
                }  
                  	
                else if (e.key.code == Keyboard::Left)     // If left key is pressed; move left
                {
                	if(!pause)
                    	left_move();                         
                }
                   	
                else if (e.key.code == Keyboard::Right)    // If right key is pressed; move right
                {
                	if(!pause)
                    	right_move();                       
                }    	
            }
        }
        
       
        if (Keyboard::isKeyPressed(Keyboard::Space))   //Just another way to detect key presses without event listener
        	if(!pause){
            	fall_through(point_1, shrink);        // If space is pressed block at once falls down
            	timer = 0;
            }
            
        if (Keyboard::isKeyPressed(Keyboard::P))      	// If P is pressed; game pauses, pause variable reverses
			pause = !pause;	



	//-------------------------------------End of Event listeners---------------------------------------//


        
		n = rand()%10000+1;		// So that bomb doesn't fall all the time
   	
   	
   		if(n==10)					// bomb falls only if n == 10
			bomb_flag++;
        
        
        if(bomb_flag != 0)		// When bomb has fallen; play bomb sound
        	sound.play();
        
        
     
        if(!game_over())	
        {
			       
        	falling_bomb(bomb_timer, bomb_delay, bombColor, bomb_piece, bomb_flag, shrink);		// bomb starts to fall
        	
        	fallingPiece(timer, delay, colorNum, shape, shrink, speed);      // piece starts to fall         
 
        	make_shadow(shad, timer, shrink);		// draw shadow 
        	halt(pause, timer, bomb_timer);				// pause the game
 
        	new_score = update_score();				// store the updated score in new_score
        	
        	score.setString(std::to_string(new_score));		// Update the score text to be displayed
        	
        }
        
        
        if(new_min < min)	// To check if one minute has passed 
        {
        
        	level += 1;			// increase the level
        	speed *= 0.9;			// increase the speed
        	new_min = min;		
        	shrink--;			// Grid shrinks
        
        }
        
        show_level.setString("Level :  " + std::to_string(level));		// show level on screen
        

        window.clear(Color::Black);	
        window.draw(background);
        
        
        for (int i=0; i<shrink; i++)
        {
            for (int j=0; j<N; j++)
            {
                if (gameGrid[i][j]==0)
                    continue; 
                sprite.setTextureRect(IntRect(gameGrid[i][j]*18,0,18,18));               
                sprite.setPosition(j*18,i*18); 
           
                sprite.move(28,31); //offset
                window.draw(sprite);
                
            }
        }
        
	//-----------------------------Suggestion blocks Arrays------------------------------//   
        
        for (int i=0;i<4;i++)
        {
			point_3[i][0] = next_block[4][i] / 2;	// x-axis
            point_3[i][1] = next_block[4][i] % 2;	// y-axis
            
            point_4[i][0] = next_block[3][i] / 2;	// x-axis
            point_4[i][1] = next_block[3][i] % 2;	// y-axis
            
            point_5[i][0] = next_block[2][i] / 2;	// x-axis
            point_5[i][1] = next_block[2][i] % 2;	// y-axis

        }
        
        
	
	//------------------------------For setting of block, shadow etc-----------------------------//
	        
        for (int i=0; i<4; i++)
        {
            sprite.setTextureRect(IntRect(colorNum[4]*18,0,18,18));
            sprite.setPosition(point_1[i][0]*18,point_1[i][1]*18);
            sprite.move(28,31);
            
            
            shadow.setTextureRect(IntRect(colorNum[4]*18,0,18,18));
            shadow.setPosition(shad[i][0]*18, shad[i][1]*18);
            shadow.setColor(Color(191, 175, 178, 110));
            shadow.move(28, 31);
            
            
            bomb.setScale(0.08, 0.08);
            bomb.setPosition(bomb_piece[0] * 18, bomb_piece[1]* 18);
            bomb.move(28, 31);
            bomb.setColor(Color(r[bombColor-1], g[bombColor-1], b[bombColor-1]));	// Using rgb color scheme
            
      
            //-----------------------No. of suggestions acc. to level-----------------------//
            
            if(level < 4){
	 			next_piece1.setTextureRect(IntRect(colorNum[3]*18,0,18,18));
	 			next_piece1.setPosition(point_3[i][0]*18, point_3[i][1]*18);
		        next_piece1.move(245, 240);
		        window.draw(next_piece1);
            }
            
            
            if(level < 3){
		        next_piece2.setTextureRect(IntRect(colorNum[2]*18,0,18,18));
	 			next_piece2.setPosition(point_4[i][0]*18, point_4[i][1]*18);
		        next_piece2.move(245, 290);
		        window.draw(next_piece2);
            }
            
            
            if(level < 2){
		        next_piece3.setTextureRect(IntRect(colorNum[1]*18,0,18,18));
	 			next_piece3.setPosition(point_5[i][0]*18, point_5[i][1]*18);
		        next_piece3.move(245, 340);
		        window.draw(next_piece3);
            }
            
            
            window.draw(bomb);
            window.draw(sprite);
            window.draw(shadow);
                          
        }

        
	//-----------------------The Final on Which Everything is Drawn Over is Loaded--------------------//
        
        window.draw(frame);
		window.draw(text);
        window.draw(score);
        window.draw(bomb);
        window.draw(text1);
        window.draw(high_score);
        window.draw(time_min);
        window.draw(time_sec);
 		window.draw(show_level);
 
        if(game_over())
			window.draw(over);
			
        window.display();
        
    }	// window closes
    
 	
 	//----------------------------------Writing the score of game in file------------------------------//
 	
 	std::ofstream myfile("highscore.txt", std::ios::app);
 	
 	myfile<<new_score<<"\n";
 	myfile.close();   
    
    return 0;
}
