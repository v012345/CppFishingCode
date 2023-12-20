#pragma once
#include "../stdafx.h"
#include "BaseScene.h"
class action;
class App;
class CollisionManger;
class bullet;
class fish;
class gold;
class files;
class fishConfig;
class PlayGameScene : public BaseScene {
  public:
    static PlayGameScene* getInstance() {
        static PlayGameScene instance;
        return &instance;
    }
    action* scene; // 当前场景的场景对象
    App* app; // 游戏app
    CollisionManger* colObj; // 碰撞对象 提供obb  aabb 相关碰撞算法 <obb 采用向量>

    float zoom; // 场景所有精灵用的zoom
    int mStageId; // 当前关数
    int nowPt; // 当前炮台的显示
    oMap<string, Sprite*> bottom; // 底部精灵组合
    ticker* tk1; // 场景计时器
    float timerFish; // 周期判断鱼是否游出屏幕
    int mDeposit; // 剩余金币数
    files* saveObj;
    Sprite* bk;

    vector<Sprite*> CoinNum;
    vector<Sprite*> bgArr; // 所有关数的背景
    vector<Sprite*> ptArr; // 炮台Arr
    vector<Sprite*> bulletArr; // 子弹Arr Img
    vector<bullet*> bulletArr2; // 子弹Arr
    vector<Sprite*> bulletWang; // 子弹Arr Img
    vector<fish*> fishArr; // 鱼数组
    vector<fishConfig*> fishConfigArr; // 创建鱼的对象数组
    vector<gold*> goldArr;
    bool isDown; // 在触发鼠标抬起事件之前是否在切换炮台按钮里面按下了鼠标 如果是就为true否则为false
    DisplayObject* maxBox; // 最大容器
    DisplayObject* bottomBox; // 底部容器
    DisplayObject* fishBox; // 鱼群容器
    Sprite* addBtn; // 切换炮台 加
    Sprite* subtractBtn; // 切换炮台 减
    void drawGoldNum();
    void visible(); // 场景显示调用
    void onClick(int x, int y); // 场景点击事件
    void onClose(); // 场景点击事件
    void onMouseDown(int x, int y); // 场景鼠标按下事件
    //  void onMouseUp(int x, int y);//场景鼠标抬起事件
    void onKeyUp(int x); // 场景点击事件
    void initPt(); // 初始炮台
    void initPt2(); // 初始化炮台位置
    Sprite* initAmt1(LPWSTR url, int w, int h, int frame, float zoom = 1); // 初始化单帧动画
    void initAmt2(Sprite* v, int startY, int w, int h, int frame, float zoom);
    DWORD WINAPI tk1Fun(); // 计时器每一帧调用函数
    void tk1FunC(App** app, ticker* tk);
    void mouseMove(int x, int y); // 鼠标移动触发函数
    void frameSpriteInfo(Sprite** sp, int type);
    void removeBullet(bullet* bt); // 排泄子弹
    void removeFish(fish* b); // 排泄鱼
    void removeGold(gold* b); // 排泄金币
    float allPower;
    float nowPower;
    HANDLE hThred;
    fishConfig* initFishConfig(LPWSTR url, int swimY, int w, int h, int swimNum, int deathY, int deathNum, int getGold, int maxFish = 30, int deathInt = 10); // 初始化创建鱼对象
  private:
    PlayGameScene();
    ~PlayGameScene();
};