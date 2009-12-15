//////////////////////////////////////////////////////////////////////////
// R树和R*树算法实现
//////////////////////////////////////////////////////////////////////////
#pragma once
#include "RSTDefine.h"

//////////////////////////////R树算法实现////////////////////////////////////////////
class RSTRTree
{
public:
	int height;// 树的高度，从跟开始到叶子节点的高度，只有一个根时高度为1
	int dim;// 树的维度
	RSTNode* Root;// 树的根节点

	int m;// 子节点的最小数目
	int M;// 子节点的最大数目
public:
	RSTRTree() : dim(0), m(0), M(0), height(0), Root(NULL) {}

	RSTRTree(int dim_, int m_, int M_) : dim(dim_), m(m_), M(M_), height(1) {Root = new RSTNode(Leaf, dim, M);}

	~RSTRTree();
	void ReleaseRec(RSTNode* pNode);

	// 区域查询,若树结构不正确时进行查找返回false
	bool Search(RSTRange& range, RSTNodeSet& result, bool isContain);
	void SearchByInter(RSTRange& range, RSTNodeSet& result, RSTNode* node);// 查找与区域相交的元素
	void SearchByContain(RSTRange& range, RSTNodeSet& result, RSTNode* node);// 查找区域内的元素

	// 插入数据
	void InsertData(RSTNode* data);

	// 插入节点，h表示node应该插入的父节点所在层数
	void InsertNode(RSTNode* insertNode, int h);

	// 根据数据选择应插入的叶子节点
	virtual RSTNode* ChooseLeaf(RSTNode* data);

	// 根据层数选择应插入的父节点
	RSTNode* ChooseNode(RSTNode* insertNode, int h);

	// 插入数据后，调整树，自底向上
	void AdjustTree(RSTNode* leafNode);

	// 删除数据
	bool Delete(RSTNode* data);

	// 查找数据所在叶子节点
	bool FindLeaf(RSTNode* data);

	// 删除后，调整树，自底向上
	void CondenseTree(RSTNode* leafNode);

	// 节点分裂算法
	// 节点被分裂成两个新节点，原来的节点在函数结束后
	// 成为无效节点
	virtual void Split(RSTNode* splitNode,RSTNode*& newSplitNode1,RSTNode*& newSplitNode2);
	void BruteForceSplit(RSTNode* splitNode,RSTNode*& newSplitNode1,RSTNode*& newSplitNode2);	
	void QuadraticSplit(RSTNode* splitNode,RSTNode*& newSplitNode1,RSTNode*& newSplitNode2);
	void LinearSplit(RSTNode* splitNode,RSTNode*& newSplitNode1,RSTNode*& newSplitNode2);

	// 为Split操作选取种子，采用复杂度为n^2的近似算法
	void PickSeedsQudratic(RSTNode* splitNode,int& firstSeedIndex,int& secondSeedIndex);
	// 为Split操作选取种子，采用线性复杂度的近似算法
	void PickSeedsLinear(RSTNode* splitNode);


	// Split算法中选择下个成员，采用平方复杂度算法
	void PickNextQudratic(RSTNode*& splitNode,RSTNode*& newSplitNode1,
								RSTNode*& newSplitNode2,RSTRange& tempBoundingRange,int& index,
								double& d1,double& d2);

	// Split算法中选择下个成员，采用线性复杂度算法
	void PickNextLinear();

	// 清除R树
	void DeconstructTree();
};

/////////////////////////////R*树算法实现/////////////////////////////////////////////

class RSTRStarTree : public RSTRTree
{	public:
	
	RSTRStarTree(int dim_, int m_, int M_):RSTRTree(dim_,m_,M_){}
public:
	// 根据数据选择应插入的叶子节点
	RSTNode* ChooseLeaf(RSTNode* data);
	// 根据层数选择应插入的父节点
	//RSTNode* ChooseNode(RSTNode* insertNode, int h);

	void Split(RSTNode* splitNode,RSTNode*& newSplitNode1,RSTNode*& newSplitNode2);
	int ChooseSplitAxis(RSTNode*& splitNode);
	//选择进行分裂的位置
	//输入分别为按min排序好的数组和按max排序好的数组
	//minOrMax在函数结束后会指示splitIndex位于min排序数组还是max排序数组
	//splitIndex指示分组后第一组数据的最后一个元素
	void ChooseSplitIndex(RSTNode**& nodes1,RSTNode**& nodes2,bool& minOrMax,int& splitIndex);

	//旧版本的split函数，可以不用，推荐用Split
	void Split2(RSTNode* splitNode,RSTNode*& newSplitNode1,RSTNode*& newSplitNode2);
	void ChooseSplitIndex(RSTNode**& nodes1,RSTNode**& node2,bool*minOrMax,int& splitIndex);
};