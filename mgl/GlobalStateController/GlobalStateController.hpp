#pragma once
namespace mgl {
	class GlobalStateController {
	public:
		GlobalStateController() = delete;
		GlobalStateController(GlobalStateController const& other) = delete;
		GlobalStateController(GlobalStateController &&other) =delete;
	};
}