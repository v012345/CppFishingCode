#pragma once
#include "../stdafx.h"
class action;
class DemoApp;
class colVec;
namespace StageSelectScene {
    extern action* scene;
    extern DemoApp* app;
    extern colVec* colObj;
    extern DisplayObject* maxBox;
    extern float zoom;
    extern void init(DemoApp* app, colVec* colObj);
    extern void visible();
    extern void onClick(int x, int y);
    extern vector<Sprite*> spArr;
    extern Sprite* initTxtSprite(string txt, int x, int y);
} // namespace StageSelectScene