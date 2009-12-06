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
void RSTRTree::QuadraticSplit(RSTNode* splitNode,RSTNode*& newSplitNode1,RSTNode*& newSplitNode2){
	//����ӽڵ����С��M������Ҫ���з��Ѳ���
	if(splitNode->childNum<=m)return;
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
	
	



	
}
void RSTRTree::PickNextQudratic(RSTNode*& splitNode,RSTNode*& newSplitNode1,RSTNode*& newSplitNode2,vector<bool>& isIn,RSTRange& tempBoundingRange,int& index){
	double diff = -1;
	double tempDiff;
	double d1,d2;
	index = -1;

	for(int i=0;i<splitNode->childNum;i++){
		if(!isIn[i])continue;
		//���㽫��ǰrange���һ�༯�ϵİ�Χ��	
		ComputeBoundingRectangle(splitNode->childNodeSet[i]->range,newSplitNode1->range,tempBoundingRange);
		//���㽫��ǰrange��ӵ���һ�༯�Ϻ������ӵĴ�С
		d1 = ComputeVolume(tempBoundingRange)-ComputeVolume(newSplitNode1->range);
		//���㵱ǰrange��ڶ��༯�ϵİ�Χ��
		ComputeBoundingRectangle(splitNode->childNodeSet[i]->range,newSplitNode2->range,tempBoundingRange);
		//���㵱ǰrange��ӵ��ڶ��༯�Ϻ������ӵĴ�С
		d2 = ComputeVolume(tempBoundingRange)-ComputeVolume(newSplitNode2->range);
		//����D1��D2�����ֵ
		tempDiff = fabs(d1-d2);

		if(tempDiff>diff){
			diff = tempDiff;
			index = i;
		}
	}

}