//////////////////////////////////////////////////////////////////////////
// 基本结构定义
//////////////////////////////////////////////////////////////////////////
#include <vector>
#include <deque>
#include <math.h>
#include <algorithm>
#include <float.h>
using std::vector;

#ifndef DEF_BASIC_STRUCTURE
#define DEF_BASIC_STRUCTURE 1

#define DEFAULT_DIMENTION 2
#define DEFAULT_LITTLE_M 2
#define DEFALUT_BIG_M 4


///////////////////////////////区间结构定义///////////////////////////////////////////

// 区间结构，表示某一维上的区间
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

// 多维区间集合
typedef std::vector<RSTInter> RSTRange;

///////////////////////////////索引数据定义///////////////////////////////////////////

#define  NonLeafNode	201
#define  Leaf			202
#define  Data           203

///////////////////////////////R树节点定义///////////////////////////////////////////

#define DefaultMValue 10
#define DefaultmValue 5

#define P 16 // 记录近似R*查找算法的判断节点个数

// 节点定义
class RSTNode
{
public:
	int type;

	RSTNode* parent;

	RSTRange range;

	int childNum;// 子节点个数	

	RSTNode** childSet;// 子节点指针，为指针动态数组
public:
	RSTNode(int M = DefaultMValue);// 自动声明该节点type为非叶子节点

	RSTNode(int dim, int M);

	RSTNode(int type_, int dim, int M);
	
	virtual ~RSTNode();

	virtual void GetDataPoints(vector<double> &vec);

	// 添加子节点，(内联函数)，添加子节点后不负责父节点（当前节点）range的更新
	void AddNode(RSTNode* pChild);
	// 添加子节点，并在增加后对父节点（当前节点）的range进行相应的更新
	void AddNodeAndUpdateRange(RSTNode* pChild);

	// 更新节点区域
	void UpdateRange(RSTRange& range);// range为新加入区域
	void UpdateRange();

	// 判断该子节点在父节点中子节点数组的位置，由父节点调用
	int GetIndexOfNode(RSTNode* pChild);

	// 从父节点中删除子节点，由父节点调用
	void deleteNode(RSTNode* pChild);
	void deleteNode(int& indexToDelete);

	void deleteNodeWithoutReleaseMem(RSTNode* pChild);
	void deleteNodeWithoutReleaseMem(int& indexToDelete);

	// 计算子节点重复度
	double ComputeNodeOverlap(int childInd);
	double ComputeNodeOverlap(int childInd, RSTRange& range);
};

// 自定义比较器，用于R*树split算法的排序，需要对不同维度的min或max进行比较
// d表示要比较的维度，从0开始
// min表示是否根据第d维区间的min值进行比较，如果为false，则根据max进行比较
class RSTNodeComparator{
private:
	int d;//用于比较的维度
	bool isMin;//是否用low值去比较
public:
	RSTNodeComparator(int dd,bool min):d(dd),isMin(min){}
	bool operator()(RSTNode* pLeft,RSTNode* pRight){
		if(isMin){
			return pLeft->range[d].min<pRight->range[d].min;
		}else{
			return pLeft->range[d].max<pRight->range[d].max;
		}
	}
};

// 记录点索引和对应值的结构，用于排序
struct RSTNodeValue
{
	int nodeInd;
	double m_value;
};

// 排序比较函数
bool CompareRSTNodeValueASC(RSTNodeValue& r1, RSTNodeValue& r2);
bool CompareRSTNodeValueDESC(RSTNodeValue& r1, RSTNodeValue& r2);

// 节点集合
typedef vector<RSTNode*> RSTNodeSet;

// 点定义，用于记录中心点
typedef vector<double> RSTCPoint;

////////////////////////////////多维区间操作定义//////////////////////////////////////////

// 判断两个区间是否相交
bool IsJoin(RSTRange& range1, RSTRange& range2);

// 判断区间2是否在区间1中
bool IsContain(RSTRange& range1, RSTRange& range2);

//计算两个Range的包围盒
void ComputeBoundingRectangle(RSTRange& range1,RSTRange& range2,RSTRange& boundingRange);

//计算Range的大小
double ComputeVolume(RSTRange& range);

//计算将range2加入到range1后所需要的最小空间
double ComputeMinAdditionVolume(RSTRange& range1,RSTRange& range2);

double ComputeMargin(RSTRange& range);
double ComputeOverlapValue(RSTRange& range1,RSTRange& range2);

//计算给定节点中部分孩子节点的包围盒
//firstIndex指示有效计算范围内的第一个孩子节点
//lastIndex指示有效计算范围内的最后一个孩子节点
void ComputePartialBoundingRange(RSTNode** pNode,int firstIndex,int lastIndex,RSTRange& resultRange);

// 得到矩形区域的中心点
void GetCenter(RSTRange& range, RSTCPoint& cPoint);

// 计算两点间距离
double GetDistance(RSTCPoint& p1, RSTCPoint& p2);

#endif