#pragma once
#include "RSTDefine.h"

///////////////////////////定义一些测试用数据结构///////////////////////////////////////////////

#define RSTPOINT2D  1
#define RSTPOINT3D 2
#define RSTRECTANGLE2D 3
#define RSTRECTANGLE3D 4
#define RSTPOINT 5
#define RSTRECTANGLE 6

// 2维点类
class RSTPoint2D : public RSTNode
{
public:
	double x;
	double y;

	static const int type = RSTPOINT2D;
public:
	RSTPoint2D() : RSTNode(Data, 2, 0) {}

	RSTPoint2D(double x_, double y_); 

	void GenerateRange();
	void GetDataPoints(vector<double> &vec);
	void OutPutData(std::ostream &output);
	int GetDataType(){return type;}
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

	RSTPoint3D(double x_, double y_, double z_);

	void GenerateRange();
};

// 2维矩形
class RSTRectangle2D : public RSTNode
{
public:
	double xmin, ymin;
	double xmax, ymax;

	static const int type = RSTRECTANGLE2D;
public:
	RSTRectangle2D() : RSTNode(Data, 2, 0) {}

	RSTRectangle2D(double xmin_, double xmax_, double ymin_, double ymax_);

	void GenerateRange();
	void GetDataPoints(vector<double> &vec);
	void OutPutData(std::ostream &output);
	int GetDataType(){return type;}
};

// 3维矩形
class RSTRectangle3D : public RSTNode
{
public:
	double xmin, ymin, zmin;
	double xmax, ymax, zmax;
public:
	RSTRectangle3D() : RSTNode(Data, 3, 0) {}

	RSTRectangle3D(double xmin_, double xmax_, double ymin_, double ymax_, double zmin_, double zmax_);

	void GenerateRange();
};

// 多维点类
class RSTPoint : public RSTNode
{
public:
	vector<double> point;
public:
	RSTPoint() : RSTNode(Data, (int)point.size(), 0) {}

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