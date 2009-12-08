#include "stdafx.h"
#include "RSTRTree.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////查询函数/////////////////////////////////////////

bool RSTRTree::Search(RSTRange& range, RSTDataSet& result, bool isContain)
{
	if (!Root || Root->childNum == 0)
	{
		return false;
	}
	result.clear();
	if (isContain)
		SearchByContain(range, result, Root);
	else
		SearchByInter(range, result, Root);
	return true;
}

void RSTRTree::SearchByContain(RSTRange& range, RSTDataSet& result, RSTNode* node)
{
	if (node->type != Leaf)
	{
		// 非叶子节点情况
		for (int i = 0; i < node->childNum; i++)
		{
			if (IsContain(node->childSet[i]->range, range))
			{
				SearchByContain(range, result, (RSTNode*)node->childSet[i]);
			}
		}
	}
	else
	{
		// 叶子节点情况
		for (int i = 0; i < node->childNum; i++)
		{
			if (IsContain(node->childSet[i]->range, range))
			{
				result.push_back((RSTData*)(node->childSet[i]));
			}
		}
	}
}

void RSTRTree::SearchByInter(RSTRange& range, RSTDataSet& result, RSTNode* node)
{
	if (node->type != Leaf)
	{
		// 非叶子节点情况
		for (int i = 0; i < node->childNum; i++)
		{
			if (IsJoin(node->childSet[i]->range, range))
			{
				SearchByContain(range, result, (RSTNode*)node->childSet[i]);
			}
		}
	}
	else
	{
		// 叶子节点情况
		for (int i = 0; i < node->childNum; i++)
		{
			if (IsJoin(node->childSet[i]->range, range))
			{
				result.push_back((RSTData*)(node->childSet[i]));
			}
		}
	}
}

/////////////////////////////////插入数据函数/////////////////////////////////////////

void RSTRTree::InsertNode(RSTData* data)
{
	RSTNode* insertNode = ChooseLeaf(data);
	insertNode->AddNode((AbstractNode*)data);
	AdjustTree(insertNode);
}

RSTNode* RSTRTree::ChooseLeaf(RSTData* data)
{
	int i;
	RSTNode* node = Root;
	double min = -1;
	double temp;
	int minChild;
	while (node->type != Leaf)
	{
		for (i = 0; i < node->childNum; i++)
		{
			temp = ComputeMinAdditionVolume(node->childSet[i]->range, data->range);
			if (temp < min || min == -1)
			{
				min = temp;
				minChild = i;
			}
		}
		node = (RSTNode*)node->childSet[minChild];	
	}
	return node;
}

void RSTRTree::AdjustTree(RSTNode* leafNode)
{
	RSTNode* currentNode = leafNode;
	RSTNode* parentNode; 
	RSTNode* splitNode1;
	RSTNode* splitNode2;
	while (currentNode != Root)
	{
		parentNode = (RSTNode*)currentNode->parent;
		if (currentNode->childNum > M)
		{
			Split(currentNode, splitNode1, splitNode2);
			parentNode->AddNode(splitNode1);
			parentNode->AddNode(splitNode2);
			parentNode->UpdateRange(splitNode1->range);
			parentNode->UpdateRange(splitNode2->range);
		}
		parentNode->UpdateRange(currentNode->range);
		currentNode = parentNode;
	}
	if (currentNode->childNum > M)
	{
		RSTNode* newRoot = new RSTNode(M);
		Split(currentNode, splitNode1, splitNode2);
		newRoot->AddNode(splitNode1);
		newRoot->AddNode(splitNode2);
		newRoot->UpdateRange(splitNode1->range);
		newRoot->UpdateRange(splitNode2->range);
		Root = newRoot;
	}
}

///////////////////////////////节点分裂相关操作///////////////////////////////////////////

