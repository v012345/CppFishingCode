#include "../stdafx.h"

#include "PlayGameScene.h"
#include "StageSelectScene.h"
#include <functional>

#include "../Manager/CollisionManger.h"
StageSelectScene::StageSelectScene() {}
StageSelectScene::~StageSelectScene() {}
void StageSelectScene::init(App* app, CollisionManger* colObj) {
    this->scene = NULL;
    this->app = NULL;
    this->colObj = NULL;
    this->maxBox = NULL;
    this->zoom = 0.7;
    this->scene = new action(app);
    this->app = app;
    this->colObj = colObj;

    this->maxBox = new DisplayObject(0, 0);
    scene->addChild((Sprite*)this->maxBox);

    // 拼图
    Sprite* bg = new Sprite(this->app, L"img/Interface/startbg.jpg");
    bg->width = app->width;
    bg->height = app->height;
    this->maxBox->addChild(bg);
    Sprite* txt1 = this->initTxtSprite("请选择场景", 15, 20);
    this->maxBox->addChild(txt1);
    int w = 1024;
    int h = 682;

    this->mStageSelectButton.push_back(new Sprite(this->app, L"img/Interface/1a.jpg"));
    this->mStageSelectButton.push_back(new Sprite(this->app, L"img/Interface/1b.jpg"));
    this->mStageSelectButton.push_back(new Sprite(this->app, L"img/Interface/1c.jpg"));
    this->mStageSelectButton.push_back(new Sprite(this->app, L"img/Interface/1d.jpg"));
    this->mStageSelectButton.push_back(new Sprite(this->app, L"img/Interface/1e.jpg"));
    this->mStageSelectButton.push_back(new Sprite(this->app, L"img/Interface/1f.jpg"));
    this->mStageSelectButton.push_back(this->initTxtSprite("这里有大乌龟", 0, 0));
    this->mStageSelectButton.push_back(this->initTxtSprite("这里有电鳗鱼", 0, 0));
    this->mStageSelectButton.push_back(this->initTxtSprite("这里有大鲨鱼", 0, 0));
    this->mStageSelectButton.push_back(this->initTxtSprite("这里有黄金大鲨鱼", 0, 0));
    this->mStageSelectButton.push_back(this->initTxtSprite("这里大珍珠", 0, 0));
    this->mStageSelectButton.push_back(this->initTxtSprite("这里有传说中的美人鱼哦！", 0, 0));

    float zoom = (float)(300.f / w);
    int x = 0;
    int y = 0;
    bool b1 = true;
    for (unsigned int i = 0; i < 6; i++) {
        this->mStageSelectButton[i]->width = w;
        this->mStageSelectButton[i]->height = h;
        x = (i % 3) * (300 + 50) + 85;
        y = 320 * (int)(i / 3) + 80;
        this->mStageSelectButton[i]->use_int["useInt"] = i;

        this->maxBox->addChild(this->mStageSelectButton[i]);
        this->mStageSelectButton[i]->setX(x);
        this->mStageSelectButton[i]->zoom = zoom;
        this->mStageSelectButton[i]->setY(y);

        this->maxBox->addChild(this->mStageSelectButton[i + 6]);
        this->mStageSelectButton[i + 6]->setX(x);
        this->mStageSelectButton[i + 6]->setY(y + this->mStageSelectButton[i]->getHeight());
    }

    // 点击回调
    app->use_onClick["StageSelectScene"] = [this](int x, int y) {
        unsigned int len = this->mStageSelectButton.size();
        for (unsigned int i = 0; i < len; i++) {
            if (this->mStageSelectButton[i]->inRect(this->app->mouse)) {
                PlayGameScene* p = PlayGameScene::getInstance();
                p->mStageId = this->mStageSelectButton[i]->use_int["useInt"];
                this->app->nowScene = ePlayGameScene;
                p->visible();
            }
        }
    };
}

Sprite* StageSelectScene::initTxtSprite(string txt, int x, int y) {
    Sprite* txt1 = new Sprite(x, y);
    txt1->spriteType = "textSprite";
    txt1->txt = txt;
    txt1->rgb = 0xffffff;
    txt1->width = txt1->getTxtWidth(this->app);
    return txt1;
}
