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
	/** Inner structure for sorting elements **/
	struct classcomp {
		bool operator() (Widget* lhs, Widget* rhs) const
		{
			return lhs->getOrder() < rhs->getOrder();		/// Sort widgets by their order in queue
		}
	};
	std::set<Widget*, classcomp> widgets;
	bool bIsShown;
public:
	
	WidgetContainer();
	~WidgetContainer();
	void Render();
	void Show(bool bShow);
	bool isShown();

	void AddCtrl(Widget *ctrl);		/// We can add only Widget objects, but not the hgeGUIObject as in super class
	void DelCtrl(int id);
};

