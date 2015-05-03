#include "Util.h"
#include "Matrix3.h"
#include "Wheel.h"

#include <math.h>

Wheel::Wheel()
{
	r=0.25f;
	m=35.f;
	inertia=0.5f*m*r*r+0.5f;
	v=0;
	w=0;
	t=0;
	f=0;
}
void Wheel::update(float dt,float torque,float force)
{	
	t=torque;
	f=force;
	float a = (t-f*r)/inertia;
	if(a<0) 
	{
		a=0;	f=t/r;
	}
	w += a*dt;
	o -= w*dt;
	
	v = r*w;
	dx = v*dt;
}
Wheel::~Wheel()
{
}
