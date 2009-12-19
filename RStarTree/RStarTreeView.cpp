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
//RSTRStarTree tree(2,4,8);

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
	ON_COMMAND(ID_RANGELOCATION, &CRStarTreeView::OnRangeLocation)
	ON_COMMAND(ID_DEMOSHOW, &CRStarTreeView::OnDemoShow)
	ON_COMMAND(ID_ADDDATA, &CRStarTreeView::OnAddData)
	ON_COMMAND(ID_FILE_SAVE, &CRStarTreeView::OnFileSave)
	
	ON_COMMAND(ID_DELETE, &CRStarTreeView::OnDelete)
	ON_COMMAND(ID_PRINT_TREE, &CRStarTreeView::OnPrintTree)
	ON_COMMAND(ID_SHOWEVERYTHING, &CRStarTreeView::OnShowEverything)
	ON_COMMAND(ID_ENDDEMO, &CRStarTreeView::OnEndDemo)
END_MESSAGE_MAP()

// CRStarTreeView construction/destruction

int CRStarTreeView::timeUnit = 1;
CRStarTreeView::CRStarTreeView()
: lbuttonflag(0),flagdraging(false)
, flagdemoshow(false)
, flagdemothread(false)
{
	// TODO: add construction code here
	m_aorectangle.z = 0;
	m_aopoint.z = 0;
	timeUnit = 1;
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

void CRStarTreeView::test3DPoint(){
	using std::ofstream;
	using std::endl;
	using std::vector;
	using ::std::ifstream;

	/*ofstream outFile("data3d.txt");
	int N = 1000000;
	srand((unsigned)time(NULL));
	outFile<<N<<endl;
	for(int i=0;i<N;i++){
		double x = rand()+(double)rand()/RAND_MAX;
		double y = rand()+(double)rand()/RAND_MAX;
		double z = rand()+(double)rand()/RAND_MAX;
		if(rand()%2==0)x = -x;
		if(rand()%2==0)y = -y;
		if(rand()%2==0)z = -z;

		outFile<<x<<" "<<y<<" "<<z<<endl;
	}
	outFile.close();*/

	LARGE_INTEGER frequency;
	LARGE_INTEGER beginCounter,endCounter;
	double resultTime;
	QueryPerformanceFrequency(&frequency);

	//生成查询范围
	double xMin = 65535,yMin = 65535,zMin = 65535;
	double yMax = -65535,xMax = -65535,zMax = -65535;
	
	
	vector<RSTRange> ranges;
	/*srand(unsigned(time(NULL)));*/
	for(int i=0;i<10;i++){
		RSTRange range;
		double xMin = rand()+(double)rand()/RAND_MAX;
		xMin = -xMin;
		double xMax = rand()+(double)rand()/RAND_MAX;

		double yMin = rand()+(double)rand()/RAND_MAX;
		yMin = -yMin;
		double yMax = rand()+(double)rand()/RAND_MAX;

		double zMin = rand()+(double)rand()/RAND_MAX;
		zMin = -zMin;
		double zMax = rand()+(double)rand()/RAND_MAX;

		int T=10;
		xMin = xMin/T;
		yMin = yMin/T;
		xMax = xMax/T;
		yMax = yMax/T;
		zMin = zMin/T;
		zMax = zMax/T;
		range.push_back(RSTInter(xMin,xMax));
		range.push_back(RSTInter(yMin,yMax));
		range.push_back(RSTInter(zMin,zMax));
		ranges.push_back(range);
	}

	int N[13] = {1000, 2000, 5000, 10000, 20000,
		30000, 40000, 50000, 60000,
		70000, 80000, 90000, 100000};
	/*int N[13] = {1000, 2000};*/
	ofstream out("result-query-time-3d.txt",ofstream::app);
	int m=2;
	int M=4;
	RSTRTree* pRTree;
	RSTRTree* pStarTree;
	
	//output 
	out<<endl<<endl<<endl;
	out<<"m="<<m<<" M="<<M<<endl;
	for(int k=0;k<13;k++){
		
		ifstream inFile("data3d.txt");
		vector<RSTPoint3D*> inputVecTree;
		vector<RSTPoint3D*> inputVecStarTree;
		

		//
		out<<endl;
		out<<"Data Set Size:"<<N[k]<<endl;
		//read in Data
		for(int i=0;i<N[k];i++){
			double x,y,z;
			inFile>>x>>y>>z;

			RSTPoint3D* p = new RSTPoint3D();
			p->x = x;
			p->y = y;
			p->z = z;

			p->GenerateRange();
			inputVecStarTree.push_back(p);

			p = new RSTPoint3D();
			p->x = x;
			p->y = y;
			p->z = z;
			p->GenerateRange();
			inputVecTree.push_back(p);

			if(x<xMin)
				xMin = x;
			if(x>xMax)
				xMax = x;
			if(y<yMin)
				yMin = y;
			if(y>yMax)
				yMax = y;
			if(z<zMin)
				zMin = z;
			if(z>zMax)
				zMax = z;
		}
		//read complete 
		pRTree = new RSTRTree(3,m,M);
		pStarTree = new RSTRStarTree(3,m,M);

		//build R-Tree and output infomation
		QueryPerformanceCounter(&beginCounter);
		for(int i=0;i<N[k];i++){
			pRTree->InsertData(inputVecTree[i]);
		}
		QueryPerformanceCounter(&endCounter);
		resultTime = 
			((double)endCounter.QuadPart-(double)beginCounter.QuadPart)
			/
			(frequency.QuadPart);
		resultTime= resultTime*1000;
		
		out<<"Build R-Tree Time:"<<resultTime<<"ms "<<" Height="<<pRTree->height<<" PointNum="<<inputVecTree.size();
		out<<" R-TREE Range:"<<(
		(xMin==pRTree->Root->range[0].min&&
		xMax==pRTree->Root->range[0].max&&
		yMin==pRTree->Root->range[1].min&&
		yMax==pRTree->Root->range[1].max&&
		zMin==pRTree->Root->range[2].min&&
		zMax==pRTree->Root->range[2].max)?"OK":"Error")<<endl;

		//build R*Tree and output infomation
		QueryPerformanceCounter(&beginCounter);
		for(int i=0;i<N[k];i++){
			pStarTree->InsertData(inputVecStarTree[i]);
		}
		QueryPerformanceCounter(&endCounter);
		resultTime = 
			((double)endCounter.QuadPart-(double)beginCounter.QuadPart)
			/
			(frequency.QuadPart);
		resultTime= resultTime*1000;
		

		out<<"Build R*Tree Time:"<<resultTime<<"ms "<<" Height="<<pStarTree->height<<" PointNum="<<inputVecTree.size();
		out<<" R*TREE Range:"<<(
		(xMin==pStarTree->Root->range[0].min&&
		xMax==pStarTree->Root->range[0].max&&
		yMin==pStarTree->Root->range[1].min&&
		yMax==pStarTree->Root->range[1].max&&
		zMin==pRTree->Root->range[2].min&&
		zMax==pRTree->Root->range[2].max)?"OK":"Error")<<endl;


		//query time
		for(size_t i=0;i<ranges.size();i++){
			RSTNodeSet rTreeSet,starTreeSet;
			RSTRange& range = ranges[i];
			double resultTime1,resultTime2;

			out<<"Range.No."<<i<<" ["<<range[0].min<<","<<range[0].max<<"]["
				<<range[1].min<<","<<range[1].max<<"]"<<"["<<range[2].min<<","<<range[2].max<<"]"<<endl;


			QueryPerformanceCounter(&beginCounter);
			pRTree->Search(range,rTreeSet,false);
			QueryPerformanceCounter(&endCounter);
			
			resultTime1 = 
				((double)endCounter.QuadPart-(double)beginCounter.QuadPart)
				/
				(frequency.QuadPart);
			resultTime1= resultTime1*1000*1000;

			out<<"    "<<"R-Tree:"<<rTreeSet.size()<<" Points";
			out<<" Time:"<<resultTime1<<"us"<<endl;

			
			QueryPerformanceCounter(&beginCounter);
			pStarTree->Search(range,starTreeSet,false);
			QueryPerformanceCounter(&endCounter);
			resultTime2 = 
				((double)endCounter.QuadPart-(double)beginCounter.QuadPart)
				/
				(frequency.QuadPart);
			resultTime2= resultTime2*1000*1000;
			out<<"    "<<"R*Tree:"<<starTreeSet.size()<<" Points";
			out<<" Time:"<<resultTime<<"us"<<" Percentage:"<<resultTime2*100/resultTime1<<"%"<<endl;
			

		}

		inFile.close();
		delete pRTree;
		delete pStarTree;
	}
	out.close();


}

void CRStarTreeView::test2DPoint(){
using std::ifstream;
	using std::ofstream;
	using std::endl;
	using std::vector;


	LARGE_INTEGER frequency;
	LARGE_INTEGER beginCounter,endCounter;
	double resultTime;
	QueryPerformanceFrequency(&frequency);

	//生成查询范围
	double xMin = 65535,yMin = 65535;
	double yMax = -65535,xMax = -65535;
	
	vector<RSTRange> ranges;
	/*srand(unsigned(time(NULL)));*/
	for(int i=0;i<10;i++){
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

	int N[13] = {1000, 2000, 5000, 10000, 20000,
		30000, 40000, 50000, 60000,
		70000, 80000, 90000, 100000};
	/*int N[13] = {1000, 2000};*/
	ofstream out("result-query-time-average.txt",ofstream::app);
	int m=12;
	int M=30;
	RSTRTree* pRTree;
	RSTRTree* pStarTree;
	
	//output 
	out<<endl<<endl<<endl;
	out<<"m="<<m<<" M="<<M<<endl;
	for(int k=0;k<13;k++){
		
		ifstream inFile("data.txt");
		vector<RSTPoint2D*> inputVecTree;
		vector<RSTPoint2D*> inputVecStarTree;
		

		//
		out<<endl;
		out<<"Data Set Size:"<<N[k]<<endl;
		//read in Data
		for(int i=0;i<N[k];i++){
			double x,y;
			inFile>>x>>y;

			RSTPoint2D* p = new RSTPoint2D();
			p->x = x;
			p->y = y;
			p->GenerateRange();
			inputVecStarTree.push_back(p);

			p = new RSTPoint2D();
			p->x = x;
			p->y = y;
			p->GenerateRange();
			inputVecTree.push_back(p);

			if(x<xMin)
				xMin = x;
			if(x>xMax)
				xMax = x;
			if(y<yMin)
				yMin = y;
			if(y>yMax)
				yMax = y;
		}
		//read complete 
		pRTree = new RSTRTree(2,m,M);
		pStarTree = new RSTRStarTree(2,m,M);

		//build R-Tree and output infomation
		QueryPerformanceCounter(&beginCounter);
		for(int i=0;i<N[k];i++){
			pRTree->InsertData(inputVecTree[i]);
		}
		QueryPerformanceCounter(&endCounter);
		resultTime = 
			((double)endCounter.QuadPart-(double)beginCounter.QuadPart)
			/
			(frequency.QuadPart);
		resultTime= resultTime*1000;
		
		out<<"Build R-Tree Time:"<<resultTime<<"ms "<<" Height="<<pRTree->height<<" PointNum="<<inputVecTree.size();
		out<<" R-TREE Range:"<<(
		(xMin==pRTree->Root->range[0].min&&
		xMax==pRTree->Root->range[0].max&&
		yMin==pRTree->Root->range[1].min&&
		yMax==pRTree->Root->range[1].max)?"OK":"Error")<<endl;

		//build R*Tree and output infomation
		QueryPerformanceCounter(&beginCounter);
		for(int i=0;i<N[k];i++){
			pStarTree->InsertData(inputVecStarTree[i]);
		}
		QueryPerformanceCounter(&endCounter);
		resultTime = 
			((double)endCounter.QuadPart-(double)beginCounter.QuadPart)
			/
			(frequency.QuadPart);
		resultTime= resultTime*1000;
		

		out<<"Build R*Tree Time:"<<resultTime<<"ms "<<" Height="<<pStarTree->height<<" PointNum="<<inputVecTree.size();
		out<<" R*TREE Range:"<<(
		(xMin==pStarTree->Root->range[0].min&&
		xMax==pStarTree->Root->range[0].max&&
		yMin==pStarTree->Root->range[1].min&&
		yMax==pStarTree->Root->range[1].max)?"OK":"Error")<<endl;


		//query time
		double rTreeQueryTime=  0;
		double starTreeQueryTime = 0.0;
		for(size_t i=0;i<ranges.size();i++){
			RSTNodeSet rTreeSet,starTreeSet;
			RSTRange& range = ranges[i];
			double resultTime1,resultTime2;

			/*out<<"Range.No."<<i<<" ["<<range[0].min<<","<<range[0].max<<"]["
				<<range[1].min<<","<<range[1].max<<"]"<<endl;*/


			QueryPerformanceCounter(&beginCounter);
			pRTree->Search(range,rTreeSet,false);
			QueryPerformanceCounter(&endCounter);
			
			resultTime1 = 
				((double)endCounter.QuadPart-(double)beginCounter.QuadPart)
				/
				(frequency.QuadPart);
			resultTime1= resultTime1*1000*1000;
			rTreeQueryTime+=resultTime1;

			/*out<<"    "<<"R-Tree:"<<rTreeSet.size()<<" Points";
			out<<" Time:"<<resultTime1<<"us"<<endl;*/

			
			QueryPerformanceCounter(&beginCounter);
			pStarTree->Search(range,starTreeSet,false);
			QueryPerformanceCounter(&endCounter);
			resultTime2 = 
				((double)endCounter.QuadPart-(double)beginCounter.QuadPart)
				/
				(frequency.QuadPart);
			resultTime2= resultTime2*1000*1000;
			starTreeQueryTime+=resultTime2;
			/*out<<"    "<<"R*Tree:"<<starTreeSet.size()<<" Points";
			out<<" Time:"<<resultTime2<<"us"<<" Percentage:"<<resultTime2*100/resultTime1<<"%"<<endl;*/

		}
		out<<"R-Tree average query time:"<<(rTreeQueryTime/ranges.size())<<"us"<<endl;
		out<<"R*Tree average query time:"<<(starTreeQueryTime/ranges.size())<<"us"<<endl;
		out<<"Average time ratio:"<<starTreeQueryTime*100/rTreeQueryTime<<"%"<<endl;

		inFile.close();
		delete pRTree;
		delete pStarTree;
	}
	out.close();
}
void CRStarTreeView::OnTestBuildTree()
{
	test2DPoint();
	/*test3DPoint();*/

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
		m_treeshow.get2DCoordinateFromSCreenToWorld(beginpoint.x,beginpoint.y,
			m_aorectangle.left,m_aorectangle.bottom);
		break;
	case LBUTTONRANGELOCATION:
		m_treeshow.get2DCoordinateFromSCreenToWorld(beginpoint.x,beginpoint.y,
			m_aorectangle.left,m_aorectangle.bottom);
		m_treeshow.get2DCoordinateFromSCreenToWorld(beginpoint.x,beginpoint.y,
			m_aorectangle.left,m_aorectangle.bottom);
		break;
	case LBUTTONPOINTLOCATION:
		break;
	case LBUTTONADDDATA:
		m_treeshow.setAssistantObjectShowState(false);
		if(this->GetDocument()->rtree==NULL)
		{
			this->GetDocument()->dateset.clear();
			if(this->GetDocument()->isRStarTree)
			{
				this->GetDocument()->rtree = new RSTRStarTree(DEFAULT_DIMENTION,
					this->GetDocument()->m,this->GetDocument()->M);
			}
			else
			{
				this->GetDocument()->rtree = new RSTRTree(DEFAULT_DIMENTION, 
					this->GetDocument()->m,this->GetDocument()->M);
			}
			m_treeshow.setTree(this->GetDocument()->rtree,&(this->GetDocument()->dateset));
		}
		m_treeshow.get2DCoordinateFromSCreenToWorld(beginpoint.x,beginpoint.y,
			m_aorectangle.left,m_aorectangle.bottom);
		m_treeshow.get2DCoordinateFromSCreenToWorld(beginpoint.x,beginpoint.y,
			m_aorectangle.left,m_aorectangle.bottom);
		break;
	case LBUTTONDELETE:
		m_treeshow.get2DCoordinateFromSCreenToWorld(beginpoint.x,beginpoint.y,
			m_aorectangle.left,m_aorectangle.bottom);
		m_treeshow.get2DCoordinateFromSCreenToWorld(beginpoint.x,beginpoint.y,
			m_aorectangle.left,m_aorectangle.bottom);
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
	RSTPoint2D* rstpoint = NULL;
	RSTRectangle2D* rstrectangle = NULL;
	RSTNodeSet* pResultSet;
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
		m_aorectangle.adjustRange();
		m_range.clear();
		m_range.push_back(RSTInter(m_aorectangle.left,m_aorectangle.right));
		m_range.push_back(RSTInter(m_aorectangle.bottom,m_aorectangle.top));
		this->GetDocument()->result.clear();
		this->GetDocument()->rtree->Search(m_range,this->GetDocument()->result,false);
		m_treeshow.setResult(&(this->GetDocument()->result));
		break;
	case LBUTTONRANGELOCATION:
		m_treeshow.get2DCoordinateFromSCreenToWorld(endpoint.x,endpoint.y,
			m_aorectangle.right,m_aorectangle.top);
		m_aorectangle.adjustRange();
		m_range.clear();
		m_range.push_back(RSTInter(m_aorectangle.left,m_aorectangle.right));
		m_range.push_back(RSTInter(m_aorectangle.bottom,m_aorectangle.top));
		this->GetDocument()->result.clear();
		this->GetDocument()->rtree->Search(m_range,this->GetDocument()->result,true);
		m_treeshow.setResult(&(this->GetDocument()->result));
		break;
	case LBUTTONPOINTLOCATION:
		break;
	case LBUTTONADDDATA:
		if(this->GetDocument()->rtree==NULL)
		{
			this->GetDocument()->dateset.clear();
			if(this->GetDocument()->isRStarTree)
			{
				this->GetDocument()->rtree = new RSTRStarTree(DEFAULT_DIMENTION,
					this->GetDocument()->m,this->GetDocument()->M);
			}
			else
			{
				this->GetDocument()->rtree = new RSTRTree(DEFAULT_DIMENTION, 
					this->GetDocument()->m,this->GetDocument()->M);
			}
		}
		if(pow(beginpoint.x - endpoint.x,2.0)+pow(beginpoint.y-endpoint.y,2.0)<20)
		{
			rstpoint = new RSTPoint2D;
			rstpoint->x = m_aorectangle.left;
			rstpoint->y = m_aorectangle.bottom;
			rstpoint->GenerateRange();
			this->GetDocument()->dateset.push_back(rstpoint);
			this->GetDocument()->rtree->InsertData(rstpoint);
			rstpoint = NULL;
		}
		else
		{
			m_treeshow.get2DCoordinateFromSCreenToWorld(endpoint.x,endpoint.y,
				m_aorectangle.right,m_aorectangle.top);
			m_aorectangle.adjustRange();
			rstrectangle = new RSTRectangle2D;
			rstrectangle->xmin = m_aorectangle.left;
			rstrectangle->ymin = m_aorectangle.bottom;
			rstrectangle->xmax = m_aorectangle.right;
			rstrectangle->ymax = m_aorectangle.top;
			rstrectangle->GenerateRange();
			this->GetDocument()->dateset.push_back(rstrectangle);
			this->GetDocument()->rtree->InsertData(rstrectangle);
			rstrectangle = NULL;
			m_treeshow.setAssistantObjectShowState(false);
		}
		m_treeshow.Reset();
		break;
	case LBUTTONDELETE:
		m_treeshow.get2DCoordinateFromSCreenToWorld(endpoint.x,endpoint.y,
			m_aorectangle.right,m_aorectangle.top);
		m_aorectangle.adjustRange();
		m_range.clear();
		m_range.push_back(RSTInter(m_aorectangle.left,m_aorectangle.right));
		m_range.push_back(RSTInter(m_aorectangle.bottom,m_aorectangle.top));
		
		this->GetDocument()->result.clear();
		
		this->GetDocument()->rtree->Search(m_range,this->GetDocument()->result,false);
		pResultSet = &(this->GetDocument()->result);
		for(size_t i=0;i<this->GetDocument()->result.size();++i)
		{
			this->GetDocument()->rtree->Delete(this->GetDocument()->result[i]);
			for(vector<RSTNode*>::iterator p=this->GetDocument()->dateset.begin();
				p<this->GetDocument()->dateset.end();++p)
			{
				if((*p) == this->GetDocument()->result[i])
					(*p) = NULL;
			}
		}
		m_treeshow.Reset();
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
			m_treeshow.get2DCoordinateFromSCreenToWorld(endpoint.x,endpoint.y,
					m_aorectangle.right,m_aorectangle.top);
			break;
		case LBUTTONPOINTLOCATION:
			break;
		case LBUTTONADDDATA:
			m_treeshow.get2DCoordinateFromSCreenToWorld(endpoint.x,endpoint.y,
					m_aorectangle.right,m_aorectangle.top);
			m_treeshow.setAssistantObjectShowState(true);
			break;
		case LBUTTONDELETE:
			m_treeshow.get2DCoordinateFromSCreenToWorld(endpoint.x,endpoint.y,
					m_aorectangle.right,m_aorectangle.top);
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
		else if(lbuttonflag != LBUTTONDISABLE)
		{
			endpoint = point;
			m_treeshow.Translation(endpoint.x-beginpoint.x,beginpoint.y-endpoint.y,false);
		}
		else;
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
	while(flagdemothread)
	{
		flagdemoshow = false;
	}
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
	else if(lbuttonflag != LBUTTONDISABLE)
	{
		endpoint = point;
		m_treeshow.Translation(endpoint.x-beginpoint.x,beginpoint.y-endpoint.y,true);
		Invalidate(TRUE);
	}
	else
		;

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
	flagdemoshow = false;
	while(flagdemothread)
	{
		flagdemoshow = false;
	}
	m_treeshow.setDemoShowState(false);
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
		MessageBox(_T("文件格式错误"),_T("错误提示"),MB_ICONERROR|MB_OK);
		return;
	}
	RSTPoint2D *points = NULL;
	size_t pointnumber = 0;
	RSTRectangle2D* rectangles = NULL;
	size_t rectanglenumber = 0;
	int errorcount = 0;
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
		{
			++errorcount;
			if(errorcount>100)
			{
				MessageBox(_T("文件格式错误"),_T("错误提示"),MB_ICONERROR|MB_OK);
				return;
			}
		}
	}
	delete this->GetDocument()->rtree;
	if(this->GetDocument()->isRStarTree){
		this->GetDocument()->rtree = new RSTRStarTree(DEFAULT_DIMENTION,
			this->GetDocument()->m,
			this->GetDocument()->M);
	}else{
		this->GetDocument()->rtree = new RSTRTree(DEFAULT_DIMENTION, 
			this->GetDocument()->m,
			this->GetDocument()->M);
	}
	
	RSTRTree* ptree = this->GetDocument()->rtree;
	vector<RSTNode*> *pset = &(this->GetDocument()->dateset);
	pset->clear();
	size_t datasize = pointnumber + rectanglenumber;
	pset->reserve(datasize);
	errorcount = 0;
	while(tempstr != "dataend")
	{
		getline(infile,tempstr,'\n');
		if(tempstr == "pointdata:")
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
		else if (tempstr == "rectangledata:")
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
		{
			++errorcount;
			if(errorcount>100)
			{
				MessageBox(_T("文件格式错误"),_T("错误提示"),MB_ICONERROR|MB_OK);
				return;
			}
		}
	}
	infile.close();
	m_treeshow.setTree(ptree,pset);
	m_treeshow.setBranchState(true);
	m_treeshow.setNodeEdgeShowState(true);
	m_treeshow.setNodeFaceShowState(true);
	m_treeshow.setDataShowState(true);
	m_treeshow.setAssistantObjectShowState(false);
	m_treeshow.setResult(false);
	lbuttonflag = LBUTTONDRAG;
	Invalidate(TRUE);
}

