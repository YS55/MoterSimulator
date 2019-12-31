
//位置制御用ゲイン
#define Kpp 0.0f
#define Kpi 0.0f
#define Kpd 0.0f

//速度制御用ゲイン
#define Kvp 6
#define Kvi 10
#define Kvd 0.01

//制御周期
#define dt 1e-3;

//PIDコントローラ
volatile double vPIDContoller(volatile double ref, volatile double y, double kp, double ki, double kd) 
{
	static double iError = 0.0;
	static double b_pError = 0.0;
	static double u = 0.0;

	double pError = ref - y;
	iError += pError * dt;
	double dError = (pError - b_pError) / dt;
	
	b_pError = pError;

	u = Kvp * pError + Kvi * iError + Kvd * dError;

	return u;

	/*double T = dt;
	volatile static double ie = 0.0;
	volatile static double pre_e = 0.0;

	volatile double e = ref - y;
	ie += e * T;
	
	volatile double de = (e - pre_e) / T;
	volatile double u = kp * e + ki * ie + kd * de;

	pre_e = e;

	return u;*/
}