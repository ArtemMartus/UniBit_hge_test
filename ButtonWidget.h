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
public:
	ButtonWidget(int id, float x, float y, float w, float h, HTEXTURE tex1, HTEXTURE tex2, std::function<void(bool)> onClick=nullptr);
	~ButtonWidget();
	//void MouseOver(bool bOver);
	bool MouseLButton(bool bDown);		/// �������������� ������ ������ ����������� �-���
	//void Update(float delta);			
	void Render();										
	//bool KeyClick(int key, int chr);
};
