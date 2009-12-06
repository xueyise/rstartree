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


void ComputeBoundingRectangle(RSTRange& range1,RSTRange& range2,RSTRange& boundingRange){
	int size = (int)boundingRange.size();
	for(int i=0;i<size;i++){
		boundingRange[i].min = 
			min(range1[i].min,range2[i].min);
		boundingRange[i].max =
			max(range1[i].max,range2[i].max);
	}
}
//compute the volume of the range
double ComputeVolume(RSTRange& range){
	RSTRange::iterator it = 
		range.begin();
	double vol = 1;
	for(;it!=range.end();it++){
		vol = vol*(it->max-it->min);
	}
	return vol;
}
double ComputeMinAdditionVolume(RSTRange& range1,RSTRange& range2){
	RSTRange boundingRange;
	ComputeBoundingRectangle(range1,range2,boundingRange);
	return ComputeVolume(boundingRange)-ComputeVolume(range1);
}
RSTNode::RSTNode(int& M):childNum(0),rstNodeType(RSTNodeType::NonLeafNode),parent(NULL),
rstData(NULL){
	//int childNum;// 子节点个数	
	//RSTNodeType rstNodeType;// 节点类型
	//RSTRange range;// 节点区域范围
	//RSTNode* parent;// 父节点指针
	//RSTNode** childNodeSet;// 子节点指针，为指针动态数组，当类型为叶子节点是为NULL
	//RSTData** rstData;// 指向数据元组，当类型为非叶子节点时为NULL
	childNodeSet = new RSTNode*[M];
}