#include "utils.h"

#include <math.h>

float distance_calculator(float x1, float x2, float y1, float y2) {	return sqrt((x1 - y1) * (x1 - y1) + (x2 - y2) * (x2 - y2));				}
float distance_calculator(int x1, int x2, int y1, int y2) {         return sqrt((x1 - y1) * (x1 - y1) + (x2 - y2) * (x2 - y2));             }
float distanceBetween2Points(int point1[2], int point2[2]) {        return distance_calculator(point1[0], point1[1], point2[0], point2[1]); }
float distanceBetween2Points(int point1[2], const int point2[2]) {  return distance_calculator(point1[0], point1[1], point2[0], point2[1]); }
