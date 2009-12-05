//////////////////////////////////////////////////////////////////////////
// R����R*���㷨ʵ��
//////////////////////////////////////////////////////////////////////////

#include "RSTDefine.h"

//////////////////////////////R���㷨ʵ��////////////////////////////////////////////
class RSTRTree
{
public:
	int dim;// ����ά��
	RSTNode* Root;// ���ĸ��ڵ�

	int m;// �ӽڵ����С��Ŀ
	int M;// �ӽڵ�������Ŀ
public:
	RSTRTree() {}

	RSTRTree(int dim_, int m_, int M_) : dim(dim_), m(m_), M(M_) {}

	~RSTRTree();

	// �����ѯ
	void Search(RSTRange& range, RSTDataSet& result, bool isContain);
	void SearchByInter(RSTRange& range, RSTDataSet& result, RSTNode* node);// �����������ཻ��Ԫ��
	void SearchByContain(RSTRange& range, RSTDataSet& result, RSTNode* node);// ���������ڵ�Ԫ��
	
	
	// ��������
	void InsertNode(RSTData* data);

	// ��������ѡ��Ӧ�����Ҷ�ӽڵ�
	RSTNode* ChooseLeaf(RSTData* data);

	// �������ݺ󣬵��������Ե�����
	void AdjustTree(RSTNode* leafNode);

	// ɾ������
	bool Delete(RSTData* data);

	// ������������Ҷ�ӽڵ�
	bool FindLeaf(RSTData* data);

	// ɾ���󣬵��������Ե�����
	void CondenseTree(RSTNode* leafNode);

	// ����һ���սڵ�
	RSTNode* ConstructNode(RSTNodeType nodeType);

	// �ڵ�����㷨
	void Split(RSTNode* splitNode);
	void BruteForceSplit(RSTNode* splitNode);
	void QuadraticSplit(RSTNode* splitNode);
	void LinearSplit(RSTNode* splitNode);

	
	
	// Ϊsplit����ѡȡ���ӣ����ø��Ӷ�Ϊn^2�Ľ����㷨
	void PickSeedsQudratic(RSTNode* splitNode,int& firstSeedIndex,int& secondSeedIndex);
	//Ϊsplit����ѡȡ���ӣ��������Ը��ӶȵĽ����㷨
	void PickSeedsLinear(RSTNode* splitNode);


	// Split�㷨��ѡ���¸���Ա������ƽ�����Ӷ��㷨
	void PickNextQudratic();
	// Split�㷨��ѡ���¸���Ա���������Ը��Ӷ��㷨
	void PickNextLinear();

	// ���R��
	void DeconstructTree();
};

/////////////////////////////R*���㷨ʵ��/////////////////////////////////////////////

class RSTRStarTree : public RSTRTree
{

};