#include <iostream>
#include "cgraphics.h"
using namespace std;

int main()
{
    char node[] = {'A', 'B', 'C', 'D', 'E', 'F'};
    int h[] = {9, 7, 6, 4, 2, 0};
    int matrix[] = {
         0,  3,  4, -1, -1, -1,
         3,  0,  4,  4,  7, -1,
         4,  4,  0,  2,  5, -1,
        -1,  4,  2,  0,  1,  4,
        -1,  7,  5,  1,  0,  2,
        -1, -1, -1,  4,  2,  0
    };
    CGraphics *graphics = new CGraphics(6, node, h, matrix);
    graphics->printGraphics();
    graphics->aStarFindWay('A', 'D');
    return 0;
}

