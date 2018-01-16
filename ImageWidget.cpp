#include "ImageWidget.h"



ImageWidget::ImageWidget(int id, float x, float y, float w, float h, HTEXTURE tex1, std::function<void(bool)> mouseOver, int ord) :Widget(id,x,y,w,h,ord)
{

	onHover = mouseOver;
	quad.tex = tex1;
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


void ImageWidget::Render(HGE* hge)
{
	if (!quad.tex)
	{
		MessageBoxA(0, "Cannot load textures", "bu", MB_OK);
		throw "very important problem";
		return;
	}


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


void ImageWidget::SetTexture(HTEXTURE tex1)
{
	quad.tex = tex1;
}


void ImageWidget::OnHover(bool bOver)
{
	if (onHover)
		onHover(bOver);
}

ImageWidget::~ImageWidget()
{
}