void CRStarTreeView::OnResetPosition()
{
	// TODO: Add your command handler code here
	flagdemoshow = false;
	while(flagdemothread)
	{
		flagdemoshow = false;
	}
	m_treeshow.setDemoShowState(false);
	lbuttonflag = LBUTTONDRAG;
	m_treeshow.ResetPosition();
	Invalidate(TRUE);
}

void CRStarTreeView::OnDisplayOption()
{
	//set current options 
	DisplayOptionDialog dlg;

	flagdemoshow = false;
	while(flagdemothread)
	{
		flagdemoshow = false;
	}
	m_treeshow.setDemoShowState(false);
	lbuttonflag = LBUTTONDRAG;

	dlg.displayDataLayer = m_treeshow.getDataShowState();
	dlg.displayNodeFrame = m_treeshow.getNodeEdgeShowState();
	dlg.displayNodeMask = m_treeshow.getNodeFaceShowState();
	dlg.displayTreeBranch = m_treeshow.getBranchState();
	dlg.isPerspectiveProjection =m_treeshow.getProjectionState();
	dlg.isRStarTree = this->GetDocument()->isRStarTree;
	dlg.m = this->GetDocument()->m;
	dlg.M = this->GetDocument()->M;
	dlg.timeUnit = CRStarTreeView::timeUnit;
	//set new options
	if(dlg.DoModal() == IDOK)
	{
		m_treeshow.setDataShowState(dlg.displayDataLayer?true:false);
		m_treeshow.setBranchState(dlg.displayTreeBranch?true:false);
		m_treeshow.setNodeEdgeShowState(dlg.displayNodeFrame?true:false);
		m_treeshow.setNodeFaceShowState(dlg.displayNodeMask?true:false);
		m_treeshow.setProjectionState(dlg.isPerspectiveProjection?true:false);
		if(this->GetDocument()->isRStarTree != (dlg.isRStarTree?true:false))
		{
			this->GetDocument()->isRStarTree = dlg.isRStarTree?true:false;
			AfxMessageBox(_T("关于树类型的修改将在下一次建树的时候生效"));
		}
		this->GetDocument()->m = dlg.m;
		this->GetDocument()->M = dlg.M;
		CRStarTreeView::timeUnit = dlg.timeUnit;
	}
	m_treeshow.demoSetAssistantObjectHeight(0);
}

