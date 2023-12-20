#pragma once
class fishConfig;
class fish {
  public:
    fish();
    fish(App* app, action* scene, CollisionManger* colObj, Sprite* img, float speed = 5);
    ~fish();
    void setX(float x);
    void setY(float y);
    void frameFun();
    void moveForword(); // 向前移动
    std::function<void(fish* b)> removeScene;
    void changeType(string type);
    bool inScreen();

  public:
    int moveTime = 1;
    int moveAllTime = 1;
    fishConfig* createClass;
    float speed = 0;
    int deathFrameTime = 30; // 死亡存活帧时间
    int deathInt = 10; // 死亡概率相关
    int getGold = 1; // 死亡金币相关
    float minAngle = 0; // 最小角度
    float maxAngle = 0; // 最大角度
    bool angleAdd = true;
    Sprite* view; // 视图呈现精灵
    vector<u_rect> swim; // 游泳动画信息
    vector<u_rect> death; // 死亡动画信息
    App* app;
    action* scene;
    CollisionManger* colObj;
    string type = "swim";
    Sprite* scInfo;
};
