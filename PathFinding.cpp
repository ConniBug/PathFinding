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
std::vector<std::string> v2(MAX, " ");
std::vector<std::vector<std::string> > Grid(MAX, v2);
const int  intGoalPosition[2] = { 2, 3 };

// Set starting position
int(*positionPointer) = new int[] { MAX - 1, MAX - 1};

enum direction {
    down, up,
    left, right
};

void cleanScreen() {
    for(int i = 0; i <= 18; i++) std::cout << std::endl;
}

void renderScreen() {
    int h = 0;
    int v = 1;
    for (int i = Grid.size() - 1; i >= 0; i--) {
        for (int j = 0; j < Grid[i].size(); j++) {
            if (positionPointer[h] == j && positionPointer[v] == i) {
                std::cout << "X" << " ";
                continue;
            }
            else if (j == intGoalPosition[0] && i == intGoalPosition[1])
            {
                std::cout << "G" << " ";
                continue;
            }

            std::cout << Grid[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

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
    direction BESTDIRECTION = up;

   // std::cout << std::endl << "Starting Position: " << positionPointer[h] << ", " << positionPointer[v];


    std::tie(BESTDIRECTION, distance) = testDir(distance, BESTDIRECTION, up);

    std::tie(BESTDIRECTION, distance) = testDir(distance, BESTDIRECTION, down);

    std::tie(BESTDIRECTION, distance) = testDir(distance, BESTDIRECTION, left);

    std::tie(BESTDIRECTION, distance) = testDir(distance, BESTDIRECTION, right);

    std::cout << std::endl << "Best direction: " << BESTDIRECTION << std::endl << "Best Distance " << distance << std::endl;
    return BESTDIRECTION;
}

int main() {

    Log("Rawr!~");

    int h = 0;
    int v = 1;

    int cnt = 0;

    do
    {
        std::cout << '\n' << "Press a key to continue...";
    } while (std::cin.get() != '\n');

    while (true) {
        bool shouldSleep = false;
        cleanScreen();
        std::cout << std::endl;
        std::cout << "Cur pos: " << positionPointer[h] << ", " << positionPointer[v] << std::endl;

        bool changed = false;

        std::cout << std::endl;
        renderScreen();
    
        int diff_V = intGoalPosition[0] - positionPointer[v];
        int diff_H = intGoalPosition[1] - positionPointer[h];


       /// std::cout << "Distance: " << sqrt((diff_V * diff_V) + (diff_H * diff_H)) << std::endl << std::endl;
       // std::cout << "Current Position: " << positionPointer[h] << ", " << positionPointer[v] << std::endl;
       // std::cout << "Left Position: " << getPos_Left()[h] << ", " << getPos_Left()[v] << std::endl;

        std::cout << "Cnt: " << cnt << std::endl;

        switch (getBestDirection())
        {
        case down:
            if (canMove_Down()) {
                moveDown();
                shouldSleep = true;
            }
            break;
        case up:
            if (canMove_Up()) {
                moveUp();
                shouldSleep = true;
            }
            break;
        case left:
            if (canMove_Left()) {
                moveLeft();
                shouldSleep = true;
            }
            break;
        case right:
            if (canMove_Right()) {
                moveRight();
                shouldSleep = true;
            }
            break;
        default:
            break;
        }

        if (intGoalPosition[h] == positionPointer[h] && intGoalPosition[v] == positionPointer[v])
        {
            do
             {
                renderScreen();
                 std::cout << '\n' << "Done...";

             } while (std::cin.get() != '\n');
        }
        if(shouldSleep) std::this_thread::sleep_for(std::chrono::milliseconds(1));

    }


}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
