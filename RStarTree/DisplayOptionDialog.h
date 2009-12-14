#pragma once


// DisplayOptionDialog �Ի���

class DisplayOptionDialog : public CDialog
{
	DECLARE_DYNAMIC(DisplayOptionDialog)

public:
	DisplayOptionDialog(CWnd* pParent = NULL);   // ��׼���캯��
	DisplayOptionDialog(BOOL displayDataNode,BOOL displayRTreeEdge,
		BOOL displayLeafNodeEdge,BOOL leafNodeObsolete,CWnd* pParent = NULL);
	virtual ~DisplayOptionDialog();

// �Ի�������
	enum { IDD = IDD_DLG_DISPLAY_OPTIONS };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	BOOL notDisplayDataNode;
	BOOL notDisplayRTreeEdge;
	BOOL notDisplayLeafNodeEdge;
	BOOL leafNodeNotObsolete;
};
