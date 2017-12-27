#include "Widget.h"


Widget::Widget(std::function<void(bool)> _event ) :event(_event), hgeGUIObject()
{
	order = 0;
}
Widget::~Widget()
{

}
void Widget::setOrder(unsigned char ord)
{
	order = ord;
}
unsigned char Widget::getOrder()
{
	return order;
}