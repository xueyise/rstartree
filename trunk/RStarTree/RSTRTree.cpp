#include "stdafx.h"
#include "RSTRTree.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

static int insertNum = 1;
/////////////////////////////////��ѯ����/////////////////////////////////////////

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
		// ��Ҷ�ӽڵ����
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
		// Ҷ�ӽڵ����
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
		// ��Ҷ�ӽڵ����
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
		// Ҷ�ӽڵ����
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

	//�ڵ�����������ǵݹ���õ�
	delete this->Root;
}

/////////////////////////////////�������ݺ���/////////////////////////////////////////

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

// ���Ҵ��������ݵ�Ҷ�ӽڵ�
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

// ���Ҵ�����ڵ�ĸ��ڵ�
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
	if(splitNode->type==Leaf){
		newSplitNode1 = new RSTNode(Leaf,this->dim,M);
		newSplitNode2 = new RSTNode(Leaf,this->dim,M);
	}else{
		newSplitNode1 = new RSTNode(NonLeafNode,this->dim,M);
		newSplitNode2 = new RSTNode(NonLeafNode,this->dim,M);
	}
	
	
	
	//�������ӽڵ���뵽�����½ڵ���
	newSplitNode1->AddNodeAndUpdateRange(splitNode->childSet[firstSeedIndex]);
	newSplitNode2->AddNodeAndUpdateRange(splitNode->childSet[secondSeedIndex]);
	splitNode->deleteNodeWithoutReleaseMem(firstSeedIndex);
	if(secondSeedIndex==splitNode->childNum){
		splitNode->deleteNodeWithoutReleaseMem(firstSeedIndex);
	}
	else splitNode->deleteNodeWithoutReleaseMem(secondSeedIndex);
	

	while(splitNode->childNum!=0){
		//�����ж��Ƿ�ʣ���ӽڵ�����պ�ʹ��ĳ��������������
		
		//TODO �������Ч�ʵ����
		//��������choooseNext�Ĺ��̽���Ӻ��range��С��¼�������������¼���
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
		tempNewNode->AddNodeAndUpdateRange(splitNode->childSet[tempIndex]);
		//�����ԭ����node��ɾ��
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

//////////////////////////////ɾ�����ݲ���////////////////////////////////////////////

bool RSTRTree::Delete(RSTNode *data)
{
	// ȷ����ɾ���������ڵ�Ҷ�ӽڵ�
	RSTNode* pnode = (data->parent);
	if(!pnode)
		return false;
	// ɾ������
	// ???????????????????????��û��ɾ�����ݵĲ���??????????????????????????????

	// ����R��
	CondenseTree(pnode);

	// �������ڵ�
	if(this->Root->childNum == 1) //���ֻ��һ�����ӣ�����������ӳ�Ϊ��
	{
		pnode = (RSTNode*)(this->Root->childSet[0]);
		delete this->Root;              //??????????????root�Ƿ���new����????????????????
		this->Root = pnode;
	}
	else if(this->Root->childNum == 0) //���û�к��ӣ��������������Ϣ
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
	vector<RSTNode*> nodeset;      // ���Դ�ű�ɾ���Ľ���ָ��
	vector<int> heightset;               // ���Դ�ű�ɾ���Ľ��Ĳ��������ڵ����Ϊ1��
	nodeset.reserve(M);
	heightset.reserve(M);
	RSTNode* fnode = NULL;
	int currentheight = 0;                // ���Դ�ŵ�ǰnode������Ҷ�ӽڵ�ĸ߶ȣ�height - currentheight�ǵ�ǰ�Ĳ���
	while(node->parent != NULL)     //������Ǹ��ڵ��ִ��ѭ��
	{
		if(node->childNum < m)
		{
			//��ʱɾ��node,���ͷ��ڴ�,��ŵ�nodeset��
			fnode = (RSTNode*)(node->parent);
			fnode->deleteNodeWithoutReleaseMem(node);
			nodeset.push_back(node);
			heightset.push_back(height - currentheight);
		}
		else
		{
			//����node�ڵ��range
			node->range = node->childSet[0]->range;
			for(int i=1;i<node->childNum;++i)
			{
				node->UpdateRange(node->childSet[i]->range);
			}
		}
		node = fnode;  // ���ϼ���
		++currentheight;   // ����Ҷ�ӽڵ�����1
	}
	//����ʱɾ���Ľڵ��ڵ���Ŀ���²��뵽R����
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

////////////////////////////R*������//////////////////////////////////////////////

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

	// �����ṩ�����汾
	// ����1 ���ӶȽϸ� ����Ϊ��ȷ
	//if (node->childNum > 0 && node->childSet[0]->type == Leaf) // �޸Ĳ���Ҷ�ӽڵ�ķ�����ͨ���������������ظ�����
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

	// ����2 ������С�ظ�������� �ٶȽϿ� �����ǽ����㷨 
	if (node->childNum > 0 && node->childSet[0]->type == Leaf) 
	{
		// �������
		for (int i = 0; i < node->childNum; i++)
		{
			for (int j = 0; j < node->childNum - 1; j++)
			{
				if (ComputeMinAdditionVolume(node->childSet[j]->range, data->range) > 
					ComputeMinAdditionVolume(node->childSet[j + 1]->range, data->range))
				{
					RSTNode* tempP;
					tempP = node->childSet[j];
					node->childSet[j] = node->childSet[j + 1];
					node->childSet[j + 1] = tempP;
				}
			}
		}
		min = -1;
		for (int i = 0; i < P && i < node->childNum; i++)
		{
			ComputeBoundingRectangle(node->childSet[i]->range, data->range, tempRange);
			temp = node->ComputeNodeOverlap(i, tempRange) - node->ComputeNodeOverlap(i);
			if (temp < min || min == -1)
			{
				min = temp;
				minChild = i;
			}
			else if (temp == min && ComputeMinAdditionVolume(node->childSet[i]->range, data->range) < 
				ComputeMinAdditionVolume(node->childSet[minChild]->range, data->range))
			{
				min = temp;
				minChild = i;
			}
		}
		node = node->childSet[minChild];
	}

	return node;
}

void RSTRStarTree::Split(RSTNode* splitNode,RSTNode*& newSplitNode1,RSTNode*& newSplitNode2){
	
	//allocate memory for two new nodes
	newSplitNode1 = new RSTNode(splitNode->type,this->dim,this->M);
	newSplitNode2 = new RSTNode(splitNode->type,this->dim,this->M);

	//ѡ��Ҫ���ѵ����귽��
	int axis = ChooseSplitAxis(splitNode);
	//���������ֱ���ʱ����newSplitNode1��newSplitNode2�Ŀռ䣬
	//��ʱ��newSplitNode1�Ŀռ�洢��min��������Ľ��
	//��ʱ��newSplitNode2�Ŀռ�洢��max��������Ľ��
	//copy pointers
	for(int i=0;i<=M;i++){
		newSplitNode1->childSet[i] = splitNode->childSet[i];
		newSplitNode2->childSet[i] = splitNode->childSet[i];
	}
	//����min�����max�����ϵıȽ���
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
	//�����ѷ��ѵ�λ�ڰ�min�����������
	if(minOrMax){
		p = newSplitNode1;
	}else{
		//�����ѷ��ѵ�λ�ڰ�max�����������
		p = newSplitNode2;
	}
	//����ѷ������ڵ��������鸴�Ƶ�ԭ������
	for(int i=0;i<=M;i++){
		splitNode->childSet[i] = p->childSet[i];
	}
	//��0~splitIndex���ڵ�Ԫ�طŵ�newSplitNode1��
	for(int i=0;i<=splitIndex;i++){
		newSplitNode1->AddNodeAndUpdateRange(splitNode->childSet[i]);
	}
	//������Ԫ�طŵ�newSplitNode2��
	for(int i=splitIndex+1;i<=M;i++){
		newSplitNode2->AddNodeAndUpdateRange(splitNode->childSet[i]);
	}
	//��splitNode��childNum����Ϊ0����ֹɾ��ʱ�ݹ�ɾ����ԭ����child
	splitNode->childNum = 0;
	
	//ɾ��ԭ����splitNode
	if(splitNode->parent){
		splitNode->parent->deleteNode(splitNode);
	}else{
		//����Ǹ���ֱ���ͷ�
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
	//��ʱ��������һ����εİ�Χ�к͵ڶ�����εİ�Χ��
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
		//��ʼ��
		
		firstGroupBoundingRange = splitNode->childSet[0]->range;
		for(int j=1;j<m-1;j++){
			ComputeBoundingRectangle(splitNode->childSet[j]->range,firstGroupBoundingRange,firstGroupBoundingRange);
		}
		//Loop
		for(int k=K_MIN;k<=K_MAX;k++){
			//��һ��İ�Χ��
			ComputeBoundingRectangle(splitNode->childSet[m-2+k]->range,firstGroupBoundingRange,firstGroupBoundingRange);
			//�ڶ���İ�Χ��
			ComputePartialBoundingRange(splitNode->childSet,m-1+k,M,secondGroupBoundingRange);
			//����margin�ĺ�
			tempS +=( ComputeMargin(firstGroupBoundingRange)+ComputeMargin(secondGroupBoundingRange));
		}
		///////max//////////
		//sort by max
		RSTNodeComparator maxCom(i,false);
		sort(splitNode->childSet,splitNode->childSet+N,maxCom);
		//��ʼ��
		firstGroupBoundingRange = splitNode->childSet[0]->range;
		for(int j=1;j<m-1;j++){
			ComputeBoundingRectangle(splitNode->childSet[j]->range,firstGroupBoundingRange,firstGroupBoundingRange);
		}
		//Loop
		for(int k=K_MIN;k<=K_MAX;k++){
			//compute margin and add to tempS
			//��һ��İ�Χ��
			ComputeBoundingRectangle(splitNode->childSet[m-2+k]->range,firstGroupBoundingRange,firstGroupBoundingRange);
			//�ڶ���İ�Χ��
			ComputePartialBoundingRange(splitNode->childSet,m-1+k,M,secondGroupBoundingRange);
			//����Margin
			tempS +=(ComputeMargin(firstGroupBoundingRange)+ComputeMargin(secondGroupBoundingRange));
		}


		//����������ȵ�ǰ�Ľ��С������µ�ǰ���
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
	//��ʼ����һ��İ�Χ��
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


	//�԰�max�����������в���
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
