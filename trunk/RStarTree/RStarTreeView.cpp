// RStarTreeView.cpp : implementation of the CRStarTreeView class
//

#include "stdafx.h"
#include "RStarTree.h"

#include "RStarTreeDoc.h"
#include "RStarTreeView.h"

#include "RSTDefine.h"
#include "RSTRTree.h"
#include "RSTTestData.h"

#include <string>
#include <sstream>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#ifdef TEST
RSTRStarTree tree(2,4,8);

int N;

#endif

// CRStarTreeView

IMPLEMENT_DYNCREATE(CRStarTreeView, CView)

BEGIN_MESSAGE_MAP(CRStarTreeView, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_COMMAND(ID_TEST_BUILD_TREE, &CRStarTreeView::OnTestBuildTree)
	ON_WM_LBUTTONDOWN()
	ON_COMMAND(ID_TESTRANGESEARCH, &CRStarTreeView::OnTestrangesearch)
	ON_COMMAND(ID_ADDPOINT, &CRStarTreeView::OnAddpoint)
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_WM_CREATE()
	ON_WM_DESTROY()
	ON_WM_ERASEBKGND()
	ON_WM_SIZE()
	ON_WM_RBUTTONDOWN()
	ON_WM_RBUTTONUP()
	ON_WM_MOUSEWHEEL()
	ON_COMMAND(ID_FILE_OPEN, &CRStarTreeView::OnFileOpen)
	ON_COMMAND(ID_RESETPOSITION, &CRStarTreeView::OnResetPosition)
	ON_COMMAND(ID_DISPLAY_OPTION, &CRStarTreeView::OnDisplayOption)
	ON_COMMAND(ID_TEST_BUILD_TREE_FROM_FILE, &CRStarTreeView::OnTestBuildTreeFromFile)
	ON_COMMAND(ID_RANGESEARCH, &CRStarTreeView::OnRangeSearch)
	ON_COMMAND(ID_MOUSEDRAG, &CRStarTreeView::OnMouseDrag)
END_MESSAGE_MAP()

// CRStarTreeView construction/destruction

CRStarTreeView::CRStarTreeView()
: lbuttonflag(0),flagdraging(false)
{
	// TODO: add construction code here
	m_aorectangle.z = 0;
	m_aopoint.z = 0;
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

void CRStarTreeView::OnDraw(CDC* pDC)
{
	CRStarTreeDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: add draw code for native data here
#ifdef TEST
	/*CBrush redBrush, blueBrush;
	CPen bluePen;	
	redBrush.CreateSolidBrush(RGB(255, 0, 0));
	blueBrush.CreateSolidBrush(RGB(0, 0, 255));
	pDC->SelectObject(redBrush);
	for (size_t i = 0; i < pointSet.size(); i++)
	{
		RSTPoint2D* p = pointSet[i];
		pDC->Ellipse((int)p->x - 5, (int)p->y - 5, (int)p->x + 5, (int)p->y + 5);
	}
	if (GetDocument()->flag == Drag)
	{
		pDC->MoveTo(GetDocument()->start.x, GetDocument()->start.y);
		pDC->LineTo(GetDocument()->dragPoint.x, GetDocument()->start.y);
		pDC->MoveTo(GetDocument()->dragPoint.x, GetDocument()->start.y);
		pDC->LineTo(GetDocument()->dragPoint.x, GetDocument()->dragPoint.y);
		pDC->MoveTo(GetDocument()->dragPoint.x, GetDocument()->dragPoint.y);
		pDC->LineTo(GetDocument()->start.x, GetDocument()->dragPoint.y);
		pDC->MoveTo(GetDocument()->start.x, GetDocument()->dragPoint.y);
		pDC->LineTo(GetDocument()->start.x, GetDocument()->start.y);
	}
	if (GetDocument()->flag == RectFlag)
	{
		pDC->MoveTo(GetDocument()->start.x, GetDocument()->start.y);
		pDC->LineTo(GetDocument()->end.x, GetDocument()->start.y);
		pDC->MoveTo(GetDocument()->end.x, GetDocument()->start.y);
		pDC->LineTo(GetDocument()->end.x, GetDocument()->end.y);
		pDC->MoveTo(GetDocument()->end.x, GetDocument()->end.y);
		pDC->LineTo(GetDocument()->start.x, GetDocument()->end.y);
		pDC->MoveTo(GetDocument()->start.x, GetDocument()->end.y);
		pDC->LineTo(GetDocument()->start.x, GetDocument()->start.y);
	}
	if (GetDocument()->result.size() > 0)
	{
		for (size_t i = 0; i < GetDocument()->result.size(); i++)
		{
			pDC->SelectObject(blueBrush);
			RSTPoint2D* p = pointSet[i];
			pDC->Ellipse((int)p->x - 5, (int)p->y - 5, (int)p->x + 5, (int)p->y + 5);
		}
	}*/
#endif
	
	m_treeshow.BeginDraw(pDC->m_hDC);
	m_treeshow.drawTree();

	m_treeshow.EndDraw(pDC->m_hDC);
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
	//���������ļ�
	

	/*ofstream outFile("data.txt");
	int N = 1000000;
	outFile<<N<<endl;
	for(int i=0;i<N;i++){
		double x = rand()+(double)rand()/RAND_MAX;
		double y = rand()+(double)rand()/RAND_MAX;
		if(rand()%2==0)x = -x;
		if(rand()%2==0)y = -y;

		outFile<<x<<" "<<y<<endl;
	}
	outFile.close();*/


	ifstream inFile("data.txt");
	int N;
	inFile>>N;
	int m,M;
	m=10;
	M=20;
	
	vector<RSTRange> ranges;
	srand(unsigned(time(NULL)));
	for(int i=0;i<5;i++){
		RSTRange range;
		double xMin = rand()+(double)rand()/RAND_MAX;
		xMin = -xMin;
		double xMax = rand()+(double)rand()/RAND_MAX;

		double yMin = rand()+(double)rand()/RAND_MAX;
		yMin = -yMin;
		double yMax = rand()+(double)rand()/RAND_MAX;

		int T=10;
		xMin = xMin/T;
		yMin = yMin/T;
		xMax = xMax/T;
		yMax = yMax/T;
		range.push_back(RSTInter(xMin,xMax));
		range.push_back(RSTInter(yMin,yMax));
		ranges.push_back(range);
	}
	//input ranges
	/*RSTRange range1;
	range1.push_back(RSTInter(-200,200));
	range1.push_back(RSTInter(300,600));
	ranges.push_back(range1);
	RSTRange range2;
	range2.push_back(RSTInter(500,600));
	range2.push_back(RSTInter(-600,600));
	ranges.push_back(range2);*/

	RSTRStarTree starTree(2,m,M);
	RSTRTree tree(2,m,M);
	for(int i=0;i<N;i++){
		double x,y;
		inFile>>x>>y;
		RSTPoint2D* p = new RSTPoint2D();
		p->x = x;
		p->y = y;
		p->GenerateRange();

		//insertData
		tree.InsertData(p);
		
		
		p = new RSTPoint2D();
		p->x = x;
		p->y = y;
		p->GenerateRange();
		starTree.InsertData(p);

	}
	inFile.close();
	
	ofstream out("result.txt",ofstream::app);
	//out<<"Tree Height:"<<tree.height<<endl;
	////print the tree
	//using std::deque;
	//deque<RSTNode*> que;
	//que.push_back(tree.Root);
	//while(!que.empty()){
	//	RSTNode* pNode = que.front();
	//	out<<(void*)pNode<<":";
	//	out<<"Parent:"<<(void*)pNode->parent;
	//	for(int i=0;i<(int)pNode->range.size();i++){
	//		out<<"("<<pNode->range[i].min<<","<<pNode->range[i].max<<")";	
	//	}
	//	out<<endl;		
	//	que.pop_front();
	//	if(pNode->type==Data)continue;
	//	
	//	else{
	//		RSTNode* pRSTNode = (RSTNode*)pNode;
	//		for(int i=0;i<pRSTNode->childNum;i++)
	//			que.push_back(pRSTNode->childSet[i]);
	//	}
	//}
	

	out<<endl<<N<<"Points in the Tree"<<endl;
	out<<"m="<<tree.m<<" M="<<tree.M<<endl;
	LARGE_INTEGER frequency;
	QueryPerformanceFrequency(&frequency);
	LARGE_INTEGER beginCounter,endCounter;
	RSTNodeSet rTreeSet,starTreeSet;
	double resultTime;

	for(size_t i=0;i<ranges.size();i++){
		RSTRange& range = ranges[i];
		out<<"Range is x:"<<range[0].min<<"to"<<range[0].max;
		out<<" y:"<<range[1].min<<"to"<<range[1].max<<endl;


		QueryPerformanceCounter(&beginCounter);
		tree.Search(range,rTreeSet,false);
		QueryPerformanceCounter(&endCounter);
		
		resultTime = 
			((double)endCounter.QuadPart-(double)beginCounter.QuadPart)
			/
			(frequency.QuadPart);
		resultTime= resultTime*1000*1000;

		out<<"RTree:"<<rTreeSet.size();
		out<<" Time:"<<resultTime<<"us"<<endl;

		
		QueryPerformanceCounter(&beginCounter);
		starTree.Search(range,starTreeSet,false);
		QueryPerformanceCounter(&endCounter);



		resultTime = 
			((double)endCounter.QuadPart-(double)beginCounter.QuadPart)
			/
			(frequency.QuadPart);
		resultTime= resultTime*1000*1000;
		out<<"R*Tree:"<<starTreeSet.size();
		out<<" Time:"<<resultTime<<"us"<<endl;

	}
	

	
	



	


	
	


	
	out.close();
}

void CRStarTreeView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
#ifdef TEST
	/*if (GetDocument()->flag == DrawPoint)
	{
		RSTPoint2D* p = new RSTPoint2D();
		p->x = point.x;
		p->y = point.y;
		p->GenerateRange();
		GetDocument()->rtree->InsertData(p);
		pointSet.push_back(p);
		Invalidate();
	}
	if (GetDocument()->flag == RectFlag)
	{
		GetDocument()->start.x = point.x;
		GetDocument()->start.y = point.y;
		GetDocument()->flag = Drag;
	}*/
	
#endif
	beginpoint = point;
	endpoint = point;
	switch(lbuttonflag)
	{
	case LBUTTONDRAG:
		flagdraging = true;
		break;
	case LBUTTONRANGESEARCH:
		m_treeshow.get2DCoordinateFromSCreenToWorld(beginpoint.x,beginpoint.y,
			m_aorectangle.left,m_aorectangle.bottom);
		break;
	case LBUTTONRANGELOCATION:
		break;
	case LBUTTONPOINTLOCATION:
		break;
	default:
		break;
	}

	CView::OnLButtonDown(nFlags, point);
}

void CRStarTreeView::OnTestrangesearch()
{
	// TODO: Add your command handler code here
#ifdef TEST
	GetDocument()->flag = RectFlag;
#endif
	
}

void CRStarTreeView::OnAddpoint()
{
	// TODO: Add your command handler code here
#ifdef TEST
	GetDocument()->flag = DrawPoint;
#endif
	
}

void CRStarTreeView::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
#ifdef TEST
	/*if (GetDocument()->flag == Drag)
	{
		GetDocument()->end.x = point.x;
		GetDocument()->end.y = point.y;
		GetDocument()->flag = RectFlag;
		RSTRange searchRange;
		searchRange.push_back(RSTInter(GetDocument()->start.x, GetDocument()->end.x));
		searchRange.push_back(RSTInter(GetDocument()->start.y, GetDocument()->end.y));
		GetDocument()->rtree->Search(searchRange, GetDocument()->result, false);
	}*/
#endif
	endpoint = point;
	switch(lbuttonflag)
	{
	case LBUTTONDRAG:
		if(flagdraging)
		{
			m_treeshow.Translation(endpoint.x-beginpoint.x,beginpoint.y-endpoint.y,true);
			flagdraging = false;
		}
		break;
	case LBUTTONRANGESEARCH:
		m_treeshow.get2DCoordinateFromSCreenToWorld(endpoint.x,endpoint.y,
			m_aorectangle.right,m_aorectangle.top);
		break;
	case LBUTTONRANGELOCATION:
		break;
	case LBUTTONPOINTLOCATION:
		break;
	default:
		break;
	}
	Invalidate(TRUE);

	CView::OnLButtonUp(nFlags, point);
}

