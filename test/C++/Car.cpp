#include "Util.h"
#include "Matrix3.h"
#include "Engine.h"
#include "TorqueConverter.h"
#include "GearBox.h"
#include "Differential.h"
#include "Contact.h"
#include "Wheel.h"
#include "Car.h"

#include <math.h>
#include <iostream>
Car::Car(int n):engine(n)
{
	centerOfMass.x = 0;
	centerOfMass.y = 0;
	centerOfMass.z = 0;

	base.a[0][0] = base.a[1][1] = base.a[2][2] = 1;

	pos.x = 0;
	pos.y = 0;
	pos.z = 0;

	wheels[0].pos.x = TRACK*0.5f;
	wheels[0].pos.y = wheels[0].r-HEIGHT*0.5f;
	wheels[0].pos.z = -WHEELBASE*0.5f;

	wheels[1].pos.x = -TRACK*0.5f;
	wheels[1].pos.y = wheels[0].r-HEIGHT*0.5f;
	wheels[1].pos.z = -WHEELBASE*0.5f;

	wheels[2].pos.x = -TRACK*0.5f;
	wheels[2].pos.y = wheels[0].r-HEIGHT*0.5f;
	wheels[2].pos.z = WHEELBASE*0.5f;

	wheels[3].pos.x = TRACK*0.5f;
	wheels[3].pos.y = wheels[0].r-HEIGHT*0.5f;
	wheels[3].pos.z = WHEELBASE*0.5f;

	for(int i=0;i<4;++i) wheels[i].base.a[0][0] = wheels[i].base.a[1][1] = wheels[i].base.a[2][2] = 1;
}

Car::~Car()
{
}
void Car::update(float st,float th,float dt)
{	
	updateSteer(st,dt);
	engine.update(th,tc.tcc,dt);
	tc.update(engine.wcc,gb.wgb);
	gb.update(tc.tgb,df.wdif);
	df.update(gb.tdif,wheels[3].w,wheels[2].w);
	wheels[3].update(dt,df.t,ct.f);
	wheels[2].update(dt,df.t,ct.f);
	ct.update(wheels[2].v,dt);
	pos.z -= wheels[3].dx;
}

void Car::updateSteer(float _steer,float dt)
{ 
		if(_steer>=-1 && _steer<=1)
			steer = _steer;

		float ro = 2*tan(steer*0.5f)/WHEELBASE;
		yaw += ro*wheels[3].v*dt;
/*
		y.rot(1,yaw);		//Yaw Matrix
		s.rot(1,steer);		//Steer Matrix
		a.rot(0,-wheels[3].o);	//Wheel Rotation Matrix

		y.mult(&base,&y,&base);	// base = yaw * base		(for vehicle)
		base.mult(&pos,&pos);

		s.mult(&s,&y,&s);		// Yrotation = yaw * steer   (for front wheels)
		s.mult(&s,&a,&s);		// XYrotation = wheelRot * yaw * steer	(for front wheels)

		a.mult(&a,&a,&y);		// XYrotation = wheelRot * yaw (for rear wheels)

		//base = XYrotation * base
		s.mult(&wheels[0].base,&s,&wheels[0].base);	
		s.mult(&wheels[1].base,&s,&wheels[1].base);

		a.mult(&wheels[2].base,&a,&wheels[2].base);
		a.mult(&wheels[3].base,&a,&wheels[3].base);

		//for(int i=0;i<4;++i)
		//	wheels[i].base.printMatrix();

		*/
	
		Matrix3 y,s,a;
		y.rot(1,yaw);
		y.transpose();
	
		pos.x += -wheels[3].v*dt*sin(yaw);
		pos.y = 0;
		pos.z += -wheels[3].v*dt*cos(yaw);

		s.rot(1,steer);
		a.rot(0,wheels[3].o);
		s.transpose();
		a.transpose();

		s.mult(&s,&a,&s);

		wheels[0].base = s;
		wheels[1].base = s;

		wheels[2].base = a;
		wheels[3].base = a;
}