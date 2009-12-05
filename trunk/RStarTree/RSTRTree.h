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
	bool Search(RSTRange range);
	
	// 插入数据
	bool InsertNode(RSTData* data);

	// 根据数据选择应插入的叶子节点
	bool ChooseLeaf(RSTData* data);

	// 插入数据后，调整树，自底向上
	void AdjustTree(RSTNode* leafNode);

	// 删除数据
	bool Delete(RSTData* data);

	// 查找数据所在叶子节点
	bool FindLeaf(RSTData* data);

	// 删除后，调整树，自底向上
	void CondenseTree(RSTNode* leafNode);

	// 节点分裂算法
	void Split(RSTNode* splitNode);
	void BruteForceSplit(RSTNode* splitNode);
	void QuadraticSplit(RSTNode* splitNode);
	void LinearSplit(RSTNode* splitNode);

	// 选择初始成员
	void PickSeeds(RSTNode* splitNode);

	// 选择下个成员
	void PickNext();

	// 清除R树
	void DeconstructTree();
};

/////////////////////////////R*树算法实现/////////////////////////////////////////////

class RSTRStarTree : public RSTRTree
{

};