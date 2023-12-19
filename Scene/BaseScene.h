#pragma once
#include "../Node.h"
class BaseScene : public Node {
  protected:
    BaseScene(/* args */);
    ~BaseScene();

  public:
    static BaseScene* getInstance() {
        // 使用静态局部变量确保线程安全的实例创建
        static BaseScene instance;
        return &instance;
    }
    // 在实际应用中，可能需要禁用拷贝构造函数和赋值运算符重载
    BaseScene(const BaseScene&) = delete;
    BaseScene& operator=(const BaseScene&) = delete;
};
