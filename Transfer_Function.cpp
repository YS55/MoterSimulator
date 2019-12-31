#include "Transfer_Function.hpp"

//モータの伝達関数
volatile double TransferFunction(volatile double Va)
{
	volatile double I = 0.0;
	volatile double T = 0.0;
	volatile double V = 0.0;
	volatile static double Vb = 0.0;
	volatile double omega = 0.0;

	V = Va - Vb;
	I = P_ele(V);
	T = Kt * I;
	omega = P_mech(T);

	Vb = Kb * omega;

	//std::cout <<"Va: "<< Va <<"   Vb: "<< Vb << std::endl;

	return omega;
}

//モータの電気系の伝達関数
volatile double P_ele(volatile double V)
{
	volatile double I = 0.0;
	volatile static double pre_I = 0.0;
	volatile double g1 = 0.0, g2 = 0.0f;
	volatile double g3 = 0.0f, g4 = 0.0f;

	g1 = f_ele(V, pre_I);
	g2 = f_ele(V + h / 2, pre_I + g1 * h / 2);
	g3 = f_ele(V + h / 2, pre_I + g2 * h / 2);
	g4 = f_ele(V + h, pre_I + h * g3);
	I = pre_I + h / 6 * (g1 + 2 * g2 + 2 * g3 + g4);

	//printf_s("I: %lf , pre_I: %lf , g1: %lf , g2: %lf , g3: %lf , g4: %lf\n", I, pre_I, g1, g2, g3, g4);

	pre_I = I;

	return I;
}

//モータの電気系の微分方程式
volatile double f_ele(volatile double V, volatile double i)
{
	volatile double g = (V - R * i) / L;
	return g;
}

//モータの機械系の伝達関数
volatile double P_mech(volatile double T)
{
	volatile double omega = 0.0;
	volatile static double pre_omega = 0.0;
	volatile double g1 = 0.0f, g2 = 0.0f, g3 = 0.0f, g4 = 0.0f;

	g1 = f_mech(T, pre_omega);
	g2 = f_mech(T + h / 2, pre_omega + g1 * h / 2);
	g3 = f_mech(T + h / 2, pre_omega + g2 * h / 2);
	g4 = f_mech(T + h, pre_omega + h * g3);
	omega = pre_omega + h / 6 * (g1 + 2 * g2 + 2 * g3 + g4);

	pre_omega = omega;

	return omega;
}

//モータの機械系の微分方程式
volatile double f_mech(volatile double T, volatile double omega)
{
	volatile double g = (T - B * omega) / J;
	return g;
}

