#pragma once
#include "../stdafx.h"
class action;
class App;
class colVec;
namespace StageSelectScene {
    extern action* scene;
    extern App* app;
    extern colVec* colObj;
    extern DisplayObject* maxBox;
    extern float zoom;
    extern void init(App* app, colVec* colObj);
    extern void visible();
    extern void onClick(int x, int y);
    extern vector<Sprite*> spArr;
    extern Sprite* initTxtSprite(string txt, int x, int y);
} // namespace StageSelectScene