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
#include "Interface.h"

Car *c;
Matrix m;
void prepareVehicle(int n)
{
	c = new Car(n);
	c->initialPos.x = 0;
	c->initialPos.y = 0;
	c->initialPos.z = 0;
}

void update(float s, float t, float dt)
{
	c->update(s,t,dt);
}

float getPosX()
{
    return c->pos.x;
}
float getPosY()
{
    return c->pos.y;
}
float getPosZ()
{
    return c->pos.z;
}

Matrix getBase(int i)
{
    if(i == 0 || i == 1){
        m.m11=c->wheels[0].base.a[0][0];
        m.m12=c->wheels[0].base.a[0][1];
        m.m13=c->wheels[0].base.a[0][2];
        m.m21=c->wheels[0].base.a[1][0];
        m.m22=c->wheels[0].base.a[1][1];
        m.m23=c->wheels[0].base.a[1][2];
        m.m31=c->wheels[0].base.a[2][0];
        m.m32=c->wheels[0].base.a[2][1];
        m.m33=c->wheels[0].base.a[2][2];
        return m;
    }
    else{
        m.m11=c->wheels[2].base.a[0][0];
        m.m12=c->wheels[2].base.a[0][1];
        m.m13=c->wheels[2].base.a[0][2];
        m.m21=c->wheels[2].base.a[1][0];
        m.m22=c->wheels[2].base.a[1][1];
        m.m23=c->wheels[2].base.a[1][2];
        m.m31=c->wheels[2].base.a[2][0];
        m.m32=c->wheels[2].base.a[2][1];
        m.m33=c->wheels[2].base.a[2][2];
        return m;
    }
}
void destroy()
{
	delete c;
}