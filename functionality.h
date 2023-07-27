//---Piece Starts to Fall When Game Starts---//


int update_score(int s=0);
bool game_over();
void check_point(int shrink);
void right_move();
void left_move();
void rotation(int shrink);
void fall_through(int arr[4][2], int shrink);
void make_shadow(int shad[4][2], float &timer, int shrink);
void halt(int &pause, float &timer, float &bomb_timer);
void bomb_reset(int& bombColor, int bomb[]);
bool bomb_anamoly(int bomb[], int shrink);
void fallingPiece(float& timer, float& delay, int colorNum[], int &shape, int shrink, float speed);
void falling_bomb(float& timer, float& delay, int& bombColor, int bomb[], int &bomb_flag, int shrink);



void fallingPiece(float& timer, float& delay, int colorNum[], int &shape, int shrink, float speed){
    
    if (timer>delay)
    {
        for (int i=0;i<4;i++)
        {
            point_2[i][0]=point_1[i][0];
            point_2[i][1]=point_1[i][1];
            point_1[i][1]+=1;                   //How much units downward
            
        }
        
        if (!anamoly(shrink))
        {
        	for(int i=0;i<4;i++)
        		gameGrid[point_2[i][1]][point_2[i][0]] = colorNum[4];
        	
        	check_point(shrink);	// checks if there are any rows to be destroyed
 
   	    	delay = speed;		// reset speed of next block 
   	    	
            for (int i=0;i<4;i++)
            {
				point_1[i][0] = next_block[4][i] / 2;	// x-axis
               	point_1[i][1] = next_block[4][i] % 2;	// y-axis

            }
            
            shape = rand()%7;	// random shape
            
            
           	for(int i=4; i>0; i--)
        	{   		
				for(int j=0; j<4; j++)
        			next_block[i][j] = next_block[i-1][j];	// Shifting each block one higher 0 into 1 and 1 into 2 etc
        			
        		colorNum[i] = colorNum[i-1];	// Shifting each color one higher 0 into 1 and 1 into 2 etc
        	}	
        	
        	for(int j=0; j<4; j++)
        		next_block[0][j] = BLOCKS[shape][j];	   // Randomising the last block
        		
        	colorNum[0] = rand()%7 + 1;				// Randomising the last color
        		
        		
        }
        timer=0;
    }
    
}

void check_point(int shrink)
{

	int flag = 1, s=0, i;		// s is number of rows destroyed
	int temp[4]={0};		// Size of 4 bcz at a time max 4 rows can be destroyed

	for(int i=shrink-1; i>=0; i--)		// loops through each grid row starting from M-1 as we are also including 0
	{
		for(int j=0; j<N; j++)		// loops through each grid column
		{
			if(gameGrid[i][j] == 0)		// if any block in grid is empty, then
			{	
				flag = 0;				
				break;					// skips the rest iteration and goes to next row
			}	
		}
		
		if(flag)		// if a row is completely filled
		{
			temp[s] = i;	// store that particular row number into an array
			s++;			// move to next index of the array
		}
		
		flag = 1;		// so that next row could also be evaluated
	}	
	
	if(temp[0] != 0)		// Checks if the array is modified
	{
		for(int l=0; l<=s; l++)		// looping through element in the array
		{
			i = temp[l];			// storing each filled row index
			for(int j=0; j<N; j++)
				gameGrid[i][j] = 0;	   // Destroying each row that is completely filled
		}
			
		for(int l=temp[0]; l>=s; l--)		// looping from respective row to upwards till the sth row like if 4 rows are destroyed
		{									// then we are briinging 4 rows downward so it should go till 4th row								
				
			for(int j=0; j<N; j++)	// looping through each column
				gameGrid[l][j] = gameGrid[l-s][j];	// bringing upper row downwards by l-s i.e the emptied gap could be 1-4, 
		}											// depending on rows destroyed at a time.
				
	}
	update_score(s);
}


void right_move()		// moves the block right
{
	for(int i=0; i<4; i++)
  		if(point_1[i][0]>=N-1 || game_over())	
			return;
				
	for(int i=0; i<4; i++)
	{
		point_2[i][0]=point_1[i][0];
        point_2[i][1]=point_1[i][1];
		point_1[i][0] += 1; 
	}
	
}


void left_move()	// moves the block left
{
	for(int i=0; i<4; i++)
  		if(point_1[i][0]<1 || game_over())
			return;
				
	for(int i=0; i<4; i++)
	{
		point_2[i][0]=point_1[i][0];
        point_2[i][1]=point_1[i][1];
		point_1[i][0] -= 1; 
	}
	
}


