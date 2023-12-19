#pragma once
#include "../stdafx.h"
class action;
class App;
namespace TitleScene {
    extern action* scene;
    extern App* app;
    extern colVec* colObj;
    extern DisplayObject* maxBox;
    extern float zoom;
    extern bool isInit;
    extern void init(App* app, colVec* colObj);
    extern void onClick(int x, int y);
    extern void visible();
    extern vector<utils::usePoint> p1;
} // namespace TitleScene