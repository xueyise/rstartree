#include "stdafx.h"
#include "RSTRTree.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////��ѯ����/////////////////////////////////////////

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
		// ��Ҷ�ӽڵ����
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
		// Ҷ�ӽڵ����
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
		// ��Ҷ�ӽڵ����
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
		// Ҷ�ӽڵ����
		for (int i = 0; i < node->childNum; i++)
		{
			if (IsJoin(node->childSet[i]->range, range))
			{
				result.push_back((RSTData*)(node->childSet[i]));
			}
		}
	}
}

/////////////////////////////////�������ݺ���/////////////////////////////////////////

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

///////////////////////////////�ڵ������ز���///////////////////////////////////////////

void RSTRTree::PickSeedsQudratic(RSTNode* splitNode,int& firstSeedIndex,int& secondSeedIndex){
	//��ʱ����
	int N = splitNode->childNum;
	double difference,tempDiff;
	double* pVol = new double[N];
	RSTRange tempBoundingRange;
	
	//��ǰ����ÿ��range�Ĵ�С
	for(int i=0;i<N;i++){
		pVol[i] = ComputeVolume(splitNode->childSet[i]->range);
	}

	//diffrence�ĳ�ʼֵ
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
	//�ͷ��ڴ�
	delete pVol;
}
void RSTRTree::Split(RSTNode* splitNode,RSTNode*& newSplitNode1,RSTNode*& newSplitNode2){
	QuadraticSplit(splitNode,newSplitNode1,newSplitNode2);
}
void RSTRTree::QuadraticSplit(RSTNode* splitNode,RSTNode*& newSplitNode1,RSTNode*& newSplitNode2){
	//
	//����ӽڵ����С��M������Ҫ���з��Ѳ���
	if(splitNode->childNum<=M)return;

	//��ʱ����
	int tempIndex;
	double d1,d2;
	RSTRange tempBoundingRange;
	RSTNode* tempNewNode;

	//����ѡȡ����Ԫ��
	int firstSeedIndex=-1,secondSeedIndex = -1;
	this->PickSeedsQudratic(splitNode,firstSeedIndex,secondSeedIndex);
	if(-1==firstSeedIndex||-1==secondSeedIndex)return;

	using std::vector;
	
	//���������µĽڵ㣬���ڴ�ź�Ľ��
	newSplitNode1 = new RSTNode(Leaf,M);;
	newSplitNode2 = new RSTNode(Leaf,M);;
	
	
	//�������ӽڵ���뵽�����½ڵ���
	newSplitNode1->AddNode(splitNode->childSet[firstSeedIndex]);
	newSplitNode2->AddNode(splitNode->childSet[secondSeedIndex]);
	splitNode->deleteNodeWithoutReleaseMem(firstSeedIndex);
	splitNode->deleteNodeWithoutReleaseMem(secondSeedIndex);
	

	while(splitNode->childNum!=0){
		//�����ж��Ƿ�ʣ���ӽڵ�����պ�ʹ��ĳ��������������
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
		//�õ�����Ч��index

		//�����жϼ��뵽�ĸ�������ʹ��MBR���ӵ������С
		if(d1<d2){
			tempNewNode = newSplitNode1;
		}else if(d1>d2){
			tempNewNode = newSplitNode2;
		}else if(ComputeVolume(newSplitNode1->range)<ComputeVolume(newSplitNode2->range)){
			//��������ѡ��MBR��С���Ǹ�
			tempNewNode = newSplitNode1;	
		}else{
			tempNewNode=  newSplitNode2;
		}
		//���뵽��Ӧ�ķ���
		tempNewNode->AddNode(splitNode->childSet[tempIndex]);
		//�����ԭ����node��ɾ��
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
		//���㽫��ǰrange���һ�༯�ϵİ�Χ��	
		ComputeBoundingRectangle(splitNode->childSet[i]->range,newSplitNode1->range,tempBoundingRange);
		//���㽫��ǰrange��ӵ���һ�༯�Ϻ������ӵĴ�С
		tempD1 = ComputeVolume(tempBoundingRange)-ComputeVolume(newSplitNode1->range);
		//���㵱ǰrange��ڶ��༯�ϵİ�Χ��
		ComputeBoundingRectangle(splitNode->childSet[i]->range,newSplitNode2->range,tempBoundingRange);
		//���㵱ǰrange��ӵ��ڶ��༯�Ϻ������ӵĴ�С
		tempD2 = ComputeVolume(tempBoundingRange)-ComputeVolume(newSplitNode2->range);
		//����D1��D2�����ֵ
		tempDiff = fabs(tempD1-tempD2);

		if(tempDiff>diff){
			diff = tempDiff;
			index = i;
			d1 = tempD1;
			d2 = tempD2;
		}
	}

}