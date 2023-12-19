#include "../stdafx.h"

#include "TitleScene.h"

#include "StageSelectScene.h"

#include "../instance/colVec.h"

action* TitleScene::scene = NULL;
DemoApp* TitleScene::app = NULL;
colVec* TitleScene::colObj = NULL;
DisplayObject* TitleScene::maxBox = NULL;
float TitleScene::zoom = 0.7;
bool TitleScene::isInit = false;
vector<utils::usePoint> TitleScene::p1;
void TitleScene::init(DemoApp* app, colVec* colObj) {
    TitleScene::scene = new action(app);
    TitleScene::app = app;

    TitleScene::colObj = colObj;
    app->use_onClick["TitleScene"] = TitleScene::onClick;
    TitleScene::maxBox = new DisplayObject(0, 0);
    scene->addChild((sprite*)TitleScene::maxBox);
}
void TitleScene::visible() {

    sprite* bg = new sprite(TitleScene::app, L"img/Interface/startbg.jpg");
    bg->width = app->width;
    bg->height = app->height;

    sprite* lg = new sprite(TitleScene::app, L"img/Interface/login.png");
    lg->zoom = TitleScene::zoom;

    sprite* sn = new sprite(TitleScene::app, L"img/Interface/sign.png");
    sn->zoom = TitleScene::zoom;
    sn->setId("start");

    TitleScene::maxBox->addChild(bg);
    TitleScene::maxBox->addChild(lg);
    TitleScene::maxBox->addChild(sn);

    lg->setX((bg->getWidth() / 2 - lg->getWidth() / 2));
    lg->setY((bg->getHeight() / 2 - lg->getHeight() / 2) - bg->getHeight() / 100 * 15);

    sn->setX((bg->getWidth() / 2 - sn->getWidth() / 2));
    sn->setY((bg->getHeight() / 2 - lg->getHeight() / 2) - bg->getHeight() / 100 * 15 + lg->getHeight() + 30);
};
void TitleScene::onClick(int x, int y) {
    sprite* sn = TitleScene::maxBox->getChildById("start");

    if (sn->inRect(TitleScene::app->mouse)) {

        app->nowScene = 2;
        StageSelectScene::visible();
    }
}
