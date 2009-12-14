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
	bool zfront;
	vector<RSTNode*> m_node;
	vector<int> m_layer;
	vector<double> m_branch;
	vector<RSTNode*> *m_dataset;
	bool showstate[4];

public:
	Tree2DShow3D():m_tree(NULL),rangeperlayer(0),zfront(true),m_dataset(NULL){};
	~Tree2DShow3D(){m_tree = NULL;m_dataset = NULL;}

	void drawTree();

	void setTree(const RSTRTree* p1,vector<RSTNode*> *p2){setTree(p1);setData(p2);}
	void setTree(const RSTRTree* p){m_tree = p;updateTreeDate();}
	void setData(vector<RSTNode*> *p){m_dataset = p;}

	void setDataShowState(const bool &state){showstate[0] = state;}
	void setBranchState(const bool &state){showstate[1] = state;}
	void setNodeEdgeShowState(const bool &state){showstate[2] = state;}
	void setNodeFaceShowState(const bool &state){showstate[3] = state;}

	void Initialization(CClientDC &dc)
	{m_gls3d.Initialization(dc);for(int i=0;i<4;++i) showstate[i] = true;}
	void Destroy(){m_gls3d.Destroy();}
	void ReSize(CClientDC &dc,int cx,int cy){m_gls3d.ReSize(dc,cx,cy);}
	void AdjustZoomRate(const double& rate){m_gls3d.AdjustZoomRate(rate);}
	void Translation(const int &cx,const int &cy,const bool &flagsave)
	{m_gls3d.Translation(cx,cy,flagsave);}
	void Rotation(const int &cx,const int &cy,const double angle,const bool &flagsave)
	{m_gls3d.Rotation(cx,cy,angle,flagsave);}
	void ResetPosition(){m_gls3d.ResetPosition();}

	void BeginDraw(HDC& m_hdc){m_gls3d.BeginDraw(m_hdc);}
	void EndDraw(HDC& m_hdc){m_gls3d.EndDraw(m_hdc);}

private:
	void drawData();
	void drawRectangle();
	void fillRectangle();
	void drawBranch();
	void setzup();
	void setDrawItem();
	bool updateTreeDate();
};




#endif
