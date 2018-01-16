#pragma once

#include <string>
#include <vector>
#include <list>
#include <memory>
#include <algorithm>
#include <hge.h>
#include <hgegui.h>
#include "Widget.h"


class WidgetContainer
{

	std::vector < std::shared_ptr<Widget> > widgets;
	HGE* hge;
	int order;
public:
	bool bIsShown;
	WidgetContainer(int order=0);
	~WidgetContainer();
	void Show(bool bShow);
	void Update();
	void Render();
	void AddCtrl(std::shared_ptr<Widget>& obj);	
	void DelCtrl(int id);
	void UpdateOrder(int id, int newOrder);
	int GetOrder(){ return order; };
	std::shared_ptr<Widget>& GetCtrl(int id);
};

