#define MAX_STEER_ANGLE 1
#define CX 0.3f				
#define LENGTH	4.459f
#define WIDTH	1.927f
#define HEIGHT	1.246f	
#define WHEELBASE 2.71f		//distance between front and rear wheels
#define TRACK 1.6f			//distance between two front/rear wheels

class Car
{
public:
	float steer;
	float yaw;

	Point3f centerOfMass; //relative to the _pos
	Point3f pos;
	Matrix3 base;
	Point3f initialPos;

	Engine engine;
	TorqueConverter tc;
	GearBox gb;
	Differential df;
	Contact ct;
	Wheel wheels[4];
	
	void update(float st,float th, float dt);
	void updateSteer(float _steer,float dt);
	void updateWheels(float angle);
	Car(int n);
	~Car();
};
