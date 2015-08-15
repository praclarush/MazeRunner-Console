/* ---------------------------------------------------------------------------
**
** File: file.h
** Description: Contains Methods used to access the Windows File System
**
** Author: Nathan Bremmer
** -------------------------------------------------------------------------*/

#include "stdafx.h"
#include "file.h"

using namespace std;

//Get Files from provided directory using a Map<int, string> format
void getFiles(char* dir, map<int, string>& files)
{

	WIN32_FIND_DATAA search_data;

	memset(&search_data, 0, sizeof(WIN32_FIND_DATAA));

	HANDLE handle = FindFirstFileA(dir, &search_data);

	int count = 0;

	while (handle != INVALID_HANDLE_VALUE)
	{
		count++;
		files[count] = search_data.cFileName;

		if (FindNextFileA(handle, &search_data) == FALSE)
			break;
	}
}