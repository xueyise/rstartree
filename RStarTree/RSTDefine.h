//////////////////////////////////////////////////////////////////////////
// 基本结构定义
//////////////////////////////////////////////////////////////////////////
#include <vector>
#include <deque>
#include <math.h>
using std::vector;
#ifndef DEF_BASIC_STRUCTURE
#define DEF_BASIC_STRUCTURE 1

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
//#define  Point			100
//#define  Rectangle		101
#define  NonLeafNode	201
#define  Leaf			202
#define  Data           203

// 点结构
//typedef vector<double> RSTPoint;

// 区域面积结构
//typedef RSTRange RSTRectangle;

///////////////////////////////R树节点定义///////////////////////////////////////////

#define DefaultMValue 10
#define DefaultmValue 5

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
	
	~RSTNode();

	// 添加子节点，(内联函数)，添加子节点后不负责父节点（当前节点）range的更新
	void AddNode(RSTNode* pChild);
	// 添加子节点，并在增加后对父节点（当前节点）的range进行相应的更新
	void AddNodeAndUpdateRange(RSTNode* pChild);

	// 更新节点区域
	void UpdateRange(RSTRange& range);// range为新加入区域

	// 判断该子节点在父节点中子节点数组的位置，由父节点调用
	int GetIndexOfNode(RSTNode* pChild);

	// 从父节点中删除子节点，由父节点调用
	void deleteNode(RSTNode* pChild);
	void deleteNode(int& indexToDelete);

	void deleteNodeWithoutReleaseMem(RSTNode* pChild);
	void deleteNodeWithoutReleaseMem(int& indexToDelete);
};

typedef vector<RSTNode*> RSTNodeSet;

////////////////////////////////多维区间操作定义//////////////////////////////////////////

// 判断两个区间是否相交
bool IsJoin(RSTRange& range1, RSTRange& range2);

// 判断区间2是否在区间1中
bool IsContain(RSTRange& range1, RSTRange& range2);

//Range相关函数
//计算两个Range的包围盒
void ComputeBoundingRectangle(RSTRange& range1,RSTRange& range2,RSTRange& boundingRange);
//计算Range的大小
double ComputeVolume(RSTRange& range);
//计算将range2加入到range1后所需要的最小空间
double ComputeMinAdditionVolume(RSTRange& range1,RSTRange& range2);

#endif