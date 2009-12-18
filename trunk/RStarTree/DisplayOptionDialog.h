#pragma once


// DisplayOptionDialog �Ի���

class DisplayOptionDialog : public CDialog
{
	DECLARE_DYNAMIC(DisplayOptionDialog)

public:
	DisplayOptionDialog(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~DisplayOptionDialog();

// �Ի�������
	enum { IDD = IDD_DLG_DISPLAY_OPTIONS };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

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
