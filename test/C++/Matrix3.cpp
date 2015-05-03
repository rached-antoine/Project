#include "Util.h"
#include "Matrix3.h"
#include <math.h>
#include <iostream>
using namespace std;

Matrix3::Matrix3()
{
	for(int i=0;i<3;++i){
		for(int j=0;j<3;++j){
			a[i][j]=0;
		}
	}
}

void Matrix3::rot(int axis, float angle){

	float co=cos(angle);
	float si=sin(angle);
	
	switch(axis){
	case 0:
		a[0][0]=1;
		a[1][1]=a[2][2]=co;
		a[2][1]=si;
		a[1][2]=-si;
	break;
	
	case 1:
		a[1][1]=1;
		a[0][0]=a[2][2]=co;
		a[0][2]=si;
		a[2][0]=-si;
	break;

	case 2:
		a[2][2]=1;
		a[1][1]=a[0][0]=co;
		a[1][0]=si;
		a[0][1]=-si;
	break;

	}
}


void Matrix3::mult(Point3f *dest,Point3f *src){
	
		Point3f *tmp=new Point3f();
		tmp->x=a[0][0]*src->x + a[0][1]*src->y + a[0][2]*src->z;
		tmp->y=a[1][0]*src->x + a[1][1]*src->y + a[1][2]*src->z;
		tmp->z=a[2][0]*src->x + a[2][1]*src->y + a[2][2]*src->z;
		*dest=*tmp;	
		delete tmp;
}

void Matrix3::mult(Matrix3 *A,Matrix3 *B,Matrix3 *C){
	Matrix3 *tmp=A;
	if((A==B)||(A==C)) tmp=new Matrix3;
		for(int i=0;i<3;++i)
			{for(int j=0;j<3;++j)
				tmp->a[i][j]=B->a[i][0]*C->a[0][j]
							+B->a[i][1]*C->a[1][j]
							+B->a[i][2]*C->a[2][j];
		}

	if((A==B)||(A==C)){ *A=*tmp; delete tmp;}
}
void Matrix3::transpose()
{	
	swap(a[0][1],a[1][0]);
	swap(a[0][2],a[2][0]);
	swap(a[1][2],a[2][1]);
}
float Matrix3::det(){
	return a[0][0]*(a[1][1]*a[2][2]-a[2][1]*a[1][2])-a[1][0]*(a[0][1]*a[2][2]-a[2][1]*a[0][2])
		+a[2][0]*(a[0][1]*a[1][2]-a[1][1]*a[0][2]);
}

void Matrix3::inv(Matrix3 *dest)
{
	float d=det();
	if(d<0.000001 && d>-0.000001)
		return;
	Matrix3 *tmp=new Matrix3;
	if(this==dest) *tmp=*this;

	float id=1.0f/d;
		dest->a[0][0]=id*(tmp->a[1][1]*tmp->a[2][2]-tmp->a[1][2]*tmp->a[2][1]);
		dest->a[0][1]=-id*(tmp->a[1][0]*tmp->a[2][2]-tmp->a[1][2]*tmp->a[2][0]);
		dest->a[0][2]=id*(tmp->a[1][0]*tmp->a[2][1]-tmp->a[1][1]*tmp->a[2][0]);
		dest->a[1][0]=-id*(tmp->a[0][1]*tmp->a[2][2]-tmp->a[0][2]*tmp->a[2][1]);
		dest->a[1][1]=id*(tmp->a[0][0]*tmp->a[2][2]-tmp->a[0][2]*tmp->a[2][0]);
		dest->a[1][2]=-id*(tmp->a[0][0]*tmp->a[2][1]-tmp->a[0][1]*tmp->a[2][0]);
		dest->a[2][0]=id*(tmp->a[0][1]*tmp->a[1][2]-tmp->a[0][2]*tmp->a[1][1]);
		dest->a[2][1]=-id*(tmp->a[0][0]*tmp->a[1][2]-tmp->a[0][2]*tmp->a[1][0]);
		dest->a[2][2]=id*(tmp->a[1][1]*tmp->a[0][0]-tmp->a[0][1]*tmp->a[1][0]);

		dest->transpose();
}

static inline void swap(float &x,float &y){
		x+=y;
		y=x-y;
		x-=y;
}

void Matrix3::printMatrix(){
	for(int i=0;i<9;++i)
	{if (i%3==0) std::cout<<"\n";
	std::cout<<a[i/3][i%3]<<"\t";}
	std::cout<<"\n"<<"\n";
}

Matrix3::~Matrix3()
{
}
/*
void main()
{
	Matrix3 m1;
	m1.rot(1,0.8);
	m1.printMatrix();
	Matrix3 m2;
	m1.a[0][0]=1;m1.a[0][1]=2;m1.a[0][2]=2;
	m1.a[1][0]=1;m1.a[1][1]=2;m1.a[1][2]=2;
	m1.a[2][0]=2;m1.a[2][1]=1;m1.a[2][2]=0;
	m1.printMatrice();

	m2.a[0][0]=1;m2.a[0][1]=2;m2.a[0][2]=4;
	m2.a[1][0]=2;m2.a[1][1]=3;m2.a[1][2]=1;
	m2.a[2][0]=5;m2.a[2][1]=1;m2.a[2][2]=3;
	m2.printMatrice();
	m1.mult(&m1,&m1,&m2);
	m1.printMatrice();
	
}
 */
