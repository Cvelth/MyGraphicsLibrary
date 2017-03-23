#pragma once

union SDL_Event;

namespace mgl {
	class AbstractEventHandler {

	public:
		virtual void handle(SDL_Event* e) abstract;
	};
}