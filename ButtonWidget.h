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
	std::shared_ptr<hgeSprite> sprite;		
	HTEXTURE tex1;
	HTEXTURE tex2;
	bool bPressed;
public:
	ButtonWidget(int id, float x, float y, float w, float h, HTEXTURE tex1, HTEXTURE tex2, std::function<void(bool)> onClick=nullptr);
	~ButtonWidget();
	bool MouseLButton(bool bDown);		/// overriding functions
	void Render();										
};

