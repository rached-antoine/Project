#include "Differential.h"

Differential::Differential()
{
	n=3;
	wdif=0;
}
void Differential::update(float td,float r,float l)
{	
	tdif = td;
	wr = r;
	wl = l;
	t = n*0.5f*tdif;
	wdif = n*0.5f*(wr+wl);
}
Differential::~Differential()
{
}
/*
void main()
{
	Differential d;
	float t,r,l;
	while(1)
	{	std::cout<<"insert torque, right wheel speed, left wheel speed: \n";
		std::cin>>t;
		std::cin>>r;
		std::cin>>l;
		d.update(t,r,l);
		std::cout<<"exiting torque :"<<d.tr <<"   exiting speed: "<<d.wdif<<"\n";
	}
}
*/