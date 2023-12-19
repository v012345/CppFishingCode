#pragma once
// #include "DemoApp.h"
class DemoApp;
class Sprite;
class DisplayObject {
  public:
    DisplayObject();
    ~DisplayObject();
    virtual int addChild(Sprite* child);
    virtual int removeChild(Sprite* child);
    virtual void render(DemoApp* app);
    virtual void setX(float x);
    virtual void setY(float y);
    virtual void setX(int x);
    virtual void setY(int y);
    virtual void setId(string id);
    virtual float getWidth();
    virtual float getHeight();
    DisplayObject(float x, float y);
    virtual Sprite* DisplayObject::getChildById(string id);
    virtual bool DisplayObject::inRect(POINT* pt);
    virtual void initG_x();
    virtual void initG_y();

  public:
    string status = "DisplayObject";
    POINT scale; // 缩放因素
    utils::usePoint pivot = {0.5, 0.5}; // 变换坐标系原点0-1相对于sprite宽高
    int angle = 0; // 角度
    float width = 0;
    float height = 0;
    float x = 0; // 局部坐标系x
    float y = 0; // 局部坐标系y
    float g_x = 0; // 全局坐标系X
    float g_y = 0; // 全局坐标系Y
    float zoom = 1;
    bool visible = true;
    string id = "";
    // 子显示对象数组
    vector<Sprite*> children;
    Sprite* parent = NULL;
    oMap<string, int> use_int;
    oMap<string, string> use_str;
};
