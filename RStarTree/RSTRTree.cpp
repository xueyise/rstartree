#include "stdafx.h"
#include "RSTRTree.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

static int insertNum = 1;
/////////////////////////////////查询函数/////////////////////////////////////////

bool RSTRTree::Search(RSTRange& range, RSTNodeSet& result, bool isContain)
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

void RSTRTree::SearchByContain(RSTRange& range, RSTNodeSet& result, RSTNode* node)
{
	if (node->type != Leaf)
	{
		// 非叶子节点情况
		for (int i = 0; i < node->childNum; i++)
		{
			if (IsContain(node->childSet[i]->range, range))
			{
				SearchByContain(range, result, node->childSet[i]);
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
				result.push_back(node->childSet[i]);
			}
		}
	}
}

void RSTRTree::SearchByInter(RSTRange& range, RSTNodeSet& result, RSTNode* node)
{
	if (node->type != Leaf)
	{
		// 非叶子节点情况
		for (int i = 0; i < node->childNum; i++)
		{
			if (IsJoin(node->childSet[i]->range, range))
			{
				SearchByInter(range, result, node->childSet[i]);
			}
		}
	}
	else
	{
		// 叶子节点情况
		for (int i = 0; i < node->childNum; i++)
		{
			if (IsContain(range, node->childSet[i]->range))
			{
				result.push_back((node->childSet[i]));
			}
		}
	}
}


RSTRTree::~RSTRTree(){

	//节点的析构函数是递归调用的
	if(pVol){
		delete pVol;
		pVol = NULL;
	}
	delete this->Root;
}

/////////////////////////////////插入数据函数/////////////////////////////////////////

void RSTRTree::InsertData(RSTNode* data)
{
#ifdef TEST
	TRACE("\n---------------%d Insert node %x--------------\n", insertNum++, (void*)data);
#endif

	RSTNode* insertNode = ChooseLeaf(data);
	if (insertNode)
	{
		insertNode->AddNode(data);
#ifdef TEST
		TRACE("Add %x to %x\n", (void*)data, (void*)insertNode);
#endif
		
		//added By BaiYanbing
		insertNode->UpdateRange(data->range);
		
		AdjustTree(insertNode);
	}	
}

void RSTRTree::InsertNode(RSTNode* insertNode, int h)
{
#ifdef TEST
	TRACE("\n---------------%d Insert node %x--------------\n", insertNum++, (void*)insertNode);
#endif

	RSTNode* node = ChooseNode(insertNode, h);
	if (node)
	{
		node->AddNode(insertNode);
#ifdef TEST
		TRACE("Add %x to %x\n", (void*)insertNode, (void*)node);
#endif
		//added By BaiYanbing
		node->UpdateRange(insertNode->range);

		AdjustTree(node);
	}
}

// 查找待插入数据的叶子节点
RSTNode* RSTRTree::ChooseLeaf(RSTNode* data)
{
	if (!Root) return NULL;
	int i;
	RSTNode* node = Root;
	double min = -1;
	double temp;
	int minChild;
	while (node->type != Leaf)
	{
		min = -1;
		for (i = 0; i < node->childNum; i++)
		{
			temp = ComputeMinAdditionVolume(node->childSet[i]->range, data->range);
			if (temp < min || min == -1)
			{
				min = temp;
				minChild = i;
			}
			else if (temp == min && ComputeVolume(node->childSet[i]->range) < ComputeVolume(node->childSet[minChild]->range)	)
			{
				min = temp;
				minChild = i;
			}
		}
		node = node->childSet[minChild];	
	}
	return node;
}

