// A simple program that uses LoadLibrary and
// GetProcAddress to access myPuts from Myputs.dll.

#include <windows.h>
#include <stdlib.h>
#include <limits.h>
#include <time.h>
#include <stdio.h>

#define TRUE 1

typedef int(__cdecl *function_nircmd)(char *);

int main(void)
{
    HINSTANCE hinstLib;
    function_nircmd nircmd;
    BOOL fFreeResult, fRunTimeLinkSuccess = FALSE;

    // Get a handle to the DLL module.

    if ((int)CHAR_BIT * sizeof(void *) == 64)
        hinstLib = LoadLibrary(TEXT("nircmd.dll"));
    else
        hinstLib = LoadLibrary(TEXT("nircmd32.dll"));

    // If the handle is valid, try to get the function address.

    if (hinstLib != NULL)
    {
        // DoNirCmd is the main function of nircmd.dll
        nircmd = (function_nircmd)GetProcAddress(hinstLib, "DoNirCmd");

        // If the function address is valid, call the function.

        if (NULL != nircmd)
        {
            fRunTimeLinkSuccess = TRUE;
            // nircmd have not any output to show, it just doing some works

            (nircmd)("emptybin");                                                                   // empty Recycle Bin
            // (nircmd)("setsysvolume 32767");                                                      // set volume os system
            // (nircmd)("urlshortcut \"http:www.google.com\" \"~$folder.desktop$\" \"Google\"");    // make shortcut to google.com
            // (nircmd)("savescreenshot \"C:\\Users\\sinar\\Desktop\\s.png\"");                     // screenshot
            // (nircmd)("killprocess cmd.exe");                                                     // kill process
            // (nircmd)("exitwin poweroff force");                                                  // logoff / reboot / poweroff / poweroff force
            // (nircmd)("setdisplay 800 600 24");                                                   // change display resoluton | not working !!!
            // (nircmd)("clipboard clear");                                                         // clipboard clear / clipboard set
            // (nircmd)(" infobox \"my fingers are powerful than your security!\" ");               // alert box
            // (nircmd)("speak text \"How Are You Bro \"");                                         // text to speak
            // (nircmd)("setcursor 204 10");                                                        // setcursor / movecursor | to change curor position
            // (nircmd)("sendkeypress shift+alt");                                                  // keyboeard key press
            // (nircmd)("sendkeypress p r i n ctrl+space");                                         // keyboeard key press
            // (nircmd)("convertimage s.png s.gif");                                                // convert image format
        }

        // Free the DLL module.

        fFreeResult = FreeLibrary(hinstLib);
    }

    // If unable to call the DLL function, use an alternative.
    if (!fRunTimeLinkSuccess)
    {
        printf("Somthing went wrong! please check the codes...");
    }

    return 0;
}
