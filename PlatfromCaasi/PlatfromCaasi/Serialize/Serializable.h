#pragma once
#include <string>
#include <ostream>

namespace serialize
{
	/**
	 * Class Serializable
	 *
	 * Use to put class in a ostream.
	 */
	class Serializable
	{
	public:
		virtual std::ostream& serialize(std::ostream& os) const;
	};
}
std::ostream& operator<<(std::ostream& os, const serialize::Serializable& entity);

