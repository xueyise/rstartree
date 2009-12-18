// DisplayOptionDialog.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "RStarTree.h"
#include "DisplayOptionDialog.h"


// DisplayOptionDialog �Ի���

IMPLEMENT_DYNAMIC(DisplayOptionDialog, CDialog)

DisplayOptionDialog::DisplayOptionDialog(CWnd* pParent /*=NULL*/)
	: CDialog(DisplayOptionDialog::IDD, pParent)
	, displayNodeFrame(FALSE)
	, displayNodeMask(FALSE)
	, displayTreeBranch(FALSE)
	, displayDataLayer(FALSE)
	, isPerspectiveProjection(FALSE)
	, isRStarTree(FALSE)
	, m(0)
	, M(0)
{

}

DisplayOptionDialog::~DisplayOptionDialog()
{
}

void DisplayOptionDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Check(pDX, IDC_CHECK1, displayNodeFrame);
	DDX_Check(pDX, IDC_CHECK2, displayNodeMask);
	DDX_Check(pDX, IDC_CHECK3, displayTreeBranch);
	DDX_Check(pDX, IDC_CHECK4, displayDataLayer);
	DDX_Radio(pDX, IDC_LEAF_OBSELETE3, isPerspectiveProjection);
	DDX_Radio(pDX, IDC_DISPLAY_LEFF_EDGE3, isRStarTree);
	DDX_Text(pDX, IDC_EDIT1, m);
	DDV_MinMaxInt(pDX, m, 2, 25);
	DDX_Text(pDX, IDC_EDIT2, M);
	DDV_MinMaxInt(pDX, M, 4, 50);
}


BEGIN_MESSAGE_MAP(DisplayOptionDialog, CDialog)
	ON_BN_CLICKED(IDOK, &DisplayOptionDialog::OnBnClickedOk)
END_MESSAGE_MAP()


// DisplayOptionDialog ��Ϣ�������

void DisplayOptionDialog::OnBnClickedOk()
{
	this->UpdateData(TRUE);
	int halfM = M/2;
	if(m>halfM){
		::AfxMessageBox(_T("m��������С�ڵ���M/2"));
		return ;
	}
	OnOK();
}
