#pragma once

#include "motor_interface.hh"

#include <ctre/phoenix6/TalonFX.hpp>

#include "vanilla/util/identification.hh"

namespace vanilla::motorctrl
{

struct talonfx_configuration : motor_interface_configuration {
	id::can_id id;
};

class talonfx_interface : public motor_interface {
	explicit talonfx_interface(talonfx_configuration &&config,
				   std::string_view &&name);

	///
	/// PROFILING
	///

	auto add_control_profile(std::size_t index,
				 const motor_control_profile &control_profile)
		-> void override;

	auto choose_control_profile(std::size_t index) -> void override;

	auto add_motion_profile(std::size_t index,
				const angular_motion_profile &profile)
		-> void override;

	auto choose_motion_profile(std::size_t index) -> void override;

	///
	/// OUTPUT
	///

	auto set_output(const duty_cycle_output_request request) noexcept
		-> void override;

	auto set_output(const voltage_output_request &request) noexcept
		-> void override;

	auto
	set_output(const position_target_request &request,
		   const std::optional<angular_motion_profile> &motion_profile =
			   std::nullopt,
		   const std::optional<motor_control_profile> &control_profile =
			   std::nullopt) -> void override;

	auto
	set_output(const velocity_target_request &request,
		   const std::optional<angular_velocity_profile>
			   &velocity_profile = std::nullopt,
		   const std::optional<motor_control_profile> &control_profile =
			   std::nullopt) -> void override;

	///
	/// GETTERS
	///

	auto get_position() noexcept -> units::radian_t override;

	auto get_velocity() noexcept -> units::radians_per_second_t override;

    private:
	ctre::phoenix6::hardware::TalonFX internal_controller_;
	id::can_id id_;
};

}