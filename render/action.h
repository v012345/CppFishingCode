#pragma once
// #include "DemoApp.h"
class DisplayObject;
class DemoApp;
class ticker;
class Sprite;
class action {
  public:
    action(DemoApp* app);
    ~action();
    void render(DemoApp** app);
    void addTicker(ticker* tk);
    ticker* getTickerById(string id);
    void addChild(Sprite*);

  public:
    vector<ticker*> tk;

  public:
    string status = "action";
    DisplayObject* Container;
    DemoApp* app;
};
