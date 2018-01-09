#pragma once
#include <string>
#include <memory>
#include <functional>
#include <hge.h>
#include <hgegui.h>

/************************************************************************/
/* Widget --interface--						                            */
/************************************************************************/
class Widget :
	public hgeGUIObject
{
protected:
	std::function<void(bool)> event;	/// callback holder

public:
	int order;							/// place in render queue 
	bool connected;

	virtual void Render()=0;		
	Widget(int order=0);
	~Widget();
	Widget(Widget& object);
	void SetOrder(int ord);
	int GetOrder();
	void SetEvent(std::function<void(bool)> fEvent);
};

