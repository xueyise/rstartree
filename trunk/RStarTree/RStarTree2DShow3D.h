#ifndef RSTARTREE_2D_SHOW_3D_H
#define RSTARTREE_2D_SHOW_3D_H

#include "stdafx.h"
#include "myglshow3d.h"
#include "RSTDefine.h"
#include "RSTRTree.h"

class Tree2DShow3D
{
private:
	MyGLShow3D m_gls3d;
	const RSTRTree* m_tree;
	double rangeperlayer;
	bool zup;
	vector<RSTNode*> m_node;
	vector<int> m_layer;

public:
	Tree2DShow3D():m_tree(NULL),rangeperlayer(0),zup(false){}
	~Tree2DShow3D(){m_tree = NULL;}

	void drawTree();
	void drawDate(const RSTNode* p);

	void settree(const RSTRTree* p){m_tree = p;updateTreeDate();}

	void Initialization(CClientDC &dc){m_gls3d.Initialization(dc);}
	void Destroy(){m_gls3d.Destroy();}
	void ReSize(CClientDC &dc,int cx,int cy){m_gls3d.ReSize(dc,cx,cy);}
	void AdjustZoomRate(const double& rate){m_gls3d.AdjustZoomRate(rate);}
	void Translation(const int &cx,const int &cy,const bool &flagsave)
	{m_gls3d.Translation(cx,cy,flagsave);}
	void Rotation(const int &cx,const int &cy,const double angle,const bool &flagsave)
	{m_gls3d.Rotation(cx,cy,angle,flagsave);}

	void BeginDraw(HDC& m_hdc){m_gls3d.BeginDraw(m_hdc);}
	void EndDraw(HDC& m_hdc){m_gls3d.EndDraw(m_hdc);}

private:
	void drawRectangle();
	void fillRectangle();
	void setzup();
	void setDrawItem();
	bool updateTreeDate();
};


#endif
