#include "header.h"
#include <vector>
#include <set>



HGE* hge = 0;			

std::shared_ptr<WidgetContainer> container1;	
std::shared_ptr<WidgetContainer> container2;

std::vector<std::shared_ptr<WidgetContainer>> renderObjects;

HTEXTURE tex_button0;
HTEXTURE tex_button1;
HTEXTURE tex_button2;
HTEXTURE tex_button3;

HTEXTURE tex_image0;
HTEXTURE tex_image1;
HTEXTURE tex_image2;

std::shared_ptr<ButtonWidget> button0;
std::shared_ptr<ButtonWidget> button1;

std::shared_ptr<ImageWidget> image0;
std::shared_ptr<ImageWidget> image1;
std::shared_ptr<ImageWidget> image2;


/// id of different widgets 
#define button0_id  227
#define button1_id  228

#define image0_id  229
#define image1_id  230
#define image2_id  231

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

	container1 = std::make_shared < WidgetContainer>(1);
	container2 = std::make_shared < WidgetContainer>();

	/**									images **/
	auto image0_onHover = [](bool bHover){
		image1->m_visible= bHover;
	};

	image0 = std::make_shared<ImageWidget>();
	image0->SetId(image0_id);
	image0->m_x = 340;
	image0->m_y = 125;
	image0->m_height = 200;
	image0->m_width = 200;
	image0->SetTexture(tex_image0);
	image0->onHover = image0_onHover;
	image0->SetOrder(3);

	image1 = std::make_shared<ImageWidget>(image1_id, 160, 250, 200, 200, tex_image1, nullptr, 4);

	image2 = std::make_shared<ImageWidget>(image2_id, 340, 325, 200, 200, tex_image2, nullptr, 1);



	/**									buttons **/

	button0 = std::make_shared<ButtonWidget>(button0_id, 100, 100, 200, 120, tex_button3, tex_button2,
		[](bool bDown){container2->Show(bDown); });
	button0->SetTextureOff(tex_button0);
	button0->SetTextureOn(tex_button1);

	button1 = std::make_shared<ButtonWidget>(button1_id, 100, 300, 200, 120, tex_button2, tex_button3);

	auto button1_onClick = [&](bool){ 
		auto old = container1->GetCtrl(image0_id)->GetOrder();
		container1->UpdateOrder(image0_id, old + 1);
	};

	button1->onClick = button1_onClick;





	container1->AddCtrl(static_cast<std::shared_ptr<Widget>>(button0));
	container1->AddCtrl(static_cast<std::shared_ptr<Widget>>(image0));
	container1->AddCtrl(static_cast<std::shared_ptr<Widget>>(image1));
	container1->AddCtrl(static_cast<std::shared_ptr<Widget>>(image1));	// second time, whoops

	container2->AddCtrl(static_cast<std::shared_ptr<Widget>>(image1));	// try asigning widget to another container
	container2->AddCtrl(static_cast<std::shared_ptr<Widget>>(button1));
	container2->AddCtrl(static_cast<std::shared_ptr<Widget>>(image2));

	/// hide second picture
	image1->m_visible = false;

	/// hide second container
	container2->Show(false);

	renderObjects.push_back(container1);
	renderObjects.push_back(container2);

	std::sort(renderObjects.begin(), renderObjects.end(), [](const std::shared_ptr<WidgetContainer>&a, const std::shared_ptr<WidgetContainer>&b){
		return a->GetOrder() < b->GetOrder();
	});

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

	container2->Update();
	container1->Update();
	
	return false;
}


bool RenderFunction()
{
	hge->Gfx_BeginScene();
	hge->Gfx_Clear(0);		

	/* render objects*/
	for (auto a = renderObjects.begin(); a != renderObjects.end(); ++a){
		auto obj = *a;
		obj->Render();
	}

	hge->Gfx_EndScene();	
	return false;
}


void Release()
{
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
