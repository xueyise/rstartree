#ifndef RSTARTREE_2D_SHOW_3D_H
#define RSTARTREE_2D_SHOW_3D_H

#include "stdafx.h"
#include "myglshow3d.h"
#include "RSTDefine.h"
#include "RSTRTree.h"

class AssistantObject;

class Tree2DShow3D
{
private:
	MyGLShow3D m_gls3d;
	const RSTRTree* m_tree;
	double rangeperlayer;
	bool zfront;
	vector<RSTNode*> m_node;
	vector<bool> flagnode;
	vector<int> m_layer;
	vector<double> m_branch;
	vector<bool> flagbranch;
	vector<int> branchlayer;
	vector<RSTNode*> *m_dataset;
	vector<RSTNode*> *m_result;
	AssistantObject* m_ao;
	bool showstate[6];
	bool demoshow;
	int democurrentlayer;

public:
	Tree2DShow3D():m_tree(NULL),rangeperlayer(0),zfront(true),m_dataset(NULL),
		m_ao(NULL),m_result(NULL),demoshow(false),democurrentlayer(1){};
	~Tree2DShow3D(){m_tree = NULL;m_dataset = NULL;}

	void drawTree();

	void setTree(const RSTRTree* p1,vector<RSTNode*> *p2){setTree(p1);setData(p2);}
	void setTree(const RSTRTree* p){m_tree = p;updateTreeData();}
	void setData(vector<RSTNode*> *p){m_dataset = p;}
	void setResult(vector<RSTNode*> *p){m_result = p;}

	void setDataShowState(const bool &state){showstate[0] = state;}
	void setBranchState(const bool &state){showstate[1] = state;}
	void setNodeEdgeShowState(const bool &state){showstate[2] = state;}
	void setNodeFaceShowState(const bool &state){showstate[3] = state;}
	void setAssistantObjectShowState(const bool &state){showstate[4] = state;}
	void setResultState(const bool &state){showstate[5] = state;}
	void setPorjectionState(const bool &state){m_gls3d.SetProjectionMethod(state);}
	bool setDemoShowState(const bool &state);
	void setDemoCurrentLayer(const int &layer){democurrentlayer = layer;}

	bool getDataShowState()const{return showstate[0];}
	bool getBranchState()const{return showstate[1];}
	bool getNodeEdgeShowState()const{return showstate[2];}
	bool getNodeFaceShowState()const{return showstate[3];}
	bool getAssistantObjectShowState()const{return showstate[4];}
	bool getPorjectionState()const{return m_gls3d.GetProjectionMethod();}
	bool getDemoShowState()const{return showstate[5];}

	void setAssistantObject(AssistantObject* p){m_ao = p;}

	void get2DCoordinateFromSCreenToWorld(const int &sx,const int &sy,double &wx,double &wy);

	void Initialization(CClientDC &dc)
	{m_gls3d.Initialization(dc);for(int i=0;i<4;++i) showstate[i] = true;showstate[4]=false;
	showstate[5] = false;}
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

	void demoXRotate(const double &angle){if(demoshow)m_gls3d.Rotation(angle,1,0,0,true);}
	void demoYRotate(const double &angle){if(demoshow)m_gls3d.Rotation(angle,0,1,0,true);}
	void demoZRotate(const double &angle){if(demoshow)m_gls3d.Rotation(angle,0,0,1,true);}
	void demoMove(const double &x,const double &y,const double &z);
	void demoZoom(const double &rate){if(demoshow)m_gls3d.AdjustZoomRate(rate);}

private:
	void drawResult();
	void drawAssistantObject();
	void drawData();
	void drawRectangle();
	void fillRectangle();
	void drawBranch();
	void setzup();
	void setDrawItem();
	bool updateTreeData();
	void setDemoItem();
	void drawDemoRectangle();
	void fillDemoRectangle();
	void drawDemoBranch();
};

class AssistantObject
{
public:
	virtual void draw(){}
	virtual void getrange(double &x1,double&x2,double &y1,double &y2)const{}
};

class AOPoint:AssistantObject
{
public:
	double x;
	double y;
	double z;

	void getrange(double &x1,double&x2,double &y1,double &y2)const
	{x1 = x; x2 = x; y1 = y; y2 = y;}
	void draw();
};

class AORectangle:AssistantObject
{
public:
	double left;
	double bottom;
	double right;
	double top;
	double z;

	void adjustRange();
	void getrange(double &x1,double&x2,double &y1,double &y2)const
	{x1 = left; x2 = right; y1 = bottom; y2 = top;}
	void draw();
};




#endif
