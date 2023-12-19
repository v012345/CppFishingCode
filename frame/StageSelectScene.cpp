#include "../stdafx.h"

#include "PlayGameScene.h"
#include "StageSelectScene.h"

#include "../instance/colVec.h"
action* StageSelectScene::scene = NULL;
DemoApp* StageSelectScene::app = NULL;
colVec* StageSelectScene::colObj = NULL;
DisplayObject* StageSelectScene::maxBox = NULL;
float StageSelectScene::zoom = 0.7;
vector<Sprite*> StageSelectScene::spArr;
void StageSelectScene::init(DemoApp* app, colVec* colObj) {
    StageSelectScene::scene = new action(app);
    StageSelectScene::app = app;
    StageSelectScene::colObj = colObj;
    app->use_onClick["StageSelectScene"] = StageSelectScene::onClick;
    StageSelectScene::maxBox = new DisplayObject(0, 0);
    scene->addChild((Sprite*)StageSelectScene::maxBox);
}
Sprite* StageSelectScene::initTxtSprite(string txt, int x, int y) {
    Sprite* txt1 = new Sprite(x, y);
    txt1->spriteType = "textSprite";
    txt1->txt = txt;
    txt1->rgb = 0xffffff;
    txt1->width = txt1->getTxtWidth(StageSelectScene::app);
    return txt1;
}
void StageSelectScene::visible() {
    if (StageSelectScene::spArr.size() != 0) { return; }
    Sprite* bg = new Sprite(StageSelectScene::app, L"img/Interface/startbg.jpg");
    bg->width = app->width;
    bg->height = app->height;
    StageSelectScene::maxBox->addChild(bg);
    Sprite* txt1 = StageSelectScene::initTxtSprite("请选择场景", 15, 20);
    StageSelectScene::maxBox->addChild(txt1);
    int w = 1024;
    int h = 682;

    StageSelectScene::spArr.push_back(new Sprite(StageSelectScene::app, L"img/Interface/1a.jpg"));
    StageSelectScene::spArr.push_back(new Sprite(StageSelectScene::app, L"img/Interface/1b.jpg"));
    StageSelectScene::spArr.push_back(new Sprite(StageSelectScene::app, L"img/Interface/1c.jpg"));
    StageSelectScene::spArr.push_back(new Sprite(StageSelectScene::app, L"img/Interface/1d.jpg"));
    StageSelectScene::spArr.push_back(new Sprite(StageSelectScene::app, L"img/Interface/1e.jpg"));
    StageSelectScene::spArr.push_back(new Sprite(StageSelectScene::app, L"img/Interface/1f.jpg"));
    StageSelectScene::spArr.push_back(StageSelectScene::initTxtSprite("这里有大乌龟", 0, 0));
    StageSelectScene::spArr.push_back(StageSelectScene::initTxtSprite("这里有电鳗鱼", 0, 0));
    StageSelectScene::spArr.push_back(StageSelectScene::initTxtSprite("这里有大鲨鱼", 0, 0));
    StageSelectScene::spArr.push_back(StageSelectScene::initTxtSprite("这里有黄金大鲨鱼", 0, 0));
    StageSelectScene::spArr.push_back(StageSelectScene::initTxtSprite("这里大珍珠", 0, 0));
    StageSelectScene::spArr.push_back(StageSelectScene::initTxtSprite("这里有传说中的美人鱼哦！", 0, 0));

    float zoom = (float)(300.f / w);
    int x = 0;
    int y = 0;
    bool b1 = true;
    for (unsigned int i = 0; i < 6; i++) {
        StageSelectScene::spArr[i]->width = w;
        StageSelectScene::spArr[i]->height = h;
        x = (i % 3) * (300 + 50) + 85;
        y = 320 * (int)(i / 3) + 80;
        StageSelectScene::spArr[i]->use_int["useInt"] = i;

        StageSelectScene::maxBox->addChild(StageSelectScene::spArr[i]);
        StageSelectScene::spArr[i]->setX(x);
        StageSelectScene::spArr[i]->zoom = zoom;
        StageSelectScene::spArr[i]->setY(y);

        StageSelectScene::maxBox->addChild(StageSelectScene::spArr[i + 6]);
        StageSelectScene::spArr[i + 6]->setX(x);
        StageSelectScene::spArr[i + 6]->setY(y + StageSelectScene::spArr[i]->getHeight());
    }
};

void StageSelectScene::onClick(int x, int y) {

    unsigned int len = StageSelectScene::spArr.size();
    for (unsigned int i = 0; i < len; i++) {
        if (StageSelectScene::spArr[i]->inRect(StageSelectScene::app->mouse)) {
            PlayGameScene::nowScane = StageSelectScene::spArr[i]->use_int["useInt"];
            StageSelectScene::app->nowScene = ePlayGameScene;
            PlayGameScene::visible();
        }
    }
}