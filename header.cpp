#include "header.h"
#include <vector>
#include <set>



/**
**		Use of smart pointers is overcomplicated because of HGE's user unfriendly copy constructor
**/




static HGE* hge = 0;			/// static variable, accessible only from this file

WidgetContainer* container1;	/// container objects as usual pointers
WidgetContainer* container2;

HTEXTURE tex_button0;
HTEXTURE tex_button1;
HTEXTURE tex_button2;
HTEXTURE tex_button3;

HTEXTURE tex_image0;
HTEXTURE tex_image1;
HTEXTURE tex_image2;

ButtonWidget* button0;
ButtonWidget* button1;

ImageWidget* image0;
ImageWidget* image1;
ImageWidget* image2;


/// id of different widgets for HGE API 
const int button0_id = 227;
const int button1_id = 228;

const int image0_id = 229;
const int image1_id = 230;
const int image2_id = 231;

bool Initialize()
{
	bool ret = false;
	hge = hgeCreate(HGE_VERSION);
	hge->System_SetState(HGE_FRAMEFUNC, FrameFunction);
	hge->System_SetState(HGE_RENDERFUNC, RenderFunction);
	hge->System_SetState(HGE_TITLE, "Some title");
	hge->System_SetState(HGE_WINDOWED, true);
	hge->System_SetState(HGE_USESOUND, false);
	hge->System_SetState(HGE_HIDEMOUSE, false);
	ret = hge->System_Initiate();
	if (!ret)
		MessageBoxA(0, hge->System_GetErrorMessage(), "Cannot initiate hge system", MB_OK);


	tex_button0 = hge->Texture_Load("button_0.png");
	tex_button1 = hge->Texture_Load("button_1.png");
	tex_button2 = hge->Texture_Load("button_2.png");
	tex_button3 = hge->Texture_Load("button_3.png");

	tex_image0 = hge->Texture_Load("image_0.jpg");
	tex_image1 = hge->Texture_Load("image_1.jpg");
	tex_image2 = hge->Texture_Load("image_2.png");

	container1 = new WidgetContainer();
	container2 = new WidgetContainer();

	auto button1_onClick = [](bool bDown){ MessageBoxA(0,"You've clicked a button!","Achivement unlocked",MB_OK); };
	
	/**									images **/
	image0 = new ImageWidget(
		image0_id, 340, 125, 200, 200, tex_image0,
		[](bool bHover){
			container1->ShowCtrl(image1_id, bHover);
		},/*order*/ 3);
	image1 = new ImageWidget(
		image1_id, 160, 250, 200, 200, tex_image1, nullptr,/*order*/9);
	image2 = new ImageWidget(
		image2_id, 340, 325, 200, 200, tex_image2, nullptr, /*order*/ 1);


	/**									buttons **/

	button0 = new ButtonWidget(
		button0_id, 100, 100, 200, 120, tex_button0, tex_button1,
		[](bool bDown){container2->Show(!container2->bIsShown);});
	button1 = new ButtonWidget(
		button1_id, 100, 300, 200, 120, tex_button2, tex_button3);
	button1->SetEvent(button1_onClick);
	


	container1->AddCtrl(button0);
	container1->AddCtrl(image0);
	container1->AddCtrl(image1);
	container1->AddCtrl(image1);	// second time, whoops

	container2->AddCtrl(image1);	// try asigning widget to another container
	container2->AddCtrl(button1);
	container2->AddCtrl(image2);

	/// hide second picture
	container1->ShowCtrl(image1_id, false);

	/// hide second container
	container2->Show(false);

	delete button0;
	delete button1;

	delete image0;
	delete image1;
	delete image2;

	return ret;
}


void Start()
{
	hge->System_Start();
}


bool FrameFunction()
{
	if (hge->Input_GetKeyState(HGEK_ESCAPE)) /// exit if Escape pressed
		return true;

	float dt = hge->Timer_GetDelta();

	container2->Update(dt);
	container1->Update(dt);
	
	return false;
}


bool RenderFunction()
{
	hge->Gfx_Clear(0);		
	hge->Gfx_BeginScene();	
	/* init render objects queue by order */
	std::vector<Widget*> renderObjects;
	
	// widget1
	{
		auto widgets = container1->GetWidgets();	// retrieve list of objs from container1 iterator
		for (auto b = widgets.begin(); b != widgets.end(); ++b)
			renderObjects.push_back(*b);
	}

	// widget2
	{
		auto widgets = container2->GetWidgets();	// retrieve list of objs from container2 iterator
		for (auto b = widgets.begin(); b != widgets.end(); ++b)
			renderObjects.push_back(*b);
	}

	std::sort(renderObjects.begin(), renderObjects.end(), [](Widget*a, Widget*b){
		return a->order < b->order; 
	});

	/* render objects*/
	for (auto a = renderObjects.begin(); a != renderObjects.end(); ++a){
		auto obj = *a;
		if (obj->bVisible)
			obj->Render();
	}

	hge->Gfx_EndScene();	
	return false;
}


void Release()
{
	delete container2;
	delete container1;	

	hge->Texture_Free(tex_button0);
	hge->Texture_Free(tex_button1);
	hge->Texture_Free(tex_button2);
	hge->Texture_Free(tex_button3);

	hge->Texture_Free(tex_image0);
	hge->Texture_Free(tex_image1);
	hge->Texture_Free(tex_image2);

	hge->System_Shutdown();
	hge->Release();
}


/*
1. стиль
1.1 minor. квалификаторы const то есть то нет
2 widget
2.1 SetOrder - всегда ли работает?
2.2 minor. widget является hgeGUIObject хотя по-сути hgeGUIObject - это деталь реализации
2.3 minor. установка всех обработчиков в конструкторе - несколько ограничивает варианты использования и усложняет добавление новых обработчиков
3 widgetcontainer
3.1 AddCtrl - что произойдет если добавить виджет в контейнер несколько раз? или добавить в разные коньейнеры?
4.2 как выставить порядок отрисовки контейнеров если нужно расположить несколько контейнеров на экране. вариант со сквозным порядком для всех виджетов не слишком хорошо масштабируется требуется исправление
*/