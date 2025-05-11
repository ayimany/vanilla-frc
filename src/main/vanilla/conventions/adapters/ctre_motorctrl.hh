#pragma once

#include <ctre/phoenix6/signals/SpnEnums.hpp>
#include "vanilla/motorctrl/motor_interface.hh"

namespace vanilla::conventions::adapters
{

[[nodiscard]] constexpr auto
to_ctre_neutral_mode(motorctrl::neutral_behavior value)
	-> ctre::phoenix6::signals::NeutralModeValue
{
	using NeutralModeValue = ctre::phoenix6::signals::NeutralModeValue;
	return value == motorctrl::neutral_behavior::brake ?
		       NeutralModeValue::Brake :
		       NeutralModeValue::Coast;
}

}