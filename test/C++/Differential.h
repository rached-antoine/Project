class Differential
{
public:
	float n;
	float wdif;
	float tdif;
	float wr,wl;
	float t;

	void update(float t,float r,float l);
	Differential();
	~Differential();
};
