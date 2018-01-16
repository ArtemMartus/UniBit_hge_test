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

public:
	ImageWidget(int id=0, float x=0.0f, float y=0.0f, float w=0.0f, float h=0.0f, HTEXTURE tex1=0, std::function<void(bool)> mouseOver = nullptr, int order = 0);
	~ImageWidget();

	void Render(HGE* hge) override;
	void SetTexture(HTEXTURE tex1);
	void OnHover(bool bOver) override;
};

