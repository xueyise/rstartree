#include "stdafx.h"
#include "RSTTestData.h"

///////////////////////////2维点类///////////////////////////////////////////////

void RSTPoint2D::GenerateRange()
{
	range[0].min = range[0].max = x;
	range[1].min = range[1].max = y;
}

///////////////////////////3维点类///////////////////////////////////////////////

void RSTPoint3D::GenerateRange()
{
	range[0].min = range[0].max = x;
	range[1].min = range[1].max = y;
	range[2].min = range[2].max = z;
}

///////////////////////////2维矩形类///////////////////////////////////////////////

void RSTRectangle2D::GenerateRange()
{
	range[0].min = xmin;
	range[0].max = xmax;
	range[1].min = ymin;
	range[1].max = ymax;
}

///////////////////////////3维矩形类///////////////////////////////////////////////

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