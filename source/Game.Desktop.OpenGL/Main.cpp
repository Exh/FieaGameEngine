#include "pch.h"

/*
 *		This Code Was Created By Jeff Molofee 2000
 *		A HUGE Thanks To Fredric Echols For Cleaning Up
 *		And Optimizing The Base Code, Making It More Flexible!
 *		If You've Found This Code Useful, Please Let Me Know.
 *		Visit My Site At nehe.gamedev.net
 */

HDC			g_hDC=NULL;		// Private GDI Device Context
HGLRC		g_hRC=NULL;		// Permanent Rendering Context
HWND		g_hWnd=NULL;		// Holds Our Window Handle
HINSTANCE	g_hInstance;		// Holds The Instance Of The Application

bool	keys[256];			// Array Used For The Keyboard Routine
bool	active=TRUE;		// Window Active Flag Set To TRUE By Default
bool	fullscreen=FALSE;	// Fullscreen Flag Set To Fullscreen Mode By Default

GLfloat	rtri;				// Angle For The Triangle ( NEW )
GLfloat	rquad;				// Angle For The Quad ( NEW )

LRESULT	CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);	// Declaration For WndProc

GLvoid ReSizeGLScene(GLsizei width, GLsizei height)		// Resize And Initialize The GL Window
{
	if (height==0)										// Prevent A Divide By Zero By
	{
		height=1;										// Making Height Equal One
	}

	glViewport(0,0,width,height);						// Reset The Current Viewport

	glMatrixMode(GL_PROJECTION);						// Select The Projection Matrix
	glLoadIdentity();									// Reset The Projection Matrix

	// Calculate The Aspect Ratio Of The Window
	gluPerspective(45.0f,(GLfloat)width/(GLfloat)height,0.1f,100.0f);

	glMatrixMode(GL_MODELVIEW);							// Select The Modelview Matrix
	glLoadIdentity();									// Reset The Modelview Matrix
}

int InitGL(GLvoid)										// All Setup For OpenGL Goes Here
{
	glShadeModel(GL_SMOOTH);							// Enable Smooth Shading
	glClearColor(0.0f, 0.0f, 0.0f, 0.5f);				// Black Background
	glClearDepth(1.0f);									// Depth Buffer Setup
	glEnable(GL_DEPTH_TEST);							// Enables Depth Testing
	glDepthFunc(GL_LEQUAL);								// The Type Of Depth Testing To Do
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);	// Really Nice Perspective Calculations
	return TRUE;										// Initialization Went OK
}

