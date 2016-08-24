#include <iostream>
#include "window.h"
namespace sparky {
	namespace graphics {
		Window::Window(const char *title, int width, int height) {
			m_Title = title;
			m_Width = width;
			m_Height = height;
			if (!init()) {
				glfwTerminate();
			}

			for (int i = 0; i < MAX_KEYS; i++) {
				m_Keys[i] = false;
			}

			for (int i = 0; i < MAX_BUTTONS; i++) {
				m_MouseButtons[i] = false;
			}
		}

		Window::~Window() {
			glfwTerminate();
		}

		void Window::update() {
			GLenum error = glGetError();
			if (error != GL_NO_ERROR) {
				std::cout << "OpenGL Error: " << error << std::endl;
			}

			glfwPollEvents();
			glfwSwapBuffers(m_Window);
		}

		bool Window::isKeyPressed(unsigned int keycode) const {
			//TODO: LOG THIS!
			if (keycode > MAX_KEYS) {
				return false;
			}
			return m_Keys[keycode];
		}

		bool Window::isMouseButtonPressed(unsigned int button) const {
			//TODO: LOG THIS!
			if (button > MAX_BUTTONS) {
				return false;
			}
			return m_MouseButtons[button];
		}

		void Window::setMousePosition(double& x, double& y) {
			mx = x;
			my = y;
		}

		void Window::getMousePosition(double& x, double& y) const {
			x = mx;
			y = my;
		}

		void Window::clear() const {
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		}

		bool Window::init() {
			if (!glfwInit()) {
				std::cout << "Failed to initialize GLFW window!" << std::endl;
				return false;
			}
			m_Window = glfwCreateWindow(m_Width, m_Height, m_Title, NULL,NULL);
			if (!m_Window) {
				std::cout << "Failed creating GLFW window!" << std::endl;
				return false;
			}
			glfwMakeContextCurrent(m_Window);
			glfwSetWindowUserPointer(m_Window, this);
			glfwSetWindowSizeCallback(m_Window, window_resize);
			glfwSetKeyCallback(m_Window, key_callback);
			glfwSetMouseButtonCallback(m_Window, mouseButton_callback);
			glfwSetCursorPosCallback(m_Window, cursor_postion_callback);
			glfwSwapInterval(0.0);
			
			if (glewInit() != GLEW_OK) {
				std::cout << "Could not initialize GLEW!" << std::endl;
				return false;
			}

			std::cout << "OpenGL " << glGetString(GL_VERSION) << std::endl;
			return true;
		}

		bool Window::closed() const {
			return glfwWindowShouldClose(m_Window) == 1;
		}

		void window_resize(GLFWwindow *window, int width, int height) {
			glViewport(0, 0, width, height);
			Window* win = (Window*)glfwGetWindowUserPointer(window);
			win->m_Width = width;
			win->m_Height = height;
		}

		void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods) {
			Window* win = (Window*)glfwGetWindowUserPointer(window);
			win->m_Keys[key] = action != GLFW_RELEASE;
		}

		void mouseButton_callback(GLFWwindow *window, int button, int action, int mods) {
			Window* win = (Window*)glfwGetWindowUserPointer(window);
			win->m_MouseButtons[button] = action != GLFW_RELEASE;
		}

		void cursor_postion_callback(GLFWwindow *window, double xpos, double ypos) {
			Window* win = (Window*)glfwGetWindowUserPointer(window);
			win->mx = xpos;
			win->my = ypos;
		}
	}
}