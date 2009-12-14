#pragma once


// DisplayOptionDialog 对话框

class DisplayOptionDialog : public CDialog
{
	DECLARE_DYNAMIC(DisplayOptionDialog)

public:
	DisplayOptionDialog(CWnd* pParent = NULL);   // 标准构造函数
	DisplayOptionDialog(BOOL displayDataNode,BOOL displayRTreeEdge,
		BOOL displayLeafNodeEdge,BOOL leafNodeObsolete,CWnd* pParent = NULL);
	virtual ~DisplayOptionDialog();

// 对话框数据
	enum { IDD = IDD_DLG_DISPLAY_OPTIONS };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	BOOL notDisplayDataNode;
	BOOL notDisplayRTreeEdge;
	BOOL notDisplayLeafNodeEdge;
	BOOL leafNodeNotObsolete;
};
