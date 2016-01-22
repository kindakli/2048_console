#include <vector>
#include <time.h>
#include <string>

using namespace std;

#define MAX 2048

class GameBoard {
private:
    //the matrix boardSizeinsion
    int boardSize;
    //the game value matrix
    vector<vector<int> > values;

    //game flag
    bool valid;

    //the game currnet score
    int score;
    int max;

    void removeMinus()
    {
        for (int i = 0; i < boardSize; i++)
            for (int j = 0; j < boardSize; j++)
                if (values[i][j] == -1)
                    values[i][j] = 0;
    }

public:
    GameBoard() //, values(boardSize,boardSize)
    {
        boardSize = 4;
        values.resize(boardSize);
        for (int i = 0; i < boardSize; i++)
            values[i].resize(boardSize);

        valid = true;
        max = 0;
        score = 0;
    }

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
    }

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
        return false; // unable to add => lose the game
    }

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

    bool moveDown()
    {
        valid = false;
        for (int i = 0; i < boardSize; i++) {
            int row = boardSize - 1;
            while (row > 0) {
                //if the cell is not empty
                if (values[row - 1][i] > 0) {
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
                            if (values[row][i] > max)
                                max = values[row][i];
                            score += values[temp][i] * 2;
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
                        if (temp >= 0 && values[i][temp] == -1) {
                            values[temp][i] = values[temp + 1][i];
                            values[temp + 1][i] = 0;
                            valid = true;
                        }
                        else if (temp >= 0 && values[temp][i] == values[temp + 1][i]) {
                            values[temp][i] = values[temp][i] * 2;
                            if (values[temp][i] > max)
                                max = values[temp][i];
                            score += values[temp][i] * 2;
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

    string displayScore()
    {
        return "Your current score : " + to_string(static_cast<long long>(getScore())) + '\n';
    }

    int getScore()
    {
        return score;
    }

    int getMax()
    {
        return max;
    }

    bool isValidMove()
    {
        return valid;
    }

    bool win()
    {
        if (max >= MAX)
            return true;
        return false;
    }
};
