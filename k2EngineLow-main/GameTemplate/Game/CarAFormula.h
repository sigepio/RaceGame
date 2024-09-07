#pragma once
class CarAFormula:public IGameObject
{
public:
	CarAFormula();
	~CarAFormula();
	bool Start();
	void Update();
	void SetGameEnd(bool m_GameEnd) {
		GameEnd = m_GameEnd;
	}
	SimulationResults CarSimulation(
					VehicleInfo vehicleinfo,				//車両の情報
					Vector3 Position,						//位置ベクトル[m]
					float VelocityVector,					//速度ベクトル[m/s]
					float PitchAngle,						//ピッチ角度[rad]
					float RollAngle,						//ロール角度[rad]
					float Acceleration,						//加速度
					float CurrentRPM,						//エンジンの回転数 [rpm]
					float DegreeOfRotationOfTheHandle,		//ハンドルの回転度合 [rad]	
					Vector3 Acceleration_DecelerationForce, //加減速力(前のフレームの車にかかるすべての力)[N]
					float CurrentGear,						//現在のギア
					float Grade,							//勾配[rad]
					float AirDensity,						//空気の密度 [kg/m3]
					float WindDirectionVector,				//風の向きベクトル [m/s]
					float Temperature,						//気温 [℃]
					float AtmosphericPressure,				//大気圧 [atm]
					float WaterVaporPressure,				//水蒸気圧 [atm]
					float RollingResistanceCoefficient,		//路面の転がり抵抗係数
					float CoefficientOfFriction,			//路面とタイヤとの摩擦係数
					float AcceleratorOpening,				//アクセルの踏み込み具合
					float BrakePressure,					//ブレーキの踏み込み具合
					float SteeringAngle,					//ステアリングアングル
					Vector3 SteeringFrontVector,			//ステアリングの正面ベクトル(正規化済みのみ)
					Vector3 FrontWheelOrientationVector,	//前輪向きを表現している単位ベクトル
					bool Transmission,						//ATかMTか
					float ΔRPM							//RPMの変化量
	);	
	void ShiftChange();



	//取得系関数

	//エンジン指示出力の取得(引数にエンジン回転数)
	float GetPi() {
	}


private:


	const float g = 9.8;			// 重力加速度 (m/s^2)

	bool GameEnd = false;
};

