
#pragma once

#include <units/velocity.h>
#include <units/time.h>

namespace vanilla::extensions
{
using meters_per_second_cubed_t = units::unit_t<units::compound_unit<
	units::meters, units::inverse<units::cubed<units::seconds> > > >;
}
