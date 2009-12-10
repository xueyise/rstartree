// RStarTreeView.cpp : implementation of the CRStarTreeView class
//

#include "stdafx.h"
#include "RStarTree.h"

#include "RStarTreeDoc.h"
#include "RStarTreeView.h"

#include "RSTDefine.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CRStarTreeView

IMPLEMENT_DYNCREATE(CRStarTreeView, CView)

BEGIN_MESSAGE_MAP(CRStarTreeView, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_COMMAND(ID_TEST_BUILD_TREE, &CRStarTreeView::OnTestBuildTree)
END_MESSAGE_MAP()

// CRStarTreeView construction/destruction

CRStarTreeView::CRStarTreeView()
{
	// TODO: add construction code here

}

CRStarTreeView::~CRStarTreeView()
{
}

BOOL CRStarTreeView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CRStarTreeView drawing

void CRStarTreeView::OnDraw(CDC* /*pDC*/)
{
	CRStarTreeDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: add draw code for native data here
}


// CRStarTreeView printing

BOOL CRStarTreeView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CRStarTreeView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CRStarTreeView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}


// CRStarTreeView diagnostics

#ifdef _DEBUG
void CRStarTreeView::AssertValid() const
{
	CView::AssertValid();
}

void CRStarTreeView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CRStarTreeDoc* CRStarTreeView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CRStarTreeDoc)));
	return (CRStarTreeDoc*)m_pDocument;
}
#endif //_DEBUG


// CRStarTreeView message handlers

void CRStarTreeView::OnTestBuildTree()
{
	using std::ifstream;
	RSTRTree tree(2,2,4);
	tree.dim = 2;
	tree.m = 2;
	tree.M = 4;
	ifstream inFile("data.txt");
	int N;
	inFile>>N;
	
	for(int i=0;i<N;i++){
		double x,y;
		inFile>>x>>y;
		//cout<<x<<" "<<y<<endl;
		RSTData* pData =new RSTData();
		pData->point = new RSTPoint();
		pData->point->push_back(x);
		pData->point->push_back(y);
		
		RSTInter xInter;
		RSTInter yInter;
		xInter.max=xInter.min = x;
		yInter.max= yInter.min = y;

		pData->range.push_back(xInter);
		pData->range.push_back(yInter);

		//insertData
		tree.InsertData(pData);
	}
	inFile.close();
}
