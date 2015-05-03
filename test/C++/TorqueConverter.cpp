#include "Util.h"
#include "TorqueConverter.h"

TorqueConverter::TorqueConverter()
{	
	x[0] = 0;
	x[1] = 0.4f;
	x[2] = 0.9f;
	x[3] = 1.f;

	fk[0] = 22.f;
	fk[1] = 23.f;
	fk[2] = 26.f;
	fk[3] = 70.f;

	fr[0] = 1.7f;
	fr[1] = 1.48f;
	fr[2] = 1.f;
	fr[3] = 1.f;

	for(int i=0;i<3;++i)
	{	ak[i] = (fk[i+1]-fk[i])/(x[i+1]-x[i]);
		ar[i] = (fr[i+1]-fr[i])/(x[i+1]-x[i]);

		bk[i] = fk[i]-ak[i]*x[i];
		br[i] = fr[i]-ar[i]*x[i];
	}
	tcc = 0.f;
	wcc = 104.7f; // = 1000 rpm, idle engine speed
}

int TorqueConverter::locateX(float x)
{	
	if(x<0.4 && x>=0)
		return 0;
	if(x<=0.9 && x >=0.4)
		return 1;
	if(x>0.9 && x <=1)
		return 2;

	return -1;
}
float TorqueConverter::evalR(float x)
{
	int index=locateX(x);
	if(index < 0) 
		return 0;

	else 
		return ar[index]*x + br[index];

}

float TorqueConverter::evalK(float x)
{
	int index=locateX(x);
	if(index < 0) 
		return 0;

	else 
		return ak[index]*x + bk[index];

}



void TorqueConverter::update(float w1,float w2)
{
	wcc = w1;
	wgb = w2;
	float rw = wgb/wcc;

	float k = evalK(rw);
	float r = evalR(rw); 
	if(k==0 || r==0)
	{
		tcc = 0;
		tgb = 0;
	}
	else
	{
		tcc = (wcc*wcc)/(k*k);
		tgb = tcc*r;
	}
}
TorqueConverter::~TorqueConverter()
{
	
}
/*
void main(){
	TorqueConverter tc;
	float w1,w2;
	while(1)
	{	std::cout<<"enter w1, w2: \n";
		std::cin>>w1;
		std::cin>>w2;
		tc.update(w1,w2);
	}
}
*/