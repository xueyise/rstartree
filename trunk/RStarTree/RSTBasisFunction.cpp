#include "stdafx.h"
#include "RSTDefine.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

///////////////////////////////��������ز���///////////////////////////////////////////

RSTData::RSTData() : point(NULL), rectangle(NULL)
{
	type = Point;
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

////////////////////////////////������ز���//////////////////////////////////////////

// �ж����������Ƿ��ཻ
bool IsJoin(RSTRange& range1, RSTRange& range2)
{
	for (int i = 0; i < (int)range1.size(); i++)
		if (!((range1[i].max < range2[i].min) && (range1[i].min > range2[i].max)))
			return true;
	return false;
}

// �ж�����2�Ƿ�������1��
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

///////////////////////////////�ڵ���ز���///////////////////////////////////////////

RSTNode::RSTNode(int M /* = DefaultMValue */):childNum(0)
{
	type = NonLeafNode;
	parent = NULL;
	childSet = new AbstractNode*[M + 1];
}

RSTNode::RSTNode(int dim, int M)
{
	type = NonLeafNode;
	parent = NULL;
	range.resize(dim);
	childSet = new AbstractNode*[M + 1];
}

RSTNode::RSTNode(int type_, int dim, int M) : childNum(0)
{
	type = type_;
	parent = NULL;
	range.resize(dim);
	childSet = new AbstractNode*[M + 1];
}

RSTNode::~RSTNode()
{
	if (childSet)
	{
		for (int i = 0; i < childNum; i++)
		{
			delete childSet[i];
		}
		delete[] childSet;
	}
	if (parent)
	{
		delete parent;
	}
}

void RSTNode::AddNode(AbstractNode* pChild)
{
	childSet[childNum] = pChild;
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

int RSTNode::GetIndexOfNode(AbstractNode* pChild)
{
	for (int i = 0; i < this->childNum; i++)
		if (pChild == this->childSet[i])
			return i;
	return -1;
}

void RSTNode::deleteNode(int& indexToDelete){
	int tailIndex = childNum-1;
	//���ɾ���Ĳ��������е����һ��Ԫ�أ���������Ȼ����ɾ��
	if(indexToDelete!=tailIndex){
		AbstractNode* temp = this->childSet[indexToDelete];
		childSet[indexToDelete] = childSet[tailIndex];
		childSet[tailIndex] = temp;
	}
	delete childSet[tailIndex];
	childNum--;
}

void RSTNode::deleteNode(AbstractNode* pChild)
{
	int index = GetIndexOfNode(pChild);
	if (index > 0) deleteNode(index);
}

void RSTNode::deleteNodeWithoutReleaseMem(int& indexToDelete){
	
	int tailIndex = childNum-1;
	//���ɾ���Ĳ��������е����һ��Ԫ�أ���������Ȼ����ɾ��
	if(indexToDelete!=tailIndex){
		AbstractNode* temp = this->childSet[indexToDelete];
		childSet[indexToDelete] = childSet[tailIndex];
		childSet[tailIndex] = temp;
	}
	childNum--;
}

void RSTNode::deleteNodeWithoutReleaseMem(AbstractNode* pChild)
{
	int index = GetIndexOfNode(pChild);
	if (index > 0) deleteNode(index);
}