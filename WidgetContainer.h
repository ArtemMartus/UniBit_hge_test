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
	/** Inner structure for sorting elements **/
	/*struct classcomp {
		bool operator() (Widget* lhs, Widget* rhs) const
		{
			return lhs->GetOrder() < rhs->GetOrder();		/// Sort widgets by their order in queue
		}
	};
	std::set<Widget*, classcomp> widgets;*/
	std::list<Widget*> widgets;

public:
	bool bIsShown;

	WidgetContainer();
	~WidgetContainer();
	WidgetContainer(WidgetContainer&obj);
	//void Render();
	void Show(bool bShow);

	std::list<Widget*>& GetWidgets();
	template<class T>
	void AddCtrl(T* obj);		/// We can add only Widget objects, but not the hgeGUIObject as in super class
	void DelCtrl(int id);
};

