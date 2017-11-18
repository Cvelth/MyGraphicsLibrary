#pragma once
#include "MGL\Windows\AbstractWindow.hpp"

namespace mgl {
	class AbstractLoopWindow : public AbstractWindow {
	protected:
		bool isAutoUpdated;
	public:
		AbstractLoopWindow(bool autoUpdate = true) : AbstractWindow(), isAutoUpdated(autoUpdate) {};
		explicit AbstractLoopWindow(std::string title, int width = 640, int height = 480, DefaultWindowMode mode = DefaultWindowMode::Windowed, bool autoUpdate = true)
			: AbstractWindow(title, width, height, mode), isAutoUpdated(autoUpdate) {};

		int loop();
	};
}
