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
	protected:
		virtual size_t recalculate_number() const override;
		virtual size_t elements_per_item() const override;
		virtual void delete_data() override;
	public:
		InstancingArray();
		~InstancingArray();
		virtual void send(DataUsage u) override;
	};
	class InstancingMultiArray : public AbstractSendableArray<std::list<std::list<math::vectorH*>>> {
	protected:
		virtual size_t recalculate_number() const override;
		virtual size_t elements_per_item() const override;
		virtual void delete_data() override;
	public:
		InstancingMultiArray();
		~InstancingMultiArray();
		virtual void send(DataUsage u) override;
	};
}