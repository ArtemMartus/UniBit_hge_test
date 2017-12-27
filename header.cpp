#include "header.h"


static HGE* hge = 0;		/// ����������� ���������� ��������� ������ �� ����� �����
WidgetContainer* container;	/// ��������� ���������� ��������

/// id ������ ������ ��� ������������ ������� � ��� ����� HGE API 
const int button_id = 227;
const int image1_id = 228;
const int image2_id = 229;

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

	/** ������� ������ � ����������� �� �� ������� � ������� �� ���������**/
	auto c = new ButtonWidget(
		button_id, 100, 100, 200, 120, hge->Texture_Load("button_0.png"), hge->Texture_Load("button_1.png"),
		[](bool bDown){hge->System_Log("Button onClick event %d\n", bDown); });
	c->setOrder(0);
	container->AddCtrl(c);

	auto b = new ImageWidget(
		image1_id, 340, 125, 200, 200, hge->Texture_Load("2.jpg"),
		[](bool bHover){container->ShowCtrl(image2_id, bHover); });
	b->setOrder(5);
	container->AddCtrl(b);

	auto a = new ImageWidget(
		image2_id, 160, 250, 200, 200, hge->Texture_Load("1.jpg"));
	a->setOrder(1);
	container->AddCtrl(a);

	/// ������ ������ ��������
	container->ShowCtrl(image2_id, false);
	return ret;
}

void start()
{
	hge->System_Start();
}

bool frameFunction()
{
	if (hge->Input_GetKeyState(HGEK_ESCAPE)) /// ������� �� ����� ���������, ���� ������������ ����� Esc
		return true;

	float dt = hge->Timer_GetDelta();

	container->Update(dt);

	return false;
}

bool renderFunction()
{
	hge->Gfx_Clear(0);		// ������� �����
	hge->Gfx_BeginScene();	// �������� ��������
	container->Render();	// ������� ���������� �������� ��������
	hge->Gfx_EndScene();	// ����� ���������
	return false;
}

void release()
{
	delete container;
	hge->System_Shutdown();
	hge->Release();
}