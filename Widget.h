#pragma once
#include <string>
#include <memory>
#include <functional>
#include <hge.h>
#include <hgegui.h>

/************************************************************************/
/* Widget interface							                            */
/************************************************************************/
class Widget :
	public hgeGUIObject
{
protected:
	std::function<void(bool)> event;	/// callback holder
	unsigned char order;				/// place in render queue (0-ff)
public:
	virtual void Render()=0;		
	Widget(std::function<void(bool)> event = nullptr);
	~Widget();
	void setOrder(unsigned char ord);
	unsigned char getOrder();
};

