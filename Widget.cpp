#include "Widget.h"


Widget::Widget(int ord ) : hgeGUIObject()
{
	order = ord;
	connected = false;
}

Widget::~Widget()
{
}


Widget::Widget(Widget& object) : hgeGUIObject()
{
	this->bEnabled = object.bEnabled;
	this->bStatic = object.bStatic;
	this->bVisible = object.bVisible;
	this->order = object.order;
	this->rect = object.rect;
	this->id = object.id;
	this->event = object.event;
	this->connected = object.connected;
}

void Widget::SetEvent(std::function<void(bool)> fEvent)
{
	event = fEvent;
}
