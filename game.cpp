#include <iostream>
#include "GameBoard.h"

#include <unistd.h>  
#include <termios.h>  

using namespace std;

char getch(){
    
    char buf=0;
    struct termios old={0};
    fflush(stdout);
    if(tcgetattr(0, &old)<0)
        perror("tcsetattr()");
    old.c_lflag&=~ICANON;
    old.c_lflag&=~ECHO;
    old.c_cc[VMIN]=1;
    old.c_cc[VTIME]=0;
    if(tcsetattr(0, TCSANOW, &old)<0)
        perror("tcsetattr ICANON");
    if(read(0,&buf,1)<0)
        perror("read()");
    old.c_lflag|=ICANON;
    old.c_lflag|=ECHO;
    if(tcsetattr(0, TCSADRAIN, &old)<0)
        perror ("tcsetattr ~ICANON");
    printf("%c\n",buf);
    return buf;
 }

int main()
{
    int boardSize = 0;
    cout << "enter the board size (-1 for default)" << endl;
    cin >> boardSize;
    if (boardSize <= 1)
        boardSize = 4;

    GameBoard game(boardSize);

    while (true) {

        cout << game.displayMatrix2();
        cout << game.displayScore();

        char direction ;
        //enter the direction
        cout << "Please choose your next move (w= up - d= right - a= left - s= down, q to quit)" << endl;
        //cin >> getchar();
        direction = getch();

        switch (direction) // decide the move based on the ASCII code of the letter
        {
        case 65:
        case 97: //A,a
            game.moveLeft();
            break;
        case 68:
        case 100: //D,d
            game.moveRight();
            break;
        case 87:
        case 119: //W,w
            game.moveUp();
            break;
        case 83:
        case 115: //S,s
            game.moveDown();
            break;

        case 81:
        case 113:
            return 0;
            break;

        default: //others
            cout << "invalid direction, please try again" << endl;
            continue;
        }
    

        if (game.isValidMove()) {
            game.generateRandomNumber();
        }   else {
            cout << "invalid move, please try again" << endl;
            continue;
        }
        if (game.win()) {
            cout << "Congratulation!" << endl;
            cout << game.displayScore();
            break;
        }
        if(!game.hasValidMove())
        {           
            cout <<game.displayMatrix2();
            cout <<game.displayScore();
            cout << "Game over..." << endl;
            break;
        }
    }
    return 0;
}