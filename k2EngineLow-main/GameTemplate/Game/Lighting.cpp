#include "stdafx.h"
#include "Lighting.h"
#include "Car_RB6.h"

Lighting::Lighting() {

}

Lighting::~Lighting() {

}

bool Lighting::Start() {
	

	//���C�g�����̐��K��
	Light_Direction.Normalize();
	//�f�B���N�V�������C�g�̐ݒ�
	RenderingEngine::GetInstance()->SetDirectionLight(Light_Direction, Light_Color);

	

	return true;
}

void Lighting::Update() {

}