#pragma once

#include <optional>
#include <string_view>
#include <units/voltage.h>
#include <units/angle.h>
#include <units/angular_velocity.h>
#include <units/angular_acceleration.h>
#include <units/angular_jerk.h>
#include <units/current.h>
#include <units/torque.h>

#include <wpi/sendable/Sendable.h>

#include "vanilla/control/coefficients.hh"
#include "vanilla/spatial/rotational.hh"

namespace vanilla::motorctrl
{

///
/// MOTOR STATE CONSTANTS
///

enum class neutral_behavior { brake, coast };

///
/// MOTOR OUTPUT CONTROL
///

struct motor_control_profile {
	using pid_feedback_coefficients =
		control::pid_feedback_coefficients<units::volts, units::radians,
						   units::seconds>;

	using svag_feedforward_coefficients =
		control::svag_feedforward_coefficients<
			units::volts, units::radians, units::seconds>;

	pid_feedback_coefficients feedback_coefficients;
	svag_feedforward_coefficients feedforward_coefficients;
};

///
/// MOTOR OUTPUT REQUESTS
///

struct output_request {};

struct duty_cycle_output_request : output_request {
	units::dimensionless_t target_output;
};

struct voltage_output_request : output_request {
	units::volt_t target_voltage;
};

struct torque_output_request : output_request {
	units::newton_meter_t target_torque;
};

struct position_target_request : output_request {
	units::radian_t target_position;
};

struct velocity_target_request : output_request {
	units::radians_per_second_t target_velocity;
};

struct angular_motion_profile {
	units::radians_per_second_t target_velocity;
	units::radians_per_second_squared_t target_acceleration;
	units::radians_per_second_cubed_t target_jerk;
};

struct angular_velocity_profile {
	units::radians_per_second_squared_t target_acceleration;
	units::radians_per_second_cubed_t target_jerk;
};

struct motor_interface_configuration {
	spatial::rotation_direction direction;
	neutral_behavior neutral_mode;
	units::ampere_t current_limit;
};

///
/// MOTOR INTERFACE
///

struct motor_interface {
	explicit motor_interface(
		std::string_view &&name,
		const motor_interface_configuration &config) noexcept;

	///
	/// ID
	///

	auto get_name() const noexcept -> std::string_view;

	///
	/// PROFILING
	///

	virtual auto add_control_profile(
		std::size_t index,
		const motor_control_profile &control_profile) -> void = 0;

	virtual auto choose_control_profile(std::size_t index) -> void = 0;

	virtual auto
	add_motion_profile(std::size_t index,
			   const angular_motion_profile &profile) -> void = 0;

	virtual auto choose_motion_profile(std::size_t index) -> void = 0;

	///
	/// OUTPUT
	///

	virtual auto set_output(
		const duty_cycle_output_request request) noexcept -> void = 0;

	virtual auto
	set_output(const voltage_output_request &request) noexcept -> void = 0;

	virtual auto
	set_output(const position_target_request &request,
		   const std::optional<angular_motion_profile> &motion_profile =
			   std::nullopt,
		   const std::optional<motor_control_profile> &control_profile =
			   std::nullopt) -> void = 0;

	auto set_output(const position_target_request &request,
			const angular_motion_profile &motion_profile) -> void;

	auto set_output(const position_target_request &request,
			const motor_control_profile &control_profile) -> void;

	virtual auto
	set_output(const velocity_target_request &request,
		   const std::optional<angular_velocity_profile>
			   &velocity_profile = std::nullopt,
		   const std::optional<motor_control_profile> &control_profile =
			   std::nullopt) -> void = 0;

	auto
	set_output(const velocity_target_request &request,
		   const angular_velocity_profile &velocity_profile) -> void;

	auto set_output(const velocity_target_request &request,
			const motor_control_profile &control_profile) -> void;

	///
	/// GETTERS
	///

	virtual auto get_position() noexcept -> units::radian_t = 0;

	virtual auto get_velocity() noexcept -> units::radians_per_second_t = 0;

    private:
	std::string_view name_;
};

}