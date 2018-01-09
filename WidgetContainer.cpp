#include "WidgetContainer.h"
#include "ImageWidget.h"
#include "ButtonWidget.h"



WidgetContainer::WidgetContainer() :hgeGUI()
{
	bIsShown = true;
}


void WidgetContainer::Show(bool bShow)
{
	bIsShown = bShow;
	for (auto i = widgets.begin(); i != widgets.end(); ++i){
		(*i)->bVisible = bIsShown;
		(*i)->bEnabled = bIsShown;
	}
}


template<>
void WidgetContainer::AddCtrl(ImageWidget* widget)
{
	if (!widget||widget->connected)
		return;
	widget->connected = true;

	//check whether we already have it
	for (auto i = widgets.begin(); i != widgets.end(); ++i)
		if (*i == widget)
			return;

	auto obj = new ImageWidget(*widget);
	widgets.push_back(obj);
	hgeGUI::AddCtrl(obj);		// HGE takes care about memory management, no need in calling 'delete'
}
template<>
void WidgetContainer::AddCtrl(ButtonWidget* widget)
{
	if (!widget || widget->connected)
		return;
	widget->connected = true;

	//check whether we already have it
	for (auto i = widgets.begin(); i != widgets.end(); ++i)
		if (*i == widget){
		throw "it seems that this widget already added";
		return;
		}

	auto obj = new ButtonWidget(*widget);
	widgets.push_back(obj);
	hgeGUI::AddCtrl(obj);		// HGE takes care about memory management, no need in calling 'delete'
}


void WidgetContainer::DelCtrl(int id)
{
	for (auto i = widgets.begin(); i != widgets.end(); ++i)
		if ((*i)->id == id)
			widgets.remove(*i);
	hgeGUI::DelCtrl(id);
}


WidgetContainer::~WidgetContainer()
{
	widgets.clear();
}


std::list<Widget*>& WidgetContainer::GetWidgets()
{
	return widgets;
}

