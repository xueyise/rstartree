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
	virtual void InsertData(RSTNode* data);

	// ����ڵ㣬h��ʾnodeӦ�ò���ĸ��ڵ����ڲ���
	void InsertNode(RSTNode* insertNode, int h);

	// ��������ѡ��Ӧ�����Ҷ�ӽڵ�
	virtual RSTNode* ChooseLeaf(RSTNode* data);

	// ���ݲ���ѡ��Ӧ����ĸ��ڵ�
	RSTNode* ChooseNode(RSTNode* insertNode, int h);

	// �������ݺ󣬵��������Ե�����
	virtual void AdjustTree(RSTNode* leafNode);

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
	void QuadraticSplit2(RSTNode* splitNode,RSTNode*& newSplitNode1,RSTNode*& newSplitNode2);
	void LinearSplit(RSTNode* splitNode,RSTNode*& newSplitNode1,RSTNode*& newSplitNode2);

	// ΪSplit����ѡȡ���ӣ����ø��Ӷ�Ϊn^2�Ľ����㷨
	void PickSeedsQudratic(RSTNode* splitNode,int& firstSeedIndex,int& secondSeedIndex);
	void PickSeedsQudratic2(RSTNode* splitNode,int& firstSeedIndex,int& secondSeedIndex);
	// ΪSplit����ѡȡ���ӣ��������Ը��ӶȵĽ����㷨
	void PickSeedsLinear(RSTNode* splitNode);


	// Split�㷨��ѡ���¸���Ա������ƽ�����Ӷ��㷨
	void PickNextQudratic(RSTNode*& splitNode,RSTNode*& newSplitNode1,
								RSTNode*& newSplitNode2,RSTRange& tempBoundingRange,int& index,
								double& d1,double& d2);
	void PickNextQudratic2(RSTNode* splitNode,int startIndex,int endIndex,
								 RSTNode* newSplitNode2,RSTRange& tempBoundingRange,int& index,
								 double& d1,double& d2);

	// Split�㷨��ѡ���¸���Ա���������Ը��Ӷ��㷨
	void PickNextLinear();

	// ���R��
	void DeconstructTree();
};

/////////////////////////////R*���㷨ʵ��/////////////////////////////////////////////

class RSTRStarTree : public RSTRTree
{	
public:
	bool reInsertFlag;// �Ƿ���Ҫ���²���ı�־ֵ

	double* distance;// ��¼�����ӽڵ�������ĵ����ڵ�������ľ�������

	double* minAddVolume;// ��С�������

	RSTCPoint center;// ��¼���ڵ����ĵ�

	RSTCPoint tempPoint;// ��¼ÿ���ӽڵ����Ľڵ�

	RSTRange* boundingRect;// ��Χ������

	RSTNode** tempNodeSet;// ��ʱ�ڵ�����
	RSTNode** tempLeaveNode;

	RSTNodeValue* rstNodeValueSet;// ��������ĵ��ֵ�������

public:
	RSTRStarTree() : RSTRTree(), reInsertFlag(true), distance(NULL), minAddVolume(NULL), 
		rstNodeValueSet(NULL), tempNodeSet(NULL), tempLeaveNode(NULL) {}
	
	RSTRStarTree(int dim_, int m_, int M_) : RSTRTree(dim_,m_,M_), reInsertFlag(true) 
	{
		distance = new double[M + 1];
		minAddVolume = new double[M];
		boundingRect = new RSTRange[M];
		rstNodeValueSet = new RSTNodeValue[M + 1];
		tempNodeSet = new RSTNode*[min(P, M + 1)];
		tempLeaveNode = new RSTNode*[M + 1 - min(P, M + 1)];
		center.resize(dim);
		tempPoint.resize(dim);
	}

	~RSTRStarTree()
	{
		if (distance) delete[] distance;
		if (minAddVolume) delete[] minAddVolume;
		if (boundingRect) delete[] boundingRect;
		if (rstNodeValueSet) delete[] rstNodeValueSet;
		if (tempNodeSet) delete[] tempNodeSet;
		if(tempLeaveNode) delete[] tempLeaveNode;
	}
public:
	// ��������
	void InsertData(RSTNode* data);
	// ��������ѡ��Ӧ�����Ҷ�ӽڵ�
	RSTNode* ChooseLeaf(RSTNode* data);
	// �������ݺ󣬵��������Ե�����
	void AdjustTree(RSTNode* leafNode);
	// ǿ���ز������
	void ReInsert(RSTNode* reInsertNode);

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