int DrawGLScene(GLvoid)									// Here's Where We Do All The Drawing
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	// Clear Screen And Depth Buffer
	glLoadIdentity();									// Reset The Current Modelview Matrix
	glTranslatef(-1.5f,0.0f,-6.0f);						// Move Left 1.5 Units And Into The Screen 6.0
	glRotatef(rtri,0.0f,1.0f,0.0f);						// Rotate The Triangle On The Y axis ( NEW )
	glBegin(GL_TRIANGLES);								// Start Drawing A Triangle
		glColor3f(1.0f,0.0f,0.0f);						// Red
		glVertex3f( 0.0f, 1.0f, 0.0f);					// Top Of Triangle (Front)
		glColor3f(0.0f,1.0f,0.0f);						// Green
		glVertex3f(-1.0f,-1.0f, 1.0f);					// Left Of Triangle (Front)
		glColor3f(0.0f,0.0f,1.0f);						// Blue
		glVertex3f( 1.0f,-1.0f, 1.0f);					// Right Of Triangle (Front)
		glColor3f(1.0f,0.0f,0.0f);						// Red
		glVertex3f( 0.0f, 1.0f, 0.0f);					// Top Of Triangle (Right)
		glColor3f(0.0f,0.0f,1.0f);						// Blue
		glVertex3f( 1.0f,-1.0f, 1.0f);					// Left Of Triangle (Right)
		glColor3f(0.0f,1.0f,0.0f);						// Green
		glVertex3f( 1.0f,-1.0f, -1.0f);					// Right Of Triangle (Right)
		glColor3f(1.0f,0.0f,0.0f);						// Red
		glVertex3f( 0.0f, 1.0f, 0.0f);					// Top Of Triangle (Back)
		glColor3f(0.0f,1.0f,0.0f);						// Green
		glVertex3f( 1.0f,-1.0f, -1.0f);					// Left Of Triangle (Back)
		glColor3f(0.0f,0.0f,1.0f);						// Blue
		glVertex3f(-1.0f,-1.0f, -1.0f);					// Right Of Triangle (Back)
		glColor3f(1.0f,0.0f,0.0f);						// Red
		glVertex3f( 0.0f, 1.0f, 0.0f);					// Top Of Triangle (Left)
		glColor3f(0.0f,0.0f,1.0f);						// Blue
		glVertex3f(-1.0f,-1.0f,-1.0f);					// Left Of Triangle (Left)
		glColor3f(0.0f,1.0f,0.0f);						// Green
		glVertex3f(-1.0f,-1.0f, 1.0f);					// Right Of Triangle (Left)
	glEnd();											// Done Drawing The Pyramid

	glLoadIdentity();									// Reset The Current Modelview Matrix
	glTranslatef(1.5f,0.0f,-7.0f);						// Move Right 1.5 Units And Into The Screen 7.0
	glRotatef(rquad,1.0f,1.0f,1.0f);					// Rotate The Quad On The X axis ( NEW )
	glBegin(GL_QUADS);									// Draw A Quad
		glColor3f(0.0f,1.0f,0.0f);						// Set The Color To Green
		glVertex3f( 1.0f, 1.0f,-1.0f);					// Top Right Of The Quad (Top)
		glVertex3f(-1.0f, 1.0f,-1.0f);					// Top Left Of The Quad (Top)
		glVertex3f(-1.0f, 1.0f, 1.0f);					// Bottom Left Of The Quad (Top)
		glVertex3f( 1.0f, 1.0f, 1.0f);					// Bottom Right Of The Quad (Top)
		glColor3f(1.0f,0.5f,0.0f);						// Set The Color To Orange
		glVertex3f( 1.0f,-1.0f, 1.0f);					// Top Right Of The Quad (Bottom)
		glVertex3f(-1.0f,-1.0f, 1.0f);					// Top Left Of The Quad (Bottom)
		glVertex3f(-1.0f,-1.0f,-1.0f);					// Bottom Left Of The Quad (Bottom)
		glVertex3f( 1.0f,-1.0f,-1.0f);					// Bottom Right Of The Quad (Bottom)
		glColor3f(1.0f,0.0f,0.0f);						// Set The Color To Red
		glVertex3f( 1.0f, 1.0f, 1.0f);					// Top Right Of The Quad (Front)
		glVertex3f(-1.0f, 1.0f, 1.0f);					// Top Left Of The Quad (Front)
		glVertex3f(-1.0f,-1.0f, 1.0f);					// Bottom Left Of The Quad (Front)
		glVertex3f( 1.0f,-1.0f, 1.0f);					// Bottom Right Of The Quad (Front)
		glColor3f(1.0f,1.0f,0.0f);						// Set The Color To Yellow
		glVertex3f( 1.0f,-1.0f,-1.0f);					// Top Right Of The Quad (Back)
		glVertex3f(-1.0f,-1.0f,-1.0f);					// Top Left Of The Quad (Back)
		glVertex3f(-1.0f, 1.0f,-1.0f);					// Bottom Left Of The Quad (Back)
		glVertex3f( 1.0f, 1.0f,-1.0f);					// Bottom Right Of The Quad (Back)
		glColor3f(0.0f,0.0f,1.0f);						// Set The Color To Blue
		glVertex3f(-1.0f, 1.0f, 1.0f);					// Top Right Of The Quad (Left)
		glVertex3f(-1.0f, 1.0f,-1.0f);					// Top Left Of The Quad (Left)
		glVertex3f(-1.0f,-1.0f,-1.0f);					// Bottom Left Of The Quad (Left)
		glVertex3f(-1.0f,-1.0f, 1.0f);					// Bottom Right Of The Quad (Left)
		glColor3f(1.0f,0.0f,1.0f);						// Set The Color To Violet
		glVertex3f( 1.0f, 1.0f,-1.0f);					// Top Right Of The Quad (Right)
		glVertex3f( 1.0f, 1.0f, 1.0f);					// Top Left Of The Quad (Right)
		glVertex3f( 1.0f,-1.0f, 1.0f);					// Bottom Left Of The Quad (Right)
		glVertex3f( 1.0f,-1.0f,-1.0f);					// Bottom Right Of The Quad (Right)
	glEnd();											// Done Drawing The Quad

	rtri+=0.2f;											// Increase The Rotation Variable For The Triangle ( NEW )
	rquad-=0.15f;										// Decrease The Rotation Variable For The Quad ( NEW )
	return TRUE;										// Keep Going
}

