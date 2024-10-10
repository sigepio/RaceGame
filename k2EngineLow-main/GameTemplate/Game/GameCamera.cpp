#include "stdafx.h"
#include "GameCamera.h"
#include "Car_Oreca07.h"
#include "Car_86GT.h"
#include <cmath>
#define _USE_MATH_DEFINES
#include <math.h>
#include "Player.h"
#include "PageNum.h"
#include <fstream>
using namespace std;


GameCamera::GameCamera() {
	
}

GameCamera::~GameCamera()
{

}

bool GameCamera::Start()
{
	m_player = FindGO<Player>("player");
	NowCar = m_player->GetCarNum();
	//m_toCameraPos.Set(0.0f, 0.0f, -5.0f);

	//カメラのニアクリップとファークリップを設定する。
	g_camera3D->SetNear(1.0f);
	g_camera3D->SetFar(10000000.0f);


	if (TitleMode == true) {
		TitleSet(0);
	}
	return true;
}

void GameCamera::TitleSet(int TitleState) {
	if (TitleState == 0) {
		titlepos = { 0.0f,70.0f,-200.0f };
		m_target = { 0.0f,20.0f,0.0f };
	}
	else if (TitleState == 1) {
		titlepos = { -100.0f,50.0f,200.0f };
		m_target = { 0.0f,20.0f,0.0f };
	}
}

Vector3 rotateY(Vector3 v, float angleDegrees) {
    float angleRadians = angleDegrees * M_PI / 180.0f;
    float cosAngle = cos(angleRadians);
    float sinAngle = sin(angleRadians);

    // Y軸回転行列を適用
    return {
        v.x * cosAngle + v.z * sinAngle,
        v.y,
        -v.x * sinAngle + v.z * cosAngle
    };
}

