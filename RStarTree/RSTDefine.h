//////////////////////////////////////////////////////////////////////////
// �����ṹ����
//////////////////////////////////////////////////////////////////////////
#include <vector>
#include<limits>
using std::vector;
#ifndef DEF_BASIC_STRUCTURE
#define DEF_BASIC_STRUCTURE 1

///////////////////////////////����ṹ����///////////////////////////////////////////

// ����ṹ����ʾĳһά�ϵ�����
struct RSTInter 
{
	double min;
	double max;
};

// ��ά���伯��
typedef std::vector<RSTInter> RSTRange;

///////////////////////////////�������ݶ���///////////////////////////////////////////
#define  Point			100
#define  Rectangle		101
#define  NonLeafNode	201
#define  Leaf			202

// ��ṹ
typedef std::vector<double> RSTPoint;

// ��������ṹ
typedef RSTRange RSTRectangle;

class RSTNode;

class AbstractNode
{
public:
	int type;
	AbstractNode* parent;
	RSTRange range;
	virtual ~AbstractNode(){}
};

// ������
class RSTData : public AbstractNode
{
public:
	RSTPoint* point;
	RSTRectangle* rectangle;
public:
	RSTData();

	virtual ~RSTData();
public:
};

typedef std::vector<RSTData*> RSTDataSet;

///////////////////////////////R���ڵ㶨��///////////////////////////////////////////

#define DefaultMValue 10
#define DefaultmValue 5

// �ڵ㶨��
class RSTNode : public AbstractNode
{
public:
	int childNum;// �ӽڵ����	

	AbstractNode** childSet;// �ӽڵ�ָ�룬Ϊָ�붯̬����
public:
	RSTNode(int M = DefaultMValue);// �Զ������ýڵ�typeΪ��Ҷ�ӽڵ�

	RSTNode(int dim, int M);

	RSTNode(int type_, int dim, int M);
	
	~RSTNode();

	// ����ӽڵ㣬(��������)������ӽڵ�󲻸��𸸽ڵ㣨��ǰ�ڵ㣩range�ĸ���
	void AddNode(AbstractNode* pChild);
	//����ӽڵ㣬�������Ӻ�Ը��ڵ㣨��ǰ�ڵ㣩��range������Ӧ�ĸ���
	void AddNodeAndUpdateRange(AbstractNode* pChild);

	// ���½ڵ�����
	void UpdateRange(RSTRange& range);// rangeΪ�¼�������

	// �жϸ��ӽڵ��ڸ��ڵ����ӽڵ������λ�ã��ɸ��ڵ����
	int GetIndexOfNode(AbstractNode* pChild);

	// �Ӹ��ڵ���ɾ���ӽڵ㣬�ɸ��ڵ����
	void deleteNode(AbstractNode* pChild);
	void deleteNode(int& indexToDelete);

	void deleteNodeWithoutReleaseMem(AbstractNode* pChild);
	void deleteNodeWithoutReleaseMem(int& indexToDelete);
};

////////////////////////////////��ά�����������//////////////////////////////////////////

// �ж����������Ƿ��ཻ
bool IsJoin(RSTRange& range1, RSTRange& range2);

// �ж�����2�Ƿ�������1��
bool IsContain(RSTRange& range1, RSTRange& range2);

//Range��غ���
//��������Range�İ�Χ��
void ComputeBoundingRectangle(RSTRange& range1,RSTRange& range2,RSTRange& boundingRange);
//����Range�Ĵ�С
double ComputeVolume(RSTRange& range);
//���㽫range2���뵽range1������Ҫ����С�ռ�
double ComputeMinAdditionVolume(RSTRange& range1,RSTRange& range2);

#endif