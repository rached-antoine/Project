class Matrix3
{	public:

	float a[3][3];
	void mult(Point3f *dest,Point3f *src);
	void mult(Matrix3 *a,Matrix3 *b,Matrix3 *c);//a=b*c
	void rot(int axis,float angle);
	void transpose();
	void inv(Matrix3 * dest);
	void printMatrix();
	float det();

	Matrix3();
	~Matrix3();
};
