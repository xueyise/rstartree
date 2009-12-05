#include "stdafx.h"
#include "RSTDefine.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

RSTData::RSTData() : dataType(Point), point(NULL), rectangle(NULL)
{

}

RSTData::~RSTData()
{
	if (point)
	{
		delete point;
		point = NULL;
	}
	if (rectangle)
	{
		delete rectangle;
		rectangle = NULL;
	}
}

// 判断两个区间是否相交
bool IsJoin(RSTRange& range1, RSTRange& range2)
{
	for (int i = 0; i < (int)range1.size(); i++)
		if (!((range1[i].max < range2[i].min) && (range1[i].min > range2[i].max)))
			return true;
	return false;
}

// 判断区间2是否在区间1中
bool IsContain(RSTRange& range1, RSTRange& range2)
{
	for (int i = 0; i < (int)range1.size(); i++)
		if (range2[i].max > range1[i].max || range2[i].min < range1[i].min)
			return false;
	return true;
}