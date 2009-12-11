//////////////////////////////////////////////////////////////////////////
// �����ṹ����
//////////////////////////////////////////////////////////////////////////
#include <vector>
#include <deque>
#include <math.h>
using std::vector;
#ifndef DEF_BASIC_STRUCTURE
#define DEF_BASIC_STRUCTURE 1

///////////////////////////////����ṹ����///////////////////////////////////////////

// ����ṹ����ʾĳһά�ϵ�����
struct RSTInter 
{
public:
	double min;
	double max;
	RSTInter(){}
	RSTInter(double min1,double max1){
		min = min1;
		max = max1;
	}
};

// ��ά���伯��
typedef std::vector<RSTInter> RSTRange;

///////////////////////////////�������ݶ���///////////////////////////////////////////
//#define  Point			100
//#define  Rectangle		101
#define  NonLeafNode	201
#define  Leaf			202
#define  Data           203

// ��ṹ
//typedef vector<double> RSTPoint;

// ��������ṹ
//typedef RSTRange RSTRectangle;

///////////////////////////////R���ڵ㶨��///////////////////////////////////////////

#define DefaultMValue 10
#define DefaultmValue 5

// �ڵ㶨��
class RSTNode
{
public:
	int type;

	RSTNode* parent;

	RSTRange range;

	int childNum;// �ӽڵ����	

	RSTNode** childSet;// �ӽڵ�ָ�룬Ϊָ�붯̬����
public:
	RSTNode(int M = DefaultMValue);// �Զ������ýڵ�typeΪ��Ҷ�ӽڵ�

	RSTNode(int dim, int M);

	RSTNode(int type_, int dim, int M);
	
	~RSTNode();

	// ����ӽڵ㣬(��������)������ӽڵ�󲻸��𸸽ڵ㣨��ǰ�ڵ㣩range�ĸ���
	void AddNode(RSTNode* pChild);
	// ����ӽڵ㣬�������Ӻ�Ը��ڵ㣨��ǰ�ڵ㣩��range������Ӧ�ĸ���
	void AddNodeAndUpdateRange(RSTNode* pChild);

	// ���½ڵ�����
	void UpdateRange(RSTRange& range);// rangeΪ�¼�������

	// �жϸ��ӽڵ��ڸ��ڵ����ӽڵ������λ�ã��ɸ��ڵ����
	int GetIndexOfNode(RSTNode* pChild);

	// �Ӹ��ڵ���ɾ���ӽڵ㣬�ɸ��ڵ����
	void deleteNode(RSTNode* pChild);
	void deleteNode(int& indexToDelete);

	void deleteNodeWithoutReleaseMem(RSTNode* pChild);
	void deleteNodeWithoutReleaseMem(int& indexToDelete);
};

typedef vector<RSTNode*> RSTNodeSet;

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