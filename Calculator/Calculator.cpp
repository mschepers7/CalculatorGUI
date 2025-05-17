#include "windows.h"

enum {
	ID_LABEL = 1, ID_IMAGE, ID_EDIT, ID_LIST, ID_BUTTON1, ID_COMBO, ID_BUTTON2, ID_BUTTON0,
	ID_BUTTON3, ID_BUTTON4, ID_BUTTON5, ID_BUTTON6, ID_BUTTON7, ID_BUTTON8, ID_BUTTON9,
	ID_BUTTONPLUS, ID_BUTTONMINUS, ID_BUTTONTIME, ID_BUTTONDIVIDE, ID_BUTTONEQUAL, ID_BUTTONMODULO
	//added modulo button
};
LRESULT CALLBACK WinProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
void setValues(float, LPCWSTR);

HINSTANCE g_hInst;
TCHAR	szAppName[] = TEXT("Calculator");
TCHAR	szWinClass[] = TEXT("WIN_CLASS");

HWND static_label;
HWND edit;
HWND list;
//number
HWND button0;
HWND button1;
HWND button2;
HWND button3;
HWND button4;
HWND button5;
HWND button6;
HWND button7;
HWND button8;
HWND button9;
//operation
HWND buttonPlus;
HWND buttonMinus;
HWND buttonTime;
HWND buttonDivide;
HWND buttonEqual;
//modulo button
HWND buttonModulo;

float value1 = 0;
float value2 = 0;
float result = 0;
wchar_t operation = 0;
bool first = true;

