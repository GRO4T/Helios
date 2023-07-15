#include "DisplayManager.hpp"

#include <iostream>

#include "opengl_all.hpp"

namespace helios {

GLFWwindow* DisplayManager::window;
int DisplayManager::width, DisplayManager::height;
double DisplayManager::last_update;
double DisplayManager::delta_time;
bool DisplayManager::first_mouse;
double DisplayManager::mouse_sensitivity_y;
double DisplayManager::mouse_sensitivity_x;
double DisplayManager::last_mouse_x, DisplayManager::last_mouse_y;
double DisplayManager::mouse_dx, DisplayManager::mouse_dy;
double DisplayManager::scroll_x, DisplayManager::scroll_y;

DisplayManager& DisplayManager::getInstance() {
    static DisplayManager instance;
    return instance;
}

void DisplayManager::init() {
    if (glfwInit() != GL_TRUE) {
        std::cout << "GLFW" << std::endl;
        throw std::runtime_error("GLFW initialization failed");
    }
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
}
void DisplayManager::createDisplay(int width, int height) {
    DisplayManager::width = width;
    DisplayManager::height = height;
    window = glfwCreateWindow(width, height, "Game Engine", nullptr, nullptr);
    if (window == nullptr) throw std::runtime_error("GLFW window not created");
    glfwMakeContextCurrent(window);

    glfwSetCursorPosCallback(window, cursorPositionCallback);
    glfwSetKeyCallback(window, keyCallback);
    glfwSetScrollCallback(window, scrollCallback);
    glfwSetWindowFocusCallback(window, windowFocusCallback);
    glfwSetCursorEnterCallback(window, cursorEnterCallback);
    glfwSetMouseButtonCallback(window, mouseButtonCallback);

    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK) {
        throw std::runtime_error("GLEW Initialization failed");
    }
    glViewport(0, 0, width, height);
}

void DisplayManager::handleEvents() {
    if (isKeyPressed(GLFW_KEY_ESCAPE)) {
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
    }
    glfwPollEvents();
}

void DisplayManager::update() {
    double now = glfwGetTime() * 1000.0f;
    delta_time = now - last_update;
    last_update = now;
    // std::cout << delta_time << "s" << std::endl;
    // std::cout << "FPS: " << 1000.0f / delta_time << std::endl;
    // std::cout << "mouse sensitivity: " << mouse_sensitivity_x << std::endl;
    glfwSwapBuffers(window);
    mouse_dx = mouse_dy = 0;
    scroll_x = scroll_y = 0;
}

bool DisplayManager::windowShouldClose() {
    return glfwWindowShouldClose(window);
}

void DisplayManager::close() {
    if (!windowShouldClose()) {
        glfwSetWindowShouldClose(window, GL_TRUE);
    }
    glfwTerminate();
}

void DisplayManager::cursorPositionCallback(GLFWwindow* window, double pos_x,
                                            double pos_y) {
    if (first_mouse) {
        last_mouse_x = pos_x;
        last_mouse_y = pos_y;
        first_mouse = false;
    }
    mouse_dx = (pos_x - last_mouse_x) * mouse_sensitivity_x;
    mouse_dy = (last_mouse_y - pos_y) * mouse_sensitivity_y;
    last_mouse_x = pos_x;
    last_mouse_y = pos_y;
}

bool DisplayManager::isKeyPressed(Key key) {
    return glfwGetKey(window, key) == GLFW_PRESS;
}

void DisplayManager::keyCallback(GLFWwindow* window, int key, int scancode,
                                 int action, int mode) {
    if (key == GLFW_KEY_1) {
        getInstance().decreaseMouseSensitivity(0.01);
    } else if (key == GLFW_KEY_2) {
        getInstance().increaseMouseSensitivity(0.01);
    }
}
void DisplayManager::scrollCallback(GLFWwindow* window, double offset_x,
                                    double offset_y) {
    scroll_x = offset_x;
    scroll_y = offset_y;
}

void DisplayManager::windowFocusCallback(GLFWwindow* window, int focused) {
    // std::cout << "window focus callback\n";
}

void DisplayManager::cursorEnterCallback(GLFWwindow* window, int entered) {
    // std::cout << "cursor enter callback\n";
}

void DisplayManager::mouseButtonCallback(GLFWwindow* window, int button,
                                         int action, int mods) {
    if (button == GLFW_MOUSE_BUTTON_LEFT) {
        int window_x, window_y;
        glfwGetWindowPos(window, &window_x, &window_y);
        if (last_mouse_x >= window_x && last_mouse_x <= window_x + width &&
            last_mouse_y >= window_y && last_mouse_y <= window_y + height) {
            std::cout << "window clicked\n";
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
        }
    }
}

void DisplayManager::increaseMouseSensitivity(double delta) {
    mouse_sensitivity_x =
        std::clamp(mouse_sensitivity_x + delta, 0.0, MAX_MOUSE_SENSITIVITY);
    mouse_sensitivity_y =
        std::clamp(mouse_sensitivity_y + delta, 0.0, MAX_MOUSE_SENSITIVITY);
}
void DisplayManager::decreaseMouseSensitivity(double delta) {
    mouse_sensitivity_x =
        std::clamp(mouse_sensitivity_x - delta, 0.0, MAX_MOUSE_SENSITIVITY);
    mouse_sensitivity_y =
        std::clamp(mouse_sensitivity_y - delta, 0.0, MAX_MOUSE_SENSITIVITY);
}

}  // namespace helios
