#pragma once
#include "RSTDefine.h"

///////////////////////////����һЩ���������ݽṹ///////////////////////////////////////////////

// 2ά����
class RSTPoint2D : public RSTNode
{
public:
	double x;
	double y;
public:
	RSTPoint2D() : RSTNode(Data, 2, 0) {GenerateRange();}

	void GenerateRange();
};

// 3ά����
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

// 2ά����
class RSTRectangle2D : public RSTNode
{
public:
	double xmin, ymin;
	double xmax, ymax;
public:
	RSTRectangle2D() : RSTNode(Data, 2, 0) {}

	void GenerateRange();
};

// 3ά����
class RSTRectangle3D : public RSTNode
{
public:
	double xmin, ymin, zmin;
	double xmax, ymax, zmax;
public:
	RSTRectangle3D() : RSTNode(Data, 3, 0) {GenerateRange();}

	void GenerateRange();
};

// ��ά����
class RSTPoint : public RSTNode
{
public:
	vector<double> point;
public:
	RSTPoint() : RSTNode(Data, (int)point.size(), 0) {GenerateRange();}

	void GenerateRange();
};

// ��ά������
class RSTRectangle : public RSTNode
{
public:
	RSTRange rect;
public:
	RSTRectangle() : RSTNode(Data, (int)rect.size(), 0) {}

	void GenerateRange();
};