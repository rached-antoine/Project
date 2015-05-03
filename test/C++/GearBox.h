class GearBox
{
public:
	char selector;
	float ratios[3];
	float wgb;
	float wdif;
	float tgb;
	float tdif;
	float ratio;
	int currentGear;
	
	void update(float t,float w);
	GearBox();
	~GearBox();
};
