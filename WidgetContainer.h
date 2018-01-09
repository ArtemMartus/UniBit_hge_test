#pragma once

#include <string>
//#include <set>
#include <list>
#include <memory>
#include <algorithm>
#include <hge.h>
#include <hgegui.h>
#include "Widget.h"


class WidgetContainer:
	public hgeGUI
{
	std::list<Widget*> widgets;

public:
	bool bIsShown;

	WidgetContainer();
	~WidgetContainer();
	void Show(bool bShow);

	std::list<Widget*>& GetWidgets();
	template<class T>
	void AddCtrl(T* obj);	
	void DelCtrl(int id);
};