int WINAPI WinMain(HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	PSTR lpCmdLine,
	int nCmdShow) {

	MSG			msg;
	WNDCLASS	wc;
	HWND		hwnd;
	g_hInst = hInstance;


	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wc.hInstance = hInstance;
	wc.lpfnWndProc = WinProc;
	wc.lpszClassName = szWinClass;
	wc.lpszMenuName = NULL;
	wc.style = CS_HREDRAW | CS_VREDRAW;

	if (!RegisterClass(&wc))
	{
		MessageBox(NULL, TEXT("Error registering class"), TEXT("ERROR"), MB_OK);
		return 0;
	}

	hwnd = CreateWindow(szWinClass,
		szAppName,
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		300,
		400,
		(HWND)NULL,
		(HMENU)NULL,
		(HINSTANCE)hInstance,
		(void*)NULL);

	ShowWindow(hwnd, nCmdShow);
	UpdateWindow(hwnd);

	while (GetMessage(&msg, (HWND)NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return msg.wParam;
}

LRESULT CALLBACK WinProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
	PAINTSTRUCT	ps;
	HDC			hdc;

	switch (msg) {
	case WM_CREATE:
		static_label = CreateWindow(L"Static", L"Please Enter A Number", WS_CHILD | WS_VISIBLE, 35, 15, 175, 25, hwnd, 0, g_hInst, 0);
		edit = CreateWindow(L"Edit", NULL, WS_BORDER | NULL | WS_CHILD | WS_VISIBLE | NULL | NULL, 35, 45, 175, 20, hwnd, (HMENU)ID_EDIT, g_hInst, 0);

		button0 = CreateWindow(L"Button", L"0", BS_PUSHBUTTON | WS_CHILD | WS_VISIBLE, 80, 220, 35, 35, hwnd, (HMENU)ID_BUTTON0, g_hInst, 0);
		button1 = CreateWindow(L"Button", L"1", BS_PUSHBUTTON | WS_CHILD | WS_VISIBLE, 35, 170, 35, 35, hwnd, (HMENU)ID_BUTTON1, g_hInst, 0);
		button2 = CreateWindow(L"Button", L"2", BS_PUSHBUTTON | WS_CHILD | WS_VISIBLE, 80, 170, 35, 35, hwnd, (HMENU)ID_BUTTON2, g_hInst, 0);
		button3 = CreateWindow(L"Button", L"3", BS_PUSHBUTTON | WS_CHILD | WS_VISIBLE, 125, 170, 35, 35, hwnd, (HMENU)ID_BUTTON3, g_hInst, 0);
		button4 = CreateWindow(L"Button", L"4", BS_PUSHBUTTON | WS_CHILD | WS_VISIBLE, 35, 120, 35, 35, hwnd, (HMENU)ID_BUTTON4, g_hInst, 0);
		button5 = CreateWindow(L"Button", L"5", BS_PUSHBUTTON | WS_CHILD | WS_VISIBLE, 80, 120, 35, 35, hwnd, (HMENU)ID_BUTTON5, g_hInst, 0);
		button6 = CreateWindow(L"Button", L"6", BS_PUSHBUTTON | WS_CHILD | WS_VISIBLE, 125, 120, 35, 35, hwnd, (HMENU)ID_BUTTON6, g_hInst, 0);
		button7 = CreateWindow(L"Button", L"7", BS_PUSHBUTTON | WS_CHILD | WS_VISIBLE, 35, 70, 35, 35, hwnd, (HMENU)ID_BUTTON7, g_hInst, 0);
		button8 = CreateWindow(L"Button", L"8", BS_PUSHBUTTON | WS_CHILD | WS_VISIBLE, 80, 70, 35, 35, hwnd, (HMENU)ID_BUTTON8, g_hInst, 0);
		button9 = CreateWindow(L"Button", L"9", BS_PUSHBUTTON | WS_CHILD | WS_VISIBLE, 125, 70, 35, 35, hwnd, (HMENU)ID_BUTTON9, g_hInst, 0);

		buttonDivide = CreateWindow(L"Button", L"/", BS_PUSHBUTTON | WS_CHILD | WS_VISIBLE, 170, 70, 35, 35, hwnd, (HMENU)ID_BUTTONDIVIDE, g_hInst, 0);
		buttonTime = CreateWindow(L"Button", L"*", BS_PUSHBUTTON | WS_CHILD | WS_VISIBLE, 170, 120, 35, 35, hwnd, (HMENU)ID_BUTTONTIME, g_hInst, 0);
		buttonMinus = CreateWindow(L"Button", L"-", BS_PUSHBUTTON | WS_CHILD | WS_VISIBLE, 170, 170, 35, 35, hwnd, (HMENU)ID_BUTTONMINUS, g_hInst, 0);
		buttonPlus = CreateWindow(L"Button", L"+", BS_PUSHBUTTON | WS_CHILD | WS_VISIBLE, 170, 220, 35, 35, hwnd, (HMENU)ID_BUTTONPLUS, g_hInst, 0);
		buttonEqual = CreateWindow(L"Button", L"=", BS_PUSHBUTTON | WS_CHILD | WS_VISIBLE, 125, 220, 35, 35, hwnd, (HMENU)ID_BUTTONEQUAL, g_hInst, 0);
		//added modulo button
		buttonModulo = CreateWindow(L"Button", L"%", BS_PUSHBUTTON | WS_CHILD | WS_VISIBLE, 215, 70, 35, 35, hwnd, (HMENU)ID_BUTTONMODULO, g_hInst, 0);


	case WM_PAINT:
		hdc = BeginPaint(hwnd, &ps);
		EndPaint(hwnd, &ps);
		return 0;
		break;
	case WM_COMMAND: //Command from Child windows and menus are under this message
		switch (wParam) //the ID is wParam
		{
		case ID_BUTTON0: //check for our button ID
		{
			// Static labels dont do messages
			//we can set the text directly though

			setValues(0, L"0");
			SetWindowText(edit, L"0");
			//SetWindowText(edit,"0");
			break;
		}

		case ID_BUTTON1:
		{
			setValues(1, L"1");
			SetWindowText(edit, L"1");
			break;
		}

		case ID_BUTTON2:
		{
			setValues(2, L"2");
			SetWindowText(edit, L"2");
			break;
		}

		case ID_BUTTON3:
		{
			setValues(3, L"3");
			SetWindowText(edit, L"3");
			break;
		}

		case ID_BUTTON4:
		{
			setValues(4, L"4");
			SetWindowText(edit, L"4");
			break;
		}

		case ID_BUTTON5:
		{
			setValues(5, L"5");
			SetWindowText(edit, L"5");
			break;
		}

		case ID_BUTTON6:
		{
			setValues(6, L"6");
			SetWindowText(edit, L"6");
			break;
		}

		case ID_BUTTON7:
		{
			setValues(7, L"7");
			SetWindowText(edit, L"7");
			break;
		}

		case ID_BUTTON8:
		{
			setValues(8, L"8");
			SetWindowText(edit, L"8");
			break;
		}

		case ID_BUTTON9:
		{
			setValues(9, L"9");
			SetWindowText(edit, L"9");
			break;
		}

		case ID_BUTTONPLUS:
		{
			operation = '+';
			break;
		}

		case ID_BUTTONMINUS:
		{
			operation = '-';
			break;
		}

		case ID_BUTTONTIME:
		{
			operation = '*';
			break;
		}

		case ID_BUTTONDIVIDE:
		{
			operation = '/';
			break;
		}
		//added modulo button

		case ID_BUTTONMODULO:
		{
			operation = '%';
			break;
		}
		case ID_BUTTONEQUAL:
		{
			if (operation == '+')
				result = value1 + value2;
			else if (operation == '-')
				result = value1 - value2;
			else if (operation == '*')
				result = value1 * value2;
			else if (operation == '/')
				result = value1 / value2;
			//modulo operation
			else if (operation == '%')
				result = static_cast<int>(value1) % static_cast<int>(value2); // Modulo operation
			else if (operation == '%' && static_cast<int>(value2) == 0)
			{
				MessageBox(hwnd, L"Cannot perform modulo by zero", L"Error", MB_OK);
				result = 0;
			}


			// Convert the result to a string
			char chars[17];
			_gcvt_s(chars, sizeof(chars), result, 8);
			wchar_t buffer[17];
			mbstowcs_s(NULL, buffer, sizeof(buffer) / 2, chars, sizeof(chars));

			SetWindowText(edit, buffer);
			break;
		}
		}//switch. 
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break; // pass to DefWindowProc(...) as well
	case WM_CLOSE:
		DestroyWindow(hwnd);
		break;
	}return DefWindowProc(hwnd, msg, wParam, lParam);
}

void setValues(float operand, LPCWSTR displayValue) {
	if (first) {
		first = false;
		value1 = operand;
	}
	else {
		first = true;
		value2 = operand;
	}
	SetWindowText(edit, displayValue);
}