class TorqueConverter
{
public:
	float wgb;
	float wcc;
	float tgb;
	float tcc;

	float x[4];
	float fk[4];
	float fr[4];

	float ak[3];
	float bk[3];

	float ar[3];
	float br[3];

	void update(float w1,float w2);
	int locateX(float x);
	float evalK(float x);
	float evalR(float x);
	TorqueConverter();
	~TorqueConverter();
};
