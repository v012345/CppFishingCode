#include "../stdafx.h"

#include "../frame/bullet.h"
#include "../frame/files.h"
#include "../frame/fish.h"
#include "../frame/fishConfig.h"
#include "../frame/gold.h"
#include "PlayGameScene.h"
PlayGameScene::PlayGameScene() {
    this->app = App::getInstance();
    this->colObj = CollisionManger::getInstance();
    this->scene = NULL;
    this->maxBox = NULL;
    this->bottomBox = NULL;
    this->fishBox = NULL;
    this->addBtn = NULL;
    this->subtractBtn = NULL;
    this->zoom = 1;
    this->mStageId = 0;
    this->nowPt = 0;
    this->tk1 = NULL;
    this->bk = NULL;

    this->timerFish = 0;
    this->saveObj = new files();
    this->allPower = 100;
    this->nowPower = 0;
    this->isDown = false;
    this->mDeposit = 0;

    PlayGameScene::scene = new action(app);
    PlayGameScene::tk1 = new ticker();

    PlayGameScene::scene->addTicker(PlayGameScene::tk1);
    PlayGameScene::tk1->addFun([this](App** app, ticker* tk) { this->tk1FunC(app, tk); });
    // 添加点击事件
    app->use_onClick["PlayGameScene"] = [this](int x, int y) { this->onClick(x, y); };
    app->use_onMouseMove["PlayGameScene"] = [this](int x, int y) { this->mouseMove(x, y); };
    app->use_onKeyUp["PlayGameScene"] = [this](int code) { this->onKeyUp(code); };
    app->use_onMouseDown["PlayGameScene"] = [this](int x, int y) { this->onMouseDown(x, y); };
    app->use_onClose["PlayGameScene"] = [this]() { this->onClose(); };

    // 初始容器
    PlayGameScene::maxBox = new DisplayObject(0, 0);
    PlayGameScene::bottomBox = new DisplayObject(0, 0);
    PlayGameScene::fishBox = new DisplayObject(0, 0);
    scene->addChild((Sprite*)PlayGameScene::maxBox);
    PlayGameScene::maxBox->addChild((Sprite*)PlayGameScene::fishBox);
    PlayGameScene::maxBox->addChild((Sprite*)PlayGameScene::bottomBox);
    PlayGameScene::bottom["yin"] = new Sprite(app, L"img/glod/coinAni1.png");
    PlayGameScene::bottom["jin"] = new Sprite(app, L"img/glod/coinAni2.png");
    PlayGameScene::bottom["pdSend"] = new Sprite(app, L"img/pwoerPd/pd.png");
    PlayGameScene::bottom["pdBoom"] = new Sprite(app, L"img/pwoerPd/cl.png");
    PlayGameScene::bottom["bar"] = new Sprite(app, L"img/Interface/energy-bar.png");
    PlayGameScene::saveObj->getFile(L"_save.sva");
    PlayGameScene::saveObj->readFile();
    if (PlayGameScene::saveObj->s == "") {
        PlayGameScene::mDeposit = 1000;
    } else {
        PlayGameScene::mDeposit = PlayGameScene::saveObj->num;
    }

    // 设置场景
    PlayGameScene::bgArr.push_back(new Sprite(app, L"img/Interface/1a.jpg"));
    PlayGameScene::bgArr.push_back(new Sprite(app, L"img/Interface/1b.jpg"));
    PlayGameScene::bgArr.push_back(new Sprite(app, L"img/Interface/1c.jpg"));
    PlayGameScene::bgArr.push_back(new Sprite(app, L"img/Interface/1d.jpg"));
    PlayGameScene::bgArr.push_back(new Sprite(app, L"img/Interface/1e.jpg"));
    PlayGameScene::bgArr.push_back(new Sprite(app, L"img/Interface/1f.jpg"));
    // 炮台
    PlayGameScene::ptArr.push_back(PlayGameScene::initAmt1(L"img/bullet/cannon1.png", 74, 74, 5));
    PlayGameScene::ptArr.push_back(PlayGameScene::initAmt1(L"img/bullet/cannon2.png", 74, 76, 5));
    PlayGameScene::ptArr.push_back(PlayGameScene::initAmt1(L"img/bullet/cannon3.png", 74, 76, 5));
    PlayGameScene::ptArr.push_back(PlayGameScene::initAmt1(L"img/bullet/cannon4.png", 74, 83, 5));
    PlayGameScene::ptArr.push_back(PlayGameScene::initAmt1(L"img/bullet/cannon5.png", 74, 85, 5));
    PlayGameScene::ptArr.push_back(PlayGameScene::initAmt1(L"img/bullet/cannon6.png", 74, 90, 5));
    PlayGameScene::ptArr.push_back(PlayGameScene::initAmt1(L"img/bullet/cannon7.png", 74, 94, 5));
    // 子弹
    PlayGameScene::bulletArr.push_back(new Sprite(app, L"img/bullet/bullet1.png"));
    PlayGameScene::bulletArr.push_back(new Sprite(app, L"img/bullet/bullet2.png"));
    PlayGameScene::bulletArr.push_back(new Sprite(app, L"img/bullet/bullet3.png"));
    PlayGameScene::bulletArr.push_back(new Sprite(app, L"img/bullet/bullet4.png"));
    PlayGameScene::bulletArr.push_back(new Sprite(app, L"img/bullet/bullet5.png"));
    PlayGameScene::bulletArr.push_back(new Sprite(app, L"img/bullet/bullet6.png"));
    PlayGameScene::bulletArr.push_back(new Sprite(app, L"img/bullet/bullet7.png"));
    // 网
    PlayGameScene::bulletWang.push_back(new Sprite(app, L"img/bullet/web1s.png"));
    PlayGameScene::bulletWang.push_back(new Sprite(app, L"img/bullet/web2s.png"));
    PlayGameScene::bulletWang.push_back(new Sprite(app, L"img/bullet/web3s.png"));
    PlayGameScene::bulletWang.push_back(new Sprite(app, L"img/bullet/web4s.png"));
    PlayGameScene::bulletWang.push_back(new Sprite(app, L"img/bullet/web5s.png"));
    PlayGameScene::bulletWang.push_back(new Sprite(app, L"img/bullet/web6s.png"));
    PlayGameScene::bulletWang.push_back(new Sprite(app, L"img/bullet/web7s.png"));

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

    // PlayGameScene::hThred = CreateThread(NULL, 0, ThreadProcStatic, this, CREATE_SUSPENDED, NULL);
    // if (PlayGameScene::hThred == NULL) { MessageBox(NULL, L"asd", L"asd", MB_OK); }
}
PlayGameScene::~PlayGameScene() {}

