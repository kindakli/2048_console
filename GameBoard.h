/**
 * @file GameBoard.h
 * @author  Kindakli
 * @version 1.0
 *
 *
 * @section DESCRIPTION
 *
 * The GameBoard class represents 2048 board game.
 */
 
#include <sstream>
#include <iomanip>
#include <vector>
#include <time.h>
#include <string>

using namespace std;

#define MAX 2048

class GameBoard {
/**
* the private data members of the GameBoard class.
*/
private:
    //the matrix boardSizeinsion
    int boardSize;
    //the game value matrix
    vector<vector<int> > values;

    //game flag
    bool valid;

    //the game currnet score
    int score;
    //represents the current max value on the board
    int max;

    void removeMinus()
    {
        for (int i = 0; i < boardSize; i++)
            for (int j = 0; j < boardSize; j++)
                if (values[i][j] == -1)
                    values[i][j] = 0;
    }

public:
/**
        * Default Constructor that initializes the class members.
        *
        */
    GameBoard() 
    {
        boardSize = 4;
        values.resize(boardSize);
        for (int i = 0; i < boardSize; i++)
            values[i].resize(boardSize);

        valid = true;
        max = 0;
        score = 0;
        for (int i = 0; i < boardSize; i++)
            for (int j = 0; j < boardSize; j++)
                values[i][j] = 0;
        generateRandomNumber();
    }

/**
        * Normal Constructor that initializes the class members.
        *
        * @param boardSize the size of the grid
        */

