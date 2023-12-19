#include "../stdafx.h"

#include "bullet.h"
#include "files.h"
#include "fish.h"
#include "fishConfig.h"
#include "PlayGameScene.h"
#include "gold.h"
// action * TitleScene::scene = NULL;
action* PlayGameScene::scene = NULL;
DemoApp* PlayGameScene::app = NULL;
colVec* PlayGameScene::colObj = NULL;
DisplayObject* PlayGameScene::maxBox = NULL;
DisplayObject* PlayGameScene::bottomBox = NULL;
DisplayObject* PlayGameScene::fishBox = NULL;
sprite* PlayGameScene::addBtn = NULL;
sprite* PlayGameScene::subtractBtn = NULL;
float PlayGameScene::zoom = 1;
int PlayGameScene::nowScane = 0;
int PlayGameScene::nowPt = 0;
ticker* PlayGameScene::tk1 = NULL;
sprite* PlayGameScene::bk = NULL;
vector<sprite*> PlayGameScene::bgArr;
float PlayGameScene::timerFish = 0;
files* PlayGameScene::saveObj = new files();
vector<sprite*> PlayGameScene::ptArr;
vector<sprite*> PlayGameScene::bulletArr;
vector<bullet*> PlayGameScene::bulletArr2;
vector<fish*> PlayGameScene::fishArr;
vector<fishConfig*> PlayGameScene::fishConfigArr;
vector<sprite*> PlayGameScene::bulletWang;
oMap<string, sprite*> PlayGameScene::bottom;
HANDLE PlayGameScene::hThred;
float PlayGameScene::allPower = 100;
float PlayGameScene::nowPower = 0;
vector<gold*> PlayGameScene::goldArr;
bool PlayGameScene::isDown = false;

