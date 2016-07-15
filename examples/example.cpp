#include <vpp/backend/win32.hpp>
#include <nanovg/nanovg.h>
#include <vgk.hpp>

constexpr auto width = 900;
constexpr auto height = 500;

LRESULT CALLBACK wndProc(HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam)
{
    switch(message)
    {
		case WM_ERASEBKGND:
		{
			//dont erase it to avoid flickering
			break;
		}

        case WM_CLOSE:
		{
			DestroyWindow(hwnd);
			PostQuitMessage(0);
			break;
		}

        default:
            return DefWindowProc(hwnd, message, wparam, lparam);
    }
}

HWND createWindow()
{
	std::string name = "test";

	WNDCLASSEX wndClass;
	wndClass.cbSize = sizeof(WNDCLASSEX);
	wndClass.style = CS_HREDRAW | CS_VREDRAW;
	wndClass.lpfnWndProc = wndProc;
	wndClass.cbClsExtra = 0;
	wndClass.cbWndExtra = 0;
	wndClass.hInstance = GetModuleHandle(nullptr);
	wndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndClass.hbrBackground = (HBRUSH) GetStockObject(WHITE_BRUSH);
	wndClass.lpszMenuName = NULL;
	wndClass.lpszClassName = name.c_str();
	wndClass.hIconSm = LoadIcon(NULL, IDI_WINLOGO);

	if (!RegisterClassEx(&wndClass))
	{
	  throw std::runtime_error("Failed to register window class");
	}

	auto flags = WS_EX_COMPOSITED | WS_EX_LAYERED | WS_EX_TRANSPARENT | WS_OVERLAPPEDWINDOW;
	auto window = CreateWindowEx(0, name.c_str(), name.c_str(), flags, CW_USEDEFAULT,
	  CW_USEDEFAULT, width, height, nullptr, nullptr, GetModuleHandle(nullptr), nullptr);

	if(!window)
	{
	  throw std::runtime_error("Failed to create window");
	}

	COLORREF RRR = RGB(255, 0, 255);
	SetLayeredWindowAttributes(window, RRR, (BYTE)0, LWA_COLORKEY);

	ShowWindow(window, SW_SHOW);
	SetForegroundWindow(window);
	SetFocus(window);

	return window;
}

int main()
{
	auto window = createWindow();
	auto vulkanContext = vpp::createContext(window, {width, height});
	// auto vulkanContext = vpp::createContext(window, {width, height, {}});
	auto nvgContext = vgk::create(vulkanContext.swapChain(), true);

	auto font = nvgCreateFont(nvgContext, "sans", "Roboto-Regular.ttf");

	while(1)
	{
	    MSG msg;
	    PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE);
	    if(msg.message == WM_QUIT)
	    {
	        break;
	    }
	    else
	    {
	        TranslateMessage(&msg);
	        DispatchMessage(&msg);
	    }

		nvgBeginFrame(nvgContext, width, height, width / (float)height);
		//nvgRect(nvgContext, 10, 10, 100, 100);
		nvgMoveTo(nvgContext, 10, 10);
		nvgLineTo(nvgContext, 10, 100);
		nvgLineTo(nvgContext, 100, 100);
		nvgQuadTo(nvgContext, 100, 50, 500, 120);
		nvgClosePath(nvgContext);

		nvgFontFaceId(nvgContext, font);
		nvgFontSize(nvgContext, 100.f);
		nvgText(nvgContext, 200, 200, "Hello VG World", nullptr);

		nvgFillColor(nvgContext, nvgRGBAf(0.5, 0.8, 0.7, 0.7));
		nvgFill(nvgContext);

		nvgStrokeWidth(nvgContext, 4.f);
		//nvgMiterLimit(nvgContext, 5.f);
		//nvgLineCap(nvgContext, NVG_SQUARE);
		//nvgLineJoin(nvgContext, NVG_ROUND);
		nvgStrokeColor(nvgContext, nvgRGBAf(1.0, 1.0, 1.0, 1.0));
		nvgStroke(nvgContext);

		nvgEndFrame(nvgContext);

		// auto vg = nvgContext;
		// nvgBeginFrame(vg, 800, 500, 800 / double(500));
		// nvgBeginPath(vg);
		// nvgMoveTo(vg, 100, 200);
		// nvgLineTo(vg, 300, 400);
		// nvgLineTo(vg, 0, 200);
		// nvgClosePath(vg);
		// nvgStrokeColor(nvgContext, nvgRGBAf(1.0, 1.0, 1.0, 1.0));
		// nvgStroke(vg);
		// nvgEndFrame(vg);
	}

	vgk::destroy(*nvgContext);
}
