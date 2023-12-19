#pragma once
#include <functional>
class gold {
  public:
    gold();
    ~gold();
    gold(Sprite* view);
    void frameFun();
    void getCenterPoint();
    void gold::setX(float x);
    void gold::setY(float y);
    float t;

  public:
    int addNum;
    Sprite* view;
    utils::usePoint endPoint;
    utils::usePoint centerPoint;
    utils::usePoint startPoint;
    int goldNum;
    std::function<void(gold*)> removeScren;
};
