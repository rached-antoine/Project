#include "Util.h"
#include "Engine.h"
#include <math.h>
#include <iostream>
#define PI 4*atan(1.0)

Engine::Engine(int n):splineH(n),splineL(n)
{
	inertia=0.5f;
	throttle=0;
	tcc=0;
	wcc=(float)(1000*PI/30);

	splineH.x[0]=1000.0;
	splineH.x[1]=3000.0;
	splineH.x[2]=4812.5;
	splineH.x[3]=6000.0;
	splineH.x[4]=8000.0;

	splineH.f[0]=300.0;
	splineH.f[1]=357.0;
	splineH.f[2]=386.0;
	splineH.f[3]=355.0;
	splineH.f[4]=205.0;

	splineL.x[0]=1000.0;
	splineL.x[1]=3000.0;
	splineL.x[2]=4812.5;
	splineL.x[3]=6000.0;
	splineL.x[4]=8000.0;

	splineL.f[0]=300.0;
	splineL.f[1]=357.0;
	splineL.f[2]=386.0;
	splineL.f[3]=355.0;
	splineL.f[4]=20.0;

	splineH.cubic_clamped(n,splineH.x,splineH.f,splineH.b,splineH.c,splineH.d, 18/375.0,-15/200.0);
	splineL.cubic_clamped(n,splineL.x,splineL.f,splineL.b,splineL.c,splineL.d, 18/375.0,-0.165);
}

void Engine::update(float th,float rt,double dt)
{	
	if(th>=0 && th<=1)
		throttle=th;
	
	if(wcc<100 || wcc>840)
		t=0;
	else{
		// get the maximum torque that the engine can deliver at current rpm
		float maxTorqueAtCurrentRpm;
		if(throttle<0.2)
			maxTorqueAtCurrentRpm = (float)splineL.spline_eval( splineL.n, splineL.x, splineL.f, splineL.b, splineL.c, splineL.d, (double)rpm);
		else
			maxTorqueAtCurrentRpm = (float)splineH.spline_eval( splineH.n, splineH.x, splineH.f, splineH.b, splineH.c, splineH.d, (double)rpm);
	
		// throttle mapping : 80% engine load at 40% throttle
		if (throttle<=0.4)
			t=2*throttle*maxTorqueAtCurrentRpm;
		else
			t=(throttle/3 + 0.65f)*maxTorqueAtCurrentRpm;
		}
	tcc=rt;
	double a=(t - tcc)/inertia;
	wcc += (float)(a*dt);
	rpm = (float)(wcc*30/(PI));
}


Engine::~Engine()
{
}
/*
void main()
{
	Engine g(5);
	int x=0;
	for(int i=1000;i<8001;i+=200)
	{	x++;
		std::cout<<"("<<i<<","<<g.splineH.spline_eval( g.splineH.n, g.splineH.x, g.splineH.f, g.splineH.b, g.splineH.c, g.splineH.d, i)<<")";
	}
	std::cout<<"\n"<<x<<"\n";
}
*/