int PlayGameScene::usegold = 0;
vector<sprite*> PlayGameScene::jbNum;
void PlayGameScene::init(DemoApp** app, colVec** colObj) {
    PlayGameScene::scene = new action(*app);
    PlayGameScene::app = *app;
    PlayGameScene::colObj = *colObj;
    PlayGameScene::tk1 = new ticker();

    PlayGameScene::scene->addTicker(PlayGameScene::tk1);
    PlayGameScene::tk1->addFun(PlayGameScene::tk1FunC);
    // 添加点击事件
    (*app)->use_onClick["PlayGameScene"] = PlayGameScene::onClick;
    (*app)->use_onMouseMove["PlayGameScene"] = PlayGameScene::mouseMove;
    (*app)->use_onKeyUp["PlayGameScene"] = PlayGameScene::onKeyUp;
    (*app)->use_onMouseDown["PlayGameScene"] = PlayGameScene::onMouseDown;
    (*app)->use_onClose["PlayGameScene"] = PlayGameScene::onClose;
    PlayGameScene::hThred = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)PlayGameScene::tk1Fun, NULL, CREATE_SUSPENDED, NULL);
    if (PlayGameScene::hThred == NULL) { MessageBox(NULL, L"asd", L"asd", MB_OK); }

    // 初始容器
    PlayGameScene::maxBox = new DisplayObject(0, 0);
    PlayGameScene::bottomBox = new DisplayObject(0, 0);
    PlayGameScene::fishBox = new DisplayObject(0, 0);
    scene->addChild((sprite*)PlayGameScene::maxBox);
    PlayGameScene::maxBox->addChild((sprite*)PlayGameScene::fishBox);
    PlayGameScene::maxBox->addChild((sprite*)PlayGameScene::bottomBox);
    PlayGameScene::bottom["yin"] = new sprite(*app, L"img/glod/coinAni1.png");
    PlayGameScene::bottom["jin"] = new sprite(*app, L"img/glod/coinAni2.png");
    PlayGameScene::bottom["pdSend"] = new sprite(*app, L"img/pwoerPd/pd.png");
    PlayGameScene::bottom["pdBoom"] = new sprite(*app, L"img/pwoerPd/cl.png");
    PlayGameScene::bottom["bar"] = new sprite(*app, L"img/Interface/energy-bar.png");
    PlayGameScene::saveObj->getFile(L"_save.sva");
    PlayGameScene::saveObj->readFile();
    if (PlayGameScene::saveObj->s == "") {
        PlayGameScene::usegold = 1000;
    } else {
        PlayGameScene::usegold = PlayGameScene::saveObj->num;
    }

    // 设置场景
    PlayGameScene::bgArr.push_back(new sprite(*app, L"img/Interface/1a.jpg"));
    PlayGameScene::bgArr.push_back(new sprite(*app, L"img/Interface/1b.jpg"));
    PlayGameScene::bgArr.push_back(new sprite(*app, L"img/Interface/1c.jpg"));
    PlayGameScene::bgArr.push_back(new sprite(*app, L"img/Interface/1d.jpg"));
    PlayGameScene::bgArr.push_back(new sprite(*app, L"img/Interface/1e.jpg"));
    PlayGameScene::bgArr.push_back(new sprite(*app, L"img/Interface/1f.jpg"));
    // 炮台
    PlayGameScene::ptArr.push_back(PlayGameScene::initAmt1(L"img/bullet/cannon1.png", 74, 74, 5));
    PlayGameScene::ptArr.push_back(PlayGameScene::initAmt1(L"img/bullet/cannon2.png", 74, 76, 5));
    PlayGameScene::ptArr.push_back(PlayGameScene::initAmt1(L"img/bullet/cannon3.png", 74, 76, 5));
    PlayGameScene::ptArr.push_back(PlayGameScene::initAmt1(L"img/bullet/cannon4.png", 74, 83, 5));
    PlayGameScene::ptArr.push_back(PlayGameScene::initAmt1(L"img/bullet/cannon5.png", 74, 85, 5));
    PlayGameScene::ptArr.push_back(PlayGameScene::initAmt1(L"img/bullet/cannon6.png", 74, 90, 5));
    PlayGameScene::ptArr.push_back(PlayGameScene::initAmt1(L"img/bullet/cannon7.png", 74, 94, 5));
    // 子弹
    PlayGameScene::bulletArr.push_back(new sprite(*app, L"img/bullet/bullet1.png"));
    PlayGameScene::bulletArr.push_back(new sprite(*app, L"img/bullet/bullet2.png"));
    PlayGameScene::bulletArr.push_back(new sprite(*app, L"img/bullet/bullet3.png"));
    PlayGameScene::bulletArr.push_back(new sprite(*app, L"img/bullet/bullet4.png"));
    PlayGameScene::bulletArr.push_back(new sprite(*app, L"img/bullet/bullet5.png"));
    PlayGameScene::bulletArr.push_back(new sprite(*app, L"img/bullet/bullet6.png"));
    PlayGameScene::bulletArr.push_back(new sprite(*app, L"img/bullet/bullet7.png"));
    // 网
    PlayGameScene::bulletWang.push_back(new sprite(*app, L"img/bullet/web1s.png"));
    PlayGameScene::bulletWang.push_back(new sprite(*app, L"img/bullet/web2s.png"));
    PlayGameScene::bulletWang.push_back(new sprite(*app, L"img/bullet/web3s.png"));
    PlayGameScene::bulletWang.push_back(new sprite(*app, L"img/bullet/web4s.png"));
    PlayGameScene::bulletWang.push_back(new sprite(*app, L"img/bullet/web5s.png"));
    PlayGameScene::bulletWang.push_back(new sprite(*app, L"img/bullet/web6s.png"));
    PlayGameScene::bulletWang.push_back(new sprite(*app, L"img/bullet/web7s.png"));

    // 鱼
    PlayGameScene::initFishConfig(L"img/fish/fish1.png", 0, 55, 37, 4, 4 * 37, 4, 2, 15);
    PlayGameScene::initFishConfig(L"img/fish/fish2.png", 0, 78, 64, 4, 4 * 64, 4, 8, 15);
    PlayGameScene::initFishConfig(L"img/fish/fish3.png", 0, 72, 56, 4, 4 * 56, 4, 30, 4, 55);
    PlayGameScene::initFishConfig(L"img/fish/fish4.png", 0, 77, 59, 4, 4 * 59, 4, 20, 5, 40);
    PlayGameScene::initFishConfig(L"img/fish/fish5.png", 0, 107, 122, 4, 4 * 122, 4, 15, 5, 30);
    PlayGameScene::initFishConfig(L"img/fish/fish6.png", 0, 105, 79, 8, 8 * 79, 4, 25, 5, 55);
    PlayGameScene::initFishConfig(L"img/fish/fish7.png", 0, 92, 151, 6, 6 * 151, 4, 45, 3, 75);
    PlayGameScene::initFishConfig(L"img/fish/fish8.png", 0, 174, 126, 8, 8 * 126, 4, 60, 3, 85);
    PlayGameScene::initFishConfig(L"img/fish/fish10.png", 0, 178, 187, 6, 6 * 187, 4, 80, 2, 94);
    PlayGameScene::initFishConfig(L"img/fish/fish9.png", 0, 166, 183, 8, 8 * 183, 4, 70, 2, 90);
    PlayGameScene::initFishConfig(L"img/fish/shark1.png", 0, 509, 270, 8, 8 * 270, 4, 90, 2, 95);
    PlayGameScene::initFishConfig(L"img/fish/shark2.png", 0, 516, 273, 8, 8 * 273, 4, 100, 1, 96);
    PlayGameScene::initFishConfig(L"img/fish/fish12.png", 0, 215, 211, 14, 14 * 211, 1, 110, 1, 97);
    PlayGameScene::initFishConfig(L"img/fish/fish11.png", 0, 274, 100, 32, 32 * 100, 1, 120, 1, 98);
}
// 地址 游泳开始帧的y 宽度 高度 游泳帧数量 死亡开始帧Y 死亡帧的数量 获得的金币
fishConfig* PlayGameScene::initFishConfig(LPWSTR url, int swimY, int w, int h, int swimNum, int deathY, int deathNum, int getGold, int maxFish, int deathInt) {
    fishConfig* fc1 = new fishConfig(PlayGameScene::app, PlayGameScene::scene, PlayGameScene::colObj, new sprite(PlayGameScene::app, url), PlayGameScene::removeFish);
    PlayGameScene::fishConfigArr.push_back(fc1);
    fc1->startYSwim = swimY;
    fc1->fishW = w;
    fc1->fishH = h;
    fc1->swimNum = swimNum;
    fc1->startYDeath = deathY;
    fc1->deathNum = deathNum;
    fc1->getGold = getGold;
    fc1->maxFish = maxFish;
    fc1->deathInt = deathInt;
    return fc1;
};
void PlayGameScene::visible() {

    PlayGameScene::fishBox->addChild(PlayGameScene::bgArr[PlayGameScene::nowScane]);
    PlayGameScene::bgArr[PlayGameScene::nowScane]->width = PlayGameScene::app->width;
    PlayGameScene::bgArr[PlayGameScene::nowScane]->height = PlayGameScene::app->height;

    if (PlayGameScene::jbNum.size() == 0) {

        // 背景

        PlayGameScene::bk = new sprite(PlayGameScene::app, L"img/Interface/back.png");
        PlayGameScene::bk->setId("back");
        PlayGameScene::maxBox->addChild(PlayGameScene::bk);
        PlayGameScene::bk->setX(15);
        PlayGameScene::bk->setY(20);
        PlayGameScene::bk->zoom = 0.5;
        // 炮台
        PlayGameScene::initPt();
        for (int i = 0; i < 10; i++) {
            sprite* l_spInit = new sprite(PlayGameScene::app, L"img/glod/coinText.png");
            PlayGameScene::jbNum.push_back(l_spInit);
            u_rect* rc = new u_rect();
            rc->x = 0;
            rc->y = 0;
            rc->width = 36;
            rc->height = 49;
            l_spInit->frame = rc;
            l_spInit->width = 36;
            l_spInit->height = 49;
            PlayGameScene::bottomBox->addChild(l_spInit);
            l_spInit->zoom = 0.5;
            l_spInit->setX((136 - i * 24));
            l_spInit->setY(45);
        }
    }

    // 启动计时器
    PlayGameScene::tk1->start();
    ResumeThread(PlayGameScene::hThred);
};
void PlayGameScene::initPt() {
    sprite* bg = new sprite(PlayGameScene::app, L"img/Interface/bottom-bar.png");
    PlayGameScene::addBtn = new sprite(PlayGameScene::app, L"img/Interface/cannon_plus.png");
    PlayGameScene::subtractBtn = new sprite(PlayGameScene::app, L"img/Interface/cannon_minus.png");

    bg->zoom = PlayGameScene::zoom;
    bg->setId("ptBg");
    PlayGameScene::bottomBox->addChild(bg);
    PlayGameScene::bottomBox->setX(PlayGameScene::app->width / 2 - bg->getWidth() / 2);
    PlayGameScene::bottomBox->setY(PlayGameScene::app->height - bg->getHeight());
    PlayGameScene::bottomBox->addChild(PlayGameScene::bottom["bar"]);
    PlayGameScene::bottom["bar"]->setX(543);
    PlayGameScene::bottom["bar"]->setY(44);
    PlayGameScene::bottomBox->addChild(PlayGameScene::addBtn);
    PlayGameScene::bottomBox->addChild(PlayGameScene::subtractBtn);
    PlayGameScene::initPt2();
}
void PlayGameScene::initPt2() {
    PlayGameScene::bottom["pt"] = PlayGameScene::ptArr[PlayGameScene::nowPt];
    PlayGameScene::bottom["bullet"] = PlayGameScene::bulletArr[PlayGameScene::nowPt];
    PlayGameScene::bottom["wang"] = PlayGameScene::bulletWang[PlayGameScene::nowPt];
    PlayGameScene::bottomBox->addChild(PlayGameScene::bottom["pt"]);
    PlayGameScene::bottom["pt"]->pivot.y = 1;
    PlayGameScene::bottom["pt"]->setX((PlayGameScene::bottomBox->getChildById("ptBg"))->getWidth() / 2 + PlayGameScene::bottom["pt"]->getWidth() / 100 * 10);

    PlayGameScene::addBtn->setX(PlayGameScene::bottom["pt"]->x + PlayGameScene::bottom["pt"]->getWidth() / 2 - PlayGameScene::addBtn->getWidth() / 2 + 100);
    PlayGameScene::subtractBtn->setX(PlayGameScene::bottom["pt"]->x + PlayGameScene::bottom["pt"]->getWidth() / 2 - PlayGameScene::addBtn->getWidth() / 2 - 100);
    PlayGameScene::addBtn->setY(PlayGameScene::bottomBox->getChildById("ptBg")->getHeight() / 3 + 10);
    PlayGameScene::subtractBtn->setY(PlayGameScene::bottomBox->getChildById("ptBg")->getHeight() / 3 + 10);
}
sprite* PlayGameScene::initAmt1(LPWSTR url, int w, int h, int frame, float zoom) {
    sprite* amtTest = new sprite(PlayGameScene::app, url);
    amtTest->width = w;
    amtTest->height = h;
    amtTest->zoom = zoom;
    amtTest->speedTime = 50;
    amtTest->spriteType = "animateSprite";
    for (int i = 0; i < frame; i++) {
        u_rect a = {0, h * i, w, h};
        amtTest->frameArr.push_back(a);
    }
    return amtTest;
};
void PlayGameScene::initAmt2(sprite* v, int startY, int w, int h, int frame, float zoom) {
    vector<u_rect> arr;
    v->width = w;
    v->height = h;
    v->spriteType = "animateSprite";
    v->speedTime = 50;
    v->zoom = zoom;
    for (int i = 0; i < frame; i++) {
        u_rect a = {0, h * i, w, h};
        arr.push_back(a);
    }
    v->frameArr = arr;
};
void PlayGameScene::drawGoldNum() {
    string a1 = g_concat(PlayGameScene::usegold, "");

    int len = a1.length();
    if (len > 6) {
        for (int d = 6; d < len; d++) { PlayGameScene::jbNum[d]->visible = true; }
    } else {
        for (int d = 6; d < 10; d++) { PlayGameScene::jbNum[d]->visible = false; }
    }
    for (int i = len - 1, q = 0; i >= 0; i--, q++) {
        int a2 = a1[q] - 48;
        PlayGameScene::jbNum[i]->frame->x = a2 * 36;
    }
    for (int e = len; e < 9; e++) { PlayGameScene::jbNum[e]->frame->x = 0; }
};
void PlayGameScene::tk1FunC(DemoApp** app, ticker* tk) {
    PlayGameScene::timerFish += 15;
    unsigned int i = 0;
    unsigned int len = PlayGameScene::fishConfigArr.size() - 5 + PlayGameScene::nowScane;
    for (i = 0; i < len; i++) { PlayGameScene::fishConfigArr[i]->frameFun(&PlayGameScene::fishArr, PlayGameScene::fishBox); }
    for (i = 0; i < PlayGameScene::fishArr.size(); i++) {
        if (PlayGameScene::timerFish >= 200) {

            if (!PlayGameScene::fishArr[i]->inScreen()) { PlayGameScene::fishArr[i]->changeType("death"); }
            if (i == len - 1) { PlayGameScene::timerFish = 0; }
        }
        PlayGameScene::fishArr[i]->frameFun();
    }
    for (i = 0; i < PlayGameScene::goldArr.size(); i++) { PlayGameScene::goldArr[i]->frameFun(); }
    for (i = 0; i < PlayGameScene::bulletArr2.size(); i++) {
        if (PlayGameScene::bulletArr2[i]->bulletType == "bt") { PlayGameScene::bulletArr2[i]->moveForword(); }
    }
    PlayGameScene::drawGoldNum();
}
DWORD WINAPI PlayGameScene::tk1Fun() {
    /*
    string a = "";
    for (unsigned int q = 0;q < PlayGameScene::fishConfigArr.size();q++) {
    a=g_concat(a, "鱼");
    a = g_concat(a, q);
    a = g_concat(a, ":    ");
    a = g_concat(a, PlayGameScene::fishConfigArr[q]->fishConfigArr.size());
    a = g_concat(a, "\n");
    }
    (*app)->content->drawText(a, 0, 0);*/
    while (true) {
        Sleep(15);
        unsigned int i = 0;
        for (i = 0; i < PlayGameScene::bulletArr2.size(); i++) {
            if (PlayGameScene::bulletArr2[i]->frameFun(&PlayGameScene::fishArr) == 1) { i--; };
        }
    }

    return 1;
}

