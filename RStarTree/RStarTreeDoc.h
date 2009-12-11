// RStarTreeDoc.h : interface of the CRStarTreeDoc class
//


#pragma once
#include <fstream>
#include "RSTRTree.h"

class CRStarTreeDoc : public CDocument
{
protected: // create from serialization only
	CRStarTreeDoc();
	DECLARE_DYNCREATE(CRStarTreeDoc)

// Attributes
public:

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

