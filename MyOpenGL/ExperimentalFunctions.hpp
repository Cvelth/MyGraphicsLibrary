#pragma once

namespace mgl {
	void enableSmooth(SmoothMode mode);
	void enableAlpha();

	void enableVertexAttribArray(size_t id);
	void enableEveryVertexAttribArray(size_t id_b, size_t id_e);
}