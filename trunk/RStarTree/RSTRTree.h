//////////////////////////////////////////////////////////////////////////
// R����R*���㷨ʵ��
//////////////////////////////////////////////////////////////////////////

#include "RSTDefine.h"

//////////////////////////////R���㷨ʵ��////////////////////////////////////////////
class RSTRTree
{
public:
	int height;// ���ĸ߶�
	int dim;// ����ά��
	RSTNode* Root;// ���ĸ��ڵ�

	int m;// �ӽڵ����С��Ŀ
	int M;// �ӽڵ�������Ŀ
public:
	RSTRTree() : dim(0), m(0), M(0), height(0), Root(NULL) {}

	RSTRTree(int dim_, int m_, int M_) : dim(dim_), m(m_), M(M_), height(1) {Root = new RSTNode(Leaf, M);}

	~RSTRTree();

	// �����ѯ,�����ṹ����ȷʱ���в��ҷ���false
	bool Search(RSTRange& range, RSTDataSet& result, bool isContain);
	void SearchByInter(RSTRange& range, RSTDataSet& result, RSTNode* node);// �����������ཻ��Ԫ��
	void SearchByContain(RSTRange& range, RSTDataSet& result, RSTNode* node);// ���������ڵ�Ԫ��

	// ��������
	void InsertData(RSTData* data);

	// ����ڵ㣬h��ʾnodeӦ�ò���ĸ��ڵ����ڲ���
	void InsertNode(RSTNode* insertNode, int h);

	// ��������ѡ��Ӧ�����Ҷ�ӽڵ�
	RSTNode* ChooseLeaf(RSTData* data);

	// ���ݲ���ѡ��Ӧ����ĸ��ڵ�
	RSTNode* ChooseNode(RSTNode* insertNode, int h);

	// �������ݺ󣬵��������Ե�����
	void AdjustTree(RSTNode* leafNode);

	// ɾ������
	bool Delete(RSTData* data);

	// ������������Ҷ�ӽڵ�
	bool FindLeaf(RSTData* data);

	// ɾ���󣬵��������Ե�����
	void CondenseTree(RSTNode* leafNode);

	// �ڵ�����㷨
	// �ڵ㱻���ѳ������½ڵ㣬ԭ���Ľڵ��ں���������
	// ��Ϊ��Ч�ڵ�
	void Split(RSTNode* splitNode,RSTNode*& newSplitNode1,RSTNode*& newSplitNode2);
	void BruteForceSplit(RSTNode* splitNode,RSTNode*& newSplitNode1,RSTNode*& newSplitNode2);	
	void QuadraticSplit(RSTNode* splitNode,RSTNode*& newSplitNode1,RSTNode*& newSplitNode2);
	void LinearSplit(RSTNode* splitNode,RSTNode*& newSplitNode1,RSTNode*& newSplitNode2);

	// ΪSplit����ѡȡ���ӣ����ø��Ӷ�Ϊn^2�Ľ����㷨
	void PickSeedsQudratic(RSTNode* splitNode,int& firstSeedIndex,int& secondSeedIndex);
	// ΪSplit����ѡȡ���ӣ��������Ը��ӶȵĽ����㷨
	void PickSeedsLinear(RSTNode* splitNode);


	// Split�㷨��ѡ���¸���Ա������ƽ�����Ӷ��㷨
	void PickNextQudratic(RSTNode*& splitNode,RSTNode*& newSplitNode1,
								RSTNode*& newSplitNode2,RSTRange& tempBoundingRange,int& index,
								double& d1,double& d2);

	// Split�㷨��ѡ���¸���Ա���������Ը��Ӷ��㷨
	void PickNextLinear();

	// ���R��
	void DeconstructTree();
};

/////////////////////////////R*���㷨ʵ��/////////////////////////////////////////////

class RSTRStarTree : public RSTRTree
{

};