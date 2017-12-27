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
	/** ���������� ��������� ��� ���������� ��������� ��������**/
	struct classcomp {
		bool operator() (Widget* lhs, Widget* rhs) const
		{
			return lhs->getOrder() < rhs->getOrder();		/// ��������� ������� �� �� ������� � �������
		}
	};
	std::set<Widget*, classcomp> widgets;
public:
	
	WidgetContainer();
	~WidgetContainer();
	//int Update(float dt);  
	void Render();
	void AddCtrl(Widget *ctrl);		/// �������� ����� ������ ������ Widget, �� �� hgeGUIObject
	void DelCtrl(int id);
};

