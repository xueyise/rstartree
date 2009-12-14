// DisplayOptionDialog.cpp : 实现文件
//

#include "stdafx.h"
#include "RStarTree.h"
#include "DisplayOptionDialog.h"


// DisplayOptionDialog 对话框

IMPLEMENT_DYNAMIC(DisplayOptionDialog, CDialog)

DisplayOptionDialog::DisplayOptionDialog(CWnd* pParent /*=NULL*/)
	: CDialog(DisplayOptionDialog::IDD, pParent)
	, notDisplayDataNode(FALSE)
	, notDisplayRTreeEdge(FALSE)
	, notDisplayLeafNodeEdge(FALSE)
	, leafNodeNotObsolete(FALSE)
{

}
DisplayOptionDialog::DisplayOptionDialog(BOOL displayDataNode,BOOL displayRTreeEdge,
		BOOL displayLeafNodeEdge,BOOL leafNodeObsolete,CWnd* pParent)
		: CDialog(DisplayOptionDialog::IDD, pParent)
	, notDisplayDataNode(!displayDataNode)
	, notDisplayRTreeEdge(!displayRTreeEdge)
	, notDisplayLeafNodeEdge(!displayLeafNodeEdge)
	, leafNodeNotObsolete(!leafNodeObsolete)
{

}

DisplayOptionDialog::~DisplayOptionDialog()
{
}

void DisplayOptionDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Radio(pDX, IDC_DISPLAY_DATA_RADIO1, notDisplayDataNode);
	DDX_Radio(pDX, IDC_DISPLAY_TREE_EDGE1, notDisplayRTreeEdge);
	DDX_Radio(pDX, IDC_DISPLAY_LEFF_EDGE1, notDisplayLeafNodeEdge);
	DDX_Radio(pDX, IDC_LEAF_OBSELETE1, leafNodeNotObsolete);
}


BEGIN_MESSAGE_MAP(DisplayOptionDialog, CDialog)
END_MESSAGE_MAP()


// DisplayOptionDialog 消息处理程序
