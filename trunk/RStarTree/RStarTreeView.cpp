// RStarTreeView.cpp : implementation of the CRStarTreeView class
//

#include "stdafx.h"
#include "RStarTree.h"

#include "RStarTreeDoc.h"
#include "RStarTreeView.h"

#include "RSTDefine.h"
#include "RSTRTree.h"
#include "RSTTestData.h"

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
	using std::ofstream;
	using std::endl;
	using std::vector;
	//生成数据文件
	

	/*ofstream outFile("data.txt");
	int N = 10000;
	outFile<<N<<endl;
	for(int i=0;i<N;i++){
		int x = rand()%100;
		int y = rand()%100;
		if(rand()%2==0)x = -x;
		if(rand()%2==0)y = -y;

		outFile<<x<<" "<<y<<endl;
	}
	outFile.close();*/



	RSTRTree tree(2,5,20);
	ifstream inFile("data.txt");
	int N;
	inFile>>N;
	
	for(int i=0;i<N;i++){
		double x,y;
		inFile>>x>>y;
		RSTPoint2D* p = new RSTPoint2D();
		p->x = x;
		p->y = y;
		p->GenerateRange();

		//insertData
		tree.InsertData(p);
	}
	inFile.close();
	ofstream out("result.txt");
	out<<"Tree Height:"<<tree.height<<endl;
	//print the tree
	using std::deque;
	deque<RSTNode*> que;
	que.push_back(tree.Root);
	while(!que.empty()){
		RSTNode* pNode = que.front();
		out<<(void*)pNode<<":";
		out<<"Parent:"<<(void*)pNode->parent;
		for(int i=0;i<(int)pNode->range.size();i++){
			out<<"("<<pNode->range[i].min<<","<<pNode->range[i].max<<")";	
		}
		out<<endl;		
		que.pop_front();
		if(pNode->type==Data)continue;
		
		else{
			RSTNode* pRSTNode = (RSTNode*)pNode;
			for(int i=0;i<pRSTNode->childNum;i++)
				que.push_back(pRSTNode->childSet[i]);
		}
	}

	
	/*out<<endl;
	out<<endl;
	RSTNodeSet resultSet;
	RSTRange range;
	range.push_back(RSTInter(-100,100));
	range.push_back(RSTInter(-100,50));
	tree.Search(range,resultSet,false);

	out<<resultSet.size() << endl;
	for(int i=0;i<(int)resultSet.size();i++){
		out<<resultSet[i]->range[0].min<<
			" "<<resultSet[i]->range[1].min<<endl;
	}*/
	out.close();
}
