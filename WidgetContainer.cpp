#include "WidgetContainer.h"
#include "ImageWidget.h"
#include "ButtonWidget.h"

WidgetContainer::WidgetContainer() :hgeGUI()
{
	bIsShown = true;
}


WidgetContainer::WidgetContainer(WidgetContainer&obj)
{
	throw "never called";
}

/*void WidgetContainer::Render()
{
	/// Draw all elements in their order. As they sorted by their place in queue we get correct rendering
	for (auto i = widgets.begin(); i != widgets.end(); ++i)
	{
		auto pi = *i;
		if (!pi->bVisible) /// If element is hidden - don't show it
			continue;
		pi->Render();
	}
}*/
/*
bool WidgetContainer::IsShown()
{
	return bIsShown;
}
*/
void WidgetContainer::Show(bool bShow)
{
	bIsShown = bShow;
	for (auto i = widgets.begin(); i != widgets.end(); ++i){
		(*i)->bVisible = bIsShown;
		(*i)->bEnabled = bIsShown;
	}
}

/*void WidgetContainer::AddCtrl(Widget *widget)
{
	widgets.insert(widget);
	hgeGUI::AddCtrl(widget);
}*/

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


/*void WidgetContainer::DelCtrl(int id)
{
	Widget* widget = (Widget*)GetCtrl(id);
	if (widget)
		widgets.erase(widget);
	hgeGUI::DelCtrl(id);
}*/

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

/*void WidgetContainer::ShowCtrl(int id, bool bShow)
{
	for (auto i = widgets.begin(); i != widgets.end(); ++i)
		if ((*i)->id == id)
			(*i)->bVisible = bShow;
}*/

std::list<Widget*>& WidgetContainer::GetWidgets()
{
	/*if (!bIsShown)
		return 0; */
	return widgets;
}

