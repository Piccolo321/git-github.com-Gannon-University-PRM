#include "grid.h"
#include <cmath>
#include <sstream>
#include <iostream>

using namespace std; 
using std::cout;
using std:: endl;
using std::string;


Grid::Grid(){
	this->gridXnum=81;
	this->gridYnum=97;
}

Grid::Grid(int gridXnum, int gridYnum, double width, double height){
	this->gridXnum=gridXnum;
	this->gridYnum=gridYnum;
	this->width=width;
	this->height=height;
}

Grid::~Grid(){

}

void Grid::setGridXYnum(int gridXnum, int gridYnum){
	this->gridXnum=gridXnum;
	this->gridYnum=gridYnum;
}

int Grid::getGridXnum(){
	return gridXnum;
}

int Grid::getGridYnum(){
	return gridYnum;
}

// need to change to 20 
double Grid::getRealXByGridY(int gridY, double realCenterX) {
	//const double FIXED_WIDTH=22; //inch   ,, changed from 22 
	const double METER_PER_INCH=0.0254;

	//Dr. Xu made change from gridXnum to gridXnum-1 
	double xUnit=width/(gridXnum-1)*METER_PER_INCH;//convert to meter
	// center of the grid is (22,16) if the grid 44 X 32

	double realX= xUnit*((-2.0*gridY+gridYnum-1)/2.0)+realCenterX;

	return realX;
}

double Grid::getRealYByGridX(int gridX, double realCenterY){
	//const double FIXED_HIGHT=20;//inch
	const double METER_PER_INCH=0.0254;
	
	double yUnit=height/(gridYnum-1)*METER_PER_INCH;

	double realY= yUnit*((2.0*gridX-gridXnum+1)/2.0)+realCenterY;

	//assume center of the grid is (22,16) ,
	// for 81*97 need  it will be 40.5, 48.5 
	return realY;
}

	//1 meter = 39.3700787 inch
	//1 inch = 0.0254 meters
	//desired area 22 X 20 inch (0.5588 X 0.508 width/|hight)
	//require 44 X 32 matrix
	//range of gridX is from 0-31
	//range of the gridY is from 0-43
	//each unit in distance between col=0.0127 m , e.g.,xUnit
	//each unit in distance betwen row=0.015875 m, e.g., yUnit  

CPointList * Grid::getResolutionGrid(double realCenterX, double realCenterY){

	CPointList * resolutionList = new CPointList();

	for(int i = 0; i < gridXnum; i++){
		for(int j = 0; j < gridYnum; j++){

			float realX = getRealXByGridY(j, realCenterX);
			float realY = getRealYByGridX(i, realCenterY);

			//float realX = getRealXByGridY(i, realCenterX);
			//float realY = getRealYByGridX(j, realCenterY);

			C3dColourPointRC* newpPoint = new C3dColourPointRC();
			newpPoint -> setXYZ(realX, realY, 0.0);

			//newpPoint->setColour((new RGBQUAD()));

			resolutionList->insertPoint(newpPoint);
		}	
	}

	return resolutionList;
}
