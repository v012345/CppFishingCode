#pragma once
// #include "App.h"
class DisplayObject;
class App;
class ticker;
class Sprite;
class action {
  public:
    action(App* app);
    ~action();
    void render(App** app);
    void addTicker(ticker* tk);
    ticker* getTickerById(string id);
    void addChild(Sprite*);

  public:
    vector<ticker*> tk;

  public:
    string status = "action";
    DisplayObject* Container;
    App* app;
};
