#ifndef _GRID_H_
#define _GRID_H_
//*************************************************************
// necessary includes
//*************************************************************

//#include "3dPoint.h"
#include "PointList.h"
//using std::string;

//*************************************************************
// grid
//*************************************************************
class Grid
{
public:
// constructor
Grid();
Grid(int , int , double width, double height);
// destructor
~Grid();
//  methods

double getRealXByGridY(int gridY,double realCenterX);
double getRealYByGridX(int gridX,double realCenterY);
CPointList * getResolutionGrid(double XCenter,double YCenter);
void setGridXYnum(int, int);
int getGridXnum();
int getGridYnum();


private:
// private attributes

int gridXnum;
int gridYnum;
double width;
double height;

//private method



};
#endif 