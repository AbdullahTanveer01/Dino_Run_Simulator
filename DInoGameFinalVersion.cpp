#include <iostream> 
#include <conio.h> 
#include <time.h>
#include <windows.h>
#include<stack>
#include<queue>
#include <cstdlib>
#include <ctime>

#define dinoPos 2
#define hurdlePos 74

using namespace std;

stack<int> scoreStack;
int score=0;

HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
COORD CursorPosition;
int dinoY;

 int speed = 40;
int gameover = 0;

class DinoGame{ 
  public: 

void gotoxy(int x, int y) {
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void setcursor(bool visible, DWORD size){
    if (size == 0) {
        size = 20; // default cursor size Changing to numbers from 1 to 20, decreases cursor width
    }
    CONSOLE_CURSOR_INFO lpCursor;
    lpCursor.bVisible = visible;
    lpCursor.dwSize = size;
    SetConsoleCursorInfo(console, & lpCursor);
}

void displayScore(stack<int> scoreStack, int score) {
 
  gotoxy(3, 3);cout << "Score: " ;
   gotoxy(10, 3);cout <<score ;
   // Iterate through the stack 
   while (!scoreStack.empty()) {
      scoreStack.pop();
   }
}


void Q_bar(){
   queue<int> q;

  // initialize the progress to 0
  int progress = 0;

  // set the total number of steps in the process
  int total_steps = 10;

  // get the current time
  clock_t start_time = clock();

  while (1) {
    // enqueue the current progress value
    q.push(progress);

    // increment the progress by 1
    progress++;

    // pause the program for 1 second
    clock_t end_time = clock();
    while ((float)(end_time - start_time) / CLOCKS_PER_SEC < 1.0) {
      end_time = clock();
    }
    start_time = end_time;

    // dequeue and display the front progress value
    if (!q.empty()) {
      gotoxy(50, 15);cout << "Progress: " << q.front() << "/10" << endl;
      q.pop();
    }

    // if the progress has reached the total number of steps, stop the loop
    if (progress >= total_steps) {
      break;
    }
  }
}
void init() {
    system("cls"); 
    gameover = 0;
    
    displayScore(scoreStack,score);
   
    for (int i = 0; i < 72; i++){
    	gotoxy(1+i, 0); cout<<"_";
		gotoxy(1+i, 1); cout<<"ß";
    	gotoxy(1+i, 25); cout<<"ß";
    	gotoxy(20, 26); cout<<"THE DINOSAUR RUNNING SIMULATOR";
        gotoxy(1+i, 28); cout<<"ß";
         
	} 
       
}

void moveDino(int jump = 0) {
    static int foot = 0;

    if (jump == 0)
        dinoY = 0;
    else if (jump == 2)
        dinoY--;
    else dinoY++;

    gotoxy(dinoPos, 15 - dinoY); cout << "                 ";
    gotoxy(dinoPos, 16 - dinoY); cout << "         /\\/\\/\\/";
    gotoxy(dinoPos, 17 - dinoY); cout << "        /\\ @ @/\\";
    gotoxy(dinoPos, 18 - dinoY); cout << "         \\_/\\/\\/";
    gotoxy(dinoPos, 19 - dinoY); cout << " /\\     /\\/\\/\\/ ";
    gotoxy(dinoPos, 20 - dinoY); cout << " /\\/\\  /\\/\\/\\\\/\\ ";
    gotoxy(dinoPos, 21 - dinoY); cout << " \\/\\/\\/\\/\\_/\\/\\ ";
    gotoxy(dinoPos, 22 - dinoY); cout << "   \\/\\/\\/\\_/     ";
    gotoxy(dinoPos, 23 - dinoY);

    if (jump == 1 || jump == 2) {
        cout << "    /\\'' /\\       ";
        gotoxy(2, 24 - dinoY);
        cout << "    /\\   /\\      ";
     
    } 
    else if (foot == 0) {
        cout << "    \\/\\  \\/\\/\\    ";
        gotoxy(2, 24 - dinoY);
        cout << "      /\\         ";
         foot = !foot;
    } 
    else if (foot == 1) {
        cout << "     \\/\\/ \\/\\      ";
        gotoxy(2, 24 - dinoY);
        cout << "          /\\     ";
        foot = !foot;
    }
    
    gotoxy(2, 25 - dinoY);
    if (jump == 0) {
        cout << "ßßßßßßßßßßßßßßßßß";
    } 
    else {
        cout << "                ";
    } 
    Sleep(speed);
}









void drawHurdle() {
    static int plantX = 0;

    if (plantX == 56 && dinoY < 4) {
        speed = 40;
        gotoxy(36, 8);cout<<"Game Over";
        getch();
        gameover = 1; 
    }
    
    gotoxy(hurdlePos - plantX, 20);cout<<"\033[31m" <<"| | ";
    gotoxy(hurdlePos - plantX, 21);cout             <<"| | ";
    gotoxy(hurdlePos - plantX, 22);cout             <<"|_| ";
    gotoxy(hurdlePos - plantX, 23);cout             <<" |  ";
    gotoxy(hurdlePos - plantX, 24);cout             <<" |  ";
     
    plantX++;
    
    if (plantX == 73) {
        plantX = 0;
     
        scoreStack.push(score++);
        displayScore(scoreStack,score);
         }
        if (speed > 20)
            speed--;
            
    }



void drawBird() {
	
    static int birdX = 40;
    static int birdY = 9;  // Increased birdY position by 3 or 4 levels
    gotoxy(birdX, birdY); cout<<"     ";
    gotoxy(birdX, birdY + 1); cout<<"     ";
    gotoxy(birdX, birdY + 2); cout<<"     ";
    gotoxy(birdX, birdY + 3); cout<<"     ";
    gotoxy(birdX, birdY + 4); cout<<"     ";
    birdX--;
    if (birdX < 0) {
        birdX = 80;
    }
 gotoxy(birdX, birdY); cout << " /\\ ";
gotoxy(birdX, birdY + 1); cout << " ||| ";
gotoxy(birdX, birdY + 2); cout << " OOO ";
gotoxy(birdX, birdY + 3); cout << " ||| ";
gotoxy(birdX, birdY + 4); cout << " \\/ ";
    if (birdX == dinoPos + 1 && !(birdY > 23 - dinoY || birdY + 4 < 19 - dinoY)) {  // Check if bird collides with dino
        speed = 40;
        gotoxy(10, 10); cout<<"Game Over  ";  // Added gameover symbol
        gotoxy(10, 12); cout<<"Score: "<<score;
        gameover = 1;
    }
    if (birdX == dinoPos - 2 && (birdY > 23 - dinoY || birdY + 4 < 19 - dinoY)) {  // Check if dino dodges bird
 
        scoreStack.push(score++);
       displayScore(scoreStack,score);
        if (score % 10 == 0 && speed > 20) {
            speed -= 5;
        }
    }
    Sleep(speed);
}

void play(){ 
	system("cls");
    system("Color E4");
	char ch;
    int i;
    score=0;
	init();
    while (true) {
        while (!kbhit()) {
            if( gameover==1 ){
            	return;
			}
			moveDino();
            drawHurdle();
        }
        ch = getch();
        if (ch == 32) {
        	i = 0;
            while( i < 12) {
                moveDino(1);
                drawHurdle();
                i++;
            }
            while(i > 0) {
                moveDino(2);
                drawHurdle();
                i--;
        	}
        }
		else if (ch == 'p'||ch=='P')
           getch();
		else if (ch == 27)
           break;
    }
  
}
void playHard() {
system("cls");
system("Color E4");
    char ch;
    srand(time(NULL));
    int i;
    score=0;
	init();
    while (true) {
        while (!kbhit()) {
            if( gameover==1 ){
            	return;
			}
			moveDino();
            if(rand()%2+1==1)     //randomizer between 1 and 2
                drawHurdle();
                else 
                drawBird();
        }
        ch = getch();
        if (ch == 32) {
        	i = 0;
            while( i < 12) {
                moveDino(1);
                if(rand()%2+1==1)
                drawHurdle();
                else 
                drawBird();
                i++;
            }
            while(i > 0) {
                moveDino(2);
                if(rand()%2+1==1)
                drawHurdle();
                else 
                drawBird();
                i--;
        	}
        }
		else if (ch == 'p'||ch=='P')
           getch();
		else if (ch == 27)
           break;
    }
}

void instructions() {
	system("cls");
	cout<<"Instructions";
	cout<<"\n----------------";
	cout<<"\n1. Avoid hurdles by jumping";
	cout<<"\n2. Press 'Spacebar' to jump ";
	cout<<"\n3. Press 'p' to pause game ";
	cout<<"\n4. Press 'Escape' to exit from game";
	cout<<"\n\nPress any key to go back to menu";
	getch();
}

void LoadingBar(){
	cout<<"\n\n\n\t\t\t\tPlease wait while loading\n\n";
 char a=177, b=219;
 cout<<"\t\t\t\t";
 for (int i=0;i<=15;i++)
 cout<<a;
 cout<<"\r";
 cout<<"\t\t\t\t";
 for (int i=0;i<=15;i++)
 {
  cout<<b;
  for (int j=0;j<=1e8;j++); //You can also use sleep function instead of for loop
  }
 }
};

int main() {
DinoGame DG;
    DG.setcursor(0, 0);
      
    do{
		system("cls");
		system("Color 09");
		DG.gotoxy(10,5); cout<<" -------------------------- "; 
		DG.gotoxy(10,6); cout<<" |        DINO RUN        | ";  
		DG.gotoxy(10,7); cout<<" -------------------------- ";
		DG.gotoxy(10,9); cout<<"1. Start Game in easy mode";
		DG.gotoxy(10,10); cout<<"2. Start Game in difficult mode";	 
		DG.gotoxy(10,11); cout<<"3. Instructions";
		DG.gotoxy(10,12); cout<<" Quit ";
		DG.gotoxy(10,14); cout<<"Select option: ";
		char op = getche();
		
		if( op=='1') {
	     system("color 0a");
       DG.LoadingBar();		
		DG.play();
		 
	}
	if( op=='2') {
	     system("color 0a");
      DG.Q_bar();		
		DG.playHard();
		 
	}
		else if( op=='3') DG.instructions();
		else if( op=='4') return 0;
		
	}while(1);
     
	return 0;
} 
