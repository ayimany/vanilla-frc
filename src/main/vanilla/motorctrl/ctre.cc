#include "ctre.hh"

#include "vanilla/conventions/adapters/ctre_spatial.hh"
#include "vanilla/conventions/adapters/ctre_motorctrl.hh"

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

auto talonfx_interface::set_duty_cycle_output(double output) noexcept -> void
{
	internal_controller_.SetControl(
		ctre::phoenix6::controls::DutyCycleOut(output));
}

auto talonfx_interface::set_voltage_output(units::volt_t voltage) noexcept
	-> void
{
	internal_controller_.SetControl(
		ctre::phoenix6::controls::VoltageOut(voltage));
}

auto talonfx_interface::set_velocity(
	units::radians_per_second_t angular_velocity) noexcept -> void
{
	internal_controller_.SetControl(
		ctre::phoenix6::controls::VelocityVoltage(angular_velocity));
}

auto talonfx_interface::set_position(units::radian_t angle) noexcept -> void
{
	internal_controller_.SetControl(
		ctre::phoenix6::controls::PositionVoltage(angle));
}

auto talonfx_interface::get_position() noexcept -> units::radian_t
{
	return internal_controller_.GetPosition().GetValue();
}

auto talonfx_interface::get_velocity() noexcept -> units::radians_per_second_t
{
	return internal_controller_.GetVelocity().GetValue();
}

}