// 查找待插入节点的父节点
RSTNode* RSTRTree::ChooseNode(RSTNode* insertNode, int h)
{
	if (!Root) return NULL;
	int i;
	int height = 1;
	RSTNode* node = Root;
	double min = -1;
	double temp;
	int minChild;
	while (height != h)
	{
		for (i = 0; i < node->childNum; i++)
		{
			min = -1;
			temp = ComputeMinAdditionVolume(node->childSet[i]->range, insertNode->range);
			if (temp < min || min == -1)
			{
				min = temp;
				minChild = i;
			}
		}
		node = node->childSet[minChild];	
		height++;
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
#ifdef TEST
			TRACE("Split %x to %x and %x\n", (void*)currentNode, (void*)splitNode1, (void*)splitNode2);
#endif
			parentNode->AddNode(splitNode1);
#ifdef TEST
			TRACE("Add %x to %x\n", (void*)splitNode1, (void*)parentNode);
#endif
			parentNode->AddNode(splitNode2);
#ifdef TEST
			TRACE("Add %x to %x\n", (void*)splitNode2, (void*)parentNode);
#endif
			parentNode->UpdateRange(splitNode1->range);
			parentNode->UpdateRange(splitNode2->range);
		}
		else
			parentNode->UpdateRange(currentNode->range);
		currentNode = parentNode;
	}
	if (currentNode->childNum > M)
	{
		RSTNode* newRoot = new RSTNode(NonLeafNode, dim, M);
		Split(currentNode, splitNode1, splitNode2);
#ifdef TEST
		TRACE("Split %x to %x and %x\n", (void*)currentNode, (void*)splitNode1, (void*)splitNode2);
#endif
		/*newRoot->AddNode(splitNode1);
		newRoot->AddNode(splitNode2);
		newRoot->UpdateRange(splitNode1->range);
		newRoot->UpdateRange(splitNode2->range);*/
		//Modified By BaiYanbing
		newRoot->AddNodeAndUpdateRange(splitNode1);
#ifdef TEST
		TRACE("Add %x to %x\n", (void*)splitNode1, (void*)newRoot);
#endif
		newRoot->AddNodeAndUpdateRange(splitNode2);
#ifdef TEST
		TRACE("Add %x to %x\n", (void*)splitNode2, (void*)newRoot);
#endif
		Root = newRoot;
		height++;
	}
}

///////////////////////////////节点分裂相关操作///////////////////////////////////////////

