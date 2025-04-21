#pragma once

#include "vanilla/extensions/units.hh"
#include <units/velocity.h>
#include <units/acceleration.h>
#include <units/angular_velocity.h>
#include <units/angular_acceleration.h>
#include <units/angular_jerk.h>
#include <units/time.h>

namespace vanilla::spatial
{

struct motion_profile {
	units::second_t acceleration_period;
	units::second_t jerk_period;
};

struct linear_motion_profile : public motion_profile {
	units::meters_per_second_t target_velocity;
	units::meters_per_second_squared_t target_acceleration;
	extensions::meters_per_second_cubed_t target_jerk;
};

struct angular_motion_profile : public motion_profile {
	units::radians_per_second_t target_velocity;
	units::radians_per_second_squared_t target_acceleration;
	units::radians_per_second_cubed_t target_jerk;
};

[[nodiscard]] constexpr auto create_linear_motion_profile(
	units::meters_per_second_t target_velocity,
	units::second_t acceleration_period,
	units::second_t jerk_period) -> linear_motion_profile
{
	linear_motion_profile profile{};
	profile.target_velocity = target_velocity;
	profile.target_acceleration = target_velocity / acceleration_period;
	profile.target_jerk = profile.target_acceleration / jerk_period;

	return profile;
}

[[nodiscard]] constexpr auto create_linear_motion_profile(
	units::meters_per_second_t target_velocity,
	units::meters_per_second_squared_t target_acceleration,
	extensions::meters_per_second_cubed_t target_jerk)
	-> linear_motion_profile
{
	linear_motion_profile profile{};
	profile.target_velocity = target_velocity;
	profile.target_acceleration = target_acceleration;
	profile.target_jerk = profile.target_jerk;

	return profile;
}

[[nodiscard]] constexpr auto create_angular_motion_profile(
	units::meters_per_second_t target_velocity,
	units::second_t acceleration_period,
	units::second_t jerk_period) -> angular_motion_profile
{
	angular_motion_profile profile{};
	profile.target_velocity = target_velocity;
	profile.target_acceleration = target_velocity / acceleration_period;
	profile.target_jerk = profile.target_acceleration / jerk_period;

	return profile;
}

[[nodiscard]] constexpr auto create_angular_motion_profile(
	units::meters_per_second_t target_velocity,
	units::meters_per_second_squared_t target_acceleration,
	extensions::meters_per_second_cubed_t target_jerk)
	-> angular_motion_profile
{
	angular_motion_profile profile{};
	profile.target_velocity = target_velocity;
	profile.target_acceleration = target_acceleration;
	profile.target_jerk = profile.target_jerk;

	return profile;
}

}