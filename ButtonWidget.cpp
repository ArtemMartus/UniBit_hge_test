#include "ButtonWidget.h"


ButtonWidget::ButtonWidget(int id, float x, float y, float w, float h, HTEXTURE tex1, HTEXTURE tex2, std::function<void(bool)> onClick) :Widget(onClick)
{
	if (!tex1 || !tex2)
	{
		MessageBoxA(0, "Cannot load textures", "bu", MB_OK);
		throw "very important problem";		/// ������ _exit ������ � ��������� ����������� � �������� 
	}
	this->id = id;
	this->bEnabled = true;
	this->bStatic = false;
	this->bVisible = true;
	this->rect.Set(x, y, x + w, y + h);
	this->tex1 = tex1;
	this->tex2 = tex2;

	sprite = std::make_shared<hgeSprite>(hgeSprite(tex1, 0.0, 0.0, (float)hge->Texture_GetWidth(tex1), (float)hge->Texture_GetHeight(tex1)));
}


bool ButtonWidget::MouseLButton(bool bDown)
{
	if (event)			/// �������� ����������, ���� �� ������
		event(bDown);
	if (bDown)
		sprite->SetTexture(tex2);
	else
		sprite->SetTexture(tex1);
	return true;
}
/*void ButtonWidget::Update(float delta)
{
	hgeGUIObject::Update(delta);
}*/

void ButtonWidget::Render()
{
	sprite->Render4V(rect.x1, rect.y1,
		rect.x2, rect.y1,
		rect.x2, rect.y2,
		rect.x1, rect.y2
		);
}

ButtonWidget::~ButtonWidget()
{
	hge->Texture_Free(tex1);
	hge->Texture_Free(tex2);
}