void CRStarTreeView::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
#ifdef TEST
	/*if (GetDocument()->flag == Drag)
	{
		GetDocument()->dragPoint.x = point.x;
		GetDocument()->dragPoint.y = point.y;
		Invalidate();
	}*/
#endif
	if(nFlags == MK_LBUTTON)
	{
		endpoint = point;
		switch(lbuttonflag)
		{
		case LBUTTONDRAG:
			m_treeshow.Translation(endpoint.x-beginpoint.x,beginpoint.y-endpoint.y,false);
			break;
		case LBUTTONRANGESEARCH:
			m_treeshow.get2DCoordinateFromSCreenToWorld(endpoint.x,endpoint.y,
					m_aorectangle.right,m_aorectangle.top);
			break;
		case LBUTTONRANGELOCATION:
			break;
		case LBUTTONPOINTLOCATION:
			break;
		default:
			break;
		}
	}
	else if(nFlags == MK_RBUTTON)
	{
		if(lbuttonflag == LBUTTONDRAG)
		{
			endpoint = point;
			double detx = endpoint.x - beginpoint.x;
			double dety = beginpoint.y - endpoint.y;
			double detlength = detx*detx+dety*dety;
			if(detlength<0.000000001)
				return;
			double angle = detlength/100000.0;
			m_treeshow.Rotation((int)-dety,(int)detx,angle,false);
		}
		else
		{
			endpoint = point;
			m_treeshow.Translation(endpoint.x-beginpoint.x,beginpoint.y-endpoint.y,false);
		}
	}
	else
		;

	Invalidate(TRUE);
	CView::OnMouseMove(nFlags, point);
}

