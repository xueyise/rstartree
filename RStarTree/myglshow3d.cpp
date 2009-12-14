/*///////////////////////////////////////////////////////////////////////////////////////////////////
                                                 by mengyu 2009 - 12 -12
filename: myglshow3d.cpp
instruction:
    These codes are used for supporting openGL in MFC environment.
	I haved used them in Microsoft Visual Studio 2005.
	If you want to use it, you should read followings:
		1, Add "myglshow3d.h" and "myglshow3d.cpp" two items in your project.
		2, Add "opengl32.lib", "glu32.lib" and "glaux.lib" three items in your linker.
		3, Include "myglshow3d.h" in your "C*View.h" file or some other files if you want.
///////////////////////////////////////////////////////////////////////////////////////////////////*/
#include "stdafx.h"
#include "myglshow3d.h"
#include "math.h"

double MyGLShow3D::copycmvmatrix[16] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};

MyGLShow3D::MyGLShow3D():m_hglrc(NULL),prange(1),lengthperpixel(1),
                    projectionflag(false),pzoomrate(1)
{
	pcenter[0] = 0;
	pcenter[1] = 0;
	pcenter[2] = 0;
	canvasrange[0] = 1;
	canvasrange[1] = 1;
	for(int i=0;i<4;++i)
	{
		for(int j=0;j<4;++j)
		{
			if(i==j)
			{
				cmvmatrix[i*4+j] = 1;
				inversecmvmatrix[i*4+j] = 1;
			}
			else
			{
				cmvmatrix[i*4+j] = 0;
				inversecmvmatrix[i*4+j] = 0;
			}
		}
	}
}

void MyGLShow3D::Initialization(CClientDC &dc)
{
	PIXELFORMATDESCRIPTOR pfd;
	memset(&pfd,0,sizeof(PIXELFORMATDESCRIPTOR));
	pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);
	pfd.nVersion = 1;
	pfd.dwFlags = PFD_DRAW_TO_WINDOW |
		                   PFD_SUPPORT_OPENGL |
						   PFD_DOUBLEBUFFER;
	pfd.iPixelType = PFD_TYPE_RGBA;
	pfd.cColorBits = 24;
	//pfd.cAlphaBits = 24;
	pfd.cDepthBits = 32;
	int pixelFormat = ChoosePixelFormat(dc.m_hDC,&pfd);
	SetPixelFormat(dc.m_hDC,pixelFormat,&pfd);
	m_hglrc = wglCreateContext(dc.m_hDC);
	//glEnable(GL_DEPTH_TEST);
	pcenter[0] = 0;
	pcenter[1] = 0;
	pcenter[2] = 0;
	canvasrange[0] = 1;
	canvasrange[1] = 1;
	ocenter[0] = 0;
	ocenter[1] = 0;
	ocenter[2] = 0;
	prange = 1;
	lengthperpixel = 1;
	projectionflag = false;
	pzoomrate = 1;
	for(int i=0;i<4;++i)
	{
		for(int j=0;j<4;++j)
		{
			if(i==j)
			{
				cmvmatrix[i*4+j] = 1;
				inversecmvmatrix[i*4+j] = 1;
			}
			else
			{
				cmvmatrix[i*4+j] = 0;
				inversecmvmatrix[i*4+j] = 0;
			}
		}
	}
	SaveCurrentModelViewMatrix();
}

void MyGLShow3D::Destroy()
{
	wglMakeCurrent(NULL,NULL);
	wglDeleteContext(m_hglrc);
	m_hglrc = NULL;
}

void MyGLShow3D::ReSize(CClientDC &dc,int cx,int cy)
{
	canvasrange[0] = cx;
	canvasrange[1] = cy;
	wglMakeCurrent(dc.m_hDC,m_hglrc);
	if(cx<cy)
	{
		glViewport((cx-cy)/2,0,cy,cy);
	}
	else
	{
		glViewport(0,(cy-cx)/2,cx,cx);
	}
	UpdateLengthPerPixel();
	wglMakeCurrent(NULL,NULL);
}

void MyGLShow3D::UpdateLengthPerPixel()
{
	if(canvasrange[0]<canvasrange[1])
	{
		lengthperpixel = (prange*pzoomrate)/(double)canvasrange[1];
	}
	else
	{
		lengthperpixel = (prange*pzoomrate)/(double)canvasrange[0];
	}
}

