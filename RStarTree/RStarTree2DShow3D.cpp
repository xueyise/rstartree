#include "stdafx.h"
#include "RStarTree2DShow3D.h"

void Tree2DShow3D::drawTree()
{
	if(!updateTreeDate())
		return;
	vector<RSTNode*> vec1;
	vector<RSTNode*> vec2;
	vec1.reserve(m_tree->height*m_tree->M);
	vec2.reserve(m_tree->height*m_tree->M);
	vector<RSTNode*> *pc = &vec1;
	vector<RSTNode*> *pn = &vec2;
	vector<RSTNode*> *tempp = NULL;
	int layernumber = m_tree->height;
	pc->push_back(m_tree->Root);
	while(layernumber>0)
	{
		for(size_t i=0;i<pc->size();++i)
		{
			drawNode((*pc)[i],layernumber);
			if( ((*pc)[i]->type) != Leaf)
			{
				for(int j=0;j<(*pc)[i]->childNum;++j)
					pn->push_back((*pc)[i]->childSet[j]);
			}
		}
		pc->clear();
		tempp = pc;
		pc = pn;
		pn = tempp;
		--layernumber;
	}
}

void Tree2DShow3D::drawNode(const RSTNode* p,const int &layernumber)
{
	int value = layernumber%3;
	if(value==0)
		glColor4f(0,1,0,0.5f);
	else if(value==1)
		glColor4f(1,0,0,0.5f);
	else
		glColor4f(0,0,1,0.5f);
	glBegin(GL_POLYGON);
	glVertex3d(p->range[0].min,p->range[1].min,layernumber*rangeperlayer);
	glVertex3d(p->range[0].min,p->range[1].max,layernumber*rangeperlayer);
	glVertex3d(p->range[0].max,p->range[1].max,layernumber*rangeperlayer);
	glVertex3d(p->range[0].max,p->range[1].min,layernumber*rangeperlayer);
	glEnd();
}

void Tree2DShow3D::drawDate(const RSTNode* p)
{
}

bool Tree2DShow3D::updateTreeDate()
{
	if(m_tree == NULL)
		return false;
	if(m_tree->dim != 2)
		return false;
	if(m_tree->height<1)
		return false;
	double range[2];
	range[0] = m_tree->Root->range[0].max - m_tree->Root->range[0].min;
	range[1] = m_tree->Root->range[1].max - m_tree->Root->range[1].min;
	if(range[0]<range[1])
		range[0] = range[1];
	rangeperlayer = range[0]/m_tree->height;
	m_gls3d.UpdataParameter(m_tree->Root->range[0].min,m_tree->Root->range[0].max,
		m_tree->Root->range[1].min,m_tree->Root->range[1].max,0,range[0]);
	return true;
}

void Tree2DShow3D::setzup()
{
	double* p = m_gls3d.GetCurrentModelViewMatrix();
	if(p[10]>0)
		zup = true;
	else
		zup = false;
}