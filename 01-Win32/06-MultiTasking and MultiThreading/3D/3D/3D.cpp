// Headers
#include <Windows.h>
#include <stdio.h>
#include <math.h>
#include "3D.h"

// For PlaySound API
#pragma comment (lib, "Winmm.lib")

// Prototypes
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
void Rotate(LPSTATE, UINT);
DWORD ThreadMove(LPVOID);
void ResetCamera(LPSTATE);

// External Functions
typedef void(*lpfnDrawShape) (LPSTATE);
typedef void(*lpfnSetLetters) (LPSTATE, char *);
//typedef void (ConvertToLines(int , int *, LPSTATE);

// WinMain
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdLine, int iCmdShow)
{
	// variables
	WNDCLASSEX wndclass;
	HWND hwnd;
	MSG msg;
	TCHAR szClassName[] = TEXT("MyClass");

	// code
	wndclass.cbSize = sizeof(WNDCLASSEX);
	wndclass.style = CS_HREDRAW | CS_VREDRAW;
	wndclass.cbClsExtra = 0;
	wndclass.cbWndExtra = 0;
	wndclass.lpfnWndProc = WndProc;
	wndclass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wndclass.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(MYICON));
	wndclass.hInstance = hInstance;
	wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndclass.lpszClassName = szClassName;
	wndclass.lpszMenuName = NULL;
	wndclass.hIconSm = LoadIcon(hInstance, MAKEINTRESOURCE(MYICON));

	// Register Class
	RegisterClassEx(&wndclass);

	hwnd = CreateWindow(szClassName,
		TEXT("3D Visualizer"),
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		NULL,
		NULL,
		hInstance,
		NULL);

	ShowWindow(hwnd, SW_MAXIMIZE);
	UpdateWindow(hwnd);

	// Message Loop
	while (TRUE)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT)
				break;

			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

	}
	return msg.wParam;

}

LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	// Shapes DLL variables 
	static HMODULE hLib = NULL;
	static HMODULE hLib2 = NULL;
	static lpfnDrawShape DrawShape = NULL;
	static lpfnSetLetters SetLetters = NULL;

	// WndProc variables 
	static STATE State = { 0 };
	static BOOL fSetOrigin = TRUE;
	int iResult;


	RECT rc;
	PAINTSTRUCT ps;
	HDC hdc;
	POINT arrPoints[50];
	HPEN hPen;
	TCHAR lpszDebugInfo[512];
	static HANDLE hThreadMove;
	char szLetters[] = "Random Text";
	//char szLetters[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

	switch (iMsg)
	{
	case WM_CREATE:

		// start main theme music
		PlaySound(MAKEINTRESOURCE(MAINTHEME), GetModuleHandle(NULL), SND_RESOURCE | SND_ASYNC);

		// Load DLLs
		hLib = LoadLibrary(TEXT("Shapes.dll"));
		if (!hLib)
		{
			MessageBox(hwnd, TEXT("Cannot Load Shapes.dll..."), TEXT("Error"), MB_OK | MB_ICONERROR);
			DestroyWindow(hwnd);
		}

		// Initialize the State
		State.hwnd = hwnd;
		State.Camera = { 0, 0, 0, 40 };
		State.iAnimate = 0;
		State.Directions[0] = 1;
		State.Directions[1] = 1;
		State.Directions[2] = 1;
		State.Offset[0] = 0;
		State.Offset[1] = 0;
		State.Origin[0] = 0;
		State.Origin[1] = 0;
		State.fAxis = FALSE;
		State.Model.iNoOfPoints = 0;
		State.Model.iNoOfLines = 0;
		State.iNoOfLetters = 0;

		memset(State.arrOffsets, 0, sizeof(int) * 250);

		//Cube(&State);
		//ThreeCubes(&State);
		//FiveAngleStar(&State);

		// DIRTY IMPLIMENTATION
		hLib2 = LoadLibrary(TEXT("AlphaNumeric.dll"));
		if (!hLib2)
		{
			MessageBox(hwnd, TEXT("Cannot Load AlphaNumeric.dll..."), TEXT("Error"), MB_OK | MB_ICONERROR);
			DestroyWindow(hwnd);
		}
		SetLetters = (lpfnSetLetters)GetProcAddress(hLib2, "SetLetters");
		SetLetters(&State, szLetters);
		// DIRTY

		hThreadMove = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)ThreadMove, (LPVOID)&State, CREATE_SUSPENDED, NULL);
		break;

	case WM_PAINT:

		// Begin!
		hdc = BeginPaint(hwnd, &ps);
		GetClientRect(hwnd, &rc);

		SetBkColor(hdc, RGB(0, 0, 0));
		// Create White Pen
		hPen = CreatePen(PS_DASH, 1, RGB(0, 255, 0));
		SelectObject(hdc, hPen);

		// Find Origin if flag is set
		if (fSetOrigin)
		{
			State.Origin[0] = (rc.right / 2) + State.Offset[0];
			State.Origin[1] = (rc.bottom / 2) + State.Offset[1];
			fSetOrigin = FALSE;
		}

		if (State.fAxis) {
			// x-axis
			arrPoints[0].x = 0;
			arrPoints[0].y = (rc.bottom / 2) + State.Offset[1];
			arrPoints[1].x = rc.right;
			arrPoints[1].y = (rc.bottom / 2) + State.Offset[1];
			Polyline(hdc, arrPoints, 2);

			// y-axis
			arrPoints[0].x = (rc.right / 2) + State.Offset[0];
			arrPoints[0].y = 0;
			arrPoints[1].x = (rc.right / 2) + State.Offset[0];
			arrPoints[1].y = rc.bottom;
			Polyline(hdc, arrPoints, 2);
		}

		// Create White Pen
		hPen = CreatePen(PS_SOLID, 1, RGB(255, 255, 255));
		SelectObject(hdc, hPen);

		//// z-axis
		//arrPoints[0].x = (rc.right / 2) + Offset[0];
		//arrPoints[0].y = 0;
		//arrPoints[1].x = (rc.right / 2) + Offset[0];
		//arrPoints[1].y = rc.bottom;
		//Polyline(hdc, arrPoints, 2);

		// Draw Object
		for (int i = 0; i < State.Model.iNoOfLines; i++)
		{
			arrPoints[0].x = (State.Camera.iScale * State.Model.arrLine[i].ptStart->x) + State.Origin[0];
			arrPoints[0].y = -(State.Camera.iScale * State.Model.arrLine[i].ptStart->y) + State.Origin[1];
			arrPoints[1].x = (State.Camera.iScale * State.Model.arrLine[i].ptEnd->x) + State.Origin[0];
			arrPoints[1].y = -(State.Camera.iScale * State.Model.arrLine[i].ptEnd->y) + State.Origin[1];
			Polyline(hdc, arrPoints, 2);
		}

		// Draw Debug Info
		SetBkColor(hdc, RGB(0, 0, 0));
		SetTextColor(hdc, RGB(255, 255, 255));
		sprintf_s(lpszDebugInfo, "Angles:\n\tX: %d\n\tY: %d\n\tZ: %d\n\nDirections:\n\tX: %d\n\tY: %d\n\tZ: %d\n\nScale: %d\n\nOrigin:\n\tX: %d\n\tY: %d",
			State.Camera.xAngle, State.Camera.yAngle, State.Camera.zAngle,
			State.Directions[0], State.Directions[1], State.Directions[2],
			State.Camera.iScale,
			State.Origin[0], State.Origin[1]);
		DrawText(hdc, lpszDebugInfo, -1, &rc, DT_TOP | DT_LEFT);

		EndPaint(hwnd, &ps);
		break;

	case WM_KEYDOWN:

		switch (wParam)
		{
		case 'U':
			State.Origin[1] -= 5;
			break;

		case 'H':
			State.Origin[0] -= 5;
			break;

		case 'J':
			State.Origin[0] += 5;
			break;

		case 'N':
			State.Origin[1] += 5;
			break;

		case '1':
			DrawShape = (lpfnDrawShape)GetProcAddress(hLib, "Cube");
			if (!DrawShape)
			{
				MessageBox(hwnd, TEXT("Cannot found Cube function"), TEXT("Error"), MB_OK | MB_ICONERROR);
			}
			DrawShape(&State);
			break;

		case '2':
			DrawShape = (lpfnDrawShape)GetProcAddress(hLib, "ThreeCubes");
			if (!DrawShape)
			{
				MessageBox(hwnd, TEXT("Cannot found ThreeCube function"), TEXT("Error"), MB_OK | MB_ICONERROR);
			}
			DrawShape(&State);
			break;

		case '3':
			DrawShape = (lpfnDrawShape)GetProcAddress(hLib, "Pyramid");
			if (!DrawShape)
			{
				MessageBox(hwnd, TEXT("Cannot found Pyramid function"), TEXT("Error"), MB_OK | MB_ICONERROR);
			}
			DrawShape(&State);
			(&State);
			break;

		case '4':
			DrawShape = (lpfnDrawShape)GetProcAddress(hLib, "Diamond");
			if (!DrawShape)
			{
				MessageBox(hwnd, TEXT("Cannot found Diamond function"), TEXT("Error"), MB_OK | MB_ICONERROR);
			}
			DrawShape(&State);
			break;

		case '5':DrawShape = (lpfnDrawShape)GetProcAddress(hLib, "FiveAngleStar");
			if (!DrawShape)
			{
				MessageBox(hwnd, TEXT("Cannot found FiveAngleStar function"), TEXT("Error"), MB_OK | MB_ICONERROR);
			}
			DrawShape(&State);
			break;

		case '6':DrawShape = (lpfnDrawShape)GetProcAddress(hLib, "Football");
			if (!DrawShape)
			{
				MessageBox(hwnd, TEXT("Cannot found Football function"), TEXT("Error"), MB_OK | MB_ICONERROR);
			}
			DrawShape(&State);
			break;

		case 'I':
			State.Camera.iScale += 1;
			break;

		case 'O':
			if (State.Camera.iScale > 2)
				State.Camera.iScale -= 1;
			break;

		case VK_SPACE:
			if (State.iAnimate == 0) {
				State.iAnimate = 1;
				ResumeThread(hThreadMove);
			}
			else
			{
				State.iAnimate = 0;
				SuspendThread(hThreadMove);
			}
			break;

		case 'R':
			State.Offset[0] = State.Offset[1] = 0;
			State.Camera.iScale = 40;

			State.Model.iNoOfLines = 0;
			State.Model.iNoOfPoints = 0;
			SetLetters(&State, szLetters);

			/*State.Directions[0] = -State.Camera.xAngle;
			State.Directions[1] = -State.Camera.yAngle;
			State.Directions[2] = -State.Camera.zAngle;

			Rotate(&State, XAXIS);
			Rotate(&State, YAXIS);
			Rotate(&State, ZAXIS);*/

			ResetCamera(&State);

			break;

		case 'X':
			if (State.fAxis)
				State.fAxis = FALSE;
			else
				State.fAxis = TRUE;

			break;

		case VK_UP:
			// Rotate along X-Axis
			State.Directions[0] = 1;
			Rotate(&State, XAXIS);
			break;

		case VK_DOWN:
			// Rotate along X-Axis Negative
			State.Directions[0] = -1;
			Rotate(&State, XAXIS);
			break;

		case VK_LEFT:
			// Rotate along Y-Axis 
			State.Directions[1] = 1;
			Rotate(&State, YAXIS);
			break;

		case VK_RIGHT:
			// Rotate along Y-Axis Negative
			State.Directions[1] = -1;
			Rotate(&State, YAXIS);
			break;

		case 'Q':
			// Rotate along Z-Axis
			State.Directions[2] = 1;
			Rotate(&State, ZAXIS);
			break;

		case 'A':
			// Rotate along Z-Axis Negative
			State.Directions[2] = -1;
			Rotate(&State, ZAXIS);
			break;

		case VK_ESCAPE:
			iResult = MessageBox(hwnd, TEXT("Do you want to Quit?"), TEXT("3D Visualilzer"), MB_YESNO | MB_ICONQUESTION);
			if (iResult == IDYES) DestroyWindow(hwnd);
			break;
		}

		GetClientRect(hwnd, &rc);
		InvalidateRect(hwnd, &rc, TRUE);
		break;

	case WM_DESTROY:
		FreeLibrary(hLib);
		PostQuitMessage(0);
		break;
	}

	return(DefWindowProc(hwnd, iMsg, wParam, lParam));
}