void MyGLShow3D::UpdateParameter(const double &x1, const double &x2, const double &y1, 
								 const double &y2,const double &z1,const double &z2)
{
	double maxrange = x2 - x1;
	double temprange = y2 - y1;
	if(maxrange<temprange)
		maxrange = temprange;
	temprange = z2 - z1;
	if(maxrange<temprange)
		maxrange = temprange;
	prange = sqrt(pow(maxrange,2.0)*3);
	ocenter[0] = (x1 + x2) /2.0;
	ocenter[1] = (y1 + y2) /2.0;
	ocenter[2] = (z1 + z2) /2.0;
	pcenter[0] = 0;
	pcenter[1] = 0;
	pcenter[2] = 0;
	//pzoomrate = 1.0;
	UpdateLengthPerPixel();
}

void MyGLShow3D::AdjustZoomRate(const double& rate)
{
	if(rate<0.0000000001)
		return;
	double zoomrate = pzoomrate * rate;
	SetZoomRate(zoomrate);
}

void MyGLShow3D::SetZoomRate(const double &zoomrate)
{
	if(zoomrate<0.0000000001)
		return;
	pzoomrate = zoomrate;
	UpdateLengthPerPixel();
}

void MyGLShow3D::BeginDraw(HDC& m_hdc)
{
	wglMakeCurrent(m_hdc,m_hglrc);
	glClearColor(0,0,0,1);
	glClearDepth(1.0);
	glDepthMask(GL_TRUE);
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_POINT_SMOOTH);
	glEnable(GL_LINE_SMOOTH);
	glEnable(GL_POLYGON_SMOOTH);
	glDepthMask(GL_FALSE);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
	glHint(GL_LINE_SMOOTH_HINT|GL_POINT_SMOOTH_HINT|GL_POLYGON_SMOOTH_HINT,
		GL_NICEST);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if(projectionflag)
	{
		//gluPerspective(60,1,prange*1.732,prange*3.732);
		glFrustum(-prange/2*pzoomrate,prange/2*pzoomrate,
				-prange/2*pzoomrate,prange/2*pzoomrate,
				prange*0.866,prange*1.866);
	}
	else
	{
		glOrtho(-prange/2*pzoomrate,prange/2*pzoomrate,
				-prange/2*pzoomrate,prange/2*pzoomrate,
				prange*0.866,prange*1.866);
	}
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(0,0,prange*1.366,0,0,0,0,1,0);
	//glTranslated(-ocenter[0],-ocenter[1],-ocenter[2]);
	glMultMatrixd(cmvmatrix);
	glTranslated(-ocenter[0],-ocenter[1],-ocenter[2]);
	/*double tv[3] = {0,0,0};
	TransformVectorFromScreenToWorld(30,30,tv[0],tv[1],tv[2]);
	glBegin(GL_LINES);
	glVertex3d(ocenter[0],ocenter[1],ocenter[2]);
	glVertex3d(ocenter[0]+tv[0],ocenter[1]+tv[1],ocenter[2]+tv[2]);
	glEnd();*/
}

void MyGLShow3D::EndDraw(HDC& m_hdc)
{
	SwapBuffers(m_hdc);
	wglMakeCurrent(NULL,NULL);
}

void MyGLShow3D::Translation(const int &cx,const int &cy,const bool &flagsave)
{
	double tv[3] = {0,0,0};
	TransformVectorFromScreenToWorld(cx,cy,tv[0],tv[1],tv[2]);
	LoadCurrentModelViewMatrix();
	SetTranslateVector(tv[0],tv[1],tv[2]);
	if(flagsave)
	{
		SaveCurrentModelViewMatrix();
		inversecmvmatrix[12] = - cmvmatrix[12];
		inversecmvmatrix[13] = - cmvmatrix[13];
		inversecmvmatrix[14] = - cmvmatrix[14];
	}
}
void MyGLShow3D::Translation(const double &cx,const double &cy,const double &cz,
							 const bool &flagsave)
{
	LoadCurrentModelViewMatrix();
	SetTranslateVector(cx,cy,cz);
	if(flagsave)
	{
		SaveCurrentModelViewMatrix();
		inversecmvmatrix[12] = - cmvmatrix[12];
		inversecmvmatrix[13] = - cmvmatrix[13];
		inversecmvmatrix[14] = - cmvmatrix[14];
	}
}

