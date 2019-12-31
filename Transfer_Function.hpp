//#include <stdio.h>
#include<iostream>

#define R 0.6
#define L 3e-3
#define B 5e-4
#define J 1.4e-3
#define Kt 0.1197f
#define Kb 0.1729f

#define h 1e-3

//モータの伝達関数
volatile double TransferFunction(volatile double u);

//モータの電気系の伝達関数
volatile double P_ele(volatile double V);
//モータの機械系の伝達関数
volatile double P_mech(volatile double T);

//電気系の微分方程式
volatile double f_ele(volatile double v, volatile double i);
//機械系の微分方程式
volatile double f_mech(volatile double T, volatile double omega);

