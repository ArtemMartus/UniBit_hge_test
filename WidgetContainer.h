#pragma once

#include <string>
#include <set>
#include <memory>
#include <algorithm>
#include <hge.h>
#include <hgegui.h>
#include "Widget.h"

class WidgetContainer:
	public hgeGUI
{
	/** Внутренняя структура для сортировки коллекции виджетов**/
	struct classcomp {
		bool operator() (Widget* lhs, Widget* rhs) const
		{
			return lhs->getOrder() < rhs->getOrder();		/// сортируем виджеты по их порядку в очереди
		}
	};
	std::set<Widget*, classcomp> widgets;
public:
	
	WidgetContainer();
	~WidgetContainer();
	//int Update(float dt);  
	void Render();
	void AddCtrl(Widget *ctrl);		/// Добавить можно только объект Widget, но не hgeGUIObject
	void DelCtrl(int id);
};

