#include "stdafx.h"
#include "RSTDefine.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

////////////////////////////////区间相关操作//////////////////////////////////////////

// 判断两个区间是否相交
bool IsJoin(RSTRange& range1, RSTRange& range2)
{
	for (int i = 0; i < (int)range1.size(); i++)
	{
		if (range1[i].max < range2[i].min || range2[i].max<range1[i].min)
			return false;
	}
	return true;
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
double ComputeMargin(RSTRange& range){
	double ret = 0;
	int N = (int)range.size();
	for(int i=0;i<N;i++){
		ret+=(range[i].max-range[i].min);
	}
	return ret;
}
double ComputeOverlapValue(RSTRange& range1,RSTRange& range2){
	double ret = 1.0;
	double min,max;
	for(int i=0;i<(int)range1.size();i++){
		min = max(range1[i].min,range2[i].min);
		max = min(range1[i].max,range2[i].max);
		//如果在一个维度上区间没有相交，则两个range就没有交，直接返回0
		if(max<=min)return 0;
		else{
			ret*=(max-min);
		}
	}
	return ret;
}

void ComputePartialBoundingRange(RSTNode** pNode,int firstIndex,int lastIndex,RSTRange& resultRange){
	//初始化
	resultRange = pNode[firstIndex]->range;
	//依次计算
	for(int i=firstIndex+1;i<=lastIndex;i++){
		ComputeBoundingRectangle(pNode[i]->range,resultRange,resultRange);
	}
}

// 不重新设置空间
void GetCenter(RSTRange& range, RSTCPoint& cPoint)
{
	//cPoint.resize(range.size());
	for (int i = 0; i < (int)range.size(); i++)
	{
		cPoint[i] = 0.5 * (range[i].min + range[i].max);
	}
}

double GetDistance(RSTCPoint& p1, RSTCPoint& p2)
{
	double dis = 0;
	for (size_t i = 0; i < p1.size(); i++)
	{
		dis += (p1[i] - p2[i]) * (p1[i] - p2[i]);
	}
	return dis;
}

///////////////////////////////节点相关操作///////////////////////////////////////////

RSTNode::RSTNode(int M /* = DefaultMValue */):childNum(0)
{
	type = NonLeafNode;
	parent = NULL;
	childSet = new RSTNode*[M + 1];
}

RSTNode::RSTNode(int dim, int M)
{
	type = NonLeafNode;
	parent = NULL;
	range.resize(dim);
	for(size_t i=0;i<range.size();++i)
	{
		range[i].max = 0;
		range[i].min = 0;
	}
	childSet = new RSTNode*[M + 1];
}

RSTNode::RSTNode(int type_, int dim, int M) : childNum(0)
{
	type = type_;
	parent = NULL;
	range.resize(dim);
	for(size_t i=0;i<range.size();++i)
	{
		range[i].max = 0;
		range[i].min = 0;
	}
	childSet = new RSTNode*[M + 1];
}

RSTNode::~RSTNode()
{
	if (childSet)
	{
		for (int i = 0; i < childNum; i++)
		{
			delete childSet[i];
			childSet[i]=NULL;
		}
		delete[] childSet;
		childSet = NULL;
	}
	if (parent)
	{
		parent=NULL;
	}
}

void RSTNode::GetDataPoints(vector<double> &vec)
{
	vec.clear();
}

void RSTNode::AddNode(RSTNode* pChild)
{
	childSet[childNum] = pChild;
	childNum++;
	//Added By BaiYanbing
	pChild->parent = this;
}
void RSTNode::AddNodeAndUpdateRange(RSTNode* pChild){
	//Add the new child node
	this->AddNode(pChild);
	//update the range of current node after the child is newly added
	this->UpdateRange(pChild->range);
}

void RSTNode::UpdateRange(RSTRange& range_)
{
	if (childNum == 1)
	{
		for (int i = 0; i < (int)range.size(); i++)
		{
			range[i].min = range_[i].min;
			range[i].max = range_[i].max;
		}
		return;
	}
	for (int i = 0; i < (int)range.size(); i++)
	{
		range[i].min = min(range[i].min, range_[i].min);
		range[i].max = max(range[i].max, range_[i].max);
	}
}
void RSTNode::UpdateRange(){
	if(childNum<1)return;
	for (int i = 0; i < (int)range.size(); i++)
	{
		range[i].min = childSet[0]->range[i].min;
		range[i].max = childSet[0]->range[i].max;
	}
	if(childNum==1)return;
	for(int j=1;j<childNum;j++){
		for (int i = 0; i < (int)range.size(); i++)
		{
			range[i].min = min(range[i].min,childSet[j]->range[i].min);
			range[i].max = max(range[i].max,childSet[j]->range[i].max);
		}
	}
		


	
}

int RSTNode::GetIndexOfNode(RSTNode* pChild)
{
	for (int i = 0; i < this->childNum; i++)
		if (pChild == this->childSet[i])
			return i;
	return -1;
}

void RSTNode::deleteNode(int& indexToDelete){
	int tailIndex = childNum-1;
	//如果删除的不是数组中的最后一个元素，做交换，然后再删除
	if(indexToDelete!=tailIndex){
		RSTNode* temp = this->childSet[indexToDelete];
		childSet[indexToDelete] = childSet[tailIndex];
		childSet[tailIndex] = temp;
	}
	delete childSet[tailIndex];
	childNum--;
}

void RSTNode::deleteNode(RSTNode* pChild)
{
	int index = GetIndexOfNode(pChild);
	if (index >= 0) deleteNode(index);
}

void RSTNode::deleteNodeWithoutReleaseMem(int& indexToDelete){
	
	int tailIndex = childNum-1;
	//如果删除的不是数组中的最后一个元素，做交换，然后再删除
	if(indexToDelete!=tailIndex){
		RSTNode* temp = this->childSet[indexToDelete];
		childSet[indexToDelete] = childSet[tailIndex];
		childSet[tailIndex] = temp;
	}
	childNum--;
}

void RSTNode::deleteNodeWithoutReleaseMem(RSTNode* pChild)
{
	int index = GetIndexOfNode(pChild);
	if (index >= 0) deleteNodeWithoutReleaseMem(index);
}

double RSTNode::ComputeNodeOverlap(int childInd)
{
	double overlap = 0;
	for (int i = 0; i < childNum; i++)
	{
		if (i == childInd)
		{
			continue;
		}
		overlap += ComputeOverlapValue(childSet[i]->range, childSet[childInd]->range);
	}
	return overlap;
}

double RSTNode::ComputeNodeOverlap(int childInd, RSTRange& range)
{
	double overlap = 0;
	for (int i = 0; i < childNum; i++)
	{
		if (i == childInd)
		{
			continue;
		}
		overlap += ComputeOverlapValue(childSet[i]->range, range);
	}
	return overlap;
}

bool CompareRSTNodeValueASC(RSTNodeValue& r1, RSTNodeValue& r2)
{
	return r1.m_value < r2.m_value;
}

bool CompareRSTNodeValueDESC(RSTNodeValue& r1, RSTNodeValue& r2)
{
	return r1.m_value > r2.m_value;
}