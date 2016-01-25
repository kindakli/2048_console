#include <limits.h>
#include "gest/gtest.h"
#include "GameBoard.h"

class GameTest : public ::testing::Test {
protected:
    virtual void SetUp()
    {
    }

    virtual void TearDown()
    {
        // Code here will be called immediately after each test
        // (right before the destructor).
    }
};

TEST(GameBoard, mergeRight)
{
    vector<vector<int> > grid;
	grid.resize(2);
    for (int i = 0; i < 2; i++)
        grid[i].resize(2);    
	for (int i = 0; i < 2; i++)
        for (int j = 0; j < 2; j++)
            grid[i][j] = 2;

	GameBoard g(2);
	g.buildBoard(grid);
    g.moveRight();

    vector<vector<int> > gridResult;
    gridResult.resize(2);
    for (int i = 0; i < 2; i++)
        gridResult[i].resize(2);
    gridResult[0][0] = 0;
    gridResult[0][1] = 4;
    gridResult[1][0] = 0;
    gridResult[1][1] = 4;

    EXPECT_EQ(true, g.compareBoard(gridResult));
}

TEST(GameBoard, mergeLeft)
{
    vector<vector<int> > grid;
	grid.resize(2);
    for (int i = 0; i < 2; i++)
        grid[i].resize(2);    
	for (int i = 0; i < 2; i++)
        for (int j = 0; j < 2; j++)
            grid[i][j] = 2;

	GameBoard g(2);
	g.buildBoard(grid);
    g.moveLeft();

    vector<vector<int> > gridResult;
    gridResult.resize(2);
    for (int i = 0; i < 2; i++)
        gridResult[i].resize(2);
    gridResult[0][0] = 4;
    gridResult[0][1] = 0;
    gridResult[1][0] = 4;
    gridResult[1][1] = 0;

    EXPECT_EQ(true, g.compareBoard(gridResult));    
}

TEST(GameBoard, mergeUp)
{
    vector<vector<int> > grid;
	grid.resize(2);
    for (int i = 0; i < 2; i++)
        grid[i].resize(2);    
	for (int i = 0; i < 2; i++)
        for (int j = 0; j < 2; j++)
            grid[i][j] = 2;

	GameBoard g(2);
	g.buildBoard(grid);
    g.moveUp();

    vector<vector<int> > gridResult;
    gridResult.resize(2);
    for (int i = 0; i < 2; i++)
        gridResult[i].resize(2);
    gridResult[0][0] = 4;
    gridResult[0][1] = 4;
    gridResult[1][0] = 0;
    gridResult[1][1] = 0;

    EXPECT_EQ(true, g.compareBoard(gridResult));    
}

TEST(GameBoard, mergeDown)
{
    vector<vector<int> > grid;
	grid.resize(2);
    for (int i = 0; i < 2; i++)
        grid[i].resize(2);    
	for (int i = 0; i < 2; i++)
        for (int j = 0; j < 2; j++)
            grid[i][j] = 2;

	GameBoard g(2);
	g.buildBoard(grid);
    g.moveDown();

    vector<vector<int> > gridResult;
    gridResult.resize(2);
    for (int i = 0; i < 2; i++)
        gridResult[i].resize(2);
    gridResult[0][0] = 0;
    gridResult[0][1] = 0;
    gridResult[1][0] = 4;
    gridResult[1][1] = 4;

    EXPECT_EQ(true, g.compareBoard(gridResult));    
}

TEST(GameBoard, InvalidMoveRight)
{
    vector<vector<int> > grid;
	grid.resize(2);
    for (int i = 0; i < 2; i++)
        grid[i].resize(2);    
    grid[0][0] = 0;
    grid[0][1] = 2;
    grid[1][0] = 0;
    grid[1][1] = 2;

	GameBoard g(2);
	g.buildBoard(grid);
    g.moveRight();

    EXPECT_EQ(true, g.compareBoard(grid));    
}
TEST(GameBoard, InvalidMoveLeft)
{
    vector<vector<int> > grid;
	grid.resize(2);
    for (int i = 0; i < 2; i++)
        grid[i].resize(2);    
    grid[0][0] = 2;
    grid[0][1] = 0;
    grid[1][0] = 2;
    grid[1][1] = 0;

	GameBoard g(2);
	g.buildBoard(grid);
    g.moveLeft();

    EXPECT_EQ(true, g.compareBoard(grid));    
}

TEST(GameBoard, InvalidMoveUp)
{
    vector<vector<int> > grid;
	grid.resize(2);
    for (int i = 0; i < 2; i++)
        grid[i].resize(2);    
    grid[0][0] = 2;
    grid[0][1] = 2;
    grid[1][0] = 0;
    grid[1][1] = 0;

	GameBoard g(2);
	g.buildBoard(grid);
    g.moveUp();

    EXPECT_EQ(true, g.compareBoard(grid));    
}

TEST(GameBoard, InvalidMoveDown)
{
    vector<vector<int> > grid;
	grid.resize(2);
    for (int i = 0; i < 2; i++)
        grid[i].resize(2);    
    grid[0][0] = 0;
    grid[0][1] = 0;
    grid[1][0] = 2;
    grid[1][1] = 2;

	GameBoard g(2);
	g.buildBoard(grid);
    g.moveDown();

    EXPECT_EQ(true, g.compareBoard(grid));    
}

TEST(GameBoard, Win)
{
    vector<vector<int> > grid;
	grid.resize(2);
    for (int i = 0; i < 2; i++)
        grid[i].resize(2);    
    grid[0][0] = 1024;
    grid[0][1] = 1024;
    grid[1][0] = 0;
    grid[1][1] = 2;

	GameBoard g(2);
	g.buildBoard(grid);
    g.moveRight();

    EXPECT_EQ(true, g.win());    
}

TEST(GameBoard, Lose)
{
    vector<vector<int> > grid;
	grid.resize(2);
    for (int i = 0; i < 2; i++)
        grid[i].resize(2);    
    grid[0][0] = 2;
    grid[0][1] = 2;
    grid[1][0] = 4;
    grid[1][1] = 2;

	GameBoard g(2);
	g.buildBoard(grid);
    g.moveRight();
	g.generateRandomNumber();

    EXPECT_EQ(false, g.hasValidMove());    
}

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}