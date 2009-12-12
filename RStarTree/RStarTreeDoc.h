// RStarTreeDoc.h : interface of the CRStarTreeDoc class
//


#pragma once
#include <fstream>
#include "RSTRTree.h"
#include "RSTTestData.h"

#ifdef TEST
#define RectFlag 1000
#define DrawPoint 1001
#define Drag 1002
#endif

class CRStarTreeDoc : public CDocument
{
protected: // create from serialization only
	CRStarTreeDoc();
	DECLARE_DYNCREATE(CRStarTreeDoc)

// Attributes
public:
	RSTRTree* rtree;
#ifdef TEST
	RSTPoint2D start;
	RSTPoint2D end;
	RSTPoint2D dragPoint;
	RSTNodeSet result;
	int flag;
#endif

// Operations
public:

// Overrides
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);

// Implementation
public:
	virtual ~CRStarTreeDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
};


