//////////////////////////////////////////////////////////////////////////
// �����ṹ����
//////////////////////////////////////////////////////////////////////////
#include <vector>

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
#define  Point 1
#define  Rectangle 2

// ��ṹ
typedef std::vector<double> RSTPoint;

// ��������ṹ
typedef RSTRange RSTRectangle;

// ������
class RSTData
{
public:
	int dataType;
	RSTRange range;
	RSTPoint* point;
	RSTRectangle* rectangle;
public:
	RSTData();

	~RSTData();
public:
};

typedef std::vector<RSTData> RSTDataSet;

///////////////////////////////R���ڵ㶨��///////////////////////////////////////////

// R���ڵ�����
enum RSTNodeType{
	NonLeafNode,
	Leaf,
};

// �ڵ㶨��
struct RSTNode 
{
	int childNum;// �ӽڵ����	
	RSTNodeType rstNodeType;// �ڵ�����
	RSTRange range;// �ڵ�����Χ
	RSTNode* parent;// ���ڵ�ָ��
	RSTNode** childPointSet;// �ӽڵ�ָ�룬Ϊָ�붯̬���飬������ΪҶ�ӽڵ���ΪNULL
	RSTData** rstData;// ָ������Ԫ�飬������Ϊ��Ҷ�ӽڵ�ʱΪNULL
};

////////////////////////////////��ά�����������//////////////////////////////////////////

// �ж����������Ƿ��ཻ
bool IsJoin(RSTRange& range1, RSTRange& range2);

// �ж�����2�Ƿ�������1��
bool IsContain(RSTRange& range1, RSTRange& range2);

// ����������1��������2�������ӵ����