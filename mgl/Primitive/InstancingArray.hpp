#pragma once
#include "../MyGraphicsLibrary/MGL/Primitive/AbstractSendableArray.hpp"
#include "../MyGraphicsLibrary/MGL/SharedHeaders/Exceptions.hpp"
DefineNewMglException(InstancingArrayException)

#include <list>
namespace mgl {
	class Buffer;
	namespace math {
		class vectorH;
	}
	class InstancingArray : public AbstractSendableArray<std::list<math::vectorH*>> {
	public:
		InstancingArray();
		~InstancingArray();

		virtual size_t getSize() const;
		virtual size_t getNumber() const;

		virtual void send(DataUsage u) override;
	};
	class InstancingMultiArray : public AbstractSendableArray<std::list<std::list<math::vectorH*>>> {
	public:
		InstancingMultiArray();
		~InstancingMultiArray();

		virtual size_t getSize() const;
		virtual size_t getNumber() const;

		virtual void send(DataUsage u) override;
	};
}