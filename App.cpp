#include "Manager.h"
#include "Resource.h"
#include "Scene/PlayGameScene.h"
#include "Scene/StageSelectScene.h"
#include "Scene/TitleScene.h"
#include "stdafx.h"

App::App() : m_hwnd(NULL), mCanvas(NULL) {
    QueryPerformanceCounter(&newtime);
    QueryPerformanceCounter(&oldtime);
    QueryPerformanceFrequency(&this->frequency); // 10000000
}

App::~App() {}

void App::addScene(action* scane) { //
    this->sceneArr.push_back(scane);
};
// 全屏
void App::fullSreen() {
    // int cx = GetSysTemMetrice(SM_CXSCREEN);
    if (this->isFull) { return; }
    this->isFull = true;
    int width = GetSystemMetrics(SM_CXSCREEN);
    int height = GetSystemMetrics(SM_CYSCREEN);
    this->wLong = GetWindowLong(m_hwnd, GWL_STYLE);
    SetWindowLong(m_hwnd, GWL_STYLE, WS_POPUP);
    SetWindowPos(this->m_hwnd, HWND_TOPMOST, 0, 0, width, height, SWP_SHOWWINDOW);
}
// 取消全屏
void App::cancelFullSreen() {
    if (!this->isFull) { return; }
    this->isFull = false;
    SetWindowLong(m_hwnd, GWL_STYLE, this->wLong);
    SetWindowPos(this->m_hwnd, HWND_NOTOPMOST, 0, 0, width, height, SWP_SHOWWINDOW);
}
void App::RunMessageLoop() {
    MSG msg;
    BOOL isLoop = TRUE;
    while (isLoop) {
        if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
            if (msg.message == WM_QUIT) { isLoop = FALSE; }
        }

        QueryPerformanceCounter(&this->newtime);
        this->msTime = ((float)(newtime.QuadPart - oldtime.QuadPart) / frequency.QuadPart * 1000);
        if (this->msTime >= 16.67f) { // 60 fps
            this->mCanvas->beginDraw();
            this->mCanvas->clear();
            this->OnRender();
            QueryPerformanceCounter(&this->oldtime);
            this->mCanvas->closeDraw();
        } else {
            Sleep(1);
        }
    }

    // CloseHandle(this->thread1);
}
HRESULT App::Initialize() {
    HRESULT hr = S_OK;
    // Initialize device-indpendent resources, such as the Direct2D factory.
    if (SUCCEEDED(hr)) {
        // Register the window class.
        WNDCLASSEX wcex = {sizeof(WNDCLASSEX)};
        wcex.style = CS_HREDRAW | CS_VREDRAW;
        wcex.lpfnWndProc = App::WndProc;
        wcex.cbClsExtra = 0;
        wcex.cbWndExtra = sizeof(LONG_PTR);
        wcex.hInstance = HINST_THISCOMPONENT;
        wcex.hbrBackground = NULL;
        wcex.lpszMenuName = NULL;
        wcex.hCursor = LoadCursor(NULL, IDI_APPLICATION);
        wcex.lpszClassName = L"MXSJ";
        wcex.hIcon = LoadIcon(HINST_THISCOMPONENT, (LPCTSTR)IDI_D2DWIN32);
        RegisterClassEx(&wcex);

        // Create the window.
        m_hwnd = CreateWindow(L"MXSJ", L"捕鱼人", WS_OVERLAPPEDWINDOW ^ WS_MAXIMIZEBOX ^ WS_THICKFRAME, CW_USEDEFAULT, CW_USEDEFAULT, 1200, 750, NULL, NULL, HINST_THISCOMPONENT, this);
        hr = m_hwnd ? S_OK : E_FAIL;
        if (SUCCEEDED(hr)) {
            this->mCanvas = new Canvas(m_hwnd);
            this->mCanvas->strokeStyle(0xff00ff, 1);
            this->mCanvas->lineWidth = 2;
            this->mCanvas->fillStyle(0xffff00, 1);
            ResourceManager::loadImages(this);
            ShowWindow(m_hwnd, SW_SHOWNORMAL);
            UpdateWindow(m_hwnd);
            this->initScenes();
        }
    }
    return hr;
}