GLvoid KillGLWindow(GLvoid)								// Properly Kill The Window
{
	if (fullscreen)										// Are We In Fullscreen Mode?
	{
		ChangeDisplaySettings(NULL,0);					// If So Switch Back To The Desktop
		ShowCursor(TRUE);								// Show Mouse Pointer
	}

	if (g_hRC)											// Do We Have A Rendering Context?
	{
		if (!wglMakeCurrent(NULL,NULL))					// Are We Able To Release The DC And RC Contexts?
		{
			MessageBox(NULL,L"Release Of DC And RC Failed.",L"SHUTDOWN ERROR",MB_OK | MB_ICONINFORMATION);
		}

		if (!wglDeleteContext(g_hRC))						// Are We Able To Delete The RC?
		{
			MessageBox(NULL,L"Release Rendering Context Failed.",L"SHUTDOWN ERROR",MB_OK | MB_ICONINFORMATION);
		}
		g_hRC=NULL;										// Set RC To NULL
	}

	if (g_hDC && !ReleaseDC(g_hWnd,g_hDC))					// Are We Able To Release The DC
	{
		MessageBox(NULL,L"Release Device Context Failed.",L"SHUTDOWN ERROR",MB_OK | MB_ICONINFORMATION);
		g_hDC=NULL;										// Set DC To NULL
	}

	if (g_hWnd && !DestroyWindow(g_hWnd))					// Are We Able To Destroy The Window?
	{
		MessageBox(NULL,L"Could Not Release hWnd.",L"SHUTDOWN ERROR",MB_OK | MB_ICONINFORMATION);
		g_hWnd=NULL;										// Set hWnd To NULL
	}

	if (!UnregisterClass(L"OpenGL",g_hInstance))			// Are We Able To Unregister Class
	{
		MessageBox(NULL,L"Could Not Unregister Class.",L"SHUTDOWN ERROR",MB_OK | MB_ICONINFORMATION);
		g_hInstance=NULL;									// Set hInstance To NULL
	}
}

/*	This Code Creates Our OpenGL Window.  Parameters Are:					*
 *	title			- Title To Appear At The Top Of The Window				*
 *	width			- Width Of The GL Window Or Fullscreen Mode				*
 *	height			- Height Of The GL Window Or Fullscreen Mode			*
 *	bits			- Number Of Bits To Use For Color (8/16/24/32)			*
 *	fullscreenflag	- Use Fullscreen Mode (TRUE) Or Windowed Mode (FALSE)	*/
 
