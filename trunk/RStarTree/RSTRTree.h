//////////////////////////////////////////////////////////////////////////
// R树和R*树算法实现
//////////////////////////////////////////////////////////////////////////

#include "RSTDefine.h"

//////////////////////////////R树算法实现////////////////////////////////////////////
class RSTRTree
{
public:
	int dim;// 树的维度
	RSTNode* Root;// 树的根节点

	int m;// 子节点的最小数目
	int M;// 子节点的最大数目
public:
	RSTRTree() {}

	RSTRTree(int dim_, int m_, int M_) : dim(dim_), m(m_), M(M_) {}

	~RSTRTree();

	// 区域查询
	void Search(RSTRange& range, RSTDataSet& result, bool isContain);
	void SearchByInter(RSTRange& range, RSTDataSet& result, RSTNode* node);// 查找与区域相交的元素
	void SearchByContain(RSTRange& range, RSTDataSet& result, RSTNode* node);// 查找区域内的元素
	
	
	// 插入数据
	void InsertNode(RSTData* data);

	// 根据数据选择应插入的叶子节点
	RSTNode* ChooseLeaf(RSTData* data);

	// 插入数据后，调整树，自底向上
	void AdjustTree(RSTNode* leafNode);

	// 删除数据
	bool Delete(RSTData* data);

	// 查找数据所在叶子节点
	bool FindLeaf(RSTData* data);

	// 删除后，调整树，自底向上
	void CondenseTree(RSTNode* leafNode);

	// 构建一个空节点
	RSTNode* ConstructNode(RSTNodeType nodeType);

	// 节点分裂算法
	void Split(RSTNode* splitNode);
	void BruteForceSplit(RSTNode* splitNode);
	void QuadraticSplit(RSTNode* splitNode);
	void LinearSplit(RSTNode* splitNode);

	
	
	// 为split操作选取种子，采用复杂度为n^2的近似算法
	void PickSeedsQudratic(RSTNode* splitNode,int& firstSeedIndex,int& secondSeedIndex);
	//为split操作选取种子，采用线性复杂度的近似算法
	void PickSeedsLinear(RSTNode* splitNode);


	// Split算法中选择下个成员，采用平方复杂度算法
	void PickNextQudratic();
	// Split算法中选择下个成员，采用线性复杂度算法
	void PickNextLinear();

	// 清除R树
	void DeconstructTree();
};

/////////////////////////////R*树算法实现/////////////////////////////////////////////

class RSTRStarTree : public RSTRTree
{

};