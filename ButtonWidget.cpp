#include "ButtonWidget.h"


ButtonWidget::ButtonWidget(int id, float x, float y, float w, float h, HTEXTURE tex1, HTEXTURE tex2, std::function<void(bool)> onClick, int ord) :Widget(id, x, y, w, h, ord)
{
	this->tex1 = tex1;
	this->tex2 = tex2;
	this->bPressed = false;
	this->onClick = onClick;

	quad.v[0].tx = 0;
	quad.v[0].ty = 0;
	quad.v[1].tx = 1;
	quad.v[1].ty = 0;
	quad.v[2].tx = 1;
	quad.v[2].ty = 1;
	quad.v[3].tx = 0;
	quad.v[3].ty = 1;

	quad.blend = BLEND_DEFAULT;

	for (int i = 0; i < 4; i++)
	{
		quad.v[i].z = 0.0f;
		quad.v[i].col = 0xFFFFFFFF;
	}
}


void ButtonWidget::Render(HGE* hge)
{
	if (!tex1 || !tex2)
	{
		MessageBoxA(0, "Cannot load textures", "bu", MB_OK);
		throw "very important problem";		/// exit with some information about the problem 
		return;
	}



	
	if (bPressed)
		quad.tex = tex2;
	else
		quad.tex = tex1;

	quad.v[0].x = m_x;
	quad.v[0].y = m_y;
	

	quad.v[1].x = m_x + m_width;
	quad.v[1].y = m_y;
	

	quad.v[2].x = m_x + m_width;
	quad.v[2].y = m_y + m_height;


	quad.v[3].x = m_x;
	quad.v[3].y = m_y + m_height;


	hge->Gfx_RenderQuad(&quad);
}


void ButtonWidget::SetTextureOn(HTEXTURE tex2)
{
	if (tex2)
		this->tex2 = tex2;
}

void ButtonWidget::SetTextureOff(HTEXTURE tex1)
{
	if (tex1)
		this->tex1 = tex1;
}

void ButtonWidget::OnClick()
{
	bPressed = !bPressed;
	if (onClick)
		onClick(bPressed);
}

ButtonWidget::~ButtonWidget()
{
}