void CRStarTreeView::OnTestBuildTreeFromFile()
{	


}

void CRStarTreeView::OnRangeSearch()
{
	// TODO: Add your command handler code here
	if(this->GetDocument()->rtree == NULL)
	{
		MessageBox(_T("当前R树为空，不能查询，请输入数据再试。"),_T("错误操作提示"),MB_OK);
		return;
	}
	flagdemoshow = false;
	while(flagdemothread)
	{
		flagdemoshow = false;
	}
	m_treeshow.setDemoShowState(false);
	lbuttonflag = LBUTTONRANGESEARCH;
	m_treeshow.ResetPosition();
	m_treeshow.setProjectionState(false);
	m_treeshow.setAssistantObject((AssistantObject *)(&m_aorectangle));
	m_treeshow.setAssistantObjectShowState(true);
	m_treeshow.setBranchState(false);
	m_treeshow.setNodeEdgeShowState(false);
	m_treeshow.setDataShowState(true);
	m_treeshow.setNodeFaceShowState(false);
	m_treeshow.setResultState(true);
	m_treeshow.setDataShowState(true);
	Invalidate(TRUE);
}

void CRStarTreeView::OnMouseDrag()
{
	// TODO: Add your command handler code here
	flagdemoshow = false;
	while(flagdemothread)
	{
		flagdemoshow = false;
	}
	lbuttonflag = LBUTTONDRAG;
}

