#include "motor_interface.hh"
#include <optional>

namespace vanilla::motorctrl
{
motor_interface::motor_interface(
	std::string_view &&name,
	const motor_interface_configuration &config) noexcept : name_{ name }
{
}

auto motor_interface::get_name() const noexcept -> std::string_view
{
	return name_;
}

auto motor_interface::set_output(const position_target_request &request,
				 const angular_motion_profile &motion_profile)
	-> void
{
	set_output(request, motion_profile, std::nullopt);
}

auto motor_interface::set_output(const position_target_request &request,
				 const motor_control_profile &control_profile)
	-> void
{
	set_output(request, std::nullopt, control_profile);
}

auto motor_interface::set_output(
	const velocity_target_request &request,
	const angular_velocity_profile &velocity_profile) -> void
{
	set_output(request, velocity_profile, std::nullopt);
}

auto motor_interface::set_output(const velocity_target_request &request,
				 const motor_control_profile &control_profile)
	-> void
{
	set_output(request, std::nullopt, control_profile);
}

}