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

void RSTRTree::InsertData(RSTData* data)
{
	RSTNode* insertNode = ChooseLeaf(data);
	if (insertNode)
	{
		insertNode->AddNode((AbstractNode*)data);
		AdjustTree(insertNode);
	}	
}

void RSTRTree::InsertNode(RSTNode* insertNode, int h)
{
}

RSTNode* RSTRTree::ChooseLeaf(RSTData* data)
{
	if (!Root) return NULL;
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
		RSTNode* newRoot = new RSTNode(NonLeafNode, M);
		Split(currentNode, splitNode1, splitNode2);
		newRoot->AddNode(splitNode1);
		newRoot->AddNode(splitNode2);
		newRoot->UpdateRange(splitNode1->range);
		newRoot->UpdateRange(splitNode2->range);
		Root = newRoot;
		height++;
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
	if(splitNode->type==Leaf){
		newSplitNode1 = new RSTNode(Leaf,M);
		newSplitNode2 = new RSTNode(Leaf,M);
	}else{
		newSplitNode1 = new RSTNode(NonLeafNode,M);
		newSplitNode2 = new RSTNode(NonLeafNode,M);
	}
	
	
	
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

//////////////////////////////删除数据操作////////////////////////////////////////////

bool RSTRTree::Delete(RSTData *data)
{
	// 确定待删除数据所在的叶子节点
	RSTNode* pnode = (RSTNode*)(data->parent);
	if(!pnode)
		return false;
	// 删除数据
	// ???????????????????????还没有删除数据的操作??????????????????????????????

	// 调整R树
	CondenseTree(pnode);

	// 调整根节点
	if(this->Root->childNum == 1) //如果只有一个孩子，就让这个孩子成为根
	{
		pnode = (RSTNode*)(this->Root->childSet[0]);
		delete this->Root;              //??????????????root是否是new出的????????????????
		this->Root = pnode;
	}
	else if(this->Root->childNum == 0) //如果没有孩子，重置这个根的信息
	{
		this->Root->type = Leaf;
		for(int i = 0; i < (int)(this->Root->range.size()); ++i)
		{
			(this->Root->range)[i].min = 0;
			(this->Root->range)[i].max = 0;
		}
	}

	return true;
}

void RSTRTree::CondenseTree(RSTNode* node)
{
	vector<RSTNode*> nodeset;      // 用以存放被删除的结点的指针
	vector<int> heightset;               // 用以存放被删除的结点的层数（根节点层数为1）
	nodeset.reserve(M);
	heightset.reserve(M);
	RSTNode* fnode = NULL;
	int currentheight = 0;                // 用以存放当前node结点距离叶子节点的高度，height - currentheight是当前的层数
	while(node->parent != NULL)     //如果不是根节点就执行循环
	{
		if(node->childNum < m)
		{
			//临时删除node,不释放内存,存放到nodeset中
			fnode = (RSTNode*)(node->parent);
			fnode->deleteNodeWithoutReleaseMem(node);
			nodeset.push_back(node);
			heightset.push_back(height - currentheight);
		}
		else
		{
			//调整node节点的range
			node->range = node->childSet[0]->range;
			for(int i=1;i<node->childNum;++i)
			{
				node->UpdateRange(node->childSet[i]->range);
			}
		}
		node = fnode;  // 向上继续
		++currentheight;   // 距离叶子节点距离加1
	}
	//将临时删除的节点内的条目重新插入到R树中
	for(size_t i=0;i<nodeset.size();++i)
	{
		if(nodeset[i]->type == Leaf)
		{
			for(int j=0;j<nodeset[i]->childNum;++j)
				InsertData((RSTData*)(nodeset[i]->childSet[j]));
		}
		else
		{
			for(int j=0;j<nodeset[i]->childNum;++j)
				InsertNode((RSTNode*)(nodeset[i]->childSet[j]),heightset[i]);
		}
	}
}
