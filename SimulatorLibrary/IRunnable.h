#pragma once
#include "IMappable.h"

namespace sim
{
	class IRunnable : public IMappable {
	public:
		virtual ~IRunnable() = default;
		virtual void run() = 0;
	};
}