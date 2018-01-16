#pragma once
#include <string>
#include <functional>
#include <memory>
#include <hge.h>
#include <hgegui.h>
#include "Widget.h"

class ButtonWidget :
	public Widget
{

	HTEXTURE tex1;
	HTEXTURE tex2;
	bool bPressed;
public:
	ButtonWidget(int id = 0, float x = 0.0f, float y = 0.0f, float w = 0.0f, float h = 0.0f, HTEXTURE tex1 = 0, HTEXTURE tex2 = 0, std::function<void(bool)> onClick = nullptr, int order = 0);
	~ButtonWidget();
	void Render(HGE*hge) override;		
	void SetTextureOn(HTEXTURE tex2);
	void SetTextureOff(HTEXTURE tex1);
	void OnClick() override;
};

