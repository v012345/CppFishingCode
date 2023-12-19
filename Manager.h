#pragma once
class DemoApp;

namespace ResourceManager {
    void loadImages(DemoApp* app);
} // namespace ResourceManager
namespace InputManager {
    void onClick(int x, int y);
    void onMouseDown(int x, int y);
    void onMouseUp(int x, int y);
    void onKeyDown(int code);
    void onKeyUp(int code);
    void onMouseMove(int x, int y);
    void onClose();
} // namespace InputManager