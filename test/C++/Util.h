class Point3f
{
	public:
	float x,y,z;
	Point3f(float _x,float _y,float _z);
	Point3f(){};
	Point3f produitVect(Point3f b,Point3f c);
	~Point3f();
};

class SplineInterpolator
{
public:
	double *x, *f, *b, *c, *d;
    int n;

	void cubic_nak (int , double*, double*, double*, double*, double* );
	void cubic_clamped (int , double*, double*, double*, double*, double*, double, double );
	double spline_eval (int , double*, double*, double*, double*, double*, double);
	void tridiagonal (int , double *c, double *a, double *b, double *r );

	SplineInterpolator(int);
	~SplineInterpolator();
};