void RSTRTree::PickSeedsQudratic(RSTNode* splitNode,int& firstSeedIndex,int& secondSeedIndex){
	//临时变量
	int N = splitNode->childNum;
	double difference,tempDiff;
	if(!pVol){
		pVol = new double[N];
	}
	RSTRange tempBoundingRange;
	
	//提前计算每个range的大小
	for(int i=0;i<N;i++){
		pVol[i] = ComputeVolume(splitNode->childSet[i]->range);
	}

	//diffrence的初始值
	ComputeBoundingRectangle(splitNode->childSet[0]->range,splitNode->childSet[1]->range,tempBoundingRange);
	difference = ComputeVolume(tempBoundingRange)-pVol[0]-pVol[1];
	firstSeedIndex = 0;
	secondSeedIndex = 1;

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
	/*delete pVol;*/
}
void RSTRTree::Split(RSTNode* splitNode,RSTNode*& newSplitNode1,RSTNode*& newSplitNode2){
	QuadraticSplit(splitNode,newSplitNode1,newSplitNode2);
}
void RSTRTree::QuadraticSplit(RSTNode* splitNode,RSTNode*& newSplitNode1,RSTNode*& newSplitNode2){
	//allocate memory for new node
	newSplitNode2 = new RSTNode(splitNode->type,dim,M);

	//
	int index;
	double d1,d2;

	RSTRange tempBoundingRange;

	//choose seeds
	int firstSeedIndex = -1;
	int secondSeedIndex = -1;
	
	this->PickSeedsQudratic(splitNode,firstSeedIndex,secondSeedIndex);
	
	
	//将第二个种子加入到newSplitNode2中
	newSplitNode2->AddNodeAndUpdateRange(splitNode->childSet[secondSeedIndex]);
	splitNode->deleteNodeWithoutReleaseMem(secondSeedIndex);
	//在splitNode中处理第一个种子 
	if(firstSeedIndex!=0){
		RSTNode* tempNode = splitNode->childSet[0];
		splitNode->childSet[0] = splitNode->childSet[firstSeedIndex];
		splitNode->childSet[firstSeedIndex] = tempNode;
	}

	int startIndex = 1;
	int endIndex = splitNode->childNum;
	while((endIndex-startIndex)!=0){
		
		if(endIndex<=m){
			//copy all left nodes
			splitNode->childNum = endIndex;
			startIndex = endIndex;
			//将第一个节点书中的可用区域标识为空
			break;
		}
		if((endIndex-startIndex+newSplitNode2->childNum)<=m){
			//copy all left nodes
			for(int i=startIndex;i<endIndex;i++){
				newSplitNode2->AddNodeAndUpdateRange(splitNode->childSet[i]);
			}
			//将第一个节点数组中的可用区域标识为空
			endIndex = startIndex;
			break;
		}

		PickNextQudratic2(splitNode,startIndex,endIndex-1,newSplitNode2,tempBoundingRange,index,d1,d2);
		bool isFirstArray = false;
		if(d1<d2){
			isFirstArray = true;
		}else if(d1>d2){
			isFirstArray = false;
		}else{
			//比较大小
			RSTRange tempRange;
			ComputePartialBoundingRange(splitNode->childSet,startIndex,endIndex-1,tempRange);
			if(ComputeVolume(tempRange)<ComputeVolume(newSplitNode2->range)){
				isFirstArray = true;
			}else {
				isFirstArray = false;
			}
		
		}
		if(isFirstArray){
			if(index==startIndex){
				startIndex++;
			}else{
				RSTNode* tempNode;
				tempNode = splitNode->childSet[startIndex];
				splitNode->childSet[startIndex]=splitNode->childSet[index];
				splitNode->childSet[index] = tempNode;
				startIndex++;
			}

		}else{
			newSplitNode2->AddNodeAndUpdateRange(splitNode->childSet[index]);
			splitNode->childSet[index]=splitNode->childSet[endIndex-1];
			endIndex--;
		}
	}
	splitNode->childNum = startIndex;
	splitNode->UpdateRange();

	if(splitNode->parent){
		splitNode->parent->deleteNodeWithoutReleaseMem(splitNode);
	}else{
		;//do nothing
	}
	newSplitNode1 = splitNode;
}
void RSTRTree::PickNextQudratic2(RSTNode* splitNode,int startIndex,int endIndex,
								 RSTNode* newSplitNode2,RSTRange& tempBoundingRange,int& index,
								 double& d1,double& d2){
	
									 
									 
									 
	

	double diff = -1;
	double tempDiff;
	double tempD1,tempD2;
	RSTRange firstRange;

	//compute the range for the first set
	ComputePartialBoundingRange(splitNode->childSet,startIndex,endIndex,firstRange);

	for(int i=startIndex;i<=endIndex;i++){
		RSTRange& currentRange = splitNode->childSet[i]->range;
		ComputeBoundingRectangle(firstRange,currentRange,tempBoundingRange);
		tempD1 = ComputeVolume(tempBoundingRange)-ComputeVolume(firstRange);
		ComputeBoundingRectangle(newSplitNode2->range,currentRange,tempBoundingRange);
		tempD2 = ComputeVolume(tempBoundingRange)-ComputeVolume(newSplitNode2->range);
		tempDiff = fabs(tempD1-tempD2);
		if(tempDiff>diff){
			diff = tempDiff;
			d1 = tempD1;
			d2= tempD2;
			index = i;
		}
	
	}

}
void RSTRTree::QuadraticSplit2(RSTNode* splitNode,RSTNode*& newSplitNode1,RSTNode*& newSplitNode2){
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
		newSplitNode1 = new RSTNode(Leaf,this->dim,M);
		newSplitNode2 = new RSTNode(Leaf,this->dim,M);
	}else{
		newSplitNode1 = new RSTNode(NonLeafNode,this->dim,M);
		newSplitNode2 = new RSTNode(NonLeafNode,this->dim,M);
	}
	
	
	
	//将种子子节点加入到两个新节点中
	newSplitNode1->AddNodeAndUpdateRange(splitNode->childSet[firstSeedIndex]);
	newSplitNode2->AddNodeAndUpdateRange(splitNode->childSet[secondSeedIndex]);
	splitNode->deleteNodeWithoutReleaseMem(firstSeedIndex);
	if(secondSeedIndex==splitNode->childNum){
		splitNode->deleteNodeWithoutReleaseMem(firstSeedIndex);
	}
	else splitNode->deleteNodeWithoutReleaseMem(secondSeedIndex);
	

	while(splitNode->childNum!=0){
		//首先判断是否剩余子节点个数刚好使得某个分类满足下限
		
		//TODO 还有提高效率的余地
		//可以利用choooseNext的过程将添加后的range大小记录下来，避免重新计算
		if((splitNode->childNum+newSplitNode1->childNum)<=m){
			for(int i=0;i<splitNode->childNum;i++){
				newSplitNode1->AddNodeAndUpdateRange(splitNode->childSet[i]);
			}
			for(int i=splitNode->childNum-1;i>=0;i--){
				splitNode->deleteNodeWithoutReleaseMem(i);
			}
			continue;
		}	
		else if((splitNode->childNum+newSplitNode2->childNum)<=m){
			for(int i=0;i<splitNode->childNum;i++){
				newSplitNode2->AddNodeAndUpdateRange(splitNode->childSet[i]);
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
		tempNewNode->AddNodeAndUpdateRange(splitNode->childSet[tempIndex]);
		//将其从原来的node中删除
		splitNode->deleteNodeWithoutReleaseMem(tempIndex);
		
		
	}
	if(splitNode->parent){
		splitNode->parent->deleteNode(splitNode);
	}else{
		delete splitNode;
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

bool RSTRTree::Delete(RSTNode *data)
{
#ifdef TEST
	TRACE("-----------------Delete Node %x---------------\n", (void*)data);
#endif

	// 确定待删除数据所在的叶子节点
	RSTNode* pnode = (data->parent);
	if(!pnode)
		return false;
	// 删除数据
	// ???????????????????????还没有删除数据的操作??????????????????????????????
	pnode->deleteNode(data);
#ifdef TEST
	TRACE("delete %x from %x\n", (void*)data, (void*)pnode);
#endif

	// 调整R树
	CondenseTree(pnode);

	// 调整根节点
	if((this->Root->childNum == 1)&&(this->Root->childSet[0]->type!=Data)) //如果只有一个孩子，就让这个孩子成为根
	{
		pnode = (RSTNode*)(this->Root->childSet[0]);
		this->Root->childNum = 0;
		delete this->Root;              //??????????????root是否是new出的????????????????
		this->Root = pnode;
		pnode->parent = NULL;
		height--;
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
	else
		this->Root->UpdateRange();

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
		node->range = node->childSet[0]->range;
		for(int i=1;i<node->childNum;++i)
		{
			node->UpdateRange(node->childSet[i]->range);
		}
		fnode = (RSTNode*)(node->parent);
		if(node->childNum < m)
		{
			//临时删除node,不释放内存,存放到nodeset中			
			fnode->deleteNodeWithoutReleaseMem(node);
#ifdef TEST
			TRACE("delete %x from %x\n", (void*)node, (void*)fnode);
#endif
			nodeset.push_back(node);
			heightset.push_back(height - currentheight);
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
				InsertData(nodeset[i]->childSet[j]);
		}
		else
		{
			for(int j=0;j<nodeset[i]->childNum;++j)
				InsertNode(nodeset[i]->childSet[j],heightset[i]);
		}
	}
}

////////////////////////////R*树操作//////////////////////////////////////////////

void RSTRStarTree::InsertData(RSTNode* data)
{
#ifdef TEST
	TRACE("\n---------------%d Insert node %x--------------\n", insertNum++, (void*)data);
#endif

	RSTNode* insertNode = ChooseLeaf(data);
	if (insertNode)
	{
		insertNode->AddNode(data);
#ifdef TEST
		TRACE("Add %x to %x\n", (void*)data, (void*)insertNode);
#endif

		//added By BaiYanbing
		insertNode->UpdateRange(data->range);

		AdjustTree(insertNode);
	}	
}

RSTNode* RSTRStarTree::ChooseLeaf(RSTNode* data)
{
	if (!Root) return NULL;
	int i;
	RSTNode* node = Root;
	double min = -1;
	double temp;
	int minChild;
	RSTRange tempRange;
	while (node->type != Leaf && node->childNum > 0 && node->childSet[0]->type != Leaf)
	{
		min = -1;
		for (i = 0; i < node->childNum; i++)
		{
			temp = ComputeMinAdditionVolume(node->childSet[i]->range, data->range);
			if (temp < min || min == -1)
			{
				min = temp;
				minChild = i;
			}
			else if (temp == min && ComputeVolume(node->childSet[i]->range) < ComputeVolume(node->childSet[minChild]->range)	)
			{
				min = temp;
				minChild = i;
			}
		}
		node = node->childSet[minChild];	
	}

	// 这里提供两个版本
	// 方案1 复杂度较高 但更为精确
	//if (node->childNum > 0 && node->childSet[0]->type == Leaf) // 修改查找叶子节点的方法，通过计算增加最少重复查找
	//{
	//	min = -1;
	//	for (i = 0; i < node->childNum; i++)
	//	{
	//		ComputeBoundingRectangle(node->childSet[i]->range, data->range, tempRange);
	//		temp = node->ComputeNodeOverlap(i, tempRange) - node->ComputeNodeOverlap(i);
	//		if (temp < min || min == -1)
	//		{
	//			min = temp;
	//			minChild = i;
	//		}
	//		else if (temp == min && ComputeMinAdditionVolume(node->childSet[i]->range, data->range) < 
	//			ComputeMinAdditionVolume(node->childSet[minChild]->range, data->range))
	//		{
	//			min = temp;
	//			minChild = i;
	//		}
	//	}
	//	node = node->childSet[minChild];
	//}

	// 方案2 近似最小重复区域查找 速度较快 但是是近似算法 
	if (node->childNum > 0 && node->childSet[0]->type == Leaf) 
	{
		// 排序操作
		bool flag = true;
		for (i = 0; i < node->childNum; i++)
		{
			ComputeBoundingRectangle(node->childSet[i]->range, data->range, boundingRect[i]);
			minAddVolume[i] = ComputeVolume(boundingRect[i]) - ComputeVolume(node->childSet[i]->range);
			rstNodeValueSet[i].m_value = minAddVolume[i];
			rstNodeValueSet[i].nodeInd = i;
		}
		// 这部分改为系统排序
		std::sort(rstNodeValueSet, rstNodeValueSet + node->childNum, CompareRSTNodeValueASC);
		min = -1;
		for (i = 0; i < P && i < node->childNum; i++)
		{
			temp = node->ComputeNodeOverlap(rstNodeValueSet[i].nodeInd, boundingRect[rstNodeValueSet[i].nodeInd]) - node->ComputeNodeOverlap(rstNodeValueSet[i].nodeInd);
			if (temp < min || min == -1)
			{
				min = temp;
				minChild = rstNodeValueSet[i].nodeInd;
			}
			else if (temp == min && minAddVolume[rstNodeValueSet[i].nodeInd] < minAddVolume[minChild])
			{
				min = temp;
				minChild = rstNodeValueSet[i].nodeInd;
			}
		}
		node = node->childSet[minChild];
	}

	return node;
}

// 相当于论文中的OverfkiwTreatment操作
void RSTRStarTree::AdjustTree(RSTNode* leafNode)
{
	RSTNode* currentNode = leafNode;
	RSTNode* parentNode; 
	RSTNode* splitNode1;
	RSTNode* splitNode2;
	while (currentNode != Root)
	{
		//
		parentNode = (RSTNode*)currentNode->parent;
		if (currentNode->childNum > M)
		{
			if (reInsertFlag)
			{
				// 强迫重插入操作
				reInsertFlag = false;
				ReInsert(currentNode);
			}
			else
			{
				Split(currentNode, splitNode1, splitNode2);
#ifdef TEST
				TRACE("Split %x to %x and %x\n", (void*)currentNode, (void*)splitNode1, (void*)splitNode2);
#endif
				parentNode->AddNode(splitNode1);
#ifdef TEST
				TRACE("Add %x to %x\n", (void*)splitNode1, (void*)parentNode);
#endif
				parentNode->AddNode(splitNode2);
#ifdef TEST
				TRACE("Add %x to %x\n", (void*)splitNode2, (void*)parentNode);
#endif
				parentNode->UpdateRange(splitNode1->range);
				parentNode->UpdateRange(splitNode2->range);
			}		
		}
		else
			parentNode->UpdateRange(currentNode->range);
		currentNode = parentNode;
	}
	if (currentNode->childNum > M)
	{
		RSTNode* newRoot = new RSTNode(NonLeafNode, dim, M);
		Split(currentNode, splitNode1, splitNode2);
#ifdef TEST
		TRACE("Split %x to %x and %x\n", (void*)currentNode, (void*)splitNode1, (void*)splitNode2);
#endif
		/*newRoot->AddNode(splitNode1);
		newRoot->AddNode(splitNode2);
		newRoot->UpdateRange(splitNode1->range);
		newRoot->UpdateRange(splitNode2->range);*/
		//Modified By BaiYanbing
		newRoot->AddNodeAndUpdateRange(splitNode1);
#ifdef TEST
		TRACE("Add %x to %x\n", (void*)splitNode1, (void*)newRoot);
#endif
		newRoot->AddNodeAndUpdateRange(splitNode2);
#ifdef TEST
		TRACE("Add %x to %x\n", (void*)splitNode2, (void*)newRoot);
#endif
		Root = newRoot;
		height++;
		reInsertFlag = true;
	}
}

// 强迫重插入
void RSTRStarTree::ReInsert(RSTNode* reInsertNode)
{
	int i;
	GetCenter(reInsertNode->range, center);

	for (i = 0; i < reInsertNode->childNum; i++)
	{
		GetCenter(reInsertNode->childSet[i]->range, tempPoint);
		rstNodeValueSet[i].m_value = GetDistance(tempPoint, center);
		rstNodeValueSet[i].nodeInd = i;
	}
	std::sort(rstNodeValueSet, rstNodeValueSet + M + 1, CompareRSTNodeValueDESC);
	for (i = 0; i < P && i < M + 1; i++)
	{
		tempNodeSet[i] = reInsertNode->childSet[rstNodeValueSet[i].nodeInd];
	}
	reInsertNode->childNum = reInsertNode->childNum - min(P, M + 1);
	for (i = 0; i < reInsertNode->childNum; i++)
	{
		tempLeaveNode[i] = reInsertNode->childSet[rstNodeValueSet[M - i].nodeInd];
	}
	for (i = 0; i < reInsertNode->childNum; i++)
	{
		reInsertNode->childSet[i] = tempLeaveNode[i];
	}
	if (reInsertNode->childNum > 0)
	{
		reInsertNode->range = reInsertNode->childSet[0]->range;
		for (i = 1; i < reInsertNode->childNum; i++)
		{
			reInsertNode->UpdateRange(reInsertNode->childSet[i]->range);
		}
	}
	for (i = 0; i < P && i < M + 1; i++)
	{
		InsertData(tempNodeSet[i]);
		tempNodeSet[i] = NULL;
	}
}

void RSTRStarTree::Split(RSTNode* splitNode,RSTNode*& newSplitNode1,RSTNode*& newSplitNode2){
	//为第二个节点分配内存
	newSplitNode2 = new RSTNode(splitNode->type,this->dim,this->M);
	int axis = ChooseSplitAxis(splitNode);
	//copy contents from splitNode to newly allocated node
	for(int i=0;i<=M;i++){
		newSplitNode2->childSet[i] = splitNode->childSet[i];
	}

	//
	RSTNodeComparator minCmp(axis,true);
	RSTNodeComparator maxCmp(axis,false);
	//sort
	using namespace std;
	sort(splitNode->childSet,splitNode->childSet+M+1,minCmp);
	sort(newSplitNode2->childSet,newSplitNode2->childSet+M+1,maxCmp);

	//
	bool minOrMax;
	int splitIndex;
	ChooseSplitIndex(splitNode->childSet,newSplitNode2->childSet,minOrMax,splitIndex);
	if(minOrMax){
		//copy the second part into newsplitnode2
		newSplitNode2->childNum = 0;
		for(int i=splitIndex+1;i<=M;i++){
			newSplitNode2->AddNodeAndUpdateRange(splitNode->childSet[i]);
		}	
		//reset the split number

		splitNode->childNum = splitIndex+1;
		splitNode->UpdateRange();
	}else{
		splitNode->childNum = 0;
		for(int i=splitIndex+1;i<=M;i++){
			splitNode->AddNodeAndUpdateRange(newSplitNode2->childSet[i]);
		}
		newSplitNode2->childNum = splitIndex+1;
	}
	newSplitNode1 = splitNode;
	//将其他位置清空
	/*for(int i=newSplitNode1->childNum;i<=M;i++){
		newSplitNode1->childSet[i]=NULL;
	}
	for(int i=newSplitNode2->childNum;i<=M;i++){
		newSplitNode2->childSet[i]=NULL;
	}*/
	/*for(int i=0;i<newSplitNode1->childNum;i++){
		newSplitNode1->childSet[i]->parent = 
			newSplitNode1;
	}
	for(int i=0;i<newSplitNode2->childNum;i++){
		newSplitNode2->childSet[i]->parent = 
			newSplitNode2;
	}
	newSplitNode1->UpdateRange();
	newSplitNode2->UpdateRange();*/
	if(minOrMax){
		newSplitNode1->UpdateRange();
	}else{
		for(int i=0;i<newSplitNode2->childNum;i++){
			newSplitNode2->childSet[i]->parent = 
				newSplitNode2;
		}
		newSplitNode2->UpdateRange();
	}
	if(splitNode->parent){
		splitNode->parent->deleteNodeWithoutReleaseMem(splitNode);
	}else{
		;//do nothing
	}
}

void RSTRStarTree::Split2(RSTNode* splitNode,RSTNode*& newSplitNode1,RSTNode*& newSplitNode2){
	
	//allocate memory for two new nodes
	newSplitNode1 = new RSTNode(splitNode->type,this->dim,this->M);
	newSplitNode2 = new RSTNode(splitNode->type,this->dim,this->M);

	//选择要分裂的坐标方向
	int axis = ChooseSplitAxis(splitNode);
	//接下来，分别暂时利用newSplitNode1和newSplitNode2的空间，
	//暂时用newSplitNode1的空间存储对min进行排序的结果
	//暂时用newSplitNode2的空间存储对max进行排序的结果
	//copy pointers
	for(int i=0;i<=M;i++){
		newSplitNode1->childSet[i] = splitNode->childSet[i];
		newSplitNode2->childSet[i] = splitNode->childSet[i];
	}
	//构造min方向和max方向上的比较器
	RSTNodeComparator minCmp(axis,true);
	RSTNodeComparator maxCmp(axis,false);
	//sort
	using namespace std;
	sort(newSplitNode1->childSet,newSplitNode1->childSet+M+1,minCmp);
	sort(newSplitNode2->childSet,newSplitNode2->childSet+M+1,maxCmp);

	//
	bool minOrMax;
	int splitIndex;
	ChooseSplitIndex(newSplitNode1->childSet,newSplitNode2->childSet,minOrMax,splitIndex);
	RSTNode* p;
	//如果最佳分裂点位于按min排序的数组中
	if(minOrMax){
		p = newSplitNode1;
	}else{
		//如果最佳分裂点位于按max排序的数组中
		p = newSplitNode2;
	}
	//将最佳分裂所在的排序数组复制到原数组中
	for(int i=0;i<=M;i++){
		splitNode->childSet[i] = p->childSet[i];
	}
	//将0~splitIndex所在的元素放到newSplitNode1中
	for(int i=0;i<=splitIndex;i++){
		newSplitNode1->AddNodeAndUpdateRange(splitNode->childSet[i]);
	}
	//将其他元素放到newSplitNode2中
	for(int i=splitIndex+1;i<=M;i++){
		newSplitNode2->AddNodeAndUpdateRange(splitNode->childSet[i]);
	}
	//将splitNode的childNum设置为0，防止删除时递归删除其原来的child
	splitNode->childNum = 0;
	
	//删除原来的splitNode
	if(splitNode->parent){
		splitNode->parent->deleteNode(splitNode);
	}else{
		//如果是根则直接释放
		delete splitNode;
	}

}
int RSTRStarTree::ChooseSplitAxis(RSTNode*& splitNode){
	double resultS= DBL_MAX;
	double tempS;
	int k;
	int resultAxis = 0;
	int D = this->dim;
	int N = this->M+1;
	int K_MAX = M-2*m+2;
	int K_MIN =1;
	//临时变量，第一组矩形的包围盒和第二组矩形的包围盒
	RSTRange firstGroupBoundingRange;
	RSTRange secondGroupBoundingRange;
	using namespace std;
	for(int i=0;i<D;i++){
		tempS = 0;
		k=1;
		//sort by min
		RSTNodeComparator minCom(i,true);
		sort(splitNode->childSet,splitNode->childSet+N,minCom);
		///////min//////////
		//初始化
		
		firstGroupBoundingRange = splitNode->childSet[0]->range;
		for(int j=1;j<m-1;j++){
			ComputeBoundingRectangle(splitNode->childSet[j]->range,firstGroupBoundingRange,firstGroupBoundingRange);
		}
		//Loop
		for(int k=K_MIN;k<=K_MAX;k++){
			//第一组的包围盒
			ComputeBoundingRectangle(splitNode->childSet[m-2+k]->range,firstGroupBoundingRange,firstGroupBoundingRange);
			//第二组的包围盒
			ComputePartialBoundingRange(splitNode->childSet,m-1+k,M,secondGroupBoundingRange);
			//计算margin的和
			tempS +=( ComputeMargin(firstGroupBoundingRange)+ComputeMargin(secondGroupBoundingRange));
		}
		///////max//////////
		//sort by max
		RSTNodeComparator maxCom(i,false);
		sort(splitNode->childSet,splitNode->childSet+N,maxCom);
		//初始化
		firstGroupBoundingRange = splitNode->childSet[0]->range;
		for(int j=1;j<m-1;j++){
			ComputeBoundingRectangle(splitNode->childSet[j]->range,firstGroupBoundingRange,firstGroupBoundingRange);
		}
		//Loop
		for(int k=K_MIN;k<=K_MAX;k++){
			//compute margin and add to tempS
			//第一组的包围盒
			ComputeBoundingRectangle(splitNode->childSet[m-2+k]->range,firstGroupBoundingRange,firstGroupBoundingRange);
			//第二组的包围盒
			ComputePartialBoundingRange(splitNode->childSet,m-1+k,M,secondGroupBoundingRange);
			//计算Margin
			tempS +=(ComputeMargin(firstGroupBoundingRange)+ComputeMargin(secondGroupBoundingRange));
		}


		//如果计算结果比当前的结果小，则更新当前结果
		if(tempS<resultS){
			resultAxis = i;
			resultS = tempS;
		}
	}
	return resultAxis;
}
void RSTRStarTree::ChooseSplitIndex(RSTNode**& nodes1,RSTNode**& nodes2,bool& minOrMax,int& splitIndex){
	RSTRange firstGroupBoundingRange;
	RSTRange secondGroupBoundingRange;
	int K_MIN = 1;
	int K_MAX = M-2*m+2;
	double resultOverlap =DBL_MAX;
	double resultArea = DBL_MAX;
	double tempOverlap,tempArea;

	minOrMax = true;
	splitIndex = 0;
	//初始化第一组的包围盒
	firstGroupBoundingRange = nodes1[0]->range;
	for(int i=1;i<m-1;i++){
		ComputeBoundingRectangle(nodes1[i]->range,firstGroupBoundingRange,firstGroupBoundingRange);
	}
	//Loop
	for(int k=K_MIN;k<=K_MAX;k++){
		ComputeBoundingRectangle(nodes1[m-2+k]->range,firstGroupBoundingRange,firstGroupBoundingRange);
		ComputePartialBoundingRange(nodes1,m-1+k,M,secondGroupBoundingRange);
		tempOverlap = ComputeOverlapValue(firstGroupBoundingRange,secondGroupBoundingRange);
		if(tempOverlap<resultOverlap){
			splitIndex = m-2+k;
			resultOverlap=tempOverlap;
			resultArea = ComputeVolume(firstGroupBoundingRange)+ComputeVolume(secondGroupBoundingRange);
		}else if(tempOverlap==resultOverlap){
			tempArea = ComputeVolume(firstGroupBoundingRange)+ComputeVolume(secondGroupBoundingRange);
			if(tempArea<resultArea){
				splitIndex = m-2+k;
				resultArea = tempArea;
			}else continue;
		}else continue;
	}


	//对按max排序的数组进行操作
	firstGroupBoundingRange = nodes2[0]->range;
	for(int i=1;i<m-1;i++){
		ComputeBoundingRectangle(nodes2[i]->range,firstGroupBoundingRange,firstGroupBoundingRange);
	}
	//Loop
	for(int k=K_MIN;k<=K_MAX;k++){
		ComputeBoundingRectangle(nodes2[m-2+k]->range,firstGroupBoundingRange,firstGroupBoundingRange);
		ComputePartialBoundingRange(nodes2,m-1+k,M,secondGroupBoundingRange);
		tempOverlap = ComputeOverlapValue(firstGroupBoundingRange,secondGroupBoundingRange);
		if(tempOverlap<resultOverlap){
			splitIndex = m-2+k;
			resultOverlap = tempOverlap;
			resultArea = ComputeVolume(firstGroupBoundingRange)+ComputeVolume(secondGroupBoundingRange);
			minOrMax = false;
		}else if(tempOverlap==resultOverlap){
			tempArea = ComputeVolume(firstGroupBoundingRange)+ComputeVolume(secondGroupBoundingRange);
			if(tempArea<resultArea){
				resultArea = tempArea;
				splitIndex = m-2+k;
				minOrMax = false;
			}else continue;
		}else continue;
	}
}
