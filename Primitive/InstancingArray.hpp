#pragma once
#include "AbstractSendableArray.hpp"
#include "SharedHeaders\Exceptions.hpp"
DefineNewException(InstancingArrayException)

namespace mgl {
	class Buffer;
	namespace math {
		class Vector;
	}
	class InstancingArray : public AbstractSendableArray<math::Vector> {
	public:
		InstancingArray();
		InstancingArray(const float* array, size_t size, size_t NUMBERS_PER_ELEMENT = 4u);
		InstancingArray(math::Vector* coords_array, size_t size);
		InstancingArray(const std::initializer_list<math::Vector*>& list);
		InstancingArray(const std::list<math::Vector*>& list);
		~InstancingArray();

		virtual size_t getSize() const;
		virtual size_t getNumber() const;

		virtual void send(DataUsage u) override;
	};
}