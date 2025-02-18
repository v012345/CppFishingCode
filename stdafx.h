// stdafx.h : 标准系统包含文件的包含文件，
// 或是经常使用但不常更改的
// 特定于项目的包含文件
//

#pragma once

#include "instance/targetver.h"

#define WIN32_LEAN_AND_MEAN // 从 Windows 头中排除极少使用的资料
// Windows 头文件:
#include <windows.h>

#include <functional>
// C 运行时头文件
#include <malloc.h>
#include <memory.h>
#include <stdlib.h>
#include <wchar.h>
// C++运行库
#include <iostream>
#include <sstream>
#include <thread>

#include <set>
#define M_PI 3.14159265358979323846 // pi
#include <cmath>
#include <time.h>
// TODO:  在此处引用程序需要的其他头文件
#include <d2d1.h>
#include <d2d1helper.h>
#include <dwrite.h>
#include <wincodec.h>
#pragma comment(lib, "d2d1.lib")
#pragma comment(lib, "dwrite.lib")
#include <vector>
using namespace std;
#include "instance/oMap.h"
#include "instance/utils.h"
// #include "oMap.h"
template <class Interface> inline void SafeRelease(Interface** ppInterfaceToRelease) {
    if (*ppInterfaceToRelease != NULL) {
        (*ppInterfaceToRelease)->Release();
        (*ppInterfaceToRelease) = NULL;
    }
}

#ifndef HINST_THISCOMPONENT
EXTERN_C IMAGE_DOS_HEADER __ImageBase;
#define HINST_THISCOMPONENT ((HINSTANCE) & __ImageBase)
#endif
wchar_t* g_chartowchar2(const char* cchar);
float random();
typedef struct {
    int x;
    int y;
    int width;
    int height;
} u_rect;
enum SceneType {
    eTitleScene,
    ePlayGameScene,
    eStageSelectScene,
};

#include "App.h"
#include "Manager/CollisionManger.h"
#include "render/Canvas.h"
#include "render/Sprite.h"
#include "render/action.h"
#include "render/ticker.h"
