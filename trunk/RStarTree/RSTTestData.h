#pragma once
#include "RSTDefine.h"

///////////////////////////定义一些测试用数据结构///////////////////////////////////////////////

// 2维点类
class RSTPoint2D : public RSTNode
{
public:
	double x;
	double y;
public:
	RSTPoint2D() : RSTNode(Data, 2, 0) {GenerateRange();}

	void GenerateRange();
};

// 3维点类
class RSTPoint3D : public RSTNode
{
public:
	double x;
	double y;
	double z;
public:
	RSTPoint3D() : RSTNode(Data, 3, 0) {}

	void GenerateRange();
};

// 2维矩形
class RSTRectangle2D : public RSTNode
{
public:
	double xmin, ymin;
	double xmax, ymax;
public:
	RSTRectangle2D() : RSTNode(Data, 2, 0) {}

	void GenerateRange();
};

// 3维矩形
class RSTRectangle3D : public RSTNode
{
public:
	double xmin, ymin, zmin;
	double xmax, ymax, zmax;
public:
	RSTRectangle3D() : RSTNode(Data, 3, 0) {GenerateRange();}

	void GenerateRange();
};

// 多维点类
class RSTPoint : public RSTNode
{
public:
	vector<double> point;
public:
	RSTPoint() : RSTNode(Data, (int)point.size(), 0) {GenerateRange();}

	void GenerateRange();
};

// 多维矩形类
class RSTRectangle : public RSTNode
{
public:
	RSTRange rect;
public:
	RSTRectangle() : RSTNode(Data, (int)rect.size(), 0) {}

	void GenerateRange();
};