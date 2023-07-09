#include "Serializable.h"

namespace serialize
{
	std::ostream& Serializable::serialize(std::ostream& os) const
	{
		return os << typeid(*this).name() << " has not implemented serializazion";
	}
}
std::ostream& operator<<(std::ostream& os, const serialize::Serializable& serialised)
{
	return serialised.serialize(os) << std::endl;
}