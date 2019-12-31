#include "Transfer_Function.hpp"
#include "PIDController.hpp"

int main()
{
	double target_omega;	//モータ目標角速度
	volatile double now_omega = 0.0;	//モータ現在角速度
	volatile double u = 0.0;	//速度指令値
	double measure_t;		//計測時間
	FILE* fp;

	//テスト条件の入力
	printf_s("Target Velocity [rpm] : ");
	scanf_s("%lf", &target_omega);
	printf_s("Measure Time [ms] : ");
	scanf_s("%lf", &measure_t);

	fopen_s(&fp, "result.csv", "w");
	fprintf_s(fp, "Measure Time [ms],Target Velocity [rpm]\n");
	puts("Moter Simulation Start ...");

	//モータの速度制御
	for (int cnt = 0; cnt < measure_t; cnt++)
	{
		//PIDコントローラによる制御量の算出
		u = vPIDContoller(target_omega, now_omega, Kvp, Kvi, Kvd);
		//モータの挙動の算出
		now_omega = TransferFunction(u);

		//現在角速度の出力
		fprintf_s(fp, "%d,%lf\n", cnt, now_omega);
	}

	fclose(fp);

	puts("Moter Simulation Finish !!!");

	//while (1);
	return 0;
}