void MyGLShow3D::TransformVectorFromScreenToWorld(const int &vx,const int &vy,double& wx,
		double& wy,double& wz)
{
	double tempvalue[2];
	tempvalue[0] = vx*lengthperpixel;
	tempvalue[1] = vy*lengthperpixel;

	wx = inversecmvmatrix[0]*tempvalue[0] + inversecmvmatrix[4]*tempvalue[1] ;
	wy = inversecmvmatrix[1]*tempvalue[0] + inversecmvmatrix[5]*tempvalue[1] ;
	wz = inversecmvmatrix[2]*tempvalue[0] + inversecmvmatrix[6]*tempvalue[1] ;
}

void MyGLShow3D::SaveCurrentModelViewMatrix()
{
	for(int i=0;i<16;++i)
		copycmvmatrix[i] = cmvmatrix[i];
}

void MyGLShow3D::LoadCurrentModelViewMatrix()
{
	for(int i=0;i<16;++i)
		cmvmatrix[i] = copycmvmatrix[i];
}

void MyGLShow3D::SetTranslateVector(const double &tx,const double &ty,const double& tz)
{
	cmvmatrix[12] += cmvmatrix[0]*tx + cmvmatrix[4]*ty + cmvmatrix[8]*tz;
	cmvmatrix[13] += cmvmatrix[1]*tx + cmvmatrix[5]*ty + cmvmatrix[9]*tz;
	cmvmatrix[14] += cmvmatrix[2]*tx + cmvmatrix[6]*ty + cmvmatrix[10]*tz;
}

void MyGLShow3D::Rotation(const double &angle, const double &ax, const double &ay, 
						  const double &az, const bool &flagsave)
{
	LoadCurrentModelViewMatrix();
	SetRotateMatrix(angle,ax,ay,az);
	if(flagsave)
	{
		SaveCurrentModelViewMatrix();
		SetInverseRotateMatrix();
	}
}

void MyGLShow3D::Rotation(const int &cx,const int &cy,const double angle,const bool &flagsave)
{
	LoadCurrentModelViewMatrix();
	// get rotate and axis
	double axis[3];
	TransformVectorFromScreenToWorld(cx,cy,axis[0],axis[1],axis[2]);
	SetRotateMatrix(angle,axis[0],axis[1],axis[2]);
	if(flagsave)
	{
		SaveCurrentModelViewMatrix();
		SetInverseRotateMatrix();
	}
}

void MyGLShow3D::SetRotateMatrix(const double &angle,const double &ax,const double &ay,
								 const double &az)
{
	double rotatematrix[3][3];
	GetRotateMatirx(angle,ax,ay,az,rotatematrix);

	/*cmvmatrix[0] = rotatematrix[0][0]*copycmvmatrix[0] + rotatematrix[0][1]*copycmvmatrix[1] + 
		rotatematrix[0][2]*copycmvmatrix[2];
	cmvmatrix[1] = rotatematrix[1][0]*copycmvmatrix[0] + rotatematrix[1][1]*copycmvmatrix[1] + 
		rotatematrix[1][2]*copycmvmatrix[2];
	cmvmatrix[2] = rotatematrix[2][0]*copycmvmatrix[0] + rotatematrix[2][1]*copycmvmatrix[1] + 
		rotatematrix[2][2]*copycmvmatrix[2];
	cmvmatrix[4] = rotatematrix[0][0]*copycmvmatrix[4] + rotatematrix[0][1]*copycmvmatrix[5] + 
		rotatematrix[0][2]*copycmvmatrix[6];
	cmvmatrix[5] = rotatematrix[1][0]*copycmvmatrix[4] + rotatematrix[1][1]*copycmvmatrix[5] + 
		rotatematrix[1][2]*copycmvmatrix[6];
	cmvmatrix[6] = rotatematrix[2][0]*copycmvmatrix[4] + rotatematrix[2][1]*copycmvmatrix[5] + 
		rotatematrix[2][2]*copycmvmatrix[6];
	cmvmatrix[8] = rotatematrix[0][0]*copycmvmatrix[8] + rotatematrix[0][1]*copycmvmatrix[9] + 
		rotatematrix[0][2]*copycmvmatrix[10];
	cmvmatrix[9] = rotatematrix[1][0]*copycmvmatrix[8] + rotatematrix[1][1]*copycmvmatrix[9] + 
		rotatematrix[1][2]*copycmvmatrix[10];
	cmvmatrix[10] = rotatematrix[2][0]*copycmvmatrix[8] + rotatematrix[2][1]*copycmvmatrix[9] + 
		rotatematrix[2][2]*copycmvmatrix[10];*/
	cmvmatrix[0] = copycmvmatrix[0]*rotatematrix[0][0] + copycmvmatrix[4]*rotatematrix[1][0] +
		copycmvmatrix[8]*rotatematrix[2][0];
	cmvmatrix[1] = copycmvmatrix[1]*rotatematrix[0][0] + copycmvmatrix[5]*rotatematrix[1][0] +
		copycmvmatrix[9]*rotatematrix[2][0];
	cmvmatrix[2] = copycmvmatrix[2]*rotatematrix[0][0] + copycmvmatrix[6]*rotatematrix[1][0] +
		copycmvmatrix[10]*rotatematrix[2][0];
	cmvmatrix[4] = copycmvmatrix[0]*rotatematrix[0][1] + copycmvmatrix[4]*rotatematrix[1][1] +
		copycmvmatrix[8]*rotatematrix[2][1];
	cmvmatrix[5] = copycmvmatrix[1]*rotatematrix[0][1] + copycmvmatrix[5]*rotatematrix[1][1] +
		copycmvmatrix[9]*rotatematrix[2][1];
	cmvmatrix[6] = copycmvmatrix[2]*rotatematrix[0][1] + copycmvmatrix[6]*rotatematrix[1][1] +
		copycmvmatrix[10]*rotatematrix[2][1];
	cmvmatrix[8] = copycmvmatrix[0]*rotatematrix[0][2] + copycmvmatrix[4]*rotatematrix[1][2] +
		copycmvmatrix[8]*rotatematrix[2][2];
	cmvmatrix[9] = copycmvmatrix[1]*rotatematrix[0][2] + copycmvmatrix[5]*rotatematrix[1][2] +
		copycmvmatrix[9]*rotatematrix[2][2];
	cmvmatrix[10] = copycmvmatrix[2]*rotatematrix[0][2] + copycmvmatrix[6]*rotatematrix[1][2] +
		copycmvmatrix[10]*rotatematrix[2][2];
}

