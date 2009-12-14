#include "stdafx.h"
#include "RStarTree2DShow3D.h"

void Tree2DShow3D::drawTree()
{
	if(m_tree == NULL)
		return;
	drawRectangle();
	fillRectangle();
}

void Tree2DShow3D::fillRectangle()
{
	glDepthMask(GL_FALSE);
	glColor4f(1,1,1,0.3f);
	glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
	if(zup)
	{
		for(size_t i=m_node.size()-1;i>=0;--i)
		{
			glBegin(GL_POLYGON);
			glVertex3d(m_node[i]->range[0].min,m_node[i]->range[1].min,
				rangeperlayer*m_layer[i]);
			glVertex3d(m_node[i]->range[0].min,m_node[i]->range[1].max,
				rangeperlayer*m_layer[i]);
			glVertex3d(m_node[i]->range[0].max,m_node[i]->range[1].max,
				rangeperlayer*m_layer[i]);
			glVertex3d(m_node[i]->range[0].max,m_node[i]->range[1].min,
				rangeperlayer*m_layer[i]);
			glEnd();
		}
	}
	else
	{
		for(size_t i=0;i<m_node.size();++i)
		{
			glBegin(GL_POLYGON);
			glVertex3d(m_node[i]->range[0].min,m_node[i]->range[1].min,
				rangeperlayer*m_layer[i]);
			glVertex3d(m_node[i]->range[0].min,m_node[i]->range[1].max,
				rangeperlayer*m_layer[i]);
			glVertex3d(m_node[i]->range[0].max,m_node[i]->range[1].max,
				rangeperlayer*m_layer[i]);
			glVertex3d(m_node[i]->range[0].max,m_node[i]->range[1].min,
				rangeperlayer*m_layer[i]);
			glEnd();
		}
	}
}


void Tree2DShow3D::drawRectangle()
{
	glDepthMask(GL_TRUE);
	size_t value;
	glLineWidth(3);
	for(size_t i=0;i<m_node.size();++i)
	{
		value = m_layer[i]%3;
		if(value==0)
			glColor4f(0,1,0,0.5f);
		else if(value==1)
			glColor4f(1,0,0,0.5f);
		else
			glColor4f(0,0,1,0.5f);
		glBegin(GL_LINE_LOOP);
		glVertex3d(m_node[i]->range[0].min,m_node[i]->range[1].min,
				rangeperlayer*m_layer[i]);
		glVertex3d(m_node[i]->range[0].min,m_node[i]->range[1].max,
			rangeperlayer*m_layer[i]);
		glVertex3d(m_node[i]->range[0].max,m_node[i]->range[1].max,
			rangeperlayer*m_layer[i]);
		glVertex3d(m_node[i]->range[0].max,m_node[i]->range[1].min,
			rangeperlayer*m_layer[i]);
		glEnd();
	}
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
	if(m_tree->M<2)
		return false;
	double range[2];
	range[0] = m_tree->Root->range[0].max - m_tree->Root->range[0].min;
	range[1] = m_tree->Root->range[1].max - m_tree->Root->range[1].min;
	if(range[0]<range[1])
		range[0] = range[1];
	rangeperlayer = range[0]/m_tree->height;
	m_gls3d.UpdateParameter(m_tree->Root->range[0].min,m_tree->Root->range[0].max,
		m_tree->Root->range[1].min,m_tree->Root->range[1].max,0,range[0]);
	setDrawItem();
	return true;
}

void Tree2DShow3D::setDrawItem()
{
	m_node.clear();
	m_layer.clear();
	size_t tempsize = (int(pow(double(m_tree->M),m_tree->height))-1) / (m_tree->M - 1);
	m_node.reserve(tempsize);
	m_layer.reserve(tempsize);
	vector<RSTNode*> vec1;
	vector<RSTNode*> vec2;
	vec1.reserve(int(pow(double(m_tree->M),m_tree->height)));
	vec2.reserve(int(pow(double(m_tree->M),m_tree->height)));
	vector<RSTNode*> *pc = &vec1;
	vector<RSTNode*> *pn = &vec2;
	vector<RSTNode*> *tempp = NULL;
	int layernumber = m_tree->height;
	pc->push_back(m_tree->Root);
	while(layernumber>0)
	{
		for(size_t i=0;i<pc->size();++i)
		{
			m_node.push_back((*pc)[i]);
			m_layer.push_back(layernumber);
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

void Tree2DShow3D::setzup()
{
	double* p = m_gls3d.GetCurrentModelViewMatrix();
	if(p[10]>0)
		zup = true;
	else
		zup = false;
}