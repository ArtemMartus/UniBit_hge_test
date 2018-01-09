#include "header.h"
/************************************************************************/
/* Whole logic moved to header.cpp					                    */
/************************************************************************/

int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nShowCmd)
{
	Initialize(); /// initialization, image loading, buttons creations
	Start();	  /// Enter render cycle
	Release();	 
	return 0;
}
