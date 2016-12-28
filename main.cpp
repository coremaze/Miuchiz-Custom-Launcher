#if defined(UNICODE) && !defined(_UNICODE)
    #define _UNICODE
#elif defined(_UNICODE) && !defined(UNICODE)
    #define UNICODE
#endif
#include <iostream> // library that contain basic input/output functions
#include <fstream>  // library that contains file input/output functions
#include <cstring>
#include <cstdio>
#include <tchar.h>
#include <windows.h>
#include <stdlib.h>     /* exit, EXIT_FAILURE */
#include "resource.h"
using namespace std;
/*  Declare Windows procedure  */
LRESULT CALLBACK WindowProcedure (HWND, UINT, WPARAM, LPARAM);

/*  Make the class name into a global variable  */
TCHAR szClassName[ ] = _T("CodeBlocksWindowsApp");
int get_file_size(std::string filename);

extern char * originalexe = "aworld.exe";
extern char * newexe = "mion.exe";

int WINAPI WinMain (HINSTANCE hThisInstance,
                     HINSTANCE hPrevInstance,
                     LPSTR lpszArgument,
                     int nCmdShow)

{

    HWND hwnd;               /* This is the handle for our window */
    MSG messages;            /* Here messages to the application are saved */
    WNDCLASSEX wincl;        /* Data structure for the windowclass */

    /* The Window structure */
    wincl.hInstance = hThisInstance;
    wincl.lpszClassName = szClassName;
    wincl.lpfnWndProc = WindowProcedure;      /* This function is called by windows */
    wincl.style = CS_DBLCLKS;                 /* Catch double-clicks */
    wincl.cbSize = sizeof (WNDCLASSEX);

    /* Use default icon and mouse-pointer */
    wincl.hIcon = LoadIcon (NULL, IDI_APPLICATION);
    wincl.hIconSm = (HICON)LoadImage(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_ICON), IMAGE_ICON, 16,16,0);;
    wincl.hCursor = LoadCursor (NULL, IDC_ARROW);
    wincl.lpszMenuName = NULL;                 /* No menu */
    wincl.cbClsExtra = 0;                      /* No extra bytes after the window class */
    wincl.cbWndExtra = 0;                      /* structure or the window instance */
    /* Use Windows's default colour as the background of the window */
    wincl.hbrBackground = (HBRUSH) COLOR_BACKGROUND;

    /* Register the window class, and if it fails quit the program */
    if (!RegisterClassEx (&wincl))
        return 0;

    /* The class is registered, let's create the program*/
    hwnd = CreateWindowEx (
           0,                   /* Extended possibilites for variation */
           szClassName,         /* Classname */
           _T("Miuchiz Custom Launcher"),       /* Title Text */
           WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX, /* default window */
           CW_USEDEFAULT,       /* Windows decides the position */
           CW_USEDEFAULT,       /* where the window ends up on the screen */
           400,                 /* The programs width */
           225,                 /* and height in pixels */
           HWND_DESKTOP,        /* The window is a child-window to desktop */
           NULL,                /* No menu */
           hThisInstance,       /* Program Instance handler */
           NULL                 /* No Window Creation data */
           );

    /* Make the window visible on the screen */
    ShowWindow (hwnd, nCmdShow);

    /* Run the message loop. It will run until GetMessage() returns 0 */
    while (GetMessage (&messages, NULL, 0, 0))
    {
        /* Translate virtual-key messages into character messages */
        TranslateMessage(&messages);
        /* Send message to WindowProcedure */
        DispatchMessage(&messages);
    }

    /* The program return-value is 0 - The value that PostQuitMessage() gave */
    return messages.wParam;
}


/*  This function is called by the Windows function DispatchMessage()  */