int CRStarTreeView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  Add your specialized creation code here
	CClientDC dc(this);
	m_treeshow.Initialization(dc);
	beginpoint.SetPoint(0,0);
	endpoint.SetPoint(0,0);
	flagdraging = false;

	return 0;
}

void CRStarTreeView::OnDestroy()
{
	CView::OnDestroy();

	// TODO: Add your message handler code here
	m_treeshow.Destroy();
}

BOOL CRStarTreeView::OnEraseBkgnd(CDC* pDC)
{
	// TODO: Add your message handler code here and/or call default

	//return CView::OnEraseBkgnd(pDC);
	return TRUE;
}

void CRStarTreeView::OnSize(UINT nType, int cx, int cy)
{
	CView::OnSize(nType, cx, cy);

	// TODO: Add your message handler code here
	CClientDC dc(this);
	m_treeshow.ReSize(dc,cx,cy);
	Invalidate(TRUE);
}

void CRStarTreeView::OnRButtonDown(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	beginpoint = point;
	endpoint = point;

	CView::OnRButtonDown(nFlags, point);
}

void CRStarTreeView::OnRButtonUp(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	if(lbuttonflag == LBUTTONDRAG)
	{
		endpoint = point;
		double detx = endpoint.x - beginpoint.x;
		double dety = beginpoint.y - endpoint.y;
		double detlength = detx*detx+dety*dety;
		if(detlength<0.000000001)
			return;
		double angle = detlength/100000.0;
		m_treeshow.Rotation((int)-dety,(int)detx,angle,true);
		Invalidate(TRUE);
	}
	else
	{
		endpoint = point;
		m_treeshow.Translation(endpoint.x-beginpoint.x,beginpoint.y-endpoint.y,true);
		Invalidate(TRUE);
	}

	CView::OnRButtonUp(nFlags, point);
}