void RSTRTree::PickSeedsQudratic(RSTNode* splitNode,int& firstSeedIndex,int& secondSeedIndex){
	//临时变量
	int N = splitNode->childNum;
	double difference,tempDiff;
	double* pVol = new double[N];
	RSTRange tempBoundingRange;
	
	//提前计算每个range的大小
	for(int i=0;i<N;i++){
		pVol[i] = ComputeVolume(splitNode->childSet[i]->range);
	}

	//diffrence的初始值
	difference =2.22507e-308;
	
	for(int i=0;i<N;i++){
		for(int j=i+1;j<N;j++){
			if(j==i)continue;
			ComputeBoundingRectangle(splitNode->childSet[i]->range,splitNode->childSet[j]->range,tempBoundingRange);
			tempDiff = ComputeVolume(tempBoundingRange)-pVol[i]-pVol[j];
			if(tempDiff>difference){
				difference = tempDiff;
				firstSeedIndex = i;
				secondSeedIndex = j;
			}
		}
	}
	//释放内存
	delete pVol;
}
void RSTRTree::Split(RSTNode* splitNode,RSTNode*& newSplitNode1,RSTNode*& newSplitNode2){
	QuadraticSplit(splitNode,newSplitNode1,newSplitNode2);
}
void RSTRTree::QuadraticSplit(RSTNode* splitNode,RSTNode*& newSplitNode1,RSTNode*& newSplitNode2){
	//
	//如果子节点个数小于M，则不需要进行分裂操作
	if(splitNode->childNum<=M)return;

	//临时变量
	int tempIndex;
	double d1,d2;
	RSTRange tempBoundingRange;
	RSTNode* tempNewNode;

	//首先选取种子元素
	int firstSeedIndex=-1,secondSeedIndex = -1;
	this->PickSeedsQudratic(splitNode,firstSeedIndex,secondSeedIndex);
	if(-1==firstSeedIndex||-1==secondSeedIndex)return;

	using std::vector;
	
	//生成两个新的节点，用于存放后的结果
	newSplitNode1 = new RSTNode(Leaf,M);;
	newSplitNode2 = new RSTNode(Leaf,M);;
	
	
	//将种子子节点加入到两个新节点中
	newSplitNode1->AddNode(splitNode->childSet[firstSeedIndex]);
	newSplitNode2->AddNode(splitNode->childSet[secondSeedIndex]);
	splitNode->deleteNodeWithoutReleaseMem(firstSeedIndex);
	splitNode->deleteNodeWithoutReleaseMem(secondSeedIndex);
	

	while(splitNode->childNum!=0){
		//首先判断是否剩余子节点个数刚好使得某个分类满足下限
		if((splitNode->childNum+newSplitNode1->childNum)<=m){
			for(int i=0;i<splitNode->childNum;i++){
				newSplitNode1->AddNode(splitNode->childSet[i]);
			}
			for(int i=splitNode->childNum-1;i>=0;i--){
				splitNode->deleteNodeWithoutReleaseMem(i);
			}
			continue;
		}	
		else if((splitNode->childNum+newSplitNode2->childNum)<=m){
			for(int i=0;i<splitNode->childNum;i++){
				newSplitNode2->AddNode(splitNode->childSet[i]);
			}
			for(int i=splitNode->childNum-1;i>=0;i--){
				splitNode->deleteNodeWithoutReleaseMem(i);
			}
			continue;
		}
		tempIndex = -1;
		PickNextQudratic(splitNode,newSplitNode1,newSplitNode2,
			tempBoundingRange,tempIndex,
			d1,d2);
		//得到了有效的index

		//首先判断加入到哪个分类中使得MBR增加的面积最小
		if(d1<d2){
			tempNewNode = newSplitNode1;
		}else if(d1>d2){
			tempNewNode = newSplitNode2;
		}else if(ComputeVolume(newSplitNode1->range)<ComputeVolume(newSplitNode2->range)){
			//如果相等则选择MBR最小的那个
			tempNewNode = newSplitNode1;	
		}else{
			tempNewNode=  newSplitNode2;
		}
		//加入到对应的分类
		tempNewNode->AddNode(splitNode->childSet[tempIndex]);
		//将其从原来的node中删除
		splitNode->deleteNodeWithoutReleaseMem(tempIndex);
	}
	
}
void RSTRTree::PickNextQudratic(RSTNode*& splitNode,RSTNode*& newSplitNode1,
								RSTNode*& newSplitNode2,RSTRange& tempBoundingRange,int& index,
								double& d1,double& d2){
	double diff = -1;
	double tempDiff;
	double tempD1,tempD2;
	index = -1;

	for(int i=0;i<splitNode->childNum;i++){
		//计算将当前range与第一类集合的包围盒	
		ComputeBoundingRectangle(splitNode->childSet[i]->range,newSplitNode1->range,tempBoundingRange);
		//计算将当前range添加到第一类集合后所增加的大小
		tempD1 = ComputeVolume(tempBoundingRange)-ComputeVolume(newSplitNode1->range);
		//计算当前range与第二类集合的包围盒
		ComputeBoundingRectangle(splitNode->childSet[i]->range,newSplitNode2->range,tempBoundingRange);
		//计算当前range添加到第二类集合后所增加的大小
		tempD2 = ComputeVolume(tempBoundingRange)-ComputeVolume(newSplitNode2->range);
		//计算D1和D2的相差值
		tempDiff = fabs(tempD1-tempD2);

		if(tempDiff>diff){
			diff = tempDiff;
			index = i;
			d1 = tempD1;
			d2 = tempD2;
		}
	}

}