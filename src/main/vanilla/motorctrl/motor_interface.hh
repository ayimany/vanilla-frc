#pragma once

#include <string_view>
#include <units/voltage.h>
#include <units/angle.h>
#include <units/angular_velocity.h>

namespace vanilla::motorctrl
{

class motor_interface {
    public:
	explicit motor_interface(std::string_view name) noexcept;

	[[nodiscard]] auto get_name() const noexcept -> std::string_view;

	virtual auto set_duty_cycle_output(double output) noexcept -> void = 0;

	virtual auto
	set_voltage_output(units::volt_t voltage) noexcept -> void = 0;

	virtual auto set_velocity(units::radians_per_second_t angular_velocity)
		noexcept -> void = 0;

	virtual auto
	set_position(units::radian_t angular_velocity) noexcept -> void = 0;

	virtual auto get_position() noexcept -> units::radian_t = 0;

	virtual auto get_velocity() noexcept -> units::radians_per_second_t = 0;

    protected:
    private:
	std::string_view name_;
};

}