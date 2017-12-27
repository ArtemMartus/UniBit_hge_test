#include "WidgetContainer.h"


WidgetContainer::WidgetContainer() :hgeGUI()
{
}

void WidgetContainer::Render()
{
	/// ������ ��� �������� ��������� �� �������. ��� ��� ��� ������������� �� �� ������� � ������� - �������� ������ �������� ��
	for (auto i = widgets.begin(); i != widgets.end(); ++i)
	{
		auto pi = *i;
		if (!pi->bVisible) /// ���� ������� ������� ��� �� ����� ��������
			continue;
		pi->Render();
	}
	//hgeGUI::Render();		
}

void WidgetContainer::AddCtrl(Widget *widget)
{
	widgets.insert(widget);
	hgeGUI::AddCtrl(widget);
}

void WidgetContainer::DelCtrl(int id)
{
	Widget* widget = (Widget*)GetCtrl(id);	// �� ������ ������ ��������
	if (widget)
		widgets.erase(widget);
	hgeGUI::DelCtrl(id);
}

/*int WidgetContainer::Update(float dt)
{
	return hgeGUI::Update(dt);
}*/

WidgetContainer::~WidgetContainer()
{

}

