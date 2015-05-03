class Engine
{
public:
	float throttle;
	float wcc;
	float t;
	float tcc;
	float inertia;
	float rpm;

	SplineInterpolator splineH;
	SplineInterpolator splineL;
	
	void update(float th, float rt, double dt);
	Engine(int);
	~Engine();

};