void App::addFun(void (*funs)(App*)) {
    vector<void (*)(App*)>::iterator it;
    it = find(this->fun.begin(), this->fun.end(), (funs));
    if (it == this->fun.end()) { //
        (this->fun).push_back((funs));
    }
};
HWND App::getHwnd() { return this->m_hwnd; };
LRESULT CALLBACK App::WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam) {
    LRESULT result = 0;
    if (message == WM_CREATE) {
        LPCREATESTRUCT pcs = (LPCREATESTRUCT)lParam;

        App* pApp = (App*)pcs->lpCreateParams;
        RECT rc;
        GetClientRect(hwnd, &rc);
        pApp->width = rc.right - rc.left;
        pApp->height = rc.bottom - rc.top;

        ::SetWindowLongPtrW(hwnd, GWLP_USERDATA, PtrToUlong(pApp));

        result = 1;
    } else {
        App* pApp = reinterpret_cast<App*>(static_cast<LONG_PTR>(::GetWindowLongPtrW(hwnd, GWLP_USERDATA)));
        //
        if (pApp == NULL) { return DefWindowProc(hwnd, message, wParam, lParam); }

        bool wasHandled = false;

        if (pApp) {

            switch (message) {
                case WM_SIZE: {
                    UINT width = LOWORD(lParam);
                    UINT height = HIWORD(lParam);
                    pApp->OnResize(width, height);
                }
                    result = 0;
                    wasHandled = true;
                    break;
                case WM_KEYUP:
                    InputManager::onKeyUp(wParam);
                    result = 0;
                    wasHandled = true;
                    break;
                case WM_KEYDOWN:
                    InputManager::onKeyDown(wParam);
                    result = 0;
                    wasHandled = true;
                    break;
                case WM_MOUSEMOVE:
                    pApp->mouse->x = LOWORD(lParam);
                    pApp->mouse->y = HIWORD(lParam);
                    InputManager::onMouseMove(pApp->mouse->x, pApp->mouse->y);
                    result = 0;
                    wasHandled = true;
                    break;
                case WM_LBUTTONUP:
                    pApp->mouse->x = LOWORD(lParam);
                    pApp->mouse->y = HIWORD(lParam);
                    InputManager::onMouseUp(pApp->mouse->x, pApp->mouse->y);
                    InputManager::onClick(pApp->mouse->x, pApp->mouse->y);
                    result = 1;
                    wasHandled = true;
                    break;
                case WM_LBUTTONDOWN:
                    pApp->mouse->x = LOWORD(lParam);
                    pApp->mouse->y = HIWORD(lParam);
                    InputManager::onMouseDown(pApp->mouse->x, pApp->mouse->y);
                    result = 1;
                    wasHandled = true;
                    break;
                case WM_DISPLAYCHANGE: {
                    InvalidateRect(hwnd, NULL, FALSE);
                }
                    result = 0;
                    wasHandled = true;
                    break;
                case WM_DESTROY: {

                    InputManager::onClose();
                    PostQuitMessage(0);
                }
                    result = 1;
                    wasHandled = true;
                    break;
            }
        }

        if (!wasHandled) { result = DefWindowProc(hwnd, message, wParam, lParam); }
    }

    return result;
}
HRESULT App::OnRender() {
    LRESULT hr = S_OK;
    for (unsigned int i = 0; i < (this->fun).size(); i++) { //
        (this->fun)[i](this);
    }
    return hr;
}
void App::OnResize(UINT width, UINT height) {}
void App::getSource(vector<string> arr) {
    for (unsigned int i = 0; i < arr.size(); i++) { //
        this->mCanvas->getSoucre(g_chartowchar2(arr[i].c_str()));
    }
};
// 窗口显示之后调用
void App::initScenes() {
    colVec* colObj = new colVec();
    TitleScene* titleScene = TitleScene::getInstance();
    titleScene->init(this, colObj);
    this->addScene(titleScene->scene);

    PlayGameScene* playGameScene = PlayGameScene::getInstance();
    playGameScene->init(this, colObj);
    this->addScene(playGameScene->scene);

    StageSelectScene* stageSelectScene = StageSelectScene::getInstance();
    stageSelectScene->init(this, colObj);
    this->addScene(stageSelectScene->scene);
}
void App::changeScene(SceneType s) { this->nowScene = s; }