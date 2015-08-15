/* ---------------------------------------------------------------------------
** 
** File: file.h
** Description: Contains Methods used to access the Windows File System
** 
** Author: Nathan Bremmer
** -------------------------------------------------------------------------*/

#pragma once

#include "targetver.h"
#include "stdafx.h"

using namespace std;

//Get Files from provided directory using a Map<int, string> format
void getFiles(char* dir, map<int, string>& files);

//getFileByName