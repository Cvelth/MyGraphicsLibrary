#include "AbstractSendableArray.hpp"
#include "OpenGL\ClassesMirror\Buffer.hpp"

mgl::Buffer* mgl::SubFunctions::generate_buffer() {
	return new Buffer();
}

void mgl::SubFunctions::buffer_bind(Buffer *buffer) {
	buffer->bind();
}

void mgl::SubFunctions::buffer_data(Buffer *buffer, bool &wasBufferGenerated, size_t floats, float *data, DataUsage u) {
	buffer->data(floats, data, u);
}

void mgl::SubFunctions::delete_buffer(Buffer *buffer) {
	delete buffer;
}
