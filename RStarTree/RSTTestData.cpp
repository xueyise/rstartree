#include "stdafx.h"
#include "RSTTestData.h"

///////////////////////////2维点类///////////////////////////////////////////////

RSTPoint2D::RSTPoint2D(double x_, double y_) : RSTNode(Data, 2, 0), x(x_), y(y_)
{
	this->childNum=0;
	GenerateRange();
}

void RSTPoint2D::GenerateRange()
{
	range[0].min = range[0].max = x;
	range[1].min = range[1].max = y;
}

void RSTPoint2D::GetDataPoints(vector<double> &vec)
{
	vec.clear();
	vec.reserve(2);
	vec.push_back(x);
	vec.push_back(y);
}
///////////////////////////3维点类///////////////////////////////////////////////

RSTPoint3D::RSTPoint3D(double x_, double y_, double z_)  : RSTNode(Data, 3, 0), x(x_), y(y_), z(z_)
{
	GenerateRange();
}

void RSTPoint3D::GenerateRange()
{
	range[0].min = range[0].max = x;
	range[1].min = range[1].max = y;
	range[2].min = range[2].max = z;
}

///////////////////////////2维矩形类///////////////////////////////////////////////

RSTRectangle2D::RSTRectangle2D(double xmin_, double xmax_, double ymin_, double ymax_) 
: RSTNode(Data, 2, 0), xmin(xmin_), ymin(ymin_), ymax(ymax_)
{
	GenerateRange();
}

void RSTRectangle2D::GenerateRange()
{
	range[0].min = xmin;
	range[0].max = xmax;
	range[1].min = ymin;
	range[1].max = ymax;
}

void RSTRectangle2D::GetDataPoints(vector<double> &vec)
{
	vec.clear();
	vec.reserve(8);
	vec.push_back(xmin);
	vec.push_back(ymin);
	vec.push_back(xmin);
	vec.push_back(ymax);
	vec.push_back(xmax);
	vec.push_back(ymax);
	vec.push_back(xmax);
	vec.push_back(ymin);
}

///////////////////////////3维矩形类///////////////////////////////////////////////

RSTRectangle3D::RSTRectangle3D(double xmin_, double xmax_, double ymin_, double ymax_, double zmin_, double zmax_)
: RSTNode(Data, 3, 0), xmin(xmin_), xmax(xmax_), ymin(ymin_), ymax(ymax_), zmin(zmin_), zmax(zmax_)
{
	GenerateRange();
}

void RSTRectangle3D::GenerateRange()
{
	range[0].min = xmin;
	range[0].max = xmax;
	range[1].min = ymin;
	range[1].max = ymax;
	range[2].min = zmin;
	range[2].max = zmax;
}

////////////////////////////多维点类//////////////////////////////////////////////

void RSTPoint::GenerateRange()
{
	for (int i = 0; i < (int)point.size(); i++)
	{
		range[i].min = range[i].max = point[i];
	}
}

////////////////////////////多维矩形类//////////////////////////////////////////////

void RSTRectangle::GenerateRange()
{
	for (int i = 0; i < (int)rect.size(); i++)
	{
		range[i].min = rect[i].min;
		range[i].max = rect[i].max;
	}
}