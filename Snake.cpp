#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <conio.h>
#include<windows.h>
void gotoxy(short x, short y);    //here we declare the gotoxy function//
void SetColor(int ForgC);

#define Rows 20
#define Cols 20

void delay(float number_of_seconds);
void instructions(); 

struct body
{
	int X[Rows];
	int Y[Cols];
};

int main() 
{ 
	time_t t;
	struct body snake[(Cols*Rows)*2]; //Array to store the coordinates of snake body.
	char matrix[Cols][Rows]; //Array for the map.
	int ch = 0, x, y, i, j, rx, ry, p = 0, pos = 0, s = 0, b = 0, a, _a, start = 0, del = 0, reset = 0, exit = 0, load = 0;
	float speed = 30;
	
	pos = rand() % 5 + 1;
	
	srand((unsigned) time(&t));
	
	x = Rows / 2;
	y = Cols / 2;
	
	//Generate first food
	do
	{
		rx = rand() % (Rows - 2) + 1;
		ry = rand() % (Cols - 2) + 1;
	} while(rx != x && ry != y);
	
	//Make border
	for(j = 0; j < Rows; j++)
	{
		matrix[0][j] = '#';
		matrix[Cols-1][j] = '#';
	}
	for(i = 0; i < Cols; i++)
	{
		matrix[i][0] = '#';
		matrix[i][Rows-1] = '#';
	}
	
	//Initialize map
	for(i = 1; i < Cols-1; i++)
	{
		for(j = 1; j < Rows-1; j++)
		{
			matrix[i][j] = ' ';
		}
	}
	
	matrix[ry][rx] = '&';
	
	instructions();
	
	//Waiting for Enter key to be pressed to start the game.
	do
	{
		ch = _getch();
	}while(ch != 13);
	if(ch == 13) start = 1; // 13 is the ENTER key
	system("cls"); //Clear entire screen
	
	while(reset == 0)
	{
		if(load == 1)
		{
			
			pos = rand() % 5 + 1;
			x = Rows / 2;
			y = Cols / 2;
			
			//Generate first food
			do
			{
				rx = rand() % Rows;
				ry = rand() % Cols;
			} while(rx != x && ry != y);
			
			//Initialize map
			for(i = 1; i < Cols-1; i++)
			{
				for(j = 1; j < Rows-1; j++)
				{
					matrix[i][j] = ' ';
				}
			}
			
			matrix[ry][rx] = '&';
			s = 0;
			p = 0;
			
			load = 0;
		}
		
	    while(start)
		{
			//Generate new food every time when the last one is eaten.
			if(x == rx && y == ry)
			{
				for(i = a; i < s; i++)
				{
					rx = rand() % (Rows - 2) + 1;
					ry = rand() % (Cols - 2) + 1;
					if(rx != snake[i].X[i] && ry != snake[i].Y[i]) break;
				}
				p++;
			} 
			
			matrix[ry][rx] = '&'; //Puts the food in the array for map
			
			//This runs ones and makes start a little bit clear.
			if(del == 0)
			{
				del = 1;
				
				matrix[y][x] = '@'; //Puts the head of the snake in the array for map.
				//Printing the hole map.
				for(i = 0; i < Cols; i++)
				{
					for(j = 0; j < Rows; j++)
					{
						if(matrix[i][j] == '#') SetColor(15);
						if(matrix[i][j] == '@') SetColor(10);
						if(matrix[i][j] == '&') SetColor(14);
						if(i == y && j == x) SetColor(12);
						putchar(matrix[i][j]);
					}
					printf("\n");
				}
				printf("\n\n	Score:%d     Speed:%.1f", p, speed);
				delay(1000);
				matrix[y][x] = ' ';
				system("cls");
			}
			
			//This switch-case moves the snake.
			switch(pos)
			{
				case 1: 	y--;
							if(y < 1) y = (Cols-1) - 1; break; //UP
							
				case 2: 	y++;
							if(y == (Cols-1)) y = 1; break; //DOWN
							
				case 3: 	x--;
							if(x < 1) x = (Rows-1) - 1; break; //LEFT
							
				case 4: 	x++;
							if(x == (Rows-1)) x = 1; break; //RIGHT
			}
			
			//Store new coordinates of head in the array for the hole snake.
			snake[s].X[s] = x;
			snake[s].Y[s] = y;
			
			matrix[y][x] = '@'; //Puts the head of the snake in the array for map.
			
			a = s-p; //Calculates the size of the snake in the snakes array.
			
			//Check if the head colide with some part of the body.
			for(i = a; i < s; i++)
			{
				if(x == snake[i].X[i] && y == snake[i].Y[i]) b = 1;
			}
			
			//Printing map
			for(i = 0; i < Cols; i++)
			{
				for(j = 0; j < Rows; j++)
				{
					if(matrix[i][j] == '#') SetColor(15);
					if(matrix[i][j] == '@') SetColor(10);
					if(matrix[i][j] == '&') SetColor(14);
					if(i == y && j == x) SetColor(12);
					printf("%c ", matrix[i][j]);
				}
				printf("\n");
			}
			SetColor(15);
			
			if(b == 1) break; //If the snake head colide with the snake body the game stops.
			
			//Checks if part of the body is not in the end ot the array. This part clears the snake tail.
			if(a >= 0) 
			{
				matrix[snake[a].Y[a]][snake[a].X[a]] = ' ';
			}
			else 
			{
				_a = (Rows*Cols) + a;
				matrix[snake[_a].Y[_a]][snake[_a].X[_a]] = ' ';
			}
			
			//Passing in the snake array.
			s++;
			if(s == (Rows*Cols)) s = 0;
			
			//Checks if key is pressed.
			if(kbhit() != 0)
			{
				ch = _getch(); //Some keys are send in two parts. For that we have 2 _getch().
				if(ch == 0 || ch == 224)
				{
					switch(_getch())
					{
						case 72:	if(pos != 2) pos = 1;    break; //72 is the UP-ARROW key
									
						case 80: 	if(pos != 1) pos = 2;    break; //80 is the DOWN-ARROW key
						
						case 75: 	if(pos != 4) pos = 3;    break; //75 is the LEFT-ARROW key
						
						case 77:	if(pos != 3) pos = 4;    break; //77 is the RIGHT-ARROW key
						
						case 81:	if(speed <= 40) //81 is the PGDOWN key
									{
										if(speed >= 10) 				speed = speed + 10;
										if(speed >= 1 && speed < 10) 	speed = speed + 1;
										if(speed <= 0.9) 				speed = speed + 0.1;
									} break;
									
						case 73:	if(speed > 0.2) //73 is the PGUP key
									{
										if(speed >= 20) 			 	speed = speed - 10;
										if(speed > 1 && speed <= 10) 	speed = speed - 1;
										if(speed <= 1) 			 	 	speed = speed - 0.1;
									} break;
					}
				}
				else if(ch == 112) break;
				else if(ch == 27) 
				{
					exit = 1;
					break; //Checks if Esc key is pressed.
				}
			}
			printf("\n\n	Score:%d     Speed:%.1f", p, speed);
			delay(speed); //The delat is used for speed of the snake.
			gotoxy(0,0);
			//system("cls");
		}
		if(b == 1) //If snake head is colided with the tail prints GAME OVER. If the game is 
		{		  //closed using the Esc key the "GAME OVER" is not printed.
			SetColor(4);
			printf("\n	   !!!GAME OVER!!!");
			SetColor(15);
		}
		printf("\n	Score:%d     Speed:%.1f\n", p, speed);
		
		printf("	 For restart press R.\n");
		printf("	  For exit press X.\n\n");
		
		reset = 1;
		if(exit == 0)
		{
			if(b == 1)
			{
				do
				{
					ch = _getch();
				}while(ch != 114 && ch != 120);
			}
			else
			{
				do
				{
					ch = _getch();
				}while(ch != 112 && ch != 114 && ch != 120);
			}
			
			if(ch == 112)
			{
				system("cls");
				reset = 0;
			}
			
			if(ch == 114) 
			{
				system("cls");
				reset = 0;
				load = 1;
			}
			b = 0;
			if(ch == 120) break;
		}
		else break;
	}
	
	return 0;
} 

