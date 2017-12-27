#include "ImageWidget.h"



ImageWidget::ImageWidget(int id, float x, float y, float w, float h, HTEXTURE tex1, std::function<void(bool)> mouseOver) :Widget(mouseOver)
{
	if (!tex1)
	{
		MessageBoxA(0, "Cannot load textures", "bu", MB_OK);
		throw "very important problem";
	}

	this->id = id;
	this->bEnabled = true;
	this->bStatic = false;
	this->bVisible = true;
	this->rect.Set(x, y, x + w, y + h);
	this->tex1 = tex1;

	sprite = std::make_shared<hgeSprite>(hgeSprite(tex1, 0.0, 0.0, (float)hge->Texture_GetWidth(tex1), (float)hge->Texture_GetHeight(tex1)));
}


void ImageWidget::MouseOver(bool bOver)
{
	if (event)		/// Если есть обработчик - вызываем его
		event(bOver);
}

/*void ImageWidget::Update(float delta)
{
	hgeGUIObject::Update(delta);
}*/

void ImageWidget::Render()
{
	sprite->Render4V(rect.x1, rect.y1, 
		rect.x2, rect.y1,
		rect.x2, rect.y2, 
		rect.x1, rect.y2
		);
}

ImageWidget::~ImageWidget()
{
	hge->Texture_Free(tex1);
}
