#include "WidgetContainer.h"


WidgetContainer::WidgetContainer() :hgeGUI()
{
}

void WidgetContainer::Render()
{
	/// Рисуем все элементы коллекции по очереди. Так как они отсортированы по их позиции в очереди - получаем рендер согласно тз
	for (auto i = widgets.begin(); i != widgets.end(); ++i)
	{
		auto pi = *i;
		if (!pi->bVisible) /// Если элемент спрятан его не стоит рисовать
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
	Widget* widget = (Widget*)GetCtrl(id);	// На всякий случай проверим
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