    GameBoard(int boardSize)
    {
        this->boardSize = boardSize;
        values.resize(boardSize);
        for (int i = 0; i < boardSize; i++)
            values[i].resize(boardSize);
        valid = true;
        max = 0;
        score = 0;
        for (int i = 0; i < boardSize; i++)
            for (int j = 0; j < boardSize; j++)
                values[i][j] = 0;
        generateRandomNumber();
    }

/**
        * generateRandomNumber generates new random number (2 or 4) at a random cell on the grid.
        * the value 2 probability is 90%
        * the value 4 probability is 10%
        *
        */
    bool generateRandomNumber()
    {
        srand(time(NULL));

        vector<bool> temp_row(boardSize);
        vector<bool> temp_column(boardSize);

        int row_tried = 0;
        int column_tried = 0;

        do {
            int row = rand() % boardSize;
            if (temp_row[row] == true)
                continue;
            row_tried++;
            temp_row[row] = true;
            do {
                int column = rand() % boardSize;
                if (temp_column[column] == true)
                    continue;
                column_tried++;
                temp_column[column] = true;
                if (values[row][column] == 0) {
                    int generated_number = rand() % 9; //.9 , .1
                    if (generated_number == 4)
                        values[row][column] = 4;
                    else
                        values[row][column] = 2;
                    return true;
                }
            } while (column_tried < boardSize);
            column_tried = 0;
            std::fill(temp_column.begin(), temp_column.end(), false);
        } while (row_tried < boardSize);
        return false; // unable to generate
    }

/**
    * moveRight tilts the board in right direction 
    *
    */
    bool moveRight()
    {
        valid = false;
        for (int i = 0; i < boardSize; i++) {
            int column = boardSize - 1;
            while (column > 0) {
                //if the cell is not empty
                if (values[i][column - 1] > 0) {
                    if (values[i][column] == values[i][column - 1]) {
                        values[i][column] = values[i][column] * 2;
                        if (values[i][column] > max)
                            max = values[i][column];
                        score += values[i][column];

                        //temporary status to insure titlting one step each round
                        values[i][column - 1] = -1;
                        valid = true;
                        column--;
                        continue;
                    }
                    else {
                        int temp = column;
                        //move the cell while we have empty solts
                        while (temp < boardSize && values[i][temp] == 0) {
                            values[i][temp] = values[i][temp - 1];
                            values[i][temp - 1] = 0;
                            temp++;
                            valid = true;
                        }
                        if (temp < boardSize && values[i][temp] == -1) {
                            values[i][temp] = values[i][temp - 1];
                            values[i][temp - 1] = 0;
                            valid = true;
                        }
                        else if (temp < boardSize && values[i][temp] == values[i][temp - 1]) {
                            values[i][temp] = values[i][temp] * 2;
                            if (values[i][temp] > max)
                                max = values[i][temp];
                            score += values[i][temp];
                            //temporary status to insure titlting one step each round
                            values[i][temp - 1] = -1;
                            valid = true;
                        }
                        column--;
                    }
                }
                else
                    column--;
            }
        }
        removeMinus();
        return valid;
    }

/**
    * moveLeft tilts the board in left direction 
    *
    *
    */
    bool moveLeft()
    {
        valid = false;
        for (int i = 0; i < boardSize; i++) {
            int column = 0;
            while (column < boardSize - 1) {
                //if the cell is not empty
                if (values[i][column + 1] > 0) {
                    if (values[i][column] == values[i][column + 1]) {
                        values[i][column] = values[i][column] * 2;
                        if (values[i][column] > max)
                            max = values[i][column];
                        score += values[i][column];

                        //temporary status to insure titlting one step each round
                        values[i][column + 1] = -1;
                        valid = true;
                        column++;
                        continue;
                    }
                    else {
                        int temp = column;
                        //move the cell while we have empty solts
                        while (temp >= 0 && values[i][temp] == 0)
                        //if(values[i][column] == 0)
                        {
                            values[i][temp] = values[i][temp + 1];
                            values[i][temp + 1] = 0;
                            temp--;
                            valid = true;
                        }
                        if (temp >= 0 && values[i][temp] == -1) {
                            values[i][temp] = values[i][temp + 1];
                            values[i][temp + 1] = 0;
                            valid = true;
                        }
                        else if (temp >= 0 && values[i][temp] == values[i][temp + 1]) {
                            values[i][temp] = values[i][temp] * 2;
                            if (values[i][column] > max)
                                max = values[i][column];
                            score += values[i][temp];
                            //temporary status to insure titlting one step each round
                            values[i][temp + 1] = -1;
                            valid = true;
                        }
                        column++;
                    }
                }
                else
                    column++;
            }
        }
        removeMinus();
        return valid;
    }

/**
    * moveDown tilts the board in down direction 
    *
    */
    bool moveDown()
    {
        valid = false;
        for (int i = 0; i < boardSize; i++) {
            int row = boardSize - 1;
            while (row > 0) {
                //if the cell is not empty
                if (values[row - 1][i] > 0) 
                {
                    if (values[row][i] == values[row - 1][i]) {
                        values[row][i] = values[row][i] * 2;
                        if (values[row][i] > max)
                            max = values[row][i];
                        score += values[row][i];
                        //temporary status to insure titlting one step each round
                        values[row - 1][i] = -1;
                        valid = true;
                        row--;
                        continue;
                    }
                    else {
                        int temp = row;
                        //move the cell while we have empty solts
                        while (temp < boardSize && values[temp][i] == 0)
                        //if(values[i][column] == 0)
                        {
                            values[temp][i] = values[temp - 1][i];
                            values[temp - 1][i] = 0;
                            temp++;
                            valid = true;
                        }
                        if (temp < boardSize && values[temp][i] == -1) {
                            values[temp][i] = values[temp - 1][i];
                            values[temp][i] = 0;
                            valid = true;
                        }
                        else if (temp < boardSize && values[temp][i] == values[temp - 1][i]) {
                            values[temp][i] = values[temp][i] * 2;
                            if (values[temp][i] > max)
                                max = values[temp][i];
                            score += values[temp][i] ;
                            //temporary status to insure titlting one step each round
                            values[temp - 1][i] = -1;
                            valid = true;
                        }
                        row--;
                    }
                }
                else
                    row--;
            }
        }
        removeMinus();
        return valid;
    }

/**
    * moveUp tilts the board in up direction 
    *
    */
    bool moveUp()
    {
        for (int i = 0; i < boardSize; i++) {
            int row = 0;
            while (row < boardSize - 1) {
                //if the cell is not empty
                if (values[row + 1][i] > 0) {
                    if (values[row][i] == values[row + 1][i]) {
                        values[row][i] = values[row][i] * 2;
                        if (values[row][i] > max)
                            max = values[row][i];
                        score += values[row][i];
                        //temporary status to insure titlting one step each round
                        values[row + 1][i] = -1;
                        valid = true;
                        row++;
                        continue;
                    }
                    else {
                        int temp = row;
                        //move the cell while we have empty solts
                        while (temp >= 0 && values[temp][i] == 0)
                        //if(values[i][column] == 0)
                        {
                            values[temp][i] = values[temp + 1][i];
                            values[temp + 1][i] = 0;
                            temp--;
                            valid = true;
                        }
                        if (temp >= 0 && values[temp][i] == -1) {
                            values[temp][i] = values[temp + 1][i];
                            values[temp + 1][i] = 0;
                            valid = true;
                        }
                        else if (temp >= 0 && values[temp][i] == values[temp + 1][i]) {
                            values[temp][i] = values[temp][i] * 2;
                            if (values[temp][i] > max)
                                max = values[temp][i];
                            score += values[temp][i] ;
                            //temporary status to insure titlting one step each round
                            values[temp + 1][i] = -1;
                            valid = true;
                        }
                        row++;
                    }
                }
                else
                    row++;
            }
        }
        removeMinus();
        return valid;
    }

/**
    * displayMatrix returns the gird values as a string 
    *
    */
    string displayMatrix()
    {
        string result("2048:\n");
        for (int i = 0; i < boardSize; i++) {
            for (int j = 0; j < boardSize; j++) {
                result += std::to_string(static_cast<long long>(values[i][j])) + " "; //(0 value ? nothing : value)
            }
            result += '\n';
        }
        result += '\n';
        return result;
    }
    
/**
    * displayMatrix2 returns the gird values as a string 
    * improving the display.
    *
    */
    string displayMatrix2()
    {
        string result("2048:\n");
        string liner("+");
        for (int i = 0; i < boardSize; i++) {
            liner+= "------+";
        }
        liner+='\n';
        for (int i = 0; i < boardSize; i++) {
            string rowString("");
            for (int j = 0; j < boardSize; j++) {
                std::ostringstream row;
                row << " " << std::setw(4) << std::setfill(' ') << values[i][j] << " |";
                rowString += row.str();
            }
            result += liner + '|'+rowString;
            result += '\n' ;
        }
        result +=  liner + '\n';
        return result;
    }

/**
    * displayMatrix returns the current user score.
    *
    */
    string displayScore()
    {
        return "Your current score : " + to_string(static_cast<long long>(getScore())) + '\n';
    }
/**
    * getScore getter of score data memmber.
    *
    */