void CRStarTreeView::OnRangeLocation()
{
	// TODO: Add your command handler code here
	if(this->GetDocument()->rtree == NULL)
	{
		MessageBox(_T("当前R树为空，不能定位，请输入数据再试。"),_T("错误操作提示"),MB_OK);
		return;
	}
	flagdemoshow = false;
	while(flagdemothread)
	{
		flagdemoshow = false;
	}
	m_treeshow.setDemoShowState(false);
	lbuttonflag = LBUTTONRANGELOCATION;
	m_treeshow.ResetPosition();
	m_treeshow.setProjectionState(false);
	m_treeshow.setAssistantObject((AssistantObject *)(&m_aorectangle));
	m_treeshow.setAssistantObjectShowState(true);
	m_treeshow.setBranchState(false);
	m_treeshow.setNodeEdgeShowState(false);
	m_treeshow.setDataShowState(true);
	m_treeshow.setNodeFaceShowState(false);
	m_treeshow.setResultState(true);
	Invalidate(TRUE);
}

UINT CRStarTreeView::demothread(LPVOID param)
{
	CRStarTreeView* p = (CRStarTreeView*)param;
	p->flagdemothread = true;
	int treeHeight = p->GetDocument()->rtree->height;
	/*p->m_treeshow.demoXRotate(-1.57);
	p->m_treeshow.demoMove(0,0,-0.5);
	while(p->flagdemoshow)
	{
		for(int i=0;i<=treeheight;++i)
		{
			p->m_treeshow.setDemoCurrentLayer(i);
			for(int j=0;j<40;++j)
			{
				p->m_treeshow.demoZRotate(0.1);
				p->m_treeshow.demoMove(0,0,1.0/(double)treeheight/80.0);
				p->Invalidate(TRUE);
				Sleep(25);
			}
		}
		p->m_treeshow.setDemoCurrentLayer(treeheight+1);
		p->m_treeshow.setResultState(true);
		p->Invalidate(TRUE);
		for(int i=0;i<40;++i)
		{
			p->m_treeshow.demoZRotate(0.1);
			p->m_treeshow.demoXRotate(1.57/40.0);
			p->Invalidate(TRUE);
			Sleep(25);
		}
		break;
	}*/



	//time definition
	long TIME_UNIT = CRStarTreeView::timeUnit;
	
	long  inclineTimes = 500;
	long fullAroundTimes = 1000;
	long  upTimes = 500;
	long downTimes = 500;

	//get percentage
	double percentagePerMoveUp = (1.0/treeHeight)/500;
	double percentagePerMoveDown = -((0.5+1.0/treeHeight)/500);

	//angle definition 
	
	double zFullAroundAngleOnce = (2.0*PI)/fullAroundTimes;
	double inclineAnglePerOnceForward = (PI/12.0)/inclineTimes;
	double inclineAnglePerOnceBackward = -inclineAnglePerOnceForward;
	
	
	//
	double xMove = 0.0;
	double yMove = 0.0;
	 
	//assistantobjectheightrate
	double aoht = 1.0;

	//get to the right position
	p->m_treeshow.ResetPosition();
	p->m_treeshow.demoXRotate(-PI/2.0);

	int numOfLayers = treeHeight+1;
	int layerIndex =1;

	//move down
	p->m_treeshow.demoMove
		(xMove,yMove,-0.5);
	p->m_treeshow.demoSetAssistantObjectHeight(aoht);

	//begin loop 
	do{
		//set layer,display the current tree edges and eliminate the upper

		p->m_treeshow.setDemoCurrentLayer(layerIndex);
		//incline forward
		for(int i=0;i<inclineTimes;i++){
			p->m_treeshow.demoXRotate(inclineAnglePerOnceForward);
			p->Invalidate(TRUE);
			Sleep(TIME_UNIT);
			if(p->flagdemoshow==false)
			{
				p->flagdemothread = false;
				return 0;
			}
		}
		//rotate full around 
		for(int i=0;i<fullAroundTimes;i++){
		
			p->m_treeshow.demoZRotate(zFullAroundAngleOnce);
			p->Invalidate(TRUE);
			Sleep(TIME_UNIT);
			if(p->flagdemoshow==false)
			{
				p->flagdemothread = false;
				return 0;
			}
		}

		//incline backward
		for(int i=0;i<inclineTimes;i++){
			p->m_treeshow.demoXRotate(inclineAnglePerOnceBackward);
			p->Invalidate(TRUE);
			Sleep(TIME_UNIT);
			if(p->flagdemoshow==false)
			{
				p->flagdemothread = false;
				return 0;
			}
		}


		//move up
		for(int i=0;i<upTimes;i++){
			p->m_treeshow.demoMove(xMove,yMove,percentagePerMoveUp);
			aoht -= percentagePerMoveUp;
			aoht = aoht<0?0:aoht;
			p->m_treeshow.demoSetAssistantObjectHeight(aoht);
			p->Invalidate(TRUE);
			Sleep(TIME_UNIT);
			if(p->flagdemoshow==false)
			{
				p->flagdemothread = false;
				return 0;
			}
		}

		//display the next layer
		layerIndex++;
	
	}while(layerIndex<=numOfLayers);


	//post 

	//Move down and incline forward
	
	for(int i=0;i<downTimes;i++){	
		p->m_treeshow.demoMove(xMove,yMove,percentagePerMoveDown);
		p->Invalidate(TRUE);
		Sleep(TIME_UNIT);
		if(p->flagdemoshow==false)
		{
			p->flagdemothread = false;
			return 0;
		}
	}
	for(int i=0;i<inclineTimes;i++){
		p->m_treeshow.demoXRotate(inclineAnglePerOnceForward);
		p->Invalidate(TRUE);
		Sleep(TIME_UNIT);
		if(p->flagdemoshow==false)
		{
			p->flagdemothread = false;
			return 0;
		}
	}
	for(int i=0;i<inclineTimes;i++){
		p->m_treeshow.demoXRotate(inclineAnglePerOnceForward);
		p->Invalidate(TRUE);
		Sleep(TIME_UNIT);
		if(p->flagdemoshow==false)
		{
			p->flagdemothread = false;
			return 0;
		}
	}
		




	p->m_treeshow.setResultState(true);
	p->m_treeshow.setProjectionState(true);
	p->Invalidate(TRUE);

	p->flagdemothread = false;
	return 0;
}

