#pragma once
#include "AbstractWindow.hpp"

namespace mgl {
	class AbstractLoopWindow : public AbstractWindow {
	public:
		AbstractLoopWindow() : AbstractWindow() {};
		explicit AbstractLoopWindow(std::string title, int width = 640, int height = 480, DefaultWindowMode mode = DefaultWindowMode::Windowed)
			: AbstractWindow(title, width, height, mode) {};

		int loop();
	};
}
