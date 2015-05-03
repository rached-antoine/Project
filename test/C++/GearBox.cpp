#include "GearBox.h"

GearBox::GearBox()
{
	selector='d';
	ratios[0]=2.66f;
	ratios[1]=1.33f;
	ratios[2]=1.0f;
	ratio = ratios[0];
	currentGear = 0;
	wgb=0;
}

void GearBox::update(float t, float w)
{	
	tgb = t;
	wdif = w;
	tdif = ratio*tgb;
	wgb = ratio*wdif;
	if(selector=='r')
	{	
		currentGear=-1;
		ratio = -ratios[0];
	}

	if(selector=='d' && ratio<0)
	{
		currentGear++;
		ratio = -ratio;
	}

	if(selector=='d' && wgb>314 && ratio>ratios[2]) // 314 rad/s == 3000rpm;
	{	
		currentGear++;
		ratio = ratios[currentGear];
	}

	if(selector=='d' && wgb<125 && ratio<ratios[0])	// 125 rad/s == 1200 rpm
	{	
		currentGear--;
		ratio = ratios[currentGear];
	}
}
GearBox::~GearBox()
{
}
/*
void main()
{
	GearBox g;
	float tgb,wdif;
	while(1)
	{
		std::cout<<"Gear: "<<g.currentGear<<"  Ratio : "<<g.ratio<<"  Tdif: "<<g.tdif<<"  Wgb: "<<g.wgb<<"\n";
		std::cout<<"insert Tgb,Wdif: \n";
		std::cin>>tgb;
		std::cin>>wdif;
		g.update(tgb,wdif);
	}
}
*/