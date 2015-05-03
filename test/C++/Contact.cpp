#include "Contact.h"

Contact::Contact()
{	
	v = 0;
	f = 0;
	m = 1500;
}
void Contact::update(float vi,float dt)
{
	float a = (vi-v)/dt;
	v = vi;
	f = m*a*0.5f;
}
Contact::~Contact()
{
}