void Rotate(LPSTATE State, UINT iAxis)
{
	double dRotationMatrix[3][3];
	double dSin = 0;
	double dCos = 0;
	double dTmp[3];

	switch (iAxis)
	{

	case XAXIS:

		// Adjust Camera Angle
		if (State->Directions[0] == 1)
		{
			if (State->Camera.xAngle < 359)
				State->Camera.xAngle++;
			else State->Camera.xAngle = 0;
		}

		if (State->Directions[0] == -1)
		{
			if (State->Camera.xAngle > 0)
				State->Camera.xAngle--;
			else State->Camera.xAngle = 359;
		}

		// Calculate Rotation Matrix 
		dSin = sin(State->Directions[0] * PI / 180);
		dCos = cos(State->Directions[0] * PI / 180);

		dRotationMatrix[0][0] = 1;
		dRotationMatrix[0][1] = 0;
		dRotationMatrix[0][2] = 0;

		dRotationMatrix[1][0] = 0;
		dRotationMatrix[1][1] = dCos;
		dRotationMatrix[1][2] = -dSin;

		dRotationMatrix[2][0] = 0;
		dRotationMatrix[2][1] = dSin;
		dRotationMatrix[2][2] = dCos;

		break;

	case YAXIS:

		// Adjust Camera Angle
		if (State->Directions[1] == 1)
		{
			if (State->Camera.yAngle < 359)
				State->Camera.yAngle++;
			else State->Camera.yAngle = 0;
		}

		if (State->Directions[1] == -1)
		{
			if (State->Camera.yAngle > 0)
				State->Camera.yAngle--;
			else State->Camera.yAngle = 359;
		}

		// Calculate Rotation Matrix 
		dSin = sin(State->Directions[1] * PI / 180);
		dCos = cos(State->Directions[1] * PI / 180);

		dRotationMatrix[0][0] = dCos;
		dRotationMatrix[0][1] = 0;
		dRotationMatrix[0][2] = dSin;

		dRotationMatrix[1][0] = 0;
		dRotationMatrix[1][1] = 1;
		dRotationMatrix[1][2] = 0;

		dRotationMatrix[2][0] = -dSin;
		dRotationMatrix[2][1] = 0;
		dRotationMatrix[2][2] = dCos;

		break;

	case ZAXIS:

		// Adjust Camera Angle
		if (State->Directions[2] == 1)
		{
			if (State->Camera.zAngle < 359)
				State->Camera.zAngle++;
			else State->Camera.zAngle = 0;
		}

		if (State->Directions[2] == -1)
		{
			if (State->Camera.zAngle > 0)
				State->Camera.zAngle--;
			else State->Camera.zAngle = 359;
		}

		// Calculate Rotation Matrix 
		dSin = sin(State->Directions[2] * PI / 180);
		dCos = cos(State->Directions[2] * PI / 180);

		dRotationMatrix[0][0] = dCos;
		dRotationMatrix[0][1] = -dSin;
		dRotationMatrix[0][2] = 0;

		dRotationMatrix[1][0] = dSin;
		dRotationMatrix[1][1] = dCos;
		dRotationMatrix[1][2] = 0;

		dRotationMatrix[2][0] = 0;
		dRotationMatrix[2][1] = 0;
		dRotationMatrix[2][2] = 1;

		break;

	}

	for (int i = 0; i < State->Model.iNoOfPoints; i++)
	{
		dTmp[0] = (dRotationMatrix[0][0] * State->Points[i].x) + (dRotationMatrix[0][1] * State->Points[i].y) + (dRotationMatrix[0][2] * State->Points[i].z);
		dTmp[1] = (dRotationMatrix[1][0] * State->Points[i].x) + (dRotationMatrix[1][1] * State->Points[i].y) + (dRotationMatrix[1][2] * State->Points[i].z);
		dTmp[2] = (dRotationMatrix[2][0] * State->Points[i].x) + (dRotationMatrix[2][1] * State->Points[i].y) + (dRotationMatrix[2][2] * State->Points[i].z);

		State->Points[i].x = dTmp[0];
		State->Points[i].y = dTmp[1];
		State->Points[i].z = dTmp[2];
	}

}

