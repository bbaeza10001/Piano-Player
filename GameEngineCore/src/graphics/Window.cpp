#include "Window.h"

namespace spacey{ namespace graphics{
	
	void window_resize(GLFWwindow *window, int width, int height);

	Window::Window(){

	}

	Window::Window(const char *name, int width, int height){
		m_Name = name;
		m_Width = width;
		m_Height = height;
		if (!init()){
			glfwTerminate();
		}

		for (int i = 0; i < MAX_KEYS; i++){
			m_Keys[i] = false;
		}
		for (int i = 0; i < MAX_BUTTONS; i++){
			m_MButtons[i] = false;
		}
	}

	Window::~Window(){
		glfwTerminate();
		close = true;
	}

	void Window::update() {
		glfwPollEvents();
		glfwGetFramebufferSize(m_Window, &m_Width, &m_Height);
		glfwSwapBuffers(m_Window);

		//For clearing Images
		glClearColor(0, 0, 0, 0);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	bool Window::init(){

		if (!glfwInit()){ 
			std::cout << "Failed to initialize glfw" << std::endl;
			return false;
		}

		m_Window = glfwCreateWindow(m_Width, m_Height, m_Name, NULL, NULL);
		if (!m_Window){
			glfwTerminate();
			std::cout << "Failed to create window" << std::endl;
			return false;
		}
		glfwMakeContextCurrent(m_Window);
		glfwSetWindowUserPointer(m_Window, this);
		glfwSetWindowSizeCallback(m_Window, window_resize);
		glfwSetMouseButtonCallback(m_Window, mouse_button_callback);
		glfwSetCursorPosCallback(m_Window, cursor_position_callback);
		glfwSetKeyCallback(m_Window, key_callback);

		if (glewInit() != GLEW_OK){
			std::cout << "Could not Initialize GLEW" << std::endl;
			return false;
		}

		return true;
	}

	bool Window::closed() const{
		if (!close){
			return glfwWindowShouldClose(m_Window);
		}
		else {
			return close;
		}
	}

	bool Window::isKeyPressed(unsigned int keycode) const{
		if (keycode >= MAX_KEYS){
			//TODO: Log this
			return false;
		}
		return m_Keys[keycode];
	}

	bool Window::isMouseButtonPressed(unsigned int button) const{
		if (button >= MAX_BUTTONS){
			//TODO: Log this
			return false;
		}
		return m_MButtons[button];
	}

	void Window::getMousePosition(double& x, double& y) const{
		x = m_mx;
		y = m_my;
	}


	void Window::clear() const{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	void window_resize(GLFWwindow *window, int width, int height){
		glViewport(0, 0, width, height);
	}

	static void mouse_button_callback(GLFWwindow* window, int button, int action, int mods){
		Window* win = (Window*)glfwGetWindowUserPointer(window);
		win->m_MButtons[button] = action != GLFW_RELEASE;
	}


	static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods){
		Window* win = (Window*) glfwGetWindowUserPointer(window);
		win->m_Keys[key] = action != GLFW_RELEASE;
	}

	static void cursor_position_callback(GLFWwindow* window, double xpos, double ypos){
		Window* win = (Window*)glfwGetWindowUserPointer(window);
		win->m_mx = xpos;
		win->m_my = ypos;
		
	}

} }