// 每一个精灵每一帧的处理函数
void PlayGameScene::frameSpriteInfo(sprite** sp, int type) {}
void PlayGameScene::removeBullet(bullet* b) {

    PlayGameScene::fishBox->removeChild(b->view);
    utils::vecRemove(PlayGameScene::bulletArr2, b);
    delete b;
}
void PlayGameScene::removeFish(fish* b) {
    PlayGameScene::fishBox->removeChild(b->view);
    utils::vecRemove(PlayGameScene::fishArr, b);
    utils::vecRemove(b->createClass->fishConfigArr, b);
    delete b;
};
void PlayGameScene::removeGold(gold* b) {
    PlayGameScene::maxBox->removeChild(b->view);
    utils::vecRemove(PlayGameScene::goldArr, b);
    PlayGameScene::usegold += b->goldNum;

    delete b;
};
void PlayGameScene::onClick(int x, int y) {
    if (PlayGameScene::bk->inRect(PlayGameScene::app->mouse)) {
        PlayGameScene::app->nowScene = eStageSelectScene;
        PlayGameScene::fishBox->removeChild(PlayGameScene::bgArr[PlayGameScene::nowScane]);
    }
    if (PlayGameScene::isDown == true) {
        PlayGameScene::addBtn->img = PlayGameScene::app->content->getSoucre(L"img/Interface/cannon_plus.png");
        PlayGameScene::subtractBtn->img = PlayGameScene::app->content->getSoucre(L"img/Interface/cannon_minus.png");
        PlayGameScene::isDown = false;
    }
    if (PlayGameScene::addBtn->inRect(PlayGameScene::app->mouse)) {
        PlayGameScene::bottomBox->removeChild(PlayGameScene::bottom["pt"]);
        if (PlayGameScene::nowPt + 1 > 6) {
            PlayGameScene::nowPt = 0;
        } else {
            PlayGameScene::nowPt++;
        }

        PlayGameScene::initPt2();
        return;
    }
    if (PlayGameScene::subtractBtn->inRect(PlayGameScene::app->mouse)) {
        PlayGameScene::bottomBox->removeChild(PlayGameScene::bottom["pt"]);
        if (PlayGameScene::nowPt - 1 < 0) {
            PlayGameScene::nowPt = 6;
        } else {
            PlayGameScene::nowPt--;
        }
        PlayGameScene::initPt2();
        return;
    }
    PlayGameScene::usegold -= (PlayGameScene::nowPt + 1);
    bullet* b = new bullet(PlayGameScene::app, PlayGameScene::scene, PlayGameScene::colObj, PlayGameScene::bottom["bullet"], PlayGameScene::bottom["wang"]);
    PlayGameScene::fishBox->addChild(b->view);
    b->hurt = PlayGameScene::nowPt + 3;
    b->view->pivot.x = 0.5;
    b->view->pivot.y = 1;
    b->view->angle = PlayGameScene::bottom["pt"]->angle;
    b->setX(PlayGameScene::bottom["pt"]->g_x + (PlayGameScene::bottom["pt"]->getWidth() / 2 - b->view->getWidth() / 2));
    b->setY(PlayGameScene::bottom["pt"]->g_y + PlayGameScene::bottom["pt"]->getHeight() - b->view->getHeight());

    PlayGameScene::bulletArr2.push_back(b);
    b->removeScene = PlayGameScene::removeBullet;
}
void PlayGameScene::onMouseDown(int x, int y) {
    PlayGameScene::isDown = true;
    if (PlayGameScene::addBtn->inRect(PlayGameScene::app->mouse)) { PlayGameScene::addBtn->img = PlayGameScene::app->content->getSoucre(L"img/Interface/cannon_plus_down.png"); }
    if (PlayGameScene::subtractBtn->inRect(PlayGameScene::app->mouse)) { PlayGameScene::subtractBtn->img = PlayGameScene::app->content->getSoucre(L"img/Interface/cannon_minus_down.png"); }
};

void PlayGameScene::onKeyUp(int code) {
    if (code == 27) { // 抬起esc键的操作
        // PlayGameScene::app->cancelFullSreen();
    }
};
void PlayGameScene::mouseMove(int x, int y) {
    if (PlayGameScene::addBtn->inRect(PlayGameScene::app->mouse) || PlayGameScene::subtractBtn->inRect(PlayGameScene::app->mouse)) { return; }
    utils::usePoint p1 = {(FLOAT)x, (FLOAT)y};
    utils::usePoint p2 = {PlayGameScene::bottom["pt"]->g_x + PlayGameScene::bottom["pt"]->getWidth() / 2, PlayGameScene::bottom["pt"]->g_y + PlayGameScene::bottom["pt"]->getHeight()};
    float angleTest = PlayGameScene::colObj->pointAngleInfo(p2, p1);

    PlayGameScene::bottom["pt"]->angle = round(angleTest + 90);
}
void PlayGameScene::onClose() {
    PlayGameScene::saveObj->num = PlayGameScene::usegold;
    PlayGameScene::saveObj->writeFile();
};