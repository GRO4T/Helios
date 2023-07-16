#pragma once

#include <algorithm>

#include "opengl_includes.hpp"

namespace helios {

using Key = uint32_t;

class DisplayManager {
 public:
  ~DisplayManager() { close(); }
  static DisplayManager& getInstance();
  static void init();
  static void createDisplay(int width, int height);
  void handleEvents();
  void update();
  bool windowShouldClose();
  // GLFWwindow* getWindow() { return window; }

  bool isKeyPressed(Key key);
  void increaseMouseSensitivity(double delta);
  void decreaseMouseSensitivity(double delta);

  double getMouseDX() const { return mouse_dx; }
  double getMouseDY() const { return mouse_dy; }
  double getScrollX() const { return scroll_x; }
  double getScrollY() const { return scroll_y; }
  double getDeltaTime() const { return delta_time; }

 private:
  enum class KeyState;

  const double MAX_MOUSE_SENSITIVITY = 4.0f;

  DisplayManager() {
    first_mouse = true;
    mouse_sensitivity_y = 1.0f;
    mouse_sensitivity_x = 1.0f;
  }
  DisplayManager(const DisplayManager&) = delete;
  DisplayManager& operator=(const DisplayManager&) = delete;

  static void keyCallback(GLFWwindow* window, int key, int scancode, int action,
                          int mode);
  static void cursorPositionCallback(GLFWwindow* window, double pos_x,
                                     double pos_y);
  static void scrollCallback(GLFWwindow* window, double offset_x,
                             double offset_y);
  static void windowFocusCallback(GLFWwindow* window, int focused);
  static void cursorEnterCallback(GLFWwindow* window, int entered);
  static void mouseButtonCallback(GLFWwindow* window, int button, int action,
                                  int mods);

  void close();

  static GLFWwindow* window;
  static int width, height;

  static double last_update;
  static double delta_time;

  static bool first_mouse;
  static double mouse_sensitivity_y;
  static double mouse_sensitivity_x;
  static double last_mouse_x, last_mouse_y;
  static double mouse_dx, mouse_dy;
  static double scroll_x, scroll_y;
};

}  // namespace helios
