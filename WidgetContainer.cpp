#include "WidgetContainer.h"
#include "ImageWidget.h"
#include "ButtonWidget.h"
#include <windows.h>


WidgetContainer::WidgetContainer(int ord) 
{
	order = ord;
	bIsShown = true;
	hge = hgeCreate(HGE_VERSION);
	hge->System_Initiate();
}


void WidgetContainer::Show(bool bShow)
{
	bIsShown = bShow;
	for (auto i = widgets.begin(); i != widgets.end(); ++i){
		(*i)->m_visible = bIsShown;
	}
}



void WidgetContainer::Update()
{
	float x = 0;
	float y = 0;
	hge->Input_GetMousePos(&x, &y);
	Widget* m_widget=0;
	for (auto i = widgets.begin(); i != widgets.end(); ++i)
	{
		auto tmp = *i;
		Widget * widget = 0;
		widget = tmp->GetWidget(x, y);
		if (widget)
			if (!m_widget)
			{
				m_widget = widget;
				m_widget->OnHover(true);
				continue;
			}
			else
			{
				if (widget->GetOrder() > m_widget->GetOrder()){
					m_widget = widget;
					m_widget->OnHover(true);
					continue;
				}
			}
		tmp->OnHover(false);
	}
	if (hge->Input_GetKey() == VK_LBUTTON&&m_widget)
		m_widget->OnClick();
}

void WidgetContainer::Render()
{
	for (auto i = widgets.begin(); i != widgets.end(); ++i)
	{
		auto tmp = *i;
		if (tmp->m_visible)
			tmp->Render(hge);
	}
}

void WidgetContainer::AddCtrl(std::shared_ptr<Widget>& widget)
{
	if (!widget || widget->connected)
		return;
	widget->connected = true;

	//check whether we already have it
	auto check = std::find(widgets.begin(), widgets.end(), widget);
	if (check != widgets.end()){
		throw "it seems that this widget already added";
		return;
	}

	widgets.push_back(widget);

	std::sort(widgets.begin(), widgets.end(), [](const std::shared_ptr<Widget>& a, const std::shared_ptr<Widget>& b){return a->GetOrder() < b->GetOrder(); });
}


void WidgetContainer::DelCtrl(int id)
{
	for (auto i = widgets.begin(); i != widgets.end(); ++i)
		if ((*i)->GetId() == id)
			widgets.erase(i);
	std::sort(widgets.begin(), widgets.end(), [](const std::shared_ptr<Widget>& a, const std::shared_ptr<Widget>& b){return a->GetOrder() < b->GetOrder(); });
}


void WidgetContainer::UpdateOrder(int id, int newOrder)
{
	auto a = GetCtrl(id);
	if (!a)
		return;
	a->SetOrder(newOrder);
	std::sort(widgets.begin(), widgets.end(), [](const std::shared_ptr<Widget>& a, const std::shared_ptr<Widget>& b){return a->GetOrder() < b->GetOrder(); });
}

std::shared_ptr<Widget> &WidgetContainer::GetCtrl(int id)
{
	for (auto i = widgets.begin(); i != widgets.end(); ++i)
		if ((*i)->GetId() == id)
			return *i;
}

WidgetContainer::~WidgetContainer()
{
	widgets.clear();
	hge->Release();
}



