#include "stdafx.h"
#include "FadeIn.h"

FadeIn::FadeIn() {

}

FadeIn::~FadeIn() {

}

bool FadeIn::Start() {
	FadeSprite.Init("Assets/Sprite/BlackOut.DDS", 1600.0f, 900.0f);
	FadeSprite.SetMulColor(FadeColor);
	FadeSprite.Update();
	return true;
}

void FadeIn::Update() {
	//if (FadeInState == true) {
	//	if (FadeInCount < 5) {
	//		FadeColor.w += 0.2f;
	//		FadeSprite.SetMulColor(FadeColor);
	//		FadeSprite.Update();
	//	}
	//}
	//else {
	//	FadeColor.w = 0.0f;;
	//	FadeSprite.SetMulColor(FadeColor);
	//	FadeSprite.Update();
	//}
	//FadeInCount++;
}

void FadeIn::Render(RenderContext& rc) {
	/*FadeSprite.Draw(rc);*/
}