void MyGLShow3D::SetInverseRotateMatrix()
{
	inversecmvmatrix[0] = cmvmatrix[0];
	inversecmvmatrix[1] = cmvmatrix[4];
	inversecmvmatrix[2] = cmvmatrix[8];
	inversecmvmatrix[4] = cmvmatrix[1];
	inversecmvmatrix[5] = cmvmatrix[5];
	inversecmvmatrix[6] = cmvmatrix[9];
	inversecmvmatrix[8] = cmvmatrix[2];
	inversecmvmatrix[9] = cmvmatrix[6];
	inversecmvmatrix[10] = cmvmatrix[10];
}

void MyGLShow3D::GetRotateMatirx(const double &angle,const double &ax,const double &ay,
								 const double &az,double (*rotatematrix)[3])
{
	double templength = sqrt(ax*ax + ay*ay + az*az);
	if(templength<0.000000001)
		return;
	double axis[3];
	axis[0] = ax / templength;
	axis[1] = ay / templength;
	axis[2] = az / templength;
	double c = cos(angle);
	double s = sin(angle);
	double t1_c = 1 - c;
	double t1_cxy = t1_c*axis[0]*axis[1];
	double t1_cyz = t1_c*axis[1]*axis[2];
	double t1_czx = t1_c*axis[2]*axis[0];
	double sx = s*axis[0];
	double sy = s*axis[1];
	double sz = s*axis[2];
	rotatematrix[0][0] = c + t1_c*axis[0]*axis[0];
	rotatematrix[0][1] = t1_cxy - sz;
	rotatematrix[0][2] = t1_czx + sy;
	rotatematrix[1][0] = t1_cxy + sz;
	rotatematrix[1][1] = c + t1_c*axis[1]*axis[1];
	rotatematrix[1][2] = t1_cyz - sx;
	rotatematrix[2][0] = t1_czx - sy;
	rotatematrix[2][1] = t1_cyz + sx;
	rotatematrix[2][2] = c + t1_c*axis[2]*axis[2];
}
void MyGLShow3D::ResetCurrentModelViewMatrix()
{
	for(int i=0;i<4;++i)
	{
		for(int j=0;j<4;++j)
		{
			if(i==j)
			{
				cmvmatrix[i*4+j] = 1;
				inversecmvmatrix[i*4+j] = 1;
			}
			else
			{
				cmvmatrix[i*4+j] = 0;
				inversecmvmatrix[i*4+j] = 0;
			}
		}
	}
	SaveCurrentModelViewMatrix();
}
void MyGLShow3D::ResetPosition()
{
	ResetCurrentModelViewMatrix();
	SetZoomRate(1);
}