void CRStarTreeView::OnDemoShow()
{
	// TODO: Add your command handler code here
	if(this->GetDocument()->rtree == NULL)
	{
		MessageBox(_T("当前R树为空，不能演示，请输入数据再试。"),_T("错误操作提示"),MB_OK);
		return;
	}
	if(lbuttonflag != LBUTTONRANGESEARCH)
	{
		MessageBox(_T("请先些换到\"区域查询\"状态"),_T("错误操作提示"),MB_OK);
		return;
	}
	if(flagdemoshow)
	{
		AfxMessageBox(_T("演示正在进行"));
		return;
	}
	else
	{
		if(m_treeshow.setDemoShowState(true))
		{
			flagdemoshow = true;
			m_treeshow.ResetPosition();
			m_treeshow.setDemoShowState(true);
			m_treeshow.setResultState(false);
			m_treeshow.setAssistantObjectShowState(true);
			m_treeshow.setProjectionState(true);
			m_treeshow.setDataShowState(true);
			AfxBeginThread(demothread,this);
			lbuttonflag = LBUTTONDISABLE;
		}
		else
		{
			AfxMessageBox(_T("演示条件不足：\n\r1-数据不为空\n\r2-有查询框"));
			m_treeshow.setTree(this->GetDocument()->rtree,&(this->GetDocument()->dateset));
		}
	}
}

