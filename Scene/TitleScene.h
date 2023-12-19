#pragma once
#include "../stdafx.h"
#include "BaseScene.h"
class action;
class App;
class TitleScene : public BaseScene {
  public:
    static TitleScene* getInstance() {
        static TitleScene instance;
        return &instance;
    }
    void init(App* app, colVec* colObj);
    action* scene;
    App* app;
    colVec* colObj;
    float zoom;
    vector<utils::usePoint> p1;
    DisplayObject* maxBox;

  private:
    TitleScene();
    ~TitleScene();
};