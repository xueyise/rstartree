/*///////////////////////////////////////////////////////////////////////////////////////////////////
                                                 by mengyu 2009 - 12 -12
filename: myglshow3d.h
instruction:
    These codes are used for supporting openGL in MFC environment.
	I haved used them in Microsoft Visual Studio 2005.
	If you want to use it, you should read followings:
		1, Add "myglshow3d.h" and "myglshow3d.cpp" two items in your project.
		2, Add "opengl32.lib", "glu32.lib" and "glaux.lib" three items in your linker.
		3, Include "myglshow3d.h" in your "C*View.h" file or some other files if you want.
///////////////////////////////////////////////////////////////////////////////////////////////////*/
#ifndef MY_GL_SHOW_3D_H
#define MY_GL_SHOW_3D_H

#include "stdafx.h"

#include <gl/GL.h>
#include <gl/GLU.h>
#include <gl/GLAux.h>

class MyGLShow3D
{
private:
	HGLRC m_hglrc;
	double pcenter[3];
	double prange;
	double ocenter[3];
	int canvasrange[2];
	double lengthperpixel;
	double pzoomrate;
	bool projectionflag;                        // true is perspective projection,false is ortho-projection
	double cmvmatrix[16];                   // current model veiw matrix
	double inversecmvmatrix[16];
	static double copycmvmatrix[16];

public:
	MyGLShow3D();            //constructor

	void Initialization(CClientDC &dc);
	void Destroy();
	void ReSize(CClientDC &dc,int cx,int cy);
	void UpdateParameter(const double& x1,const double& x2,const double& y1,
		const double& y2,const double &z1,const double &z2);
	void AdjustZoomRate(const double& rate);

	void Translation(const int &cx,const int &cy,const bool &flagsave);
	void Translation(const double &cx,const double &cy,const double &cz,const bool &flagsave);

	void Rotation(const int &cx,const int &cy,const double angle,const bool &flagsave);
	void Rotation(const double &angle,const double &ax,const double &ay,const double &az,
		const bool &flagsave);

	void BeginDraw(HDC& m_hdc);
	void EndDraw(HDC& m_hdc);

	double* GetCurrentModelViewMatrix()const{return (double*)cmvmatrix;}

private:
	void TransformVectorFromScreenToWorld(const int &vx,const int &vy,double& wx,
		double& wy,double& wz);
	void TransformVectorFromWorldToScreen(const double& wx,const double& wy,
		const double& wz,int &vx,int &vy);
	void UpdateLengthPerPixel();
	void SaveCurrentModelViewMatrix();
	void LoadCurrentModelViewMatrix();
	void SetZoomRate(const double& zoomrate);
	void SetTranslateVector(const double &tx,const double &ty,const double &tz);
	void SetRotateMatrix(const double &angle,const double &ax,const double &ay,const double &az);
	void SetInverseRotateMatrix();
	void GetRotateMatirx(const double &angle,const double &ax,const double &ay,const double &az
		,double (*rotatematrix)[3]);
};

#endif