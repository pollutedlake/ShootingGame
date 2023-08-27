#pragma once
#pragma warning(disable : 4005)

#include<SDKDDKVER.h>

#define WIN32_LEAN_AND_MEAN
#pragma comment(linker,"/entry:WinMainCRTStartup /subsystem:console")

#pragma comment (lib, "msimg32.lib")
#pragma comment (lib, "fmod_vc.lib")

#include <windows.h>
#include "inc/fmod.hpp"
#include "inc/fmod_errors.h"
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>

#include <tchar.h>
#include <stdio.h>
#include <time.h>
#include <timeapi.h>
#include <iostream>
#include <chrono>
#include <random>
#include <memory>
#include <vector>
#include<map>
#include<string.h>
#include <algorithm>
#include <functional>
#include <unordered_map>
#include<cassert>
#include<bitset>
#define _USE_MATH_DEFINES
#include <math.h>
using namespace std;

#include "CommonMacroFunction.h"
#include "RandomFunction.h"
#include "KeyManager.h"
#include "ImageManager.h"
#include "FontManager.h"
#include "TimeManager.h"
#include "SceneManager.h"
#include "SoundManager.h"
#include "Utils.h"
using namespace MY_UTIL;

#define RND RandomFunction::getSingleton()
#define KEYMANAGER KeyManager::getSingleton()
#define IMAGEMANAGER ImageManager::getSingleton()
#define FONTMANAGER FontManager::getSingleton()
#define TIMEMANAGER TimeManager::getSingleton()
#define SCENEMANAGER SceneManager::getSingleton()
#define SOUNDMANAGER SoundManager::getSingleton()

#define WINNAME					(LPTSTR)(TEXT("WindowsAPI"))
#define WINSTART_X				400
#define WINSTART_Y				0
#define WINSIZE_X				672
#define WINSIZE_Y				672

#define PI                       3.141592
#define WINSTYLE				WS_CAPTION | WS_SYSMENU

#define SAFE_DELETE(p)			{if(p) {delete (p); (p) = nullptr;}}
#define SAFE_DELETE_ARRAY(p)	{if(p) {delete[] (p); (p) = nullptr;}}
#define SAFE_RELEASE(p)			{if(p) {(p)->release(); (p) = nullptr;}}

extern HINSTANCE				_hInstance;
extern HWND						_hWnd;
extern POINT					_ptMouse;
