// PathFinding.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <iostream>
#include <string>
#include <vector>
#include <chrono>
#include <thread>
#include <math.h>

#include "utils.h"
#include "logging.h"

const int MAX = 20;
const int MAX_DISPLAYABLE = 9;

//Width and Height of grid
std::vector<std::string>                 v2(MAX, " ");
std::vector<std::vector<std::string> > Grid(MAX, v2);
const int  intGoalPosition[2] = { 2, 3 };

// Set starting position
int(*positionPointer) = new int[] { MAX - 1, MAX - 1};

enum direction {
    down, up,
    left, right,
    na
};

void cleanScreen(int NewLines = 23) {
    for(int i = 0; i <= NewLines; i++) std::cout << std::endl;
}


/**
 * Renders and processes the text to be displayed on the cli.
 */
void renderScreen() {
    int h = 0; // Horizontal indicator
    int v = 1; // Vertical   indicator
    for (int i = Grid.size() - 1; i >= 0; i--) {                            // Iterate through y axis
        for (int j = 0; j < Grid[i].size(); j++) {                          // Iterate through x axis
            if (positionPointer[h] == j && positionPointer[v] == i) {       // Check if current pos matches currently rendering char
                std::cout << "X" << " ";
                continue;
            }
            else if (j == intGoalPosition[0] && i == intGoalPosition[1]) {  // Check if goal pos matches currently rendering char
                std::cout << "G" << " ";
                continue;
            }

            std::cout << Grid[i][j] << " "; // Output grid piece
        }
        Log_EndLine();                      // Endline
    }
}

#pragma region moveLeft

bool canMove_Left() {
    int h = 0;
    int v = 1;
    if (positionPointer[h] != 0) return true;
    return false;
}

void moveLeft() {
    int h = 0;
    int v = 1;
    if (canMove_Left()) {
        positionPointer[h]--;
    }
}

int* get_Left_Pos() {
    int h = 0;
    int v = 1;
    int saved[2];
    saved[v] = positionPointer[v];
    saved[h] = positionPointer[h] - 1;

    int(*val);
    val = saved;
    return val;
}

#pragma endregion

#pragma region moveRight

bool canMove_Right() {
    int h = 0;
    int v = 1;
    if (positionPointer[h] < MAX_DISPLAYABLE) return true;
    return false;
}

void moveRight() {
    int h = 0;
    int v = 1;
    if (canMove_Right()) {
        positionPointer[h]++;
    }
}

int* get_Right_Pos() {
    int h = 0;
    int v = 1;
    int saved[2];
    saved[v] = positionPointer[v];
    saved[h] = positionPointer[h] + 1;

    int(*val);
    val = saved;
    return val;
}

#pragma endregion

#pragma region moveDown

bool canMove_Down() {
    int h = 0;
    int v = 1;
    if (positionPointer[v] != 0) return true;
    return false;
}

void moveDown() {
    int h = 0;
    int v = 1;
    if (canMove_Down()) {
        positionPointer[v]--;
    }
}

int* get_Down_Pos() {
    int h = 0;
    int v = 1;
    int saved[2];
    saved[v] = positionPointer[v] - 1;
    saved[h] = positionPointer[h];

    int(*val);
    val = saved;
    return val;
}

#pragma endregion

#pragma region moveUp

bool canMove_Up() {
    int h = 0;
    int v = 1;
    if (positionPointer[v] < MAX_DISPLAYABLE) return true;
    return false;
}

void moveUp() {
    int h = 0;
    int v = 1;
    if (canMove_Up()) {
        positionPointer[v]++;
    }
}

int* get_Up_Pos() {
    int h = 0;
    int v = 1;
    int saved[2];
    saved[v] = positionPointer[v] + 1;
    saved[h] = positionPointer[h];

    int(*val);
    val = saved;
    return val;
}

#pragma endregion

std::tuple<direction, float> testDir(float curBestDistance, direction curBESTDIRECTION, direction TestingDirection) {
    int h = 0;
    int v = 1;

    int tmpPos[2];
    int(*tmp435345);
    switch (TestingDirection)
    {
    case down:
        tmp435345 = get_Down_Pos();
        break;
    case up:
        tmp435345 = get_Up_Pos();
        break;
    case left:
        tmp435345 = get_Left_Pos();
        break;
    case right:
        tmp435345 = get_Right_Pos();
        break;
    default:
        tmp435345 = new int(-1);
    }

    tmpPos[h] = tmp435345[h];
    tmpPos[v] = tmp435345[v];

    float goalDist = distanceBetween2Points(tmpPos, intGoalPosition);
    if (goalDist < curBestDistance) {
        curBestDistance = goalDist;
        curBESTDIRECTION = TestingDirection;
    }

    //std::cout << std::endl << "position: " << tmpPos[h] << ", " << tmpPos[v] << std::endl << "Distance to goal: " << goalDist;

    return  std::make_tuple(curBESTDIRECTION, curBestDistance);
}

direction getBestDirection() {
    int h = 0;
    int v = 1;

    float distance = 102349028.f;
    direction BESTDIRECTION = na;

    std::tie(BESTDIRECTION, distance) = testDir(distance, BESTDIRECTION, up);

    std::tie(BESTDIRECTION, distance) = testDir(distance, BESTDIRECTION, down);

    std::tie(BESTDIRECTION, distance) = testDir(distance, BESTDIRECTION, left);

    std::tie(BESTDIRECTION, distance) = testDir(distance, BESTDIRECTION, right);

    std::cout << std::endl << "Best direction: " << BESTDIRECTION << std::endl << "Best Distance " << distance << std::endl;
    return BESTDIRECTION;
}

int main() {
    Log("Rawr!~ The pathfinding has started!!");

    int h = 0;
    int v = 1;

    int cnt = 0;

    do{
        std::cout << '\n' << "Press a key to begin...";
    } while (std::cin.get() != '\n');

    while (true) {
        bool shouldSleep = true;
        bool changed = true;

        cleanScreen();

        renderScreen();
    
        int diff_V = intGoalPosition[0] - positionPointer[v];
        int diff_H = intGoalPosition[1] - positionPointer[h];

        std::cout << "Cnt: " << cnt << std::endl;

        switch (getBestDirection()) {
        case down:
            if (canMove_Down()) moveDown();
            break;
        case up:
            if (canMove_Up()) moveUp();
            break;
        case left:
            if (canMove_Left())  moveLeft();
            break;
        case right:
            if (canMove_Right()) moveRight();
            break;
        default:
            shouldSleep = false;
            break;
        }

        if (intGoalPosition[h] == positionPointer[h] && intGoalPosition[v] == positionPointer[v]) {
            do
             {
                renderScreen();
                 std::cout << '\n' << "Done...";

             } while (std::cin.get() != '\n');
        }
        if(shouldSleep) std::this_thread::sleep_for(std::chrono::milliseconds(1));

    }
}