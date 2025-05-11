#include "ctre.hh"

#include "ctre/phoenix6/configs/Configs.hpp"
#include "ctre/phoenix6/controls/DutyCycleOut.hpp"
#include "ctre/phoenix6/controls/DynamicMotionMagicVoltage.hpp"
#include "ctre/phoenix6/controls/MotionMagicVoltage.hpp"
#include "ctre/phoenix6/controls/VoltageOut.hpp"
#include "vanilla/conventions/adapters/ctre_spatial.hh"
#include "vanilla/conventions/adapters/ctre_motorctrl.hh"
#include <stdexcept>

namespace vanilla::motorctrl
{

talonfx_interface::talonfx_interface(talonfx_configuration &&config,
				     std::string_view &&name)
	: motor_interface{ std::move(name), std::move(config) }
	, internal_controller_{ config.id }
	, id_{ config.id }
{
	auto configurator = ctre::phoenix6::configs::TalonFXConfiguration{};

	configurator.MotorOutput.Inverted =
		conventions::adapters::to_ctre_inverted_value(config.direction);

	configurator.MotorOutput.NeutralMode =
		conventions::adapters::to_ctre_neutral_mode(
			config.neutral_mode);
}

///
/// PROFILING
///

auto talonfx_interface::add_control_profile(
	std::size_t index, const motor_control_profile &control_profile) -> void
{
	switch (index) {
	case 1: {
		ctre::phoenix6::configs::Slot0Configs cfg{};
		cfg.WithKP(control_profile.feedback_coefficients
				   .proportional_gain.value());
		cfg.WithKI(control_profile.feedback_coefficients.integral_gain
				   .value());
		cfg.WithKD(control_profile.feedback_coefficients.derivative_gain
				   .value());
		cfg.WithKS(control_profile.feedforward_coefficients.static_gain
				   .value());
		cfg.WithKV(control_profile.feedforward_coefficients
				   .velocity_gain.value());
		cfg.WithKA(control_profile.feedforward_coefficients
				   .acceleration_gain.value());
		cfg.WithKG(control_profile.feedforward_coefficients
				   .gravitational_gain.value());

		internal_controller_.GetConfigurator().Apply(cfg);
	} break;
	case 2: {
		ctre::phoenix6::configs::Slot1Configs cfg{};
		cfg.WithKP(control_profile.feedback_coefficients
				   .proportional_gain.value());
		cfg.WithKI(control_profile.feedback_coefficients.integral_gain
				   .value());
		cfg.WithKD(control_profile.feedback_coefficients.derivative_gain
				   .value());
		cfg.WithKS(control_profile.feedforward_coefficients.static_gain
				   .value());
		cfg.WithKV(control_profile.feedforward_coefficients
				   .velocity_gain.value());
		cfg.WithKA(control_profile.feedforward_coefficients
				   .acceleration_gain.value());
		cfg.WithKG(control_profile.feedforward_coefficients
				   .gravitational_gain.value());

		internal_controller_.GetConfigurator().Apply(cfg);
	} break;
	case 3: {
		ctre::phoenix6::configs::Slot2Configs cfg{};
		cfg.WithKP(control_profile.feedback_coefficients
				   .proportional_gain.value());
		cfg.WithKI(control_profile.feedback_coefficients.integral_gain
				   .value());
		cfg.WithKD(control_profile.feedback_coefficients.derivative_gain
				   .value());
		cfg.WithKS(control_profile.feedforward_coefficients.static_gain
				   .value());
		cfg.WithKV(control_profile.feedforward_coefficients
				   .velocity_gain.value());
		cfg.WithKA(control_profile.feedforward_coefficients
				   .acceleration_gain.value());
		cfg.WithKG(control_profile.feedforward_coefficients
				   .gravitational_gain.value());

		internal_controller_.GetConfigurator().Apply(cfg);
	} break;
	default: {
		throw std::range_error{
			"A TalonFX may only hold 3 control slots, indexed 0, 1 and 2"
		};
	} break;
	}
}

auto talonfx_interface::choose_control_profile(std::size_t index) -> void
{
}

auto talonfx_interface::add_motion_profile(
	std::size_t index, const angular_motion_profile &profile) -> void
{
}

auto talonfx_interface::choose_motion_profile(std::size_t index) -> void
{
}

///
/// OUTPUT
///

auto talonfx_interface::set_output(
	const duty_cycle_output_request request) noexcept -> void
{
	internal_controller_.SetControl(
		ctre::phoenix6::controls::DutyCycleOut(request.target_output));
}

auto talonfx_interface::set_output(
	const voltage_output_request &request) noexcept -> void
{
	internal_controller_.SetControl(
		ctre::phoenix6::controls::VoltageOut(request.target_voltage));
}

auto talonfx_interface::set_output(
	const position_target_request &request,
	const std::optional<angular_motion_profile> &motion_profile,
	const std::optional<motor_control_profile> &control_profile) -> void
{
	if (control_profile.has_value()) {
		throw std::runtime_error{
			"TalonFX does not support setting control constants on the fly. "
			"Choose a control slot instead."
		};
	}

	if (motion_profile.has_value()) {
		if (internal_controller_.GetIsProLicensed().GetValue()) {
			throw std::runtime_error{
				"Cannot set a motion profile on the fly without a Pro License on a TalonFX."
			};
		}

		ctre::phoenix6::controls::DynamicMotionMagicVoltage rq{
			request.target_position,
			motion_profile->target_velocity,
			motion_profile->target_acceleration,
			motion_profile->target_jerk
		};

		internal_controller_.SetControl(rq);
	}

	internal_controller_.SetControl(
		ctre::phoenix6::controls::MotionMagicVoltage{
			request.target_position });
}

auto talonfx_interface::set_output(
	const velocity_target_request &request,
	const std::optional<angular_velocity_profile> &velocity_profile,
	const std::optional<motor_control_profile> &control_profile) -> void
{
	internal_controller_.SetControl(
		ctre::phoenix6::controls::VoltageOut(request.target_voltage));
}

///
/// GETTERS
///

auto talonfx_interface::get_position() noexcept -> units::radian_t
{
}

auto talonfx_interface::get_velocity() noexcept -> units::radians_per_second_t
{
}

}