void rotation(int shrink)	// rotates the block
{

	int x, y, dummy[4][2];
	int temp_x = point_1[0][0];		// Center point(x-cor)
	int temp_y = point_1[0][1];		// Center point(y-cor)
	
	for(int i=0; i<4;i++)
	{
		x = point_1[i][1] - temp_y;		// new x
		y = point_1[i][0] - temp_x;		// new y
		dummy[i][0] = temp_x - x; 			// storing in dummy to avoid unwanted rotation
		dummy[i][1] = temp_y + y;
		
		if (dummy[i][0]<0 || dummy[i][0]>=N || dummy[i][1]>=shrink || dummy[i][1]<0)
            return;
        else if (gameGrid[dummy[i][1]][dummy[i][0]])
            return;
     } 
       
     for(int i=0; i<4;i++)
     {      
    	point_1[i][0] = dummy[i][0];
    	point_1[i][1] = dummy[i][1];       
   
	 }
	
}


bool game_over()
{

	for(int j=0; j<N; j++)
		if(gameGrid[0][j])
			return 1;
	return 0;
}


int update_score(int s)		// Updates score acc. to lines destroyed
{
	static int score=0;
	
	if(s==1)
		score += 10;
		
	else if(s==2)
		score += 30;
		
	else if(s==3)
		score += 60;
		
	else if(s==4)
		score += 100;			

	return score;
}


void fall_through(int arr[4][2], int shrink)	// block falls at once
{


	while(true)
	{
		for(int i=0; i<4; i++)		
			if(arr[i][1] >= shrink-1 || gameGrid[arr[i][1]+1][arr[i][0]])	// till block reaches end or 
				return;														// on another block
		
		for(int i=0; i<4; i++)
			arr[i][1] += 1;	

	}
	
}


void make_shadow(int shad[4][2], float &timer, int shrink)		// makes the shadow of block
{
	
	for(int i=0; i<4; i++)
	{
		shad[i][0] = point_1[i][0];
		shad[i][1] = point_1[i][1];
	}
		
	fall_through(shad, shrink);

}


void halt(int &pause, float &timer, float &bomb_timer)		// pauses the game
{
	if(pause)
	{
		timer = 0;
		bomb_timer = 0;
	}
}


void bomb_reset(int& bombColor, int bomb[])		// Resets the bomb after it has fallen
{

	bomb[0] = rand()%9 + 1; 
  	bomb[1] = -3;   	
    bombColor = rand()%7 + 1;

}


bool bomb_anamoly(int bomb[], int shrink)		// checks if bomb has fallen
{
	if (bomb[1] >= shrink || gameGrid[ bomb[1] ][ bomb[0] ])
		return 0;

	return 1;


}


void falling_bomb(float& timer, float& delay, int& bombColor, int bomb[], int &bomb_flag, int shrink)
{
	static int counter = 0;		// to check if bomb has started falling
	
	
	if(bomb_flag != 0)		// if bomb is to be dropped
	{	
		if (counter==0)		// if the bomb is being dropped
			bomb[1] = 0;		// start bomb to fall from top of grid
			
		
		counter++;	
		
		if (timer>delay)
		{
				 
		    	bomb[1] += 1;		// bomb falls downward one step
		    
		    if ( !bomb_anamoly(bomb, shrink) )
		    {
		    
				if(bomb[1]>= shrink)	// bomb reached dropped at vacant spot
				{
					bomb_reset(bombColor, bomb);	// reset bomb position
					counter = 0;
					bomb_flag = 0;
		        	return;
				}
				
		    	if(gameGrid[ bomb[1] ][ bomb[0] ] == bombColor)		// if bomb dropped on same color block
		    	{
					for(int i=shrink-1; i>=0; i--)		// loops through each grid row starting from M-1 as we are also including 0
					{
						for(int j=0; j<N; j++)		// loops through each grid column
							gameGrid[i][j] = 0;				
					}		
				}
				
				else		// if bomb dropped on different color block
				{
					int row = bomb[1];
					int col = bomb[0];
					
					gameGrid[row][col] = 0; 	// four blocks will be destroyed
					gameGrid[row][col-1] = 0;	
					
					if(row + 1 < shrink)
					{
						gameGrid[row+1][col] = 0;
						gameGrid[row+1][col-1] = 0;	
					}	
				}
				
				counter = 0;
				bomb_flag = 0;
				bomb_reset(bombColor, bomb);
		    }	 

		    timer=0;
		}
	}
}



