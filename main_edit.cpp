#include<iostream>
#include<conio.h>
#include<dos.h>
#include <windows.h>
#include <time.h>
#include <chrono>
#include <unistd.h>

#define WIN_WIDTH 70

#define T1POS 15
#define T2POS 30
#define T3POS 45
#define DISKS 7

using namespace std;



HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
COORD CursorPosition;

class Game
{

public:
  int towers[3][DISKS];              // The three towers to fill one of them //
  int towerTop[3] = {DISKS-1,-1,-1};   // Top of the Stack of each tower //

int tries = 0;
int score = 0;


void gotoxy(int x, int y)             // To set Coordinates of any output on the screen //
{
	CursorPosition.X = x;
	CursorPosition.Y = y;
	SetConsoleCursorPosition(console, CursorPosition);
}
void setcursor(bool visible, DWORD size)
{
	if(size == 0)
		size = 20;

	CONSOLE_CURSOR_INFO lpCursor;
	lpCursor.bVisible = visible;
	lpCursor.dwSize = size;
	SetConsoleCursorInfo(console,&lpCursor);
}

void instructions()
{
    // In case the user does not know how to play //

	system("cls");
	cout<<"Instructions";
	cout<<"\n----------------";
	cout<<"\n  if Easy mode : Shift Disks from Tower 1 to Tower 3 or 2. \n";
	cout<<"\n  if Harder mode : Shift Disks from Tower 1 to specific tower .\n ";
	cout<<"\n You can not place large disk on small disk \n";
	cout<<"\n Towers are Numbered as 1,2 and 3 \n";
	cout<<"\n\nPress any key to go back to menu \n";
	getch();
}
void drawTile(int tower, int tileNo, int y)
{
    // Set the position of the TowerDisks //

	int x;
	if( tower == 1 )
        x = T1POS;
	else if( tower == 2 )
	 x = T2POS;
	else if( tower == 3 )
	x = T3POS;

	x -= tileNo;

	for(int j=0; j<((tileNo)*2)-1; j++){
		gotoxy(x,y);
		cout<<"±";
		x++;
	}
}

void drawTower(int tower)
{

	int y = 9;

	gotoxy(10, 10); cout<<"==========";
	gotoxy(25, 10); cout<<"==========";
	gotoxy(40, 10); cout<<"==========";

	gotoxy(15, 11); cout<<"1";
	gotoxy(30, 11); cout<<"2";
	gotoxy(45, 11); cout<<"3";

	for(int i=0; i<DISKS; i++) // Draw DISKS , we can change no. of them //
    {
		drawTile(tower, towers[tower-1][i], y);
		y--;
	}
}

int isEmpty(int towerNo)

{ // To check if The tower is empty of DISKS or not //

	for(int i=0; i<DISKS; i++)
		if( towers[towerNo][i] != 0 )
			return 0;
	return 1;
}

int validate(int top, int top2)

{  // Check the condition of the game that must the DISKS to be move smaller than the other //

	if( !isEmpty(top2) )
    {

		if( towers[top][towerTop[top]] < towers[top2][towerTop[top2]] )
			return 1;
		else
			    return 0;
	}
	return 1;
}
int move(int top, int top2)      // The structure of the game how to move DISK of tower to another //
{
    // If the current tower is empty then we will not move anything //

	if( isEmpty(top) )
        return 0;

    // If it isn't empty , Check the Condition of the Movement //

	if( validate(top, top2) )
	{
	    // If the Condition came true , Now we can move the level to another tower //

		if( towers[top][towerTop[top]] != 0 )
            {

			towerTop[top2]++;

			// By default top of the stack = -1 , now must be increased //

			towers[top2][towerTop[top2]] = towers[top][towerTop[top]];

			// Move the level From -> To //

			towers[top][towerTop[top]] = 0;

			// Clear the level from the current tower //

			towerTop[top]--;

			// the decrement the top to point to the last level in the tower (stack)

			return 1;
		}
	}
	return 0;
}
int win(char mode)
{
    // The user will choose the Mode of game //

    if(mode =='1')

	{   // Easier Mode that user can win if he could move the tower to any another one //

	    for(int i=0; i<DISKS; i++)
		      if (towers[2][i]!= DISKS-i )
                if (towers[1][i]!= DISKS-i )
                return 0;

	}
	if(mode =='2')

    { // Harder Mode that user can win only if he could move the tower to tower no 2 //

        for(int i=0; i<DISKS; i++)
            if (towers[1][i]!= DISKS-i )
            return 0;

    }
    if(mode =='3')

    { // Harder Mode that user can win only if he could move the tower to tower no 3 //

        for(int i=0; i< DISKS; i++)
            if (towers[2][i]!= DISKS-i )
            return 0;
    }

	return 1;
}

void play()
{
    auto start = chrono::steady_clock::now();

	int top , top2;
	int count=0;
	char mode;
	for(int i=0; i<DISKS; i++)

        // To start the game Put the complete tower in 1 //

		towers[0][i] = DISKS-i;
	for(int i=0; i< DISKS; i++)

	//Set empty
		towers[1][i] = 0;
	for(int i=0; i<DISKS; i++)
		towers[2][i] = 0;

   //Set empty
	   gotoxy(10,5);
	   cout<<"--> Enter your mode.. "<<endl<<endl;
		gotoxy(10,7);
		 cout<<"1.Easy (win either from tower 2 or tower 3)\n";
		 gotoxy(10,9);
		 cout<<"2.Win if move to tower number 2\n";
		gotoxy(10,11);
		 cout<<"3.Win if move to tower number 3\n";
		gotoxy(10,13);
		cout<<"--> Select option: ";

		// to choose the mode //
		mode = getche();

	do{

		system("cls");

		cout<<"============================================================"<<endl;
		cout<<"                       TOWER OF HANOI                       "<<endl;
		cout<<"============================================================"<<endl<<endl;

		drawTower(1);
		drawTower(2);
		drawTower(3);

		if( win(mode))

            { // check the conditions of Winning according to the chosen mode //

			system("cls");
			cout<<"============================================================"<<endl;
			cout<<"                           YOU WIN                          "<<endl;
			cout<<"============================================================"<<endl;
			cout<<endl<<endl<<endl;
			//sleep(3);
        auto end = chrono::steady_clock::now();
	 cout<<"Elapsed time in seconds: "<<chrono::duration_cast<chrono::seconds>(end - start).count()<<endl;
	 cout<<endl<<endl<<"Number of Moves is : "<<count<<endl;
			exit(0);

		}

		gotoxy(10,15);
		cout << "From (Values: 1,2,3): ";  // choose the Disk to be move from the tower //
		cin >> top;
		gotoxy(10,16);
		cout << "To (Values: 1,2,3): ";   // choose the tower that will accept the new disk //
		cin >> top2;

		if( top2 < 1 || top2 > 3 )     // towers are { 1 ,2 ,3 } only , if user entered invalid no. //
            continue;
		if( top < 1 || top > 3 )       // towers are { 1 ,2 ,3 } only , if user entered invalid no. //
		 continue;
		if( top == top2 )              // No Movement will happen ! //
            continue;

		top--; // Because array starts from 0 not 1 , we Make the towers starts from 1 to be shown for user //
		top2--;

		move(top, top2);
		count++;


		if(kbhit())
        {
         char ch = getch();
			if( ch=='a' || ch=='A' ){
			}
			if( ch=='d' || ch=='D' ){
			}
			if(ch==27){
				break;
			}
		}

	}
	while(1);
}


};

int main()
{


    Game game;
    game.setcursor(0,0);
	srand( (unsigned)time(NULL));

	do{
		system("cls");
		game.gotoxy(10,5); cout<<" -------------------------- ";
		game.gotoxy(10,6); cout<<" |     Tower of Hanoi     | ";
		game.gotoxy(10,7); cout<<" --------------------------";
		game.gotoxy(10,9); cout<<"1. Start Game";
		game.gotoxy(10,10); cout<<"2. Instructions";


		game.gotoxy(10,11); cout<<"3. Quit";
		game.gotoxy(10,13); cout<<"Select option: ";

		char op = getche();

        system("cls");

		// to choose option to start the game //

		if( op =='1')
            game.play();

		else if( op =='2')
            game.instructions();

		else if( op =='3')
		exit(0);

	}while(1);


	return 0;
}
