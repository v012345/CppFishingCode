#pragma once
#include "../stdafx.h"
class action;
class DemoApp;
namespace TitleScene {
    extern action* scene;
    extern DemoApp* app;
    extern colVec* colObj;
    extern DisplayObject* maxBox;
    extern float zoom;
    extern bool isInit;
    extern void init(DemoApp* app, colVec* colObj);
    extern void onClick(int x, int y);
    extern void visible();
    extern vector<utils::usePoint> p1;
} // namespace TitleScene