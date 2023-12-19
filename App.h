#pragma once
#include <functional>
class Canvas;
class Sprite;
class action;
class App {
  public:
    static App* getInstance() {
        // 使用静态局部变量确保线程安全的实例创建
        static App instance;
        return &instance;
    }
    // 在实际应用中，可能需要禁用拷贝构造函数和赋值运算符重载
    App(const App&) = delete;
    App& operator=(const App&) = delete;

    HRESULT Initialize();
    void RunMessageLoop();
    void addFun(void (*fun)(App*));
    void addScene(action* scane);
    POINT* mouse = new POINT();
    void fullSreen();
    void cancelFullSreen();
    bool isFull = false;
    void getSource(vector<string>);
    void initScenes();
    void changeScene(SceneType);
    // DWORD  newT = 0;
    // DWORD oldT = 0;
  public:
    Canvas* mCanvas;
    LARGE_INTEGER oldtime;
    LARGE_INTEGER newtime;
    LARGE_INTEGER frequency;
    oMap<std::string, std::function<void(int, int)>> use_onClick;
    oMap<string, void (*)(int, int)> use_onMouseDown;
    oMap<string, void (*)(int, int)> use_onMouseUp;
    oMap<string, void (*)(int, int)> use_onMouseMove;
    oMap<string, void (*)()> use_onClose;

    oMap<string, void (*)(int)> use_onKeyDown;
    oMap<string, void (*)(int)> use_onKeyUp;
    int width;
    int height;
    unsigned int nowScene = eTitleScene;
    float msTime = 0;
    vector<action*> sceneArr;
    string status = "DeamApp";
    HWND getHwnd();
    LONG wLong;

  private:
    App();
    ~App();
    HRESULT OnRender();

    // Resize the render target.
    void OnResize(UINT width, UINT height);

    // The windows procedure.
    static LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

    vector<void (*)(App*)> fun;

  private:
    HWND m_hwnd;
};