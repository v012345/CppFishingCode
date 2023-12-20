#include "../stdafx.h"

#include "TitleScene.h"
#include <functional>

#include "StageSelectScene.h"

#include "../Manager/CollisionManger.h"
TitleScene::TitleScene() {
    this->app = App::getInstance();
    this->colObj = CollisionManger::getInstance();
    this->scene = NULL;
    this->maxBox = NULL;
    this->zoom = 0.7f;
    this->scene = new action(app);

    this->colObj = colObj;
    this->maxBox = new DisplayObject(0, 0);
    scene->addChild((Sprite*)this->maxBox);

    app->use_onClick["TitleScene"] = [this](int x, int y) {
        DisplayObject* m = this->maxBox;
        Sprite* sn = m->getChildById("start");
        if (sn->inRect(this->app->mouse)) { //
            this->app->changeScene(eStageSelectScene);
        }
    };

    // 拼图
    Sprite* bg = new Sprite(this->app, L"img/Interface/startbg.jpg");
    bg->width = app->width;
    bg->height = app->height;

    Sprite* lg = new Sprite(this->app, L"img/Interface/login.png");
    lg->zoom = this->zoom;

    Sprite* sn = new Sprite(this->app, L"img/Interface/sign.png");
    sn->zoom = this->zoom;
    sn->setId("start");

    this->maxBox->addChild(bg);
    this->maxBox->addChild(lg);
    this->maxBox->addChild(sn);

    lg->setX((bg->getWidth() / 2 - lg->getWidth() / 2));
    lg->setY((bg->getHeight() / 2 - lg->getHeight() / 2) - bg->getHeight() / 100 * 15);

    sn->setX((bg->getWidth() / 2 - sn->getWidth() / 2));
    sn->setY((bg->getHeight() / 2 - lg->getHeight() / 2) - bg->getHeight() / 100 * 15 + lg->getHeight() + 30);
}
TitleScene::~TitleScene() {}