    int getScore()
    {
        return score;
    }

/**
    * getMax getter of max data memmber.
    * represents the current max value on the board
    */
    int getMax()
    {
        return max;
    }

/**
    * isValidMove getter of valid data memmber.
    */
    bool isValidMove()
    {
        return valid;
    }

/**
    * win checks if the score reaches the max value (2048).
    */
    bool win()
    {
        if (max >= MAX)
            return true;
        return false;
    }
    /**
    * hasValidMove checks the availability of any valid move remaining.
    * either merging two numbers
    * or having an empty cell on the grid
    */
    bool hasValidMove()
    {
        for(int i = 0 ; i < boardSize; i ++)
            for(int j=0; j < boardSize ; j++)
                if(values[i][j] == 0)
                    return true;

        for(int i = 0 ; i < boardSize; i ++)
            for(int j=0; j < boardSize-1 ; j++)
                if(values[i][j] == values[i][j+1])
                    return true;
        for(int i = 0 ; i < boardSize; i ++)
            for(int j=0; j < boardSize-1 ; j++)
                if(values[j][i] == values[j+1][i])
                    return true;
        return false;
    }
    /**
    * buildBoard creates new entry based on existing grid
    * @grid input board values 
    */
    void buildBoard(vector<vector<int> > grid)
    {
        for(int i = 0 ; i < boardSize; i ++)
            for(int j=0; j < boardSize ; j++)
                values[i][j] = grid[i][j];
    }

    /**
     * compareBoard compare the current grid values with input
     * @grid input board values 
    */
    bool compareBoard(vector<vector<int> > grid)
    {
        for(int i = 0 ; i < boardSize; i ++)
            for(int j=0; j < boardSize ; j++)
                if(values[i][j] != grid[i][j])
                 return false;
        return true;
     }
};
