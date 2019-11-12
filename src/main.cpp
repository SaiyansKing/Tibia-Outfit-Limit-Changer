#include "main.h"
#include <stdio.h>

#include <vector>

HWND hPath;
HWND hLimit;
HINSTANCE hInstance;

char exefile[MAX_PATH];
char exefile2[MAX_PATH];
char outfitLimit[12];
std::vector<unsigned char> clientData;

void CreateClient()
{
	GetWindowText(hPath, exefile, MAX_PATH);
	GetWindowText(hLimit, outfitLimit, 12);
	
	DWORD limit = (DWORD)strtoul(outfitLimit, NULL, 0);
	if(limit == 0)
	{
		MessageBoxA(NULL, "You didn't specify outfit limit", "Tibia Outfit Limit Changer", 0x10);
		return;
	}
	else if(limit > 65535)
	{
		MessageBoxA(NULL, "Internal outfit limit is 65535", "Tibia Outfit Limit Changer", 0x10);
		return;
	}
	DWORD fixedStartAddons = limit*4;
	DWORD fixedStartNames = limit*8;
	
	FILE* clientFile = fopen(exefile, "rb");
	if(!clientFile)
	{
		MessageBoxA(NULL, "Tibia Client not found", "Tibia Outfit Limit Changer", 0x10);
		return;
	}
	
	fseek(clientFile, 0, SEEK_END);
	long int clientSize = ftell(clientFile);
	clientData.resize(clientSize);
	fseek(clientFile, 0, SEEK_SET);
	fread(&clientData[0], 1, (size_t)clientSize, clientFile);
	fclose(clientFile);
	
	DWORD Client_EntryPoint = reinterpret_cast<PIMAGE_NT_HEADERS>(&clientData[0] + reinterpret_cast<PIMAGE_DOS_HEADER>(&clientData[0])->e_lfanew)->OptionalHeader.AddressOfEntryPoint;
	if(Client_EntryPoint == 0x15D02B)//854
	{
		sprintf(exefile2, "%s.old", exefile);
		rename(exefile, exefile2);
		
		//Set correct value for memory allocation
		*(DWORD*)(&clientData[0x9C60C]) = 0x28E + (limit * 38);
		*(DWORD*)(&clientData[0x13A0C]) = 0x1C + (limit * 8);
		*(DWORD*)(&clientData[0x13A20]) = limit * 30;
		
		//Disable min(1)/max(25) outfit check - to change it we'll need to jump(don't have time for that implementation)
		*(BYTE*)(&clientData[0x964A3]) = 0xB8;
		*(DWORD*)(&clientData[0x964A4]) = 1;
		*(BYTE*)(&clientData[0x13A7B]) = 0xB8;
		*(DWORD*)(&clientData[0x13A7C]) = 1;
		*(DWORD*)(&clientData[0x13A87]) = 0x08;
		for(int i = 0; i < 8; ++i)
			*(BYTE*)(&clientData[0x964A8 + i]) = 0x90;
		for(int i = 0; i < 5; ++i)
			*(BYTE*)(&clientData[0x13A80 + i]) = 0x90;

		//Set correct values for addons/outfit colors
		*(DWORD*)(&clientData[0x8772B]) = 0x288 + fixedStartAddons;
		*(DWORD*)(&clientData[0x877FD]) = 0x288 + fixedStartAddons;
		*(DWORD*)(&clientData[0x87828]) = 0x288 + fixedStartAddons;
		*(DWORD*)(&clientData[0x96588]) = 0x288 + fixedStartAddons;
		*(DWORD*)(&clientData[0x9659F]) = 0x288 + fixedStartAddons;
		*(DWORD*)(&clientData[0x965BA]) = 0x288 + fixedStartAddons;
		*(DWORD*)(&clientData[0x96B2D]) = 0x288 + fixedStartAddons;

		//Set correct values for outfit names
		*(DWORD*)(&clientData[0x8788F]) = 0x288 + fixedStartNames;
		*(DWORD*)(&clientData[0x965D1]) = 0x288 + fixedStartNames;
		*(DWORD*)(&clientData[0x96B94]) = 0x288 + fixedStartNames;
		
		if(limit > 255)
		{
			//change outfit size network msg to uint16_t
			*(DWORD*)(&clientData[0x13A71]) = 0x000E157B;
			*(BYTE*)(&clientData[0x13A76]) = 0xB7;
		}
	}
	else if(Client_EntryPoint == 0x1625EB)//860
	{
		sprintf(exefile2, "%s.old", exefile);
		rename(exefile, exefile2);
		
		//Set correct value for memory allocation
		*(DWORD*)(&clientData[0xA09FC]) = 0x28E + (limit * 38);
		*(DWORD*)(&clientData[0x13D9C]) = 0x1C + (limit * 8);
		*(DWORD*)(&clientData[0x13DB0]) = limit * 30;
		
		//Disable min(1)/max(25) outfit check - to change it we'll need to jump(don't have time for that implementation)
		*(BYTE*)(&clientData[0x98B83]) = 0xB8;
		*(DWORD*)(&clientData[0x98B84]) = 1;
		*(BYTE*)(&clientData[0x13E0B]) = 0xB8;
		*(DWORD*)(&clientData[0x13E0C]) = 1;
		*(BYTE*)(&clientData[0x13E17]) = 0x08;
		for(int i = 0; i < 8; ++i)
			*(BYTE*)(&clientData[0x98B88 + i]) = 0x90;
		for(int i = 0; i < 5; ++i)
			*(BYTE*)(&clientData[0x13E10 + i]) = 0x90;

		//Set correct values for addons/outfit colors
		*(DWORD*)(&clientData[0x880BB]) = 0x288 + fixedStartAddons;
		*(DWORD*)(&clientData[0x8818D]) = 0x288 + fixedStartAddons;
		*(DWORD*)(&clientData[0x881B8]) = 0x288 + fixedStartAddons;
		*(DWORD*)(&clientData[0x98C68]) = 0x288 + fixedStartAddons;
		*(DWORD*)(&clientData[0x98C7F]) = 0x288 + fixedStartAddons;
		*(DWORD*)(&clientData[0x98C9A]) = 0x288 + fixedStartAddons;
		*(DWORD*)(&clientData[0x9920D]) = 0x288 + fixedStartAddons;

		//Set correct values for outfit names
		*(DWORD*)(&clientData[0x8821F]) = 0x288 + fixedStartNames;
		*(DWORD*)(&clientData[0x98CB1]) = 0x288 + fixedStartNames;
		*(DWORD*)(&clientData[0x99274]) = 0x288 + fixedStartNames;
		
		if(limit > 255)
		{
			//change outfit size network msg to uint16_t
			*(DWORD*)(&clientData[0x13E01]) = 0x000E5DFB;
			*(BYTE*)(&clientData[0x13E06]) = 0xB7;
		}
	}
	else
	{
		MessageBoxA(NULL, "Tibia Client is not supported", "Tibia Outfit Limit Changer", 0x10);
		return;
	}
	
	clientFile = fopen(exefile, "wb");
	if(!clientFile)
	{
		MessageBoxA(NULL, "Cannot save modified client", "Tibia Outfit Limit Changer", 0x10);
		return;
	}
	fwrite(&clientData[0], 1, clientData.size(), clientFile);
	fclose(clientFile);
}
	
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;
	switch(message)
	{
		case WM_CREATE:
		{
			hPath = CreateWindow("edit", "Path to Tibia.exe", WS_CHILD|WS_VISIBLE|WS_BORDER|ES_AUTOHSCROLL, 5, 5, 260, 20, hWnd, (HMENU)IDC_B, hInstance, 0);
			CreateWindow("button", "...", WS_CHILD|WS_VISIBLE|WS_BORDER, 270, 5, 25, 20, hWnd, (HMENU)IDC_A, hInstance, 0);
			hLimit = CreateWindow("edit", "Outfits Limit", WS_CHILD|WS_VISIBLE|WS_BORDER|ES_AUTOHSCROLL, 5, 30, 290, 20, hWnd, (HMENU)IDC_C, hInstance, 0);
			CreateWindow("button", "Change Limit", WS_CHILD|WS_VISIBLE|WS_BORDER, 5, 60, 290, 30, hWnd, (HMENU)IDC_D, hInstance, 0);
		}
		break;
		case WM_COMMAND:
		{
			wmId = LOWORD(wParam);
			wmEvent = HIWORD(wParam);
			switch (wmId)
			{
				case IDC_A:
				{
					char dstart[MAX_PATH];
					GetWindowText(hPath, dstart, MAX_PATH);
	
					OPENFILENAME filename;
					ZeroMemory(&filename, sizeof(filename));
					#if (_WIN32_WINNT >= 0x0500) && (WINVER >= 0x0500)
					filename.lStructSize = OPENFILENAME_SIZE_VERSION_400;
					#else
					filename.lStructSize = sizeof(OPENFILENAME);
					#endif
					char fname[3072];
					fname[0] = 0;
					filename.hwndOwner = hWnd;
					filename.hInstance = hInstance;
					filename.lpstrFilter = ".exe files (*.exe)\0*.exe\0";
					filename.lpstrCustomFilter = NULL;
					filename.nMaxCustFilter = 0;
					filename.nFilterIndex = 1;
					filename.lpstrFile = (LPTSTR)fname;
					filename.nMaxFile = 3072;
					filename.lpstrFileTitle = NULL;
					filename.nMaxFileTitle = 0;
					filename.lpstrInitialDir = (LPTSTR)dstart;
					filename.lpstrTitle = (LPTSTR)"Tibia.exe search";
					filename.lpstrDefExt = (LPTSTR)"exe";
					filename.Flags = OFN_EXPLORER|OFN_FILEMUSTEXIST;
					if(GetOpenFileName(&filename))
						SetWindowText(hPath, fname);
				}
				break;
				case IDC_D: CreateClient(); break;
				default: return DefWindowProc(hWnd, message, wParam, lParam);
			}
		}
		break;
		case WM_DISPLAYCHANGE: InvalidateRect(hWnd, NULL, FALSE); break;
		case WM_DESTROY: PostQuitMessage(0); break;
		default: return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

int main(int argc, char *argv[])
{
	hInstance = GetModuleHandle(0);
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style			= CS_PARENTDC;
	wcex.lpfnWndProc	= WndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= hInstance;
	wcex.hIcon			= 0;
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(16);
	wcex.lpszMenuName	= 0;
	wcex.lpszClassName	= "Tibia Outfit Limit Changer";
	wcex.hIconSm		= 0;

	RegisterClassEx(&wcex);

	HWND hWnd = CreateWindowEx(WS_EX_APPWINDOW, "Tibia Outfit Limit Changer", "Tibia Outfit Limit Changer", WS_OVERLAPPED|WS_SYSMENU|WS_MINIMIZEBOX, CW_USEDEFAULT, 0, 310, 125, NULL, NULL, hInstance, NULL);

	ShowWindow(hWnd, SW_SHOW);
	UpdateWindow(hWnd);

	MSG msg;
	while(GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return 0;
}
