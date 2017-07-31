#pragma once
#include <string>
#include "SharedHeaders\Enums.hpp"
#include "SharedHeaders\Exceptions.hpp"
#include "Events\EmptyEventHandler.hpp"

struct GLFWwindow;

namespace mgl {
	enum class DefaultWindowMode {
		Windowed = 0, Fullscreen = 1
	};
	namespace Exceptions {
		class WindowInitializationException : public AbstractStringException {
			using AbstractStringException::AbstractStringException;
		};
	}

	class Color;
	class Shader;
	class Program;
	namespace math {
		class Matrix;
	}
	class DefaultEventHandler;

	typedef struct {
		int w, h;
	} Size;

	class AbstractWindow {
		friend DefaultEventHandler;
	private:
		GLFWwindow* m_window;
	protected:
		float m_aspectRatio;
		math::Matrix* m_projection;

		AbstractEventHandler* m_default_event_handler;
		bool isWindowInitialized;
	protected:
		virtual void initializeRenderProcess() abstract;
		virtual void renderProcess() abstract;
		virtual void clearRenderProcess() abstract;
	protected:
		virtual void resize();
		virtual void resize(int width, int height);
		void setOpenGLVersion(int major = 3, int minor = 3);
	public:
		explicit AbstractWindow();
		explicit AbstractWindow(std::string title, int width = 640, int height = 480, DefaultWindowMode mode = DefaultWindowMode::Windowed);
		virtual ~AbstractWindow();

		void initialize(std::string title, int width = 640, int height = 480, DefaultWindowMode mode = DefaultWindowMode::Windowed);
		void clean();

		Program* linkDefaultProgram(DefaulProgramType type = DefaulProgramType::Vertex_1Matrix);
		Program* linkProgramWithDefaultFragmentShader(Shader* vertex_shader);
		void update();
		void pollEvents();
		void clearWindow();
		void setClearColor(const mgl::Color& color);
		void setClearColor(const float r = 0.f, const float g = 0.f, const float b = 0.f, const float a = 1.f);

		int getWidth();
		int getHeight();
		Size getSize();

		void initializeEventHandling(AbstractEventHandler* h);
		void initializeEventHandling();
		void changleEventHandler(AbstractEventHandler* h);

		inline GLFWwindow* window() { return m_window; }
		bool isWindowClosed();
	};
}