BOOL CRStarTreeView::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt)
{
	// TODO: Add your message handler code here and/or call default
	if(zDelta>0)
	{
		m_treeshow.AdjustZoomRate(1/(1+((double)zDelta/1200)));
	}
	else if(zDelta<0)
	{
		m_treeshow.AdjustZoomRate(1-((double)zDelta/1200));
	}
	Invalidate(TRUE);

	return CView::OnMouseWheel(nFlags, zDelta, pt);
}

void CRStarTreeView::OnFileOpen()
{
	// TODO: Add your command handler code here
	CFileDialog mydlg(true,_T("*.txt"),_T("*.txt"),NULL,_T("(*.txt)|*.txt||"),
		this,NULL);
	if(mydlg.DoModal()!=IDOK)
		return;
	std::wstring filename = mydlg.GetPathName();
	std::ifstream infile(filename.c_str());
	std::string tempstr;
	std::getline(infile,tempstr);
	if(tempstr.compare("testdata2d") != 0)
	{
		MessageBox(_T("�ļ���ʽ����"),_T("������ʾ"),MB_ICONERROR|MB_OK);
		return;
	}
	RSTPoint2D *points = NULL;
	size_t pointnumber = 0;
	RSTRectangle2D* rectangles = NULL;
	size_t rectanglenumber = 0;
	while(tempstr != "databegin")
	{
		getline(infile,tempstr,'\n');
		if(tempstr == "pointnumber:")
		{
			infile>>pointnumber;
			getline(infile,tempstr,'\n');
		}
		else if (tempstr == "rectanglenumber:")
		{
			infile>>rectanglenumber;
			getline(infile,tempstr,'\n');
		}
		else
			break;
	}
	RSTRTree* ptree = this->GetDocument()->rtree;
	vector<RSTNode*> *pset = &(this->GetDocument()->dateset);
	pset->clear();
	size_t datasize = pointnumber + rectanglenumber;
	pset->reserve(datasize);
	while(tempstr != "dataend")
	{
		getline(infile,tempstr,'\n');
		if(tempstr == "pointdate:")
		{
			for(size_t i=0;i<pointnumber;++i)
			{
				points = new RSTPoint2D;
				infile>>points->x>>points->y;
				points->GenerateRange();
				pset->push_back(points);
				ptree->InsertData(points);
			}
			getline(infile,tempstr,'\n');
		}
		else if (tempstr == "retangledate:")
		{
			for(size_t i=0;i<rectanglenumber;++i)
			{
				rectangles = new RSTRectangle2D;
				infile>>rectangles->xmin>>rectangles->ymin
					>>rectangles->xmax>>rectangles->ymax;
				rectangles->GenerateRange();
				pset->push_back(rectangles);
				ptree->InsertData(rectangles);
			}
			getline(infile,tempstr,'\n');
		}
		else
			break;
	}
	infile.close();
	m_treeshow.setTree(ptree,pset);
	Invalidate(TRUE);
}