void instructions()
{
	printf("\n			     Snake Game\n\n");
	printf("		Control the snake with the arrow keys.\n");
	printf("		    Use PgUp for increasing speed.\n");
	printf("		   Use PgDown for decreasing speed.\n");
	printf("		  	   Use P for pause.\n");
	printf("		      Use Esc for exit the game.\n\n");
	printf("			For START press ENTER!");
}

void delay(float number_of_seconds) 
{ 
    // Converting time into milli_seconds 
    float milli_seconds =  number_of_seconds; 
  
    // Storing start time 
    clock_t start_time = clock(); 
  
    // looping till required time is not achieved 
    while (clock() < start_time + milli_seconds); 
} 

void gotoxy(short x, short y)           //definition of gotoxy function//                                               
{
 COORD pos ={x,y};
 SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

void SetColor(int ForgC)
 {
     WORD wColor;

      HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
      CONSOLE_SCREEN_BUFFER_INFO csbi;

                       //We use csbi for the wAttributes word.
     if(GetConsoleScreenBufferInfo(hStdOut, &csbi))
     {
                 //Mask out all but the background attribute, and add in the forgournd     color
          wColor = (csbi.wAttributes & 0xF0) + (ForgC & 0x0F);
          SetConsoleTextAttribute(hStdOut, wColor);
     }
     return;
 }
