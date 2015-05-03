#ifdef __cplusplus
extern "C"{
#endif
    
    typedef struct{
        float m11,m12,m13,m21,m22,m23,m31,m32,m33;
    }Matrix;
    
	void prepareVehicle(int n);

	void update(float s, float t, float dt);

	void destroy();

	float getPosX();
    float getPosY();
    float getPosZ();

    Matrix getBase(int i);
#ifdef __cplusplus
}
#endif