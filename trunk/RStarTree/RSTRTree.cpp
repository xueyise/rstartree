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
			if (IsContain(node->childPointSet[i]->range, range))
			{
				SearchByContain(range, result, node->childPointSet[i]);
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
			if (IsJoin(node->childPointSet[i]->range, range))
			{
				SearchByContain(range, result, node->childPointSet[i]);
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

}

RSTNode* RSTRTree::ChooseLeaf(RSTData* data)
{
	RSTNode* node = Root;
	double max = -1;
	int maxChild;
	while (node->rstNodeType != Leaf)
	{
		
	}
	return node;
}

void RSTRTree::AdjustTree(RSTNode* leafNode)
{

}

void RSTRTree::PickSeedsQudratic(RSTNode* splitNode,int& firstSeedIndex,int& secondSeedIndex){
	

}