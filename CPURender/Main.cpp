#include <windows.h>
#include <assert.h>
#include <string>
#include <WindowsX.h>

using namespace std;
const int WIDTH = 800;
const int HEIGHT = 600;

LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wparam, LPARAM lParam)
{
	PAINTSTRUCT ps;
	HDC hdc;
	switch (message)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	case WM_KEYDOWN:
		if (wparam == VK_ESCAPE)
		{
			DestroyWindow(hwnd);
		}
		break;
	default:
		return DefWindowProc(hwnd, message, wparam, lParam);
	}
	return 0;
}

HWND GameStart(HINSTANCE hInstance, int nShowCmd, string wcName, string title)
{
	//1.����������
	WNDCLASSEX wndClass = {};
	wndClass.cbSize = sizeof(WNDCLASSEX);
	wndClass.style = CS_HREDRAW | CS_VREDRAW;
	wndClass.lpfnWndProc = WndProc;
	wndClass.cbClsExtra = 0;
	wndClass.cbWndExtra = 0;
	wndClass.hInstance = hInstance;
	wndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndClass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wndClass.lpszMenuName = NULL;
	wndClass.lpszClassName = wcName.c_str();

	//2.ע�ᴰ����
	assert(RegisterClassEx(&wndClass));

	//3.��������
	HWND hwnd = CreateWindow(wcName.c_str(), title.c_str(), WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, WIDTH, HEIGHT, NULL, NULL, hInstance, NULL);

	//4.������С���ƶ�����ʾ������
	RECT window_rect = { 0, 0, WIDTH, HEIGHT };
	AdjustWindowRectEx(&window_rect, GetWindowStyle(hwnd), GetMenu(hwnd) != NULL, GetWindowExStyle(hwnd));
	MoveWindow(hwnd, 300, 150, window_rect.right - window_rect.left, window_rect.bottom - window_rect.top, false);
	ShowWindow(hwnd, nShowCmd);
	UpdateWindow(hwnd);

	return hwnd;
}

void GameUpdate(HWND hwnd)
{
	/*ͼ�λ���*/
}

void GameEnd(string wcName, HINSTANCE hInstance)
{
	//5.ע��������
	UnregisterClass(wcName.c_str(), hInstance);
}


int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nShowCmd)
{
	//1.��������
	string windowClassName = "Main";
	string title = "CPURender";
	HWND hwnd = GameStart(hInstance, nShowCmd, windowClassName, title);

	//ʱ���ʼ��
	DWORD curTime = GetTickCount();
	DWORD preTime = GetTickCount();
	//2.��Ϣѭ��
	MSG msg = { 0 };
	while (msg.message != WM_QUIT)
	{
		//��ȡ��Ϣ
		if (PeekMessage(&msg, 0, NULL, NULL, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			curTime = GetTickCount();
			if (curTime - preTime>30)
			{
				preTime = curTime;
				GameUpdate(hwnd);
			}
		}
	}

	//3.��Ϸ����
	GameEnd(windowClassName, hInstance);
	return 0;
}