#pragma once
#include <functional>
#include <string>
#include <vector>
class App;
class ticker {
  public:
    ticker();
    ~ticker();
    void start();
    void stop();
    void setTimmer(float timmer);
    void addFun(std::function<void(App**, ticker*)>);
    void render(App** app);
    void setId(std::string str);

  public:
    float timmer = 0;
    double msTime = 0;
    int fps = 0;
    int fpsInt = 0;
    double oldTimmer = 0;
    double newTimmer = 0;
    double fpsTimmer = 0;
    std::string id = "";

  private:
    std::vector<std::function<void(App**, ticker*)>> tickerArr;
    bool started = false;
};