DWORD ThreadMove(LPVOID State)
{
	RECT rc;
	LPSTATE lpState = (LPSTATE)State;
	double dTmp[3];
	//while (TRUE)
	//{
	//	Rotate(lpState, XAXIS);
	//	Rotate(lpState, YAXIS);
	//	Rotate(lpState, ZAXIS);
	//	GetClientRect(lpState->hwnd, &rc);
	//	InvalidateRect(lpState->hwnd, &rc, TRUE);
	//	Sleep(100);
	//}

	// Calculate Rotation Matrix 
	double dRotationMatrix[3][3] = { 0 };
	dRotationMatrix[0][0] = 1;
	dRotationMatrix[0][1] = 0;
	dRotationMatrix[0][2] = 0;

	dRotationMatrix[1][0] = 0;
	dRotationMatrix[1][1] = 0.98480775301;
	dRotationMatrix[1][2] = -0.17364817766;

	dRotationMatrix[2][0] = 0;
	dRotationMatrix[2][1] = 0.17364817766;
	dRotationMatrix[2][2] = 0.98480775301;

	//dRotationMatrix[0][0] = 0.98480775301;
	//dRotationMatrix[0][1] = 0;
	//dRotationMatrix[0][2] = 0.17364817766;

	//dRotationMatrix[1][0] = 0;
	//dRotationMatrix[1][1] = 1;
	//dRotationMatrix[1][2] = 0;

	//dRotationMatrix[2][0] = -0.17364817766;
	//dRotationMatrix[2][1] = 0;
	//dRotationMatrix[2][2] = 0.98480775301;

	int i = 0;
	int iBegin = 249; 
	int iEnd = 0;

	for (int k = 0; k < 36 + lpState->iNoOfLetters; k++)
	{
		for (int j = lpState->arrOffsets[iBegin]; j < lpState->arrOffsets[iEnd]; j++)
		{
			dTmp[0] = (dRotationMatrix[0][0] * lpState->Points[j].x) + (dRotationMatrix[0][1] * lpState->Points[j].y) + (dRotationMatrix[0][2] * lpState->Points[j].z);
			dTmp[1] = (dRotationMatrix[1][0] * lpState->Points[j].x) + (dRotationMatrix[1][1] * lpState->Points[j].y) + (dRotationMatrix[1][2] * lpState->Points[j].z);
			dTmp[2] = (dRotationMatrix[2][0] * lpState->Points[j].x) + (dRotationMatrix[2][1] * lpState->Points[j].y) + (dRotationMatrix[2][2] * lpState->Points[j].z);

			lpState->Points[j].x = dTmp[0];
			lpState->Points[j].y = dTmp[1];
			lpState->Points[j].z = dTmp[2];
		}

		GetClientRect(lpState->hwnd, &rc);
		InvalidateRect(lpState->hwnd, &rc, TRUE);
		Sleep(100);

		if (k < lpState->iNoOfLetters - 1)
		{
			iEnd++;
		}

		if (k = 35)
		{
			iBegin = 0;
		}

		if (k > 35)
		{
			iBegin++;
		}

	}
	
	/*while (i < lpState->iNoOfLetters)
	{
		


		for (int j = 0; j < lpState->arrOffsets[i]; j++)
		{
			dTmp[0] = (dRotationMatrix[0][0] * lpState->Points[j].x) + (dRotationMatrix[0][1] * lpState->Points[j].y) + (dRotationMatrix[0][2] * lpState->Points[j].z);
			dTmp[1] = (dRotationMatrix[1][0] * lpState->Points[j].x) + (dRotationMatrix[1][1] * lpState->Points[j].y) + (dRotationMatrix[1][2] * lpState->Points[j].z);
			dTmp[2] = (dRotationMatrix[2][0] * lpState->Points[j].x) + (dRotationMatrix[2][1] * lpState->Points[j].y) + (dRotationMatrix[2][2] * lpState->Points[j].z);

			lpState->Points[j].x = dTmp[0];
			lpState->Points[j].y = dTmp[1];
			lpState->Points[j].z = dTmp[2];
		}

		GetClientRect(lpState->hwnd, &rc);
		InvalidateRect(lpState->hwnd, &rc, TRUE);
		Sleep(100);
		
		if(i != lpState->iNoOfLetters - 1)
			i++;
	}*/

	return 0;
}

void ResetCamera(LPSTATE State)
{
	State->Directions[0] = 1;
	State->Directions[1] = 1;
	State->Directions[2] = 1;

	State->Camera.xAngle = 0;
	State->Camera.yAngle = 0;
	State->Camera.zAngle = 0;
}