void GameCamera::Update() {
	if (GameEnd == true) {
		DeleteGO(this);
	}
	if (GarageMode == true) {
		m_target = { 0.0f,20.0f,50.0f };
		titlepos = { -175.0f,40.0f,50.0f };
		g_camera3D->SetTarget(m_target);
		g_camera3D->SetPosition(titlepos);
		g_camera3D->Update();
	}
	else if (TitleMode == true) {
		if (TitleState == 0) {
			if (TitleCount == 4000) {
				TitleState++;
				TitleSet(TitleState);
			}
			titlepos.z += 0.1f;
			g_camera3D->SetTarget(m_target);
			g_camera3D->SetPosition(titlepos);
			TitleCount++;
		}
		else if (TitleState == 1) {
			if (TitleCount == 4000) {
				TitleState++;
				TitleSet(TitleState);
			}
			titlepos.z -= 0.1f;
			m_target.z -= 0.1f;
			g_camera3D->SetTarget(m_target);
			g_camera3D->SetPosition(titlepos);
			TitleCount++;
		}

		//カメラの更新。
		g_camera3D->Update();
	}
	else {
		if (PlayFlag == false) {
			//ロビー時
			if (MainRaceManagerFlag == true) {
				if (m_player->GetNowCourse() == 0) {
					if (LobbyCount == 0) {
						m_target = { 24056,2471,41436 };
						m_cameraPosition = { 24056,2471,41536 };
					}
					if (LobbyCount <= 1800) {
						m_target += {3, 0.0, -9.55};
						m_cameraPosition += {3, 0.0, -9.55};
						g_camera3D->SetTarget(m_target);
						g_camera3D->SetPosition(m_cameraPosition);
						LobbyCount++;
					}
					else {
						Vector3 m_target = Vector3::Zero;
						LobbyCount = 0;
					}
				}
				else if (m_player->GetNowCourse() == 1) {
					if (LobbyCount == 0) {
						m_target = { -17671.0f,-197.0f,-41603.0f };
						m_cameraPosition = { -17671.0f,-197.0f,-41703.0f };
					}
					if (LobbyCount <= 1800) {
						m_target += {0.92, 0.0, 9.96};
						m_cameraPosition += {0.92, 0.0, 9.96};
						g_camera3D->SetTarget(m_target);
						g_camera3D->SetPosition(m_cameraPosition);
						LobbyCount++;
					}
					else {
						Vector3 m_target = Vector3::Zero;
						LobbyCount = 0;
					}
				}
				else if (m_player->GetNowCourse() == 2) {
					if (LobbyCount == 0) {
						m_target = { 0.0f,-100.0f,2000.0f };
						m_cameraPosition = { 0.0f,-100.0f,2100.0f };
					}
					if (LobbyCount <= 1800) {
						m_target += {0, 0.0, -1.0};
						m_cameraPosition += {0.0, 0.0, -1.0};
						g_camera3D->SetTarget(m_target);
						g_camera3D->SetPosition(m_cameraPosition);
						LobbyCount++;
					}
					else {
						Vector3 m_target = Vector3::Zero;
						LobbyCount = 0;
					}
				}
				else if (m_player->GetNowCourse() == 3) {
					if (LobbyCount == 0) {
						m_target = { -15229.0f,-3259.0f,-1000.0f };
						m_cameraPosition = { -15229.0f,-3259.0f,1100.0f };
					}
					if (LobbyCount <= 1800) {
						m_target += {0, 0.0, -1.0};
						m_cameraPosition += {0.0, 0.0, -1.0};
						g_camera3D->SetTarget(m_target);
						g_camera3D->SetPosition(m_cameraPosition);
						LobbyCount++;
					}
					else {
						Vector3 m_target = Vector3::Zero;
						LobbyCount = 0;
					}
				}
			}

			//ガレージ時
			else {
				m_target = { 0.0f,0.0f,50.0f };
				g_camera3D->SetTarget(m_target);
				m_cameraPosition = { -150.0f,30.0f,0.0f };
				g_camera3D->SetPosition(m_cameraPosition);
			}
		}
		else {
			
			m_toCameraPos.Set(MAIN_TO_CAMERA_POS);
			////カメラを更新。

			float x = g_pad[0]->GetRStickXF();
			float y = g_pad[0]->GetRStickYF();
			Vector3 pos = g_vec3Zero;

			CameraEvacuate = MAIN_TO_CAMERA_POS.y;
			TargetEvacuate = TargetPoint.y;

			if (m_PauseState == 0 || m_PauseState == -1) {
				//バックビュー
				if (g_pad[0]->IsPress(enButtonDown) || y <= -0.8f) {
					DP = rotateY(DP, 180.0f);
					FrontWheelForwardCatch = rotateY(FrontWheelForwardCatch, 180.0f);
					MAIN_TO_CAMERA_POS.z += -ViewpointDirectionCorrectionByVehicleType.z;
				}
				//ライトビュー
				else if (g_pad[0]->IsPress(enButtonRight) || x <= -0.8f) {
					DP = rotateY(DP, 90.0f);
					FrontWheelForwardCatch = rotateY(FrontWheelForwardCatch, 90.0f);
					MAIN_TO_CAMERA_POS.x += ViewpointDirectionCorrectionByVehicleType.x;
				}
				//レフトビュー
				else if (g_pad[0]->IsPress(enButtonLeft) || x >= 0.8f) {
					DP = rotateY(DP, -90.0f);
					FrontWheelForwardCatch = rotateY(FrontWheelForwardCatch, -90.0f);
					MAIN_TO_CAMERA_POS.x += -ViewpointDirectionCorrectionByVehicleType.x;
				}
				else {
					ViewpointDirectionCorrection = g_vec3Zero;
				}
			}
			float magnitude = m_toCameraPos.Length();
			float Target_magnitude = TargetPoint.Length();
			pos = m_target;
			pos.y += ViewpointHeight;

			if (ViewpointMode == true) {
				m_target = FrontWheelForwardCatch * Target_magnitude;
				m_target += pos;
				m_toCameraPos = DP * -magnitude;
			}
			else {
				m_target = DP * Target_magnitude;
				m_target += pos;
				m_toCameraPos = FrontWheelForwardCatch * magnitude;
			}
			pos += m_toCameraPos;

			g_camera3D->SetTarget(m_target);
			g_camera3D->SetPosition(pos);

			//カメラの更新。
			g_camera3D->Update();
		}
	}
	
}