#pragma once

#include "motor_interface.hh"

#include <ctre/phoenix6/TalonFX.hpp>

#include "vanilla/conventions/adapters/ctre_spatial.hh"
#include "vanilla/util/identification.hh"

namespace vanilla::motorctrl
{

struct talonfx_configuration : motor_interface_configuration {
	id::can_id id;
};

class talonfx_interface : public motor_interface {
	explicit talonfx_interface(talonfx_configuration &&config,
				   std::string_view &&name);

	auto set_duty_cycle_output(double output) noexcept -> void override;

	auto
	set_voltage_output(units::volt_t voltage) noexcept -> void override;

	auto set_velocity(units::radians_per_second_t angular_velocity) noexcept
		-> void override;

	auto set_position(units::radian_t angle) noexcept -> void override;

	auto get_position() noexcept -> units::radian_t override;

	auto get_velocity() noexcept -> units::radians_per_second_t override;

    private:
	ctre::phoenix6::hardware::TalonFX internal_controller_;
	id::can_id id_;
};

}