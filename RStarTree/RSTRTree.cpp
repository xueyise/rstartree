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
	double d1,d2,difference,tempDiff;
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