#include "Widget.h"


Widget::Widget(int id, float x, float y, float width, float height,int ord)
{
	m_visible = true;
	SetOrder(ord);
	this->id = id;
	m_x = x;
	m_y = y;
	m_height = height;
	m_width = width;
}

Widget::~Widget()
{
}

Widget* Widget::GetWidget(int x, int y)
{
	if (x < m_x || x > m_width+m_x)
		return nullptr;
	if (y < m_y || y > m_height+m_y)
		return nullptr;
	return this;
}

void Widget::Render(HGE* hge)
{

}

void Widget::OnClick()
{

}

void Widget::OnHover(bool)
{

}