static DWORD WINAPI ThreadProcStatic(LPVOID lpParam) {
    PlayGameScene* pYourClass = reinterpret_cast<PlayGameScene*>(lpParam);
    pYourClass->tk1Fun();
    return 0;
}

// 地址 游泳开始帧的y 宽度 高度 游泳帧数量 死亡开始帧Y 死亡帧的数量 获得的金币
fishConfig* PlayGameScene::initFishConfig(LPWSTR url, int swimY, int w, int h, int swimNum, int deathY, int deathNum, int getGold, int maxFish, int deathInt) {
    fishConfig* fc1 = new fishConfig(PlayGameScene::app, PlayGameScene::scene, PlayGameScene::colObj, new Sprite(PlayGameScene::app, url), [this](fish* b) { this->removeFish(b); });
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

    PlayGameScene::fishBox->addChild(PlayGameScene::bgArr[PlayGameScene::mStageId]);
    PlayGameScene::bgArr[PlayGameScene::mStageId]->width = PlayGameScene::app->width;
    PlayGameScene::bgArr[PlayGameScene::mStageId]->height = PlayGameScene::app->height;

    if (PlayGameScene::CoinNum.size() == 0) {

        // 背景

        PlayGameScene::bk = new Sprite(PlayGameScene::app, L"img/Interface/back.png");
        PlayGameScene::bk->setId("back");
        PlayGameScene::maxBox->addChild(PlayGameScene::bk);
        PlayGameScene::bk->setX(15);
        PlayGameScene::bk->setY(20);
        PlayGameScene::bk->zoom = 0.5;
        // 炮台
        PlayGameScene::initPt();
        for (int i = 0; i < 10; i++) {
            Sprite* l_spInit = new Sprite(PlayGameScene::app, L"img/glod/coinText.png");
            PlayGameScene::CoinNum.push_back(l_spInit);
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
    // ResumeThread(PlayGameScene::hThred);
};
void PlayGameScene::initPt() {
    Sprite* bg = new Sprite(PlayGameScene::app, L"img/Interface/bottom-bar.png");
    PlayGameScene::addBtn = new Sprite(PlayGameScene::app, L"img/Interface/cannon_plus.png");
    PlayGameScene::subtractBtn = new Sprite(PlayGameScene::app, L"img/Interface/cannon_minus.png");

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
Sprite* PlayGameScene::initAmt1(LPWSTR url, int w, int h, int frame, float zoom) {
    Sprite* amtTest = new Sprite(PlayGameScene::app, url);
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
void PlayGameScene::initAmt2(Sprite* v, int startY, int w, int h, int frame, float zoom) {
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
    string a1 = std::to_string(PlayGameScene::mDeposit);

    int len = a1.length();
    if (len > 6) {
        for (int d = 6; d < len; d++) { PlayGameScene::CoinNum[d]->visible = true; }
    } else {
        for (int d = 6; d < 10; d++) { PlayGameScene::CoinNum[d]->visible = false; }
    }
    for (int i = len - 1, q = 0; i >= 0; i--, q++) {
        int a2 = a1[q] - 48;
        PlayGameScene::CoinNum[i]->frame->x = a2 * 36;
    }
    for (int e = len; e < 9; e++) { PlayGameScene::CoinNum[e]->frame->x = 0; }
};
void PlayGameScene::tk1FunC(App** app, ticker* tk) {
    PlayGameScene::timerFish += 15;
    unsigned int i = 0;
    unsigned int len = PlayGameScene::fishConfigArr.size() - 5 + PlayGameScene::mStageId;
    for (i = 0; i < len; i++) { //
        PlayGameScene::fishConfigArr[i]->frameFun(&this->fishArr, PlayGameScene::fishBox);
    }
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
// DWORD WINAPI PlayGameScene::tk1Fun() {
//     while (true) {
//         Sleep(15);
//         unsigned int i = 0;
//         for (i = 0; i < PlayGameScene::bulletArr2.size(); i++) {
//             if (PlayGameScene::bulletArr2[i]->frameFun(&this->fishArr) == 1) { i--; };
//         }
//     }
//     return 1;
// }

// 每一个精灵每一帧的处理函数
void PlayGameScene::frameSpriteInfo(Sprite** sp, int type) {}
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
    PlayGameScene::mDeposit += b->goldNum;

    delete b;
};
void PlayGameScene::onClick(int x, int y) {
    if (PlayGameScene::bk->inRect(PlayGameScene::app->mouse)) {
        PlayGameScene::app->nowScene = eStageSelectScene;
        PlayGameScene::fishBox->removeChild(PlayGameScene::bgArr[PlayGameScene::mStageId]);
    }
    if (PlayGameScene::isDown == true) {
        PlayGameScene::addBtn->img = PlayGameScene::app->mCanvas->getSoucre(L"img/Interface/cannon_plus.png");
        PlayGameScene::subtractBtn->img = PlayGameScene::app->mCanvas->getSoucre(L"img/Interface/cannon_minus.png");
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
    PlayGameScene::mDeposit -= (PlayGameScene::nowPt + 1);
    bullet* b = new bullet(PlayGameScene::app, PlayGameScene::scene, PlayGameScene::colObj, PlayGameScene::bottom["bullet"], PlayGameScene::bottom["wang"]);
    PlayGameScene::fishBox->addChild(b->view);
    b->hurt = PlayGameScene::nowPt + 3;
    b->view->pivot.x = 0.5;
    b->view->pivot.y = 1;
    b->view->angle = PlayGameScene::bottom["pt"]->angle;
    b->setX(PlayGameScene::bottom["pt"]->g_x + (PlayGameScene::bottom["pt"]->getWidth() / 2 - b->view->getWidth() / 2));
    b->setY(PlayGameScene::bottom["pt"]->g_y + PlayGameScene::bottom["pt"]->getHeight() - b->view->getHeight());

    PlayGameScene::bulletArr2.push_back(b);
    b->removeScene = [this](bullet* b) { PlayGameScene::removeBullet(b); };
}
void PlayGameScene::onMouseDown(int x, int y) {
    PlayGameScene::isDown = true;
    if (PlayGameScene::addBtn->inRect(PlayGameScene::app->mouse)) { PlayGameScene::addBtn->img = PlayGameScene::app->mCanvas->getSoucre(L"img/Interface/cannon_plus_down.png"); }
    if (PlayGameScene::subtractBtn->inRect(PlayGameScene::app->mouse)) { PlayGameScene::subtractBtn->img = PlayGameScene::app->mCanvas->getSoucre(L"img/Interface/cannon_minus_down.png"); }
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
    PlayGameScene::saveObj->num = PlayGameScene::mDeposit;
    PlayGameScene::saveObj->writeFile();
};