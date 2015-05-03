class Wheel
{
public:
	float r;
	float m;
	float inertia;

	float f;
	float t;
	float w;
	float o;
	float v;
	float dx;

	Matrix3 base;
	Point3f pos;

	void update(float dt, float torque, float force);
	Wheel();
	~Wheel();
};
