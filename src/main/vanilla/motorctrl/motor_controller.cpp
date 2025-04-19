#include "motor_interface.hh"

namespace vanilla::motorctrl
{
motor_interface::motor_interface(std::string_view name) noexcept : name_{ name }
{
}

auto motor_interface::get_name() const noexcept -> std::string_view
{
	return name_;
}

}