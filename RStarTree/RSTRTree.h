//////////////////////////////////////////////////////////////////////////
// R����R*���㷨ʵ��
//////////////////////////////////////////////////////////////////////////
#pragma once
#include "RSTDefine.h"

//////////////////////////////R���㷨ʵ��////////////////////////////////////////////
class RSTRTree
{
public:
	int height;// ���ĸ߶ȣ��Ӹ���ʼ��Ҷ�ӽڵ�ĸ߶ȣ�ֻ��һ����ʱ�߶�Ϊ1
	int dim;// ����ά��
	RSTNode* Root;// ���ĸ��ڵ�

	int m;// �ӽڵ����С��Ŀ
	int M;// �ӽڵ�������Ŀ
public:
	RSTRTree() : dim(0), m(0), M(0), height(0), Root(NULL) {}

	RSTRTree(int dim_, int m_, int M_) : dim(dim_), m(m_), M(M_), height(1) {Root = new RSTNode(Leaf, dim, M);}

	~RSTRTree();
	void ReleaseRec(RSTNode* pNode);

	// �����ѯ,�����ṹ����ȷʱ���в��ҷ���false
	bool Search(RSTRange& range, RSTNodeSet& result, bool isContain);
	void SearchByInter(RSTRange& range, RSTNodeSet& result, RSTNode* node);// �����������ཻ��Ԫ��
	void SearchByContain(RSTRange& range, RSTNodeSet& result, RSTNode* node);// ���������ڵ�Ԫ��

	// ��������
	void InsertData(RSTNode* data);

	// ����ڵ㣬h��ʾnodeӦ�ò���ĸ��ڵ����ڲ���
	void InsertNode(RSTNode* insertNode, int h);

	// ��������ѡ��Ӧ�����Ҷ�ӽڵ�
	virtual RSTNode* ChooseLeaf(RSTNode* data);

	// ���ݲ���ѡ��Ӧ����ĸ��ڵ�
	RSTNode* ChooseNode(RSTNode* insertNode, int h);

	// �������ݺ󣬵��������Ե�����
	void AdjustTree(RSTNode* leafNode);

	// ɾ������
	bool Delete(RSTNode* data);

	// ������������Ҷ�ӽڵ�
	bool FindLeaf(RSTNode* data);

	// ɾ���󣬵��������Ե�����
	void CondenseTree(RSTNode* leafNode);

	// �ڵ�����㷨
	// �ڵ㱻���ѳ������½ڵ㣬ԭ���Ľڵ��ں���������
	// ��Ϊ��Ч�ڵ�
	virtual void Split(RSTNode* splitNode,RSTNode*& newSplitNode1,RSTNode*& newSplitNode2);
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
{	public:
	
	RSTRStarTree(int dim_, int m_, int M_):RSTRTree(dim_,m_,M_){}
public:
	// ��������ѡ��Ӧ�����Ҷ�ӽڵ�
	RSTNode* ChooseLeaf(RSTNode* data);
	// ���ݲ���ѡ��Ӧ����ĸ��ڵ�
	//RSTNode* ChooseNode(RSTNode* insertNode, int h);

	void Split(RSTNode* splitNode,RSTNode*& newSplitNode1,RSTNode*& newSplitNode2);
	int ChooseSplitAxis(RSTNode*& splitNode);
	//ѡ����з��ѵ�λ��
	//����ֱ�Ϊ��min����õ�����Ͱ�max����õ�����
	//minOrMax�ں����������ָʾsplitIndexλ��min�������黹��max��������
	//splitIndexָʾ������һ�����ݵ����һ��Ԫ��
	void ChooseSplitIndex(RSTNode**& nodes1,RSTNode**& nodes2,bool& minOrMax,int& splitIndex);

	//�ɰ汾��split���������Բ��ã��Ƽ���Split
	void Split2(RSTNode* splitNode,RSTNode*& newSplitNode1,RSTNode*& newSplitNode2);
	void ChooseSplitIndex(RSTNode**& nodes1,RSTNode**& node2,bool*minOrMax,int& splitIndex);
};