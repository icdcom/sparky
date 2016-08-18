#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#define MAX_KEYS 1024
#define MAX_BUTTONS  32
#define INIT_WIN_WIDTH  1280
#define INIT_WIN_HEIGHT 720
namespace sparky {
	namespace graphics{
		class Window {
		private:
			const char *m_Title;
			int m_Width, m_Height;
			GLFWwindow *m_Window;
			bool m_closed;
			
		    bool m_Keys[MAX_KEYS];
		    bool m_MouseButtons[MAX_BUTTONS];
		    double mx, my;
			
		public:
			Window(const char *name, int width,int height);
			~Window();
			bool closed() const;
			void update();
			void clear() const;
			inline int getWidth() const {
				return m_Width;
			}
			inline int getHeight() const {
				return m_Height; 
			}
			bool isKeyPressed(unsigned int keycode) const;
			bool isMouseButtonPressed(unsigned int button) const;
			void setMousePosition(double& x, double& y);
			void getMousePosition(double& x, double& y) const;
		private:
			bool init();
			friend static void window_resize(GLFWwindow *window, int width, int height);
			friend static void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods);
			friend static void mouseButton_callback(GLFWwindow *window, int button, int action, int mods);
			friend static void cursor_postion_callback(GLFWwindow *window, double xpos, double ypos);
		};
	}
}