BOOL CreateGLWindow(char* title, int width, int height, int bits, bool fullscreenflag)
{
	GLuint		PixelFormat;			// Holds The Results After Searching For A Match
	WNDCLASS	wc;						// Windows Class Structure
	DWORD		dwExStyle;				// Window Extended Style
	DWORD		dwStyle;				// Window Style
	RECT		WindowRect;				// Grabs Rectangle Upper Left / Lower Right Values
	WindowRect.left=(long)0;			// Set Left Value To 0
	WindowRect.right=(long)width;		// Set Right Value To Requested Width
	WindowRect.top=(long)0;				// Set Top Value To 0
	WindowRect.bottom=(long)height;		// Set Bottom Value To Requested Height

    UNREFERENCED_PARAMETER(title);

    FieaGameEngine::SList list;
    list.Data();

	fullscreen=fullscreenflag;			// Set The Global Fullscreen Flag

	g_hInstance			= GetModuleHandle(NULL);				// Grab An Instance For Our Window
	wc.style			= CS_HREDRAW | CS_VREDRAW | CS_OWNDC;	// Redraw On Size, And Own DC For Window.
	wc.lpfnWndProc		= (WNDPROC) WndProc;					// WndProc Handles Messages
	wc.cbClsExtra		= 0;									// No Extra Window Data
	wc.cbWndExtra		= 0;									// No Extra Window Data
	wc.hInstance		= g_hInstance;							// Set The Instance
	wc.hIcon			= LoadIcon(NULL, IDI_WINLOGO);			// Load The Default Icon
	wc.hCursor			= LoadCursor(NULL, IDC_ARROW);			// Load The Arrow Pointer
	wc.hbrBackground	= NULL;									// No Background Required For GL
	wc.lpszMenuName		= NULL;									// We Don't Want A Menu
	wc.lpszClassName	= L"OpenGL";					     	// Set The Class Name

	if (!RegisterClass(&wc))									// Attempt To Register The Window Class
	{
		MessageBox(NULL,L"Failed To Register The Window Class.",L"ERROR",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;											// Return FALSE
	}
	
	if (fullscreen)												// Attempt Fullscreen Mode?
	{
		DEVMODE dmScreenSettings;								// Device Mode
		memset(&dmScreenSettings,0,sizeof(dmScreenSettings));	// Makes Sure Memory's Cleared
		dmScreenSettings.dmSize=sizeof(dmScreenSettings);		// Size Of The Devmode Structure
		dmScreenSettings.dmPelsWidth	= width;				// Selected Screen Width
		dmScreenSettings.dmPelsHeight	= height;				// Selected Screen Height
		dmScreenSettings.dmBitsPerPel	= bits;					// Selected Bits Per Pixel
		dmScreenSettings.dmFields=DM_BITSPERPEL|DM_PELSWIDTH|DM_PELSHEIGHT;

		// Try To Set Selected Mode And Get Results.  NOTE: CDS_FULLSCREEN Gets Rid Of Start Bar.
		if (ChangeDisplaySettings(&dmScreenSettings,CDS_FULLSCREEN)!=DISP_CHANGE_SUCCESSFUL)
		{
			// If The Mode Fails, Offer Two Options.  Quit Or Use Windowed Mode.
			if (MessageBox(NULL,L"The Requested Fullscreen Mode Is Not Supported By\nYour Video Card. Use Windowed Mode Instead?",L"NeHe GL",MB_YESNO|MB_ICONEXCLAMATION)==IDYES)
			{
				fullscreen=FALSE;		// Windowed Mode Selected.  Fullscreen = FALSE
			}
			else
			{
				// Pop Up A Message Box Letting User Know The Program Is Closing.
				MessageBox(NULL,L"Program Will Now Close.",L"ERROR",MB_OK|MB_ICONSTOP);
				return FALSE;									// Return FALSE
			}
		}
	}

	if (fullscreen)												// Are We Still In Fullscreen Mode?
	{
		dwExStyle=WS_EX_APPWINDOW;								// Window Extended Style
		dwStyle=WS_POPUP;										// Windows Style
		ShowCursor(FALSE);										// Hide Mouse Pointer
	}
	else
	{
		dwExStyle=WS_EX_APPWINDOW | WS_EX_WINDOWEDGE;			// Window Extended Style
		dwStyle=WS_OVERLAPPEDWINDOW;							// Windows Style
	}

	AdjustWindowRectEx(&WindowRect, dwStyle, FALSE, dwExStyle);		// Adjust Window To True Requested Size

	// Create The Window
    g_hWnd = CreateWindowEx(dwExStyle,							// Extended Style For The Window
        L"OpenGL",							// Class Name
        L"Window",   						// Window Title
        dwStyle |							// Defined Window Style
        WS_CLIPSIBLINGS |					// Required Window Style
        WS_CLIPCHILDREN,					// Required Window Style
        0, 0,								// Window Position
        WindowRect.right - WindowRect.left,	// Calculate Window Width
        WindowRect.bottom - WindowRect.top,	// Calculate Window Height
        NULL,								// No Parent Window
        NULL,								// No Menu
        g_hInstance,							// Instance
        NULL);
	if (!g_hWnd)								// Dont Pass Anything To WM_CREATE
	{
		KillGLWindow();								// Reset The Display
		MessageBox(NULL,L"Window Creation Error.",L"ERROR",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;								// Return FALSE
	}

	static	PIXELFORMATDESCRIPTOR pfd=				// pfd Tells Windows How We Want Things To Be
	{
		sizeof(PIXELFORMATDESCRIPTOR),				// Size Of This Pixel Format Descriptor
		1,											// Version Number
		PFD_DRAW_TO_WINDOW |						// Format Must Support Window
		PFD_SUPPORT_OPENGL |						// Format Must Support OpenGL
		PFD_DOUBLEBUFFER,							// Must Support Double Buffering
		PFD_TYPE_RGBA,								// Request An RGBA Format
		(BYTE) bits,										// Select Our Color Depth
		0, 0, 0, 0, 0, 0,							// Color Bits Ignored
		0,											// No Alpha Buffer
		0,											// Shift Bit Ignored
		0,											// No Accumulation Buffer
		0, 0, 0, 0,									// Accumulation Bits Ignored
		16,											// 16Bit Z-Buffer (Depth Buffer)  
		0,											// No Stencil Buffer
		0,											// No Auxiliary Buffer
		PFD_MAIN_PLANE,								// Main Drawing Layer
		0,											// Reserved
		0, 0, 0										// Layer Masks Ignored
	};
	
    g_hDC=GetDC(g_hWnd);
	if (!g_hDC)							// Did We Get A Device Context?
	{
		KillGLWindow();								// Reset The Display
		MessageBox(NULL,L"Can't Create A GL Device Context.",L"ERROR",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;								// Return FALSE
	}

    PixelFormat=ChoosePixelFormat(g_hDC,&pfd);
	if (!PixelFormat)	// Did Windows Find A Matching Pixel Format?
	{
		KillGLWindow();								// Reset The Display
		MessageBox(NULL,L"Can't Find A Suitable PixelFormat.",L"ERROR",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;								// Return FALSE
	}

	if(!SetPixelFormat(g_hDC,PixelFormat,&pfd))		// Are We Able To Set The Pixel Format?
	{
		KillGLWindow();								// Reset The Display
		MessageBox(NULL,L"Can't Set The PixelFormat.",L"ERROR",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;								// Return FALSE
	}

    g_hRC=wglCreateContext(g_hDC);
	if (!g_hRC)				// Are We Able To Get A Rendering Context?
	{
		KillGLWindow();								// Reset The Display
		MessageBox(NULL,L"Can't Create A GL Rendering Context.",L"ERROR",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;								// Return FALSE
	}

	if(!wglMakeCurrent(g_hDC, g_hRC))					// Try To Activate The Rendering Context
	{
		KillGLWindow();								// Reset The Display
		MessageBox(NULL,L"Can't Activate The GL Rendering Context.",L"ERROR",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;								// Return FALSE
	}

	ShowWindow(g_hWnd,SW_SHOW);						// Show The Window
	SetForegroundWindow(g_hWnd);						// Slightly Higher Priority
	SetFocus(g_hWnd);									// Sets Keyboard Focus To The Window
	ReSizeGLScene(width, height);					// Set Up Our Perspective GL Screen

	if (!InitGL())									// Initialize Our Newly Created GL Window
	{
		KillGLWindow();								// Reset The Display
		MessageBox(NULL,L"Initialization Failed.",L"ERROR",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;								// Return FALSE
	}

	return TRUE;									// Success
}

LRESULT CALLBACK WndProc(	HWND	hWnd,			// Handle For This Window
							UINT	uMsg,			// Message For This Window
							WPARAM	wParam,			// Additional Message Information
							LPARAM	lParam)			// Additional Message Information
{
	switch (uMsg)									// Check For Windows Messages
	{
		case WM_ACTIVATE:							// Watch For Window Activate Message
		{
			// LoWord Can Be WA_INACTIVE, WA_ACTIVE, WA_CLICKACTIVE,
			// The High-Order Word Specifies The Minimized State Of The Window Being Activated Or Deactivated.
			// A NonZero Value Indicates The Window Is Minimized.
			if ((LOWORD(wParam) != WA_INACTIVE) && !((BOOL)HIWORD(wParam)))
				active=TRUE;						// Program Is Active
			else
				active=FALSE;						// Program Is No Longer Active

			return 0;								// Return To The Message Loop
		}

		case WM_SYSCOMMAND:							// Intercept System Commands
		{
			switch (wParam)							// Check System Calls
			{
				case SC_SCREENSAVE:					// Screensaver Trying To Start?
				case SC_MONITORPOWER:				// Monitor Trying To Enter Powersave?
				return 0;							// Prevent From Happening
			}
			break;									// Exit
		}

		case WM_CLOSE:								// Did We Receive A Close Message?
		{
			PostQuitMessage(0);						// Send A Quit Message
			return 0;								// Jump Back
		}

		case WM_KEYDOWN:							// Is A Key Being Held Down?
		{
			keys[wParam] = TRUE;					// If So, Mark It As TRUE
			return 0;								// Jump Back
		}

		case WM_KEYUP:								// Has A Key Been Released?
		{
			keys[wParam] = FALSE;					// If So, Mark It As FALSE
			return 0;								// Jump Back
		}

		case WM_SIZE:								// Resize The OpenGL Window
		{
			ReSizeGLScene(LOWORD(lParam),HIWORD(lParam));  // LoWord=Width, HiWord=Height
			return 0;								// Jump Back
		}
	}

	// Pass All Unhandled Messages To DefWindowProc
	return DefWindowProc(hWnd,uMsg,wParam,lParam);
}

int WINAPI WinMain(	HINSTANCE	hInstance,			// Instance
					HINSTANCE	hPrevInstance,		// Previous Instance
					LPSTR		lpCmdLine,			// Command Line Parameters
					int			nCmdShow)			// Window Show State
{
	MSG		msg;								// Windows Message Structure
	BOOL	done=FALSE;								// Bool Variable To Exit Loop

    msg.wParam = 0;

    

    if (strcmp(lpCmdLine, "Boop"))
    {
        hPrevInstance = 0;
        hInstance = 0;
        nCmdShow = 0;
    }

	// Create Our OpenGL Window
	if (!CreateGLWindow("NeHe's Solid Object Tutorial",640,480,16,fullscreen))
	{
		return 0;									// Quit If Window Was Not Created
	}

	while(!done)									// Loop That Runs While done=FALSE
	{
		if (PeekMessage(&msg,NULL,0,0,PM_REMOVE))	// Is There A Message Waiting?
		{
			if (msg.message==WM_QUIT)				// Have We Received A Quit Message?
			{
				done=TRUE;							// If So done=TRUE
			}
			else									// If Not, Deal With Window Messages
			{
				TranslateMessage(&msg);				// Translate The Message
				DispatchMessage(&msg);				// Dispatch The Message
			}
		}
		else										// If There Are No Messages
		{
			// Draw The Scene.  Watch For ESC Key And Quit Messages From DrawGLScene()
			if ((active && !DrawGLScene()) || keys[VK_ESCAPE])	// Active?  Was There A Quit Received?
			{
				done=TRUE;							// ESC or DrawGLScene Signalled A Quit
			}
			else									// Not Time To Quit, Update Screen
			{
				SwapBuffers(g_hDC);					// Swap Buffers (Double Buffering)
			}

			if (keys[VK_F1])						// Is F1 Being Pressed?
			{
				keys[VK_F1]=FALSE;					// If So Make Key FALSE
				KillGLWindow();						// Kill Our Current Window
				fullscreen=!fullscreen;				// Toggle Fullscreen / Windowed Mode
				// Recreate Our OpenGL Window
				if (!CreateGLWindow("NeHe's Solid Object Tutorial",640,480,16,fullscreen))
				{
					return 0;						// Quit If Window Was Not Created
				}
			}
		}
	}

	// Shutdown
	KillGLWindow();									// Kill The Window
	return ((int)msg.wParam);							// Exit The Program
}
