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
	bool Search(RSTRange range);
	
	// ��������
	bool InsertNode(RSTData* data);

	// ��������ѡ��Ӧ�����Ҷ�ӽڵ�
	bool ChooseLeaf(RSTData* data);

	// �������ݺ󣬵��������Ե�����
	void AdjustTree(RSTNode* leafNode);

	// ɾ������
	bool Delete(RSTData* data);

	// ������������Ҷ�ӽڵ�
	bool FindLeaf(RSTData* data);

	// ɾ���󣬵��������Ե�����
	void CondenseTree(RSTNode* leafNode);

	// �ڵ�����㷨
	void Split(RSTNode* splitNode);
	void BruteForceSplit(RSTNode* splitNode);
	void QuadraticSplit(RSTNode* splitNode);
	void LinearSplit(RSTNode* splitNode);

	// ѡ���ʼ��Ա
	void PickSeeds(RSTNode* splitNode);

	// ѡ���¸���Ա
	void PickNext();

	// ���R��
	void DeconstructTree();
};

/////////////////////////////R*���㷨ʵ��/////////////////////////////////////////////

class RSTRStarTree : public RSTRTree
{

};