#pragma once
#include <functional>
class App;
class action;
class colVec;
class gold;
class fish;
class bullet {
  public:
    bullet();
    bullet(App* app, action* scene, colVec* colObj, Sprite* bt, Sprite* wang, int hurt = 1, float speed = 8);
    ~bullet();
    void changeType(string type); // 改变显示状态
    void moveForword(); // 向前移动
    int frameFun(vector<fish*>* fishArr); // 每一帧调用
    void isHit(vector<fish*>* fishArr);
    void bullet::createGold(fish* fs);
    void bullet::setX(float x);
    void bullet::setY(float y);
    bool bullet::inScreen();
    utils::useSpSt st1; // 子弹结构一
    utils::useSpSt st2; // 鱼结构二
  public:
    string bulletType = "bt"; // 子弹当前显示状态
    Sprite* view; // 视图精灵
    Sprite* bt; // 炮台精灵
    Sprite* wang; // 网精灵
    int hurt = 0;
    int w_time = 20;
    float speed = 0;
    float angle = 0;
    std::function<void(bullet* b)> removeScene;
    Sprite* scInfo;

  private:
    App* app; // 游戏app
    action* scene; // 游戏场景
    colVec* colObj; // 游戏碰撞对象
};
