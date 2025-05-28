#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include "EnigmaSandFront.h"

typedef void (WINAPI*cfunc)();
cfunc beginEnigmaSand;

int main()
{
	HINSTANCE hLib= LoadLibrary ("enigmasand2.dll");
	if (NULL == hLib)
	{
		printf ("LoadLibrary failed\n");
		return 1;
	}

beginEnigmaSand=(cfunc)GetProcAddress((HMODULE)hLib, "beginEnigmaSand");

if(beginEnigmaSand==NULL){printf("oops"); return 1;}

beginEnigmaSand();

		FreeLibrary((HMODULE)hLib);
	// 1.
	return 0;
}
