#pragma once
#include "MGL\Primitive\AbstractSendableArray.hpp"
#include "MGL\SharedHeaders\Exceptions.hpp"
DefineNewMglException(InstancingArrayException)

namespace mgl {
	class Buffer;
	namespace math {
		class vectorH;
	}
	class InstancingArray : public AbstractSendableArray<math::vectorH> {
	public:
		InstancingArray();
		InstancingArray(const float* array, size_t size, size_t NUMBERS_PER_ELEMENT = 4u);
		InstancingArray(math::vectorH* coords_array, size_t size);
		InstancingArray(const std::initializer_list<math::vectorH*>& list);
		InstancingArray(const std::list<math::vectorH*>& list);
		~InstancingArray();

		virtual size_t getSize() const;
		virtual size_t getNumber() const;

		void deleteObject(math::vectorH *obj);

		virtual void send(DataUsage u) override;
	};
}