void CRStarTreeView::OnAddData()
{
	// TODO: Add your command handler code here
	flagdemoshow = false;
	while(flagdemothread)
	{
		flagdemoshow = false;
	}
	m_treeshow.setDemoShowState(false);
	lbuttonflag = LBUTTONADDDATA;
	m_treeshow.ResetPosition();
	m_treeshow.setProjectionState(false);
	m_treeshow.setAssistantObject((AssistantObject *)(&m_aorectangle));
	m_treeshow.setAssistantObjectShowState(true);
	m_treeshow.setBranchState(false);
	m_treeshow.setNodeEdgeShowState(false);
	m_treeshow.setDataShowState(true);
	m_treeshow.setNodeFaceShowState(false);
	m_treeshow.setResultState(false);
	m_treeshow.setDataShowState(true);
	Invalidate(TRUE);
}

void CRStarTreeView::OnFileSave()
{
	// TODO: Add your command handler code here
	if(this->GetDocument()->rtree == NULL)
	{
		MessageBox(_T("当前R树为空，不能保存"),_T("错误操作提示"),MB_OK);
		return;
	}
	flagdemoshow = false;
	while(flagdemothread)
	{
		flagdemoshow = false;
	}
	m_treeshow.setDemoShowState(false);
	CFileDialog mydlg(false,_T("*.txt"),_T("*.txt"),NULL,_T("(*.txt)|*.txt||"),this,NULL);
	if(mydlg.DoModal()!=IDOK)
		return;
	std::wstring filename = mydlg.GetPathName();
	std::ofstream outfile(filename.c_str());
	outfile<<"testdata2d"<<std::endl;
	vector<RSTNode*> pointset;
	vector<RSTNode*> rectangleset;
	vector<double> tempvec;
	vector<RSTNode*> *pdata = &(this->GetDocument()->dateset);
	pointset.reserve(pdata->size());
	rectangleset.reserve(pdata->size());
	pointset.clear();
	rectangleset.clear();
	for(size_t i=0;i<pdata->size();++i)
	{
		if((*pdata)[i] == NULL)
			continue;
		if( (*pdata)[i]->GetDataType() == RSTPOINT2D)
			pointset.push_back((*pdata)[i]);
		else if((*pdata)[i]->GetDataType() == RSTRECTANGLE2D)
			rectangleset.push_back((*pdata)[i]);
		else;
	}
	if(!(pointset.empty()))
		outfile<<"pointnumber:"<<std::endl<<pointset.size()<<std::endl;
	if(!(rectangleset.empty()))
		outfile<<"rectanglenumber:"<<std::endl<<rectangleset.size()<<std::endl;
	outfile<<"databegin"<<std::endl;
	if(!(pointset.empty()))
		outfile<<"pointdata:"<<std::endl;
	for(size_t i=0;i<pointset.size();++i)
		pointset[i]->OutPutData(outfile);
	if(!(rectangleset.empty()))
		outfile<<"rectangledata:"<<std::endl;
	for(size_t i=0;i<rectangleset.size();++i)
		rectangleset[i]->OutPutData(outfile);
	outfile<<"dataend"<<std::endl;
	outfile.close();
}

