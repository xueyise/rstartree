#include "stdafx.h"
#include "RSTRTree.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////查询函数/////////////////////////////////////////

void RSTRTree::Search(RSTRange& range, RSTDataSet& result, bool isContain)
{
	result.clear();
	if (isContain)
		SearchByContain(range, result, Root);
	else
		SearchByInter(range, result, Root);
}

void RSTRTree::SearchByContain(RSTRange& range, RSTDataSet& result, RSTNode* node)
{
	if (node->rstNodeType != Leaf)
	{
		// 非叶子节点情况
		for (int i = 0; i < node->childNum; i++)
		{
			if (IsContain(node->childNodeSet[i]->range, range))
			{
				SearchByContain(range, result, node->childNodeSet[i]);
			}
		}
	}
	else
	{
		// 叶子节点情况
		for (int i = 0; i < node->childNum; i++)
		{
			if (IsContain(node->rstData[i]->range, range))
			{
				result.push_back(*(node->rstData[i]));
			}
		}
	}
}

void RSTRTree::SearchByInter(RSTRange& range, RSTDataSet& result, RSTNode* node)
{
	if (node->rstNodeType != Leaf)
	{
		// 非叶子节点情况
		for (int i = 0; i < node->childNum; i++)
		{
			if (IsJoin(node->childNodeSet[i]->range, range))
			{
				SearchByContain(range, result, node->childNodeSet[i]);
			}
		}
	}
	else
	{
		// 叶子节点情况
		for (int i = 0; i < node->childNum; i++)
		{
			if (IsJoin(node->rstData[i]->range, range))
			{
				result.push_back(*(node->rstData[i]));
			}
		}
	}
}

/////////////////////////////////插入数据函数/////////////////////////////////////////

void RSTRTree::InsertNode(RSTData* data)
{
	RSTNode* insertNode = ChooseLeaf(data);
	if (insertNode->childNum < M)
	{
		insertNode->AddData(data);
	}
}

RSTNode* RSTRTree::ChooseLeaf(RSTData* data)
{
	int i;
	RSTNode* node = Root;
	double min = -1;
	double temp;
	int minChild;
	while (node->rstNodeType != Leaf)
	{
		for (i = 0; i < node->childNum; i++)
		{
			temp = ComputeMinAdditionVolume(node->childNodeSet[i]->range, data->range);
			if (temp < min || min == -1)
			{
				min = temp;
				minChild = i;
			}
		}
		node = node->childNodeSet[minChild];
		
	}
	return node;
}

void RSTRTree::AdjustTree(RSTNode* leafNode)
{

}

void RSTRTree::PickSeedsQudratic(RSTNode* splitNode,int& firstSeedIndex,int& secondSeedIndex){
	//临时变量
	int N = splitNode->childNum;
	double difference,tempDiff;
	double* pVol = new double[N];
	RSTRange tempBoundingRange;
	
	//提前计算每个range的大小
	for(int i=0;i<N;i++){
		pVol[i] = ComputeVolume(splitNode->childNodeSet[i]->range);
	}

	//diffrence的初始值
	difference =2.22507e-308;
	
	for(int i=0;i<N;i++){
		for(int j=i+1;j<N;j++){
			if(j==i)continue;
			ComputeBoundingRectangle(splitNode->childNodeSet[i]->range,splitNode->childNodeSet[j]->range,tempBoundingRange);
			tempDiff = ComputeVolume(tempBoundingRange)-pVol[i]-pVol[j];
			if(tempDiff>difference){
				difference = tempDiff;
				firstSeedIndex = i;
				secondSeedIndex = j;
			}
		}
	}
	delete pVol;
}
void RSTRTree::QuadraticSplit(RSTNode* splitNode,RSTNode*& newSplitNode1,RSTNode*& newSplitNode2){
	//如果子节点个数小于M，则不需要进行分裂操作
	if(splitNode->childNum<=m)return;
	//首先选取种子元素
	int firstSeedIndex=-1,secondSeedIndex = -1;
	this->PickSeedsQudratic(splitNode,firstSeedIndex,secondSeedIndex);
	if(-1==firstSeedIndex||-1==secondSeedIndex)return;

	using std::vector;
	//标识数组，用于标识里面的子节点是否还有效
	vector<bool> isIn(splitNode->childNum);
	int size = (int)isIn.size();
	for(int i=0;i<size;i++)
		isIn[i] = false;
	
	//生成两个新的节点，用于存放后的结果
	newSplitNode1 = new RSTNode(M);
	newSplitNode2 = new RSTNode(M);
	
	//将种子子节点加入到两个新节点中
	newSplitNode1->AddChildNode(splitNode->childNodeSet[firstSeedIndex]);
	newSplitNode2->AddChildNode(splitNode->childNodeSet[secondSeedIndex]);
	
	



	
}
void RSTRTree::PickNextQudratic(RSTNode*& splitNode,RSTNode*& newSplitNode1,RSTNode*& newSplitNode2,vector<bool>& isIn,RSTRange& tempBoundingRange,int& index){
	double diff = -1;
	double tempDiff;
	double d1,d2;
	index = -1;

	for(int i=0;i<splitNode->childNum;i++){
		if(!isIn[i])continue;
		//计算将当前range与第一类集合的包围盒	
		ComputeBoundingRectangle(splitNode->childNodeSet[i]->range,newSplitNode1->range,tempBoundingRange);
		//计算将当前range添加到第一类集合后所增加的大小
		d1 = ComputeVolume(tempBoundingRange)-ComputeVolume(newSplitNode1->range);
		//计算当前range与第二类集合的包围盒
		ComputeBoundingRectangle(splitNode->childNodeSet[i]->range,newSplitNode2->range,tempBoundingRange);
		//计算当前range添加到第二类集合后所增加的大小
		d2 = ComputeVolume(tempBoundingRange)-ComputeVolume(newSplitNode2->range);
		//计算D1和D2的相差值
		tempDiff = fabs(d1-d2);

		if(tempDiff>diff){
			diff = tempDiff;
			index = i;
		}
	}

}