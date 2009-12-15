#include "stdafx.h"
#include "RStarTree2DShow3D.h"

void Tree2DShow3D::drawTree()
{
	if(m_tree == NULL)
		return;
	drawResult();
	if(showstate[0])
		drawData();
	if(showstate[1])
		drawBranch();
	if(showstate[2])
		drawRectangle();
	if(showstate[4])
		drawAssistantObject();
	if(showstate[3])
		fillRectangle();
}

void Tree2DShow3D::fillRectangle()
{
	glDepthMask(GL_FALSE);
	glColor4f(1,1,1,0.3f);
	glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
	if(zfront)
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
			if(i==0)
				break;
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

void Tree2DShow3D::drawBranch()
{
	glDepthMask(GL_TRUE);
	glLineWidth(2);
	glColor4f(1,1,0,1);
	glBegin(GL_LINES);
	for(size_t i=0;i<m_branch.size();i+=6)
	{
		glVertex3d(m_branch[i],m_branch[i+1],m_branch[i+2]);
		glVertex3d(m_branch[i+3],m_branch[i+4],m_branch[i+5]);
	}
	glEnd();
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
			glColor4f(0,1,0,1);
		else if(value==1)
			glColor4f(1,0,0,1);
		else
			glColor4f(0,0,1,1);
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

void Tree2DShow3D::drawData()
{
	if(m_dataset == NULL)
		return;
	vector<double> vec;
	glDepthMask(GL_TRUE);
	glColor4f(0.5f,0.25f,1.0f,1);
	glPointSize(10);
	glLineWidth(1);
	for(size_t i=0;i<m_dataset->size();++i)
	{
		(*m_dataset)[i]->GetDataPoints(vec);
		if(vec.size() == 2)
		{
			glBegin(GL_POINTS);
			glVertex3d(vec[0],vec[1],0);
			glEnd();
		}
		else
		{
			glBegin(GL_LINE_LOOP);
			for(size_t j=0;j<vec.size();j+=2)
			{
				glVertex3d(vec[j],vec[j+1],0);
			}
			glEnd();
		}
	}
}

void Tree2DShow3D::drawResult()
{
	if(m_result == NULL)
		return;
	vector<double> vec;
	glDepthMask(GL_TRUE);
	glColor4f(1.0f,1.0f,0.5f,1);
	glPointSize(10);
	glLineWidth(1);
	for(size_t i=0;i<m_result->size();++i)
	{
		(*m_result)[i]->GetDataPoints(vec);
		if(vec.size() == 2)
		{
			glBegin(GL_POINTS);
			glVertex3d(vec[0],vec[1],0);
			glEnd();
		}
		else
		{
			glBegin(GL_LINE_LOOP);
			for(size_t j=0;j<vec.size();j+=2)
			{
				glVertex3d(vec[j],vec[j+1],0);
			}
			glEnd();
		}
	}
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
	m_branch.clear();
	size_t sizevalue1 = size_t(pow(double(m_tree->M),m_tree->height));
	size_t sizevalue2 = (sizevalue1 -1) / (m_tree->M - 1);
	m_node.reserve(sizevalue2);
	m_layer.reserve(sizevalue2);
	m_branch.reserve(sizevalue2 * (m_tree->M) *3);
	vector<RSTNode*> vec1;
	vector<RSTNode*> vec2;
	vec1.reserve(sizevalue1);
	vec2.reserve(sizevalue1);
	vector<RSTNode*> *pc = &vec1;
	vector<RSTNode*> *pn = &vec2;
	vector<RSTNode*> *tempp = NULL;
	int layernumber = m_tree->height;
	pc->push_back(m_tree->Root);
	double tempx;
	double tempy;
	double tempz;
	while(layernumber>0)
	{
		for(size_t i=0;i<pc->size();++i)
		{
			m_node.push_back((*pc)[i]);
			m_layer.push_back(layernumber);
			tempx = ((*pc)[i]->range[0].min + (*pc)[i]->range[0].max)*0.5;
			tempy = ((*pc)[i]->range[1].min + (*pc)[i]->range[1].max)*0.5;
			tempz = layernumber * rangeperlayer;
			if( ((*pc)[i]->type) != Data)
			{
				for(int j=0;j<(*pc)[i]->childNum;++j)
				{
					pn->push_back((*pc)[i]->childSet[j]);
					m_branch.push_back(tempx);
					m_branch.push_back(tempy);
					m_branch.push_back(tempz);
					m_branch.push_back((pn->back()->range[0].max+pn->back()->range[0].min)*0.5);
					m_branch.push_back((pn->back()->range[1].max+pn->back()->range[1].min)*0.5);
					m_branch.push_back(rangeperlayer*(layernumber-1));
				}
			}
		}
		pc->clear();
		tempp = pc;
		pc = pn;
		pn = tempp;
		--layernumber;
	}
}

void Tree2DShow3D::drawAssistantObject()
{
	glDepthMask(GL_TRUE);
	if(m_ao!=NULL)
		m_ao->draw();
}

void Tree2DShow3D::get2DCoordinateFromSCreenToWorld(const int &sx,const int &sy,
													double &wx,double &wy)
{
	int screen[2];
	double oc[3];
	m_gls3d.GetCanvasRange(screen[0],screen[1]);
	m_gls3d.GetObjectCenter(oc[0],oc[1],oc[2]);
	double tempvalue1 = m_gls3d.GetViewRange()*0.5;
	double tempvalue2 = m_gls3d.GetLengthPerPixel();
	double* mx = m_gls3d.GetCurrentModelViewMatrix();
	if(screen[0]<screen[1])
	{
		wx = - tempvalue1*screen[0]/screen[1] + tempvalue2*sx + oc[0] - mx[12];
		wy = tempvalue1 - tempvalue2*sy + oc[1] - mx[13];
	}
	else
	{
		wx = -tempvalue1 + tempvalue2*sx + oc[0] - mx[12];
		wy = tempvalue1*screen[1]/screen[0] - tempvalue2*sy + oc[1] - mx[13];
	}
}
void Tree2DShow3D::setzup()
{
	double* p = m_gls3d.GetCurrentModelViewMatrix();
	if(p[10]>0)
		zfront = true;
	else
		zfront = false;
}

void AOPoint::draw()
{
	glColor4f(1,0,0,1);
	glPointSize(8);
	glBegin(GL_POINTS);
	glVertex3d(x,y,z);
	glEnd();
}

void AORectangle::draw()
{
	glColor4f(1,1,1,1);
	glLineWidth(5);
	glBegin(GL_LINE_LOOP);
	glVertex3d(left,bottom,z);
	glVertex3d(left,top,z);
	glVertex3d(right,top,z);
	glVertex3d(right,bottom,z);
	glEnd();
}

void AORectangle::adjustRange()
{
	double tempvalue;
	if(right<left)
	{
		tempvalue = right;
		right = left;
		left = tempvalue;
	}
	if(top<bottom)
	{
		tempvalue = top;
		top = bottom;
		bottom = tempvalue;
	}
}