void CRStarTreeView::OnResetPosition()
{
	// TODO: Add your command handler code here
	m_treeshow.ResetPosition();
	Invalidate(TRUE);
}

void CRStarTreeView::OnDisplayOption()
{
	//TODO
	DisplayOptionDialog dlg;
	dlg.notDisplayDataNode = m_treeshow.getDataShowState()?false:true;
	dlg.notDisplayRTreeEdge = m_treeshow.getBranchState()?false:true;
	dlg.notDisplayLeafNodeEdge = m_treeshow.getNodeEdgeShowState()?false:true;
	dlg.leafNodeNotObsolete = m_treeshow.getNodeFaceShowState()?false:true;
	if(dlg.DoModal() == IDOK)
	{
		m_treeshow.setDataShowState(dlg.notDisplayDataNode?false:true);
		m_treeshow.setBranchState(dlg.notDisplayRTreeEdge?false:true);
		m_treeshow.setNodeEdgeShowState(dlg.notDisplayLeafNodeEdge?false:true);
		m_treeshow.setNodeFaceShowState(dlg.leafNodeNotObsolete?false:true);
	}
}

void CRStarTreeView::OnTestBuildTreeFromFile()
{


	
	
}

void CRStarTreeView::OnRangeSearch()
{
	// TODO: Add your command handler code here
	lbuttonflag = LBUTTONRANGESEARCH;
	m_treeshow.ResetPosition();
	m_treeshow.setAssistantObject((AssistantObject *)(&m_aorectangle));
	m_treeshow.setAssistantObjectShowState(true);
	m_treeshow.setBranchState(false);
	m_treeshow.setNodeEdgeShowState(false);
	m_treeshow.setDataShowState(true);
	m_treeshow.setNodeFaceShowState(false);
	Invalidate(TRUE);
}

void CRStarTreeView::OnMouseDrag()
{
	// TODO: Add your command handler code here
	lbuttonflag = LBUTTONDRAG;
}
