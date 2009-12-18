#pragma once


// DisplayOptionDialog 对话框

class DisplayOptionDialog : public CDialog
{
	DECLARE_DYNAMIC(DisplayOptionDialog)

public:
	DisplayOptionDialog(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~DisplayOptionDialog();

// 对话框数据
	enum { IDD = IDD_DLG_DISPLAY_OPTIONS };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	BOOL displayNodeFrame;
	BOOL displayNodeMask;
	BOOL displayTreeBranch;
	BOOL displayDataLayer;
	BOOL isPerspectiveProjection;
	BOOL isRStarTree;
	int m;
	int M;
	afx_msg void OnBnClickedOk();
};
