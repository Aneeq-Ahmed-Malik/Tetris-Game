/* This header contains the global/common variables of the project.
 * You don't really need to change anything.
 * */

//---Title: PTetris Game Project---//
const char title[] = "Tetris Game Project";

//---Height and Width of the Actual Interactive Game---//
const int M = 20;   //Number of rows for a piece to cover on the screen (not the entire screen) = 20
const int N = 10;   //Number of columns for a piece to cover on the screen (not the entire screen) = 10

//---The Actual Interactive Game Grid - Built Over (MxN)---//
int gameGrid[M][N] = {0};

//---To Hold the Coordinates of the Piece---//
int point_1[4][2]={0}, point_2[4][2]={0};

//---Check Uncertain Conditions---//
bool anamoly(int shrink){
    for (int i=0;i<4;i++)
        if (point_1[i][0]<0 || point_1[i][0]>=N || point_1[i][1]>=shrink)
            return 0;
        else if (gameGrid[point_1[i][1]][point_1[i][0]])
            return 0;
    return 1;
};
