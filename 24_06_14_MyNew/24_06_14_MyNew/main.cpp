#define _CRT_SECURE_NO_WARNINGS 1
#include <Windows.h>

wchar_t szMyNewClassName[] = L"MyClass";			// The name of the window class,L is used to define a wide character string

LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam) // The window procedure£¬hwnd is the handle to the window, message is the message to be processed, wParam is the additional message information, lParam is the additional message information
{
	switch (message)			// The message to be processed
	{
		case WM_CREATE:			// The window is being created
			MessageBox(hwnd, L"Loading My New", L"Loading", MB_OK | MB_ICONINFORMATION);		// Display a message box
			SetWindowPos(hwnd, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);				// Set the window to the topmost(¶¥²ã£© position£¬SWP_NOMOVE is the window is not moved, SWP_NOSIZE is the window is not resized£¬which can be a template used to set the window to the topmost position
			break;
		case WM_DESTROY:		// The window is being destroyed
			PostQuitMessage(0);			// Post a quit message to the message queue
			break;
		default:				// The default message
			return DefWindowProc(hwnd, message, wParam, lParam); // The default window procedure
	}
	return 0;
}
int main()
{
	// Initialize this window class
	WNDCLASS wc;
	{
		wc.style = CS_HREDRAW | CS_VREDRAW;						// Redraw the window horizontally and virtically if the size changes
		wc.lpfnWndProc = WndProc;								// Set Default window procedure fuction,really [important]
		wc.cbClsExtra = 0;										// No extra bytes after the window class
		wc.cbWndExtra = 0;										// No extra bytes after the window instance
		wc.hInstance = GetModuleHandle(NULL);					// Get the instance of the current module
		wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);				// Load the default icon on the left top corner of the window
		//NULL is the handle to the instance of the [module that contains the icon resource]
		//IDI_APPLICATION is the default system icon resource to be loaded,more icons can be loaded such as IDI_QUESTION, IDI_WARNING, IDI_ERROR,IDI_XXX...
		wc.hCursor = LoadCursor(NULL, IDC_ARROW);				// Load the default mouse cursor,more cursors can be loaded such as IDC_WAIT, IDC_HELP, IDC_XXX...(initialize the cursor style)
		wc.hbrBackground = (HBRUSH)GetStockObject(GRAY_BRUSH);  // Initialize the background color of the window
		//Can also use "wc.hbrBackground = CreateSolidBrush(RGB(255, 0, 0));"to Create a solid brush with the color RGB(255, 0, 0)
		wc.lpszMenuName = NULL;									// No menu is associated with the window
		wc.lpszClassName = szMyNewClassName;					// Set the name of the window class, which is used to create the window
	}



	// Register this window class
	if (!RegisterClass(&wc)/*if(TRUE == RegisterClass(&wc)*/)	//TRUE is a macro defined as 1, FALSE is a macro defined as 0
	{
		MessageBox(NULL, L"Failed to register window class", L"Error", MB_OK | MB_ICONERROR);
	}
	



	// Create the window
	HWND hwnd = CreateWindow(
		szMyNewClassName,			// The name of the window class
		L"My New Window",			// The display title of the window
		WS_BORDER | WS_CAPTION | WS_SYSMENU | WS_MAXIMIZEBOX | WS_MINIMIZEBOX , // The window style, WS_BORDER is the window with a thin-line border, WS_CAPTION is the window with a title bar, WS_SYSMENU is the window with a system menu on its title bar
		0, 0, 800, 600,				// The position and size of the window, (0,0) is the top-left corner of the screen, 800 is the width of the window, 600 is the height of the window
		NULL, NULL,					// The parent window and the menu of the window, NULL means no parent window and no menu
		GetModuleHandle(NULL),		// The instance of the module that contains the window procedure
		NULL);						// The lParam of the WM_CREATE message, NULL means no lParam, lParam means ¸½¼Ó²ÎÊý
	



	// Display the window
	ShowWindow(hwnd, SW_SHOWNORMAL);		// Show the window with the normal state



	// Update the window
	UpdateWindow(hwnd);						// Update the window to make it visible




	// Message loop, the main loop of the program, it retrieves and dispatches messages,to [make the window responsive(continue to exist)]
	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0))	// GetMessage() retrieves a message from the calling thread's message queue
	{
		TranslateMessage(&msg);				// Translate virtual-key messages into character messages, it is used to translate [keyboard input into character messages]
		DispatchMessage(&msg);				// Dispatches a message to a window procedure, it is used to [dispatch a message to a window procedure]
	}
}