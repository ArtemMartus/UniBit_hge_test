#pragma once
#include <string>
#include <memory>
#include <functional>
#include <hge.h>
#include <hgegui.h>

/************************************************************************/
/* Widget --interface--						                            */
/************************************************************************/
class Widget 
{
protected:

	int order;							/// place in render queue 
	int id;
	hgeQuad quad;
	
public:
		
	Widget(int id =0,float x = 0, float y = 0, float width = 128, float height = 128,int order=0);
	virtual ~Widget();
	void SetOrder(int ord){ order = ord; }
	int GetOrder(){ return order; }
	void SetId(int id){ this->id = id; }
	int GetId(){ return id; }
	Widget* GetWidget(int x, int y);

	virtual void Render(HGE* hge);
	virtual void OnClick();
	virtual void OnHover(bool);

	std::function<void(bool)> onClick;	/// callback holder
	std::function<void(bool)> onHover;	/// callback holder

	float m_x = 0;
	float m_y = 0;
	float m_width = 128;
	float m_height = 128;
	bool m_visible = true;
	bool connected = false;
};

