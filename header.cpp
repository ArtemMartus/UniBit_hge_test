#include "header.h"


static HGE* hge = 0;		/// static variable, accessible only from this file
WidgetContainer* container;	/// container objects as usual pointers
WidgetContainer* container2;

/// id of different widgets for HGE API 
const int button1_id = 227;
const int button2_id = 228;
const int image1_id = 229;
const int image2_id = 230;
const int image3_id = 231;

bool initialize()
{
	bool ret = false;
	hge = hgeCreate(HGE_VERSION);
	hge->System_SetState(HGE_FRAMEFUNC, frameFunction);
	hge->System_SetState(HGE_RENDERFUNC, renderFunction);
	hge->System_SetState(HGE_TITLE, "Some title");
	hge->System_SetState(HGE_WINDOWED, true);
	hge->System_SetState(HGE_USESOUND, false);
	hge->System_SetState(HGE_HIDEMOUSE, false);
	ret = hge->System_Initiate();
	if (!ret)
		MessageBoxA(0, hge->System_GetErrorMessage(), "Cannot initiate hge system", MB_OK);


	container = new WidgetContainer();
	container2 = new WidgetContainer();

	/** create widget, set the order and connect to container **/
	auto a = new ButtonWidget(
		button1_id, 100, 100, 200, 120, hge->Texture_Load("button_0.png"), hge->Texture_Load("button_1.png"),
		[](bool bDown)
		{
			container2->Show(!container2->isShown());
		}
	);

	auto b = new ImageWidget(
		image1_id, 340, 125, 200, 200, hge->Texture_Load("2.jpg"),
		[](bool bHover){container->ShowCtrl(image2_id, bHover); });

	auto c = new ImageWidget(
		image2_id, 160, 250, 200, 200, hge->Texture_Load("1.jpg"));


	/** even more widgets for another container **/
	auto d = new ButtonWidget(
		button2_id, 100, 300, 200, 120, hge->Texture_Load("button_2.png"), hge->Texture_Load("button_3.png"),
		[](bool bDown){hge->System_Log("Button2 onClick event %d\n", bDown); });

	auto e = new ImageWidget(
		image3_id, 340, 325, 200, 200, hge->Texture_Load("3.png"));


	a->setOrder(0);
	b->setOrder(3);
	c->setOrder(2);
	d->setOrder(0);
	e->setOrder(1);

	container->AddCtrl(a);
	container->AddCtrl(b);
	container->AddCtrl(c);
	container2->AddCtrl(d);
	container2->AddCtrl(e);

	/// hide second picture
	container->ShowCtrl(image2_id, false);

	/// hide second container
	container2->Show(false);

	return ret;
}

void start()
{
	hge->System_Start();
}

bool frameFunction()
{
	if (hge->Input_GetKeyState(HGEK_ESCAPE)) /// exit if Escape pressed
		return true;

	float dt = hge->Timer_GetDelta();

	container2->Update(dt);
	container->Update(dt);
	
	return false;
}

bool renderFunction()
{
	hge->Gfx_Clear(0);		
	hge->Gfx_BeginScene();	
	container2->Render();	
	container->Render();	
	hge->Gfx_EndScene();	
	return false;
}

void release()
{
	delete container;		
	delete container2;
	hge->System_Shutdown();
	hge->Release();
}