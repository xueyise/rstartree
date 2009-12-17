// RStarTreeView.h : interface of the CRStarTreeView class
//


#pragma once
#include "RStarTree2DShow3D.h"
#include "DisplayOptionDialog.h"

#ifdef TEST
	#include <vector>
	#include "RSTDefine.h"
	#include "RSTRTree.h"
	#include "RSTTestData.h"
#endif


class CRStarTreeView : public CView
{
protected: // create from serialization only
	CRStarTreeView();
	DECLARE_DYNCREATE(CRStarTreeView)

// Attributes
public:
	CRStarTreeDoc* GetDocument() const;
#ifdef TEST
	std::vector<RSTPoint2D*> pointSet;
#endif
	

// Operations
public:

// Overrides
public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// Implementation
public:
	virtual ~CRStarTreeView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnTestBuildTree();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnTestrangesearch();
	afx_msg void OnAddpoint();
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
protected:
	Tree2DShow3D m_treeshow;
	RSTRange m_range;
	CPoint beginpoint;
	CPoint endpoint;
	int lbuttonflag;
	bool flagdraging;
	AOPoint m_aopoint;
	AORectangle m_aorectangle;
	static const int LBUTTONDRAG = 0;
	static const int LBUTTONRANGESEARCH = 1;
	static const int LBUTTONRANGELOCATION = 2;
	static const int LBUTTONPOINTLOCATION = 3;
	static const int LBUTTONDISABLE = 4;
	static const int LBUTTONADDDATA = 5;
public:
	afx_msg void OnDestroy();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
	afx_msg void OnFileOpen();
	afx_msg void OnResetPosition();
	afx_msg void OnDisplayOption();
	afx_msg void OnRangeSearch();
	afx_msg void OnMouseDrag();
	afx_msg void OnTestBuildTreeFromFile();
	afx_msg void OnRangeLocation();
	afx_msg void OnDemoShow();
	static UINT demothread(LPVOID param);
	bool flagdemoshow;
	afx_msg void OnAddData();
};

#ifndef _DEBUG  // debug version in RStarTreeView.cpp
inline CRStarTreeDoc* CRStarTreeView::GetDocument() const
   { return reinterpret_cast<CRStarTreeDoc*>(m_pDocument); }
#endif

