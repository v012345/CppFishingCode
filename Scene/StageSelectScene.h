#pragma once
#include "../stdafx.h"
#include "BaseScene.h"
class action;
class App;
class CollisionManger;
class StageSelectScene : public BaseScene {
  public:
    static StageSelectScene* getInstance() {
        static StageSelectScene instance;
        return &instance;
    }
    action* scene;
    App* app;
    CollisionManger* colObj;
    DisplayObject* maxBox;
    float zoom;
    void init(App* app, CollisionManger* colObj);
    vector<Sprite*> mStageSelectButton;
    Sprite* initTxtSprite(string txt, int x, int y);

  private:
    StageSelectScene();
    ~StageSelectScene();
};