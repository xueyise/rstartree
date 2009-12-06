//////////////////////////////////////////////////////////////////////////
// 基本结构定义
//////////////////////////////////////////////////////////////////////////
#include <vector>
#include<limits>
using std::vector;

///////////////////////////////区间结构定义///////////////////////////////////////////

// 区间结构，表示某一维上的区间
struct RSTInter 
{
	double min;
	double max;
};

// 多维区间集合
typedef std::vector<RSTInter> RSTRange;

///////////////////////////////索引数据定义///////////////////////////////////////////
#define  Point 1
#define  Rectangle 2

// 点结构
typedef std::vector<double> RSTPoint;

// 区域面积结构
typedef RSTRange RSTRectangle;

// 数据类
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

///////////////////////////////R树节点定义///////////////////////////////////////////

#define DefaultMValue 10
#define DefaultmValue 5

// R树节点类型
enum RSTNodeType{
	NonLeafNode,
	Leaf,
};

// 节点定义
class RSTNode 
{
public:
	int childNum;// 子节点个数	
	RSTNodeType rstNodeType;// 节点类型
	RSTRange range;// 节点区域范围
	RSTNode* parent;// 父节点指针
	RSTNode** childNodeSet;// 子节点指针，为指针动态数组，当类型为叶子节点是为NULL
	RSTData** rstData;// 指向数据元组，当类型为非叶子节点时为NULL
public:
	RSTNode(int M = DefaultMValue);
	
	~RSTNode();

	// 添加子节点，内联函数
	void AddChildNode(RSTNode* pChild);
	void AddData(RSTData* pData);

	// 更新节点区域
	void UpdateRange(RSTRange& range);// range为新加入区域

	
	void deleteNode(int& indexToDelete);
	void deleteNodeWithoutReleaseMem(int& indexToDelete);
};

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