void CRStarTreeView::OnDelete()
{
	// TODO: Add your command handler code here
	if(this->GetDocument()->rtree == NULL)
	{
		MessageBox(_T("当前R树为空，能删除"),_T("错误操作提示"),MB_OK);
		return;
	}
	flagdemoshow = false;
	while(flagdemothread)
	{
		flagdemoshow = false;
	}
	m_treeshow.setDemoShowState(false);
	lbuttonflag = LBUTTONDELETE;
	m_treeshow.ResetPosition();
	m_treeshow.setProjectionState(false);
	m_treeshow.setAssistantObject((AssistantObject *)(&m_aorectangle));
	m_treeshow.setAssistantObjectShowState(true);
	m_treeshow.setBranchState(false);
	m_treeshow.setNodeEdgeShowState(false);
	m_treeshow.setDataShowState(true);
	m_treeshow.setNodeFaceShowState(false);
	m_treeshow.setResultState(false);
	Invalidate(TRUE);
}

void CRStarTreeView::OnPrintTree()
{
	
	using std::ofstream;
	using std::deque;
	using std::endl;

	ofstream out("treeData.txt");
	deque<RSTNode*> que;
	que.push_back(this->GetDocument()->rtree->Root);
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
	out.close();
	
}

void CRStarTreeView::OnShowEverything()
{
	// TODO: Add your command handler code here
	flagdemoshow = false;
	while(flagdemothread)
	{
		flagdemoshow = false;
	}
	m_treeshow.setDemoShowState(false);
	m_treeshow.setBranchState(true);
	m_treeshow.setNodeEdgeShowState(true);
	m_treeshow.setDataShowState(true);
	m_treeshow.setNodeFaceShowState(true);
	m_treeshow.setAssistantObjectShowState(false);
	m_treeshow.setResultState(false);
	lbuttonflag = LBUTTONDRAG;
	Invalidate(TRUE);
}

void CRStarTreeView::OnEndDemo()
{
	// TODO: Add your command handler code here
	flagdemoshow = false;
	while(flagdemothread)
	{
		flagdemoshow = false;
	}
}
