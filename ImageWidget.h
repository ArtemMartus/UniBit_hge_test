#pragma once
#include <string>
#include <memory>
#include <functional>
#include <hge.h>
#include <hgegui.h>
#include "Widget.h"

class ImageWidget :
	public Widget
{
	std::shared_ptr<hgeSprite> sprite;
	HTEXTURE tex1;
public:
	ImageWidget(int id, float x, float y, float w, float h, HTEXTURE tex1,std::function<void(bool)> mouseOver=nullptr);
	~ImageWidget();

	void MouseOver(bool bOver);		/// Переопределяем только нужные ф-ции
	//bool MouseLButton(bool bDown);
	//void Update(float delta);
	void Render();
	//bool KeyClick(int key, int chr);
};

