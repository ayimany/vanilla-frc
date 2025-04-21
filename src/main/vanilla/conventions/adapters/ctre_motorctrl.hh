#pragma once

#include <ctre/phoenix6/signals/SpnEnums.hpp>
#include "vanilla/motorctrl/motor_interface.hh"

namespace vanilla::conventions::adapters
{

[[nodiscard]] constexpr auto
to_ctre_neutral_mode(motorctrl::motor_neutral_mode value)
	-> ctre::phoenix6::signals::NeutralModeValue
{
	using NeutralModeValue = ctre::phoenix6::signals::NeutralModeValue;
	return value == motorctrl::motor_neutral_mode::BRAKE ?
		       NeutralModeValue::Brake :
		       NeutralModeValue::Coast;
}

}