LRESULT CALLBACK WindowProcedure (HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{

    STARTUPINFO si;
	PROCESS_INFORMATION pi;
    ZeroMemory( &si, sizeof(si) );
	si.cb = sizeof(si);
	ZeroMemory( &pi, sizeof(pi) );
    switch (message)                  /* handle the messages */
    {
        case WM_CREATE:

            CreateWindow(TEXT("STATIC"),TEXT("Choose the cheats you want to use in Planet Mion."),WS_CHILD | WS_VISIBLE, 10,10,400,300,hwnd,0,0,0);

            CreateWindow(TEXT("button"), TEXT("Run"),
                         WS_VISIBLE | WS_CHILD,
                         10, 150, 80, 25,
                         hwnd, (HMENU) 1, NULL, NULL
                         );


            CreateWindow(TEXT("button"), TEXT("Object selection"),
                         WS_VISIBLE | WS_CHILD | BS_CHECKBOX,
                         10, 50, 200, 25,
                         hwnd, (HMENU) 2, NULL, NULL
                         );
            CreateWindow(TEXT("button"), TEXT("Pass-through (Noclip)"),
                         WS_VISIBLE | WS_CHILD | BS_CHECKBOX,
                         10, 75, 200, 25,
                         hwnd, (HMENU) 3, NULL, NULL
                         );
            CreateWindow(TEXT("button"), TEXT("Flight"),
                         WS_VISIBLE | WS_CHILD | BS_CHECKBOX,
                         10, 100, 200, 25,
                         hwnd, (HMENU) 4, NULL, NULL
                         );
            CreateWindow(TEXT("button"), TEXT("Increase object selection limit"),
                         WS_VISIBLE | WS_CHILD | BS_CHECKBOX,
                         10, 125, 275, 25,
                         hwnd, (HMENU) 5, NULL, NULL
                         );

                         break;

        case WM_COMMAND:
        if(LOWORD(wParam) == 2){//object selection

	    if (IsDlgButtonChecked(hwnd, 2)) {
	        CheckDlgButton(hwnd, 2, BST_UNCHECKED);

	    } else {
		 CheckDlgButton(hwnd, 2, BST_CHECKED);

	    }
        }

        if(LOWORD(wParam) == 3){//noclip

	    if (IsDlgButtonChecked(hwnd, 3)) {
	        CheckDlgButton(hwnd, 3, BST_UNCHECKED);

	    } else {
		 CheckDlgButton(hwnd, 3, BST_CHECKED);

	    }
        }
        if(LOWORD(wParam) == 4){//flight

	    if (IsDlgButtonChecked(hwnd, 4)) {
	        CheckDlgButton(hwnd, 4, BST_UNCHECKED);

	    } else {
		 CheckDlgButton(hwnd, 4, BST_CHECKED);

	    }
        }

        if(LOWORD(wParam) == 5){//Remove object selection limit

	    if (IsDlgButtonChecked(hwnd, 5)) {
	        CheckDlgButton(hwnd, 5, BST_UNCHECKED);

	    } else {
		 CheckDlgButton(hwnd, 5, BST_CHECKED);

	    }
        }



            if(LOWORD(wParam) == 1){

            DeleteFile(newexe);

            	ifstream fin(originalexe, ios_base::in | ios_base::binary);
  if(fin.is_open())
	{
	                int array_size = get_file_size(originalexe);
            char * array = new char[array_size+2];
            int position = 0;




		while(position < array_size+2)
		{

			fin.get(array[position]);


			if (IsDlgButtonChecked(hwnd, 2)) { //Object selection checkbox
                if(position>=0x000D66ED && position<=0x000D66F2){
                    array[position]=0x90;
                }
			}
			if (IsDlgButtonChecked(hwnd, 3)) { //Noclip checkbox
                if(position==0x000FEDF0){
                    array[position]=0xEB;
                }
			}
			if (IsDlgButtonChecked(hwnd, 4)) { //Flight checkbox
                if(position==0x000FF3BF || position ==0x000FF426){
                    array[position]=0xEB;
                }
			}
			if (IsDlgButtonChecked(hwnd, 5)) { //Remove object selection limit checkbox
                if(position==0x000D923F){
                    array[position]=0x00;
                }else if(position==0x000D9240){
                    array[position]=0x80;
                }
			}

            position++;

		}

            ofstream out(newexe, ios_base::out | ios_base::binary);
        if(! out)
        {
       return 1;
        }

        out.write((char *)array,position-2);
        out.close();
              	if (!
                CreateProcess
                (
                TEXT(newexe),
                NULL,NULL,NULL,FALSE,
                CREATE_NEW_CONSOLE,
                NULL,NULL,
                &si,
                &pi
                )
                )
            {

            }
            exit(EXIT_SUCCESS);
	}
            }

            break;
        case WM_DESTROY:
            PostQuitMessage (0);       /* send a WM_QUIT to the message queue */
            break;
        default:                      /* for messages that we don't deal with */
            return DefWindowProc (hwnd, message, wParam, lParam);
    }

    return 0;
}
int get_file_size(std::string filename) // path to file
{
    FILE *p_file = NULL;
    p_file = fopen(filename.c_str(),"rb");
    fseek(p_file,0,SEEK_END);
    int size = ftell(p_file);
    fclose(p_file);
    return size;
}
