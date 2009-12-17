// RStarTreeDoc.cpp : implementation of the CRStarTreeDoc class
//

#include "stdafx.h"
#include "RStarTree.h"

#include "RStarTreeDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CRStarTreeDoc

IMPLEMENT_DYNCREATE(CRStarTreeDoc, CDocument)

BEGIN_MESSAGE_MAP(CRStarTreeDoc, CDocument)
END_MESSAGE_MAP()


// CRStarTreeDoc construction/destruction

CRStarTreeDoc::CRStarTreeDoc()
{
	// TODO: add one-time construction code here
	/*rtree = new RSTRTree(DEFAULT_DIMENTION, DEFAULT_LITTLE_M, DEFALUT_BIG_M);*/
	this->rtree = NULL;
#ifdef TEST
	flag = DrawPoint;
#endif
}

CRStarTreeDoc::~CRStarTreeDoc()
{
	delete rtree;
}

BOOL CRStarTreeDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}




// CRStarTreeDoc serialization

void CRStarTreeDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}


// CRStarTreeDoc diagnostics

#ifdef _DEBUG
void CRStarTreeDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CRStarTreeDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CRStarTreeDoc commands
