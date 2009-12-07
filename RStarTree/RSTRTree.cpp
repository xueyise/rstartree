#include "stdafx.h"
#include "RSTRTree.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////��ѯ����/////////////////////////////////////////

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
		// ��Ҷ�ӽڵ����
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
		// Ҷ�ӽڵ����
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
		// ��Ҷ�ӽڵ����
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
		// Ҷ�ӽڵ����
		for (int i = 0; i < node->childNum; i++)
		{
			if (IsJoin(node->rstData[i]->range, range))
			{
				result.push_back(*(node->rstData[i]));
			}
		}
	}
}

/////////////////////////////////�������ݺ���/////////////////////////////////////////

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
	//��ʱ����
	int N = splitNode->childNum;
	double difference,tempDiff;
	double* pVol = new double[N];
	RSTRange tempBoundingRange;
	
	//��ǰ����ÿ��range�Ĵ�С
	for(int i=0;i<N;i++){
		pVol[i] = ComputeVolume(splitNode->childNodeSet[i]->range);
	}

	//diffrence�ĳ�ʼֵ
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
void RSTRTree::Split(RSTNode* splitNode,RSTNode*& newSplitNode1,RSTNode*& newSplitNode2){
	QuadraticSplit(splitNode,newSplitNode1,newSplitNode2);
}
void RSTRTree::QuadraticSplit(RSTNode* splitNode,RSTNode*& newSplitNode1,RSTNode*& newSplitNode2){
	//
	//����ӽڵ����С��M������Ҫ���з��Ѳ���
	if(splitNode->childNum<=m)return;

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
	//��ʶ���飬���ڱ�ʶ������ӽڵ��Ƿ���Ч
	vector<bool> isIn(splitNode->childNum);
	int size = (int)isIn.size();
	for(int i=0;i<size;i++)
		isIn[i] = false;
	
	//���������µĽڵ㣬���ڴ�ź�Ľ��
	newSplitNode1 = new RSTNode(M);
	newSplitNode2 = new RSTNode(M);
	
	//�������ӽڵ���뵽�����½ڵ���
	newSplitNode1->AddChildNode(splitNode->childNodeSet[firstSeedIndex]);
	newSplitNode2->AddChildNode(splitNode->childNodeSet[secondSeedIndex]);
	splitNode->deleteNodeWithoutReleaseMem(firstSeedIndex);
	splitNode->deleteNodeWithoutReleaseMem(secondSeedIndex);
	

	while(splitNode->childNum!=0){
		//�����ж��Ƿ�ʣ���ӽڵ�����պ�ʹ��ĳ��������������
		if((splitNode->childNum+newSplitNode1->childNum)<=m){
			for(int i=0;i<splitNode->childNum;i++){
				newSplitNode1->AddChildNode(splitNode->childNodeSet[i]);
			}
			for(int i=splitNode->childNum-1;i>=0;i--){
				splitNode->deleteNodeWithoutReleaseMem(i);
			}
			continue;
		}	
		if((splitNode->childNum+newSplitNode2->childNum)<=m){
			for(int i=0;i<splitNode->childNum;i++){
				newSplitNode2->AddChildNode(splitNode->childNodeSet[i]);
			}
			for(int i=splitNode->childNum-1;i>=0;i--){
				splitNode->deleteNodeWithoutReleaseMem(i);
			}
			continue;
		}
		tempIndex = -1;
		PickNextQudratic(splitNode,newSplitNode1,newSplitNode2,isIn,
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
		tempNewNode->AddChildNode(splitNode->childNodeSet[tempIndex]);
		//�����ԭ����node��ɾ��
		splitNode->deleteNodeWithoutReleaseMem(tempIndex);
	}
	
}
void RSTRTree::PickNextQudratic(RSTNode*& splitNode,RSTNode*& newSplitNode1,
								RSTNode*& newSplitNode2,vector<bool>& isIn,
								RSTRange& tempBoundingRange,int& index,
								double& d1,double& d2){
	double diff = -1;
	double tempDiff;
	double tempD1,tempD2;
	index = -1;

	for(int i=0;i<splitNode->childNum;i++){
		if(!isIn[i])continue;
		//���㽫��ǰrange���һ�༯�ϵİ�Χ��	
		ComputeBoundingRectangle(splitNode->childNodeSet[i]->range,newSplitNode1->range,tempBoundingRange);
		//���㽫��ǰrange��ӵ���һ�༯�Ϻ������ӵĴ�С
		tempD1 = ComputeVolume(tempBoundingRange)-ComputeVolume(newSplitNode1->range);
		//���㵱ǰrange��ڶ��༯�ϵİ�Χ��
		ComputeBoundingRectangle(splitNode->childNodeSet[i]->range,newSplitNode2->range,tempBoundingRange);
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