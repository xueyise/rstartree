#include "stdafx.h"
#include "RSTDefine.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

///////////////////////////////数据类相关操作///////////////////////////////////////////

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

////////////////////////////////区间相关操作//////////////////////////////////////////

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
	boundingRange.resize(range1.size());
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

///////////////////////////////节点相关操作///////////////////////////////////////////

RSTNode::RSTNode(int M):childNum(0),rstNodeType(NonLeafNode),parent(NULL),
rstData(NULL)
{
	childNodeSet = new RSTNode*[M];
}

RSTNode::~RSTNode()
{
	if (childNodeSet)
	{
		for (int i = 0; i < childNum; i++)
		{
			delete childNodeSet[i];
		}
		delete[] childNodeSet;
	}
	if (rstData)
	{
		for (int i = 0; i < childNum; i++)
		{
			delete rstData[i];
		}
		delete[] rstData;
	}
	if (parent)
	{
		delete parent;
	}
}

void RSTNode::AddChildNode(RSTNode* pChild)
{
	childNodeSet[childNum] = pChild;
	childNum++;
}

void RSTNode::AddData(RSTData* pData)
{
	rstData[childNum] = pData;
	childNum++;
}

void RSTNode::UpdateRange(RSTRange& range_)
{
	for (int i = 0; i < (int)range.size(); i++)
	{
		range[i].min = min(range[i].min, range_[i].min);
		range[i].max = max(range[i].max, range_[i].max);
	}
}

int RSTNode::GetIndexOfNode(RSTNode* pChild)
{
	for (int i = 0; i < this->childNum; i++)
		if (pChild == this->childNodeSet[i])
			return i;
	return -1;
}

void RSTNode::deleteNode(int& indexToDelete){
	int tailIndex = childNum-1;
	//如果删除的不是数组中的最后一个元素，做交换，然后再删除
	if(indexToDelete!=tailIndex){
		RSTNode* temp = this->childNodeSet[indexToDelete];
		childNodeSet[indexToDelete] = childNodeSet[tailIndex];
		childNodeSet[tailIndex] = temp;
	}
	delete childNodeSet[tailIndex];
	childNum--;
}

void RSTNode::deleteNode(RSTNode* pChild)
{
	int index = GetIndexOfNode(pChild);
	if (index > 0) deleteNode(index);
}

void RSTNode::deleteNodeWithoutReleaseMem(int& indexToDelete){
	
	int tailIndex = childNum-1;
	//如果删除的不是数组中的最后一个元素，做交换，然后再删除
	if(indexToDelete!=tailIndex){
		RSTNode* temp = this->childNodeSet[indexToDelete];
		childNodeSet[indexToDelete] = childNodeSet[tailIndex];
		childNodeSet[tailIndex] = temp;
	}
	childNum--;
}

void RSTNode::deleteNodeWithoutReleaseMem(RSTNode* pChild)
{
	int index = GetIndexOfNode(pChild);
	if (index > 0) deleteNode(index);
}