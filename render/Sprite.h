#pragma once
#include "DisplayObject.h"
class DemoApp;
class Sprite : public DisplayObject {
  public:
    Sprite(int x, int y);
    Sprite(DemoApp* app, WCHAR* url, string spriteType = "default", int width = -1, int height = -1);
    Sprite(DemoApp* app, ID2D1Bitmap* url, string spriteType = "default", int width = -1, int height = -1);
    ~Sprite();
    virtual void render(DemoApp*);
    u_rect* frame = NULL;
    void setNowFrame(unsigned int);
    unsigned int getNowFrame();

  public:
    ID2D1Bitmap* img;
    string status = "Sprite";
    string spriteType = "default"; // animateSprite fillSprite textSprite

    // animateSprite
    vector<u_rect> frameArr; // 帧数组
    float speedTime = 0; // 毫秒
    float speedNowTime = 0; // 毫秒
    int loop = -1;
    void (*amtEnd)(Sprite*);
    // fillSprite

    // textSprite
    string txt = "";
    UINT rgb = 0x000000;
    float alpha = 1;
    float getTxtWidth(DemoApp* app);
    float getTxtHeight(DemoApp* app);

  private:
    unsigned int mNowFrame = 0; // 当前帧
};
