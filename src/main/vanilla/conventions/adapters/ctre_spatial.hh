#pragma once

#include <ctre/phoenix6/signals/SpnEnums.hpp>

#include "vanilla/spatial/rotational.hh"

namespace vanilla::conventions::adapters
{

[[nodiscard]] constexpr auto
to_ctre_inverted_value(spatial::rotation_direction value)
	-> ctre::phoenix6::signals::InvertedValue
{
	using InvertedValue = ctre::phoenix6::signals::InvertedValue;
	return value == spatial::rotation_direction::left ?
		       InvertedValue::CounterClockwise_Positive :
		       InvertedValue::Clockwise_Positive;
}

}