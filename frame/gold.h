#pragma once
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
    //	void setFrameArr(vector<u_rect>  * arr);
  public:
    int addNum;
    Sprite* view;
    utils::usePoint endPoint;
    utils::usePoint centerPoint;
    utils::usePoint startPoint;
    int goldNum;
    void (*removeScren)(gold*);
};
