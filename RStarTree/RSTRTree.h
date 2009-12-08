//////////////////////////////////////////////////////////////////////////
// R树和R*树算法实现
//////////////////////////////////////////////////////////////////////////

#include "RSTDefine.h"

//////////////////////////////R树算法实现////////////////////////////////////////////
class RSTRTree
{
public:
	int height;// 树的高度
	int dim;// 树的维度
	RSTNode* Root;// 树的根节点

	int m;// 子节点的最小数目
	int M;// 子节点的最大数目
public:
	RSTRTree() : dim(0), m(0), M(0), height(0), Root(NULL) {}

	RSTRTree(int dim_, int m_, int M_) : dim(dim_), m(m_), M(M_), height(1) {Root = new RSTNode(Leaf, M);}

	~RSTRTree();

	// 区域查询,若树结构不正确时进行查找返回false
	bool Search(RSTRange& range, RSTDataSet& result, bool isContain);
	void SearchByInter(RSTRange& range, RSTDataSet& result, RSTNode* node);// 查找与区域相交的元素
	void SearchByContain(RSTRange& range, RSTDataSet& result, RSTNode* node);// 查找区域内的元素

	// 插入数据
	void InsertData(RSTData* data);

	// 插入节点，h表示node应该插入的父节点所在层数
	void InsertNode(RSTNode* insertNode, int h);

	// 根据数据选择应插入的叶子节点
	RSTNode* ChooseLeaf(RSTData* data);

	// 根据层数选择应插入的父节点
	RSTNode* ChooseNode(RSTNode* insertNode, int h);

	// 插入数据后，调整树，自底向上
	void AdjustTree(RSTNode* leafNode);

	// 删除数据
	bool Delete(RSTData* data);

	// 查找数据所在叶子节点
	bool FindLeaf(RSTData* data);

	// 删除后，调整树，自底向上
	void CondenseTree(RSTNode* leafNode);

	// 节点分裂算法
	// 节点被分裂成两个新节点，原来的节点在函数结束后
	// 成为无效节点
	void Split(RSTNode* splitNode,RSTNode*& newSplitNode1,RSTNode*& newSplitNode2);
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
{

};