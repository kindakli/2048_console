#include <iostream>
#include "GameBoard.h"

using namespace std;

void main()
{
    int boardSize = 0;
    cout << "enter the board size (-1 for default)" << endl;
    cin >> boardSize;
    if (boardSize <= 1)
        boardSize = 4;

    GameBoard game(boardSize);

    while (true) {
        if (game.isValidMove()) {
            if (!game.generateRandomNumber()) {
                cout << "Game over..." << endl;
                game.displayScore();
                break;
            }
        }

        cout << game.displayMatrix();
        cout << game.displayScore();

        char direction = 0;
        //enter the direction
        cout << "Please choose your next move (w= up - d= right - a= left - s= down)" << endl;
        cin >> direction;

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

        default: //others
            cout << "invalid direction, please try again" << endl;
            continue;
        }
        if (!game.isValidMove()) {
            cout << "invalid move, please try again" << endl;
            continue;
        }
        else if (game.win()) {
            cout << "Congratulation!" << endl;
            game.displayScore();
            break;
        }
    }
}
