// RStarTreeView.h : interface of the CRStarTreeView class
//


#pragma once
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
};

#ifndef _DEBUG  // debug version in RStarTreeView.cpp
inline CRStarTreeDoc* CRStarTreeView::GetDocument() const
   { return reinterpret_cast<CRStarTreeDoc*>(m_pDocument); }
#endif

