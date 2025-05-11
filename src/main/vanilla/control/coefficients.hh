#pragma once

#include <units/base.h>
#include <units/dimensionless.h>

namespace vanilla::control
{

template <typename output_unit, typename effect_unit, typename time_unit>
requires units::traits::is_unit_v<output_unit>
	&&units::traits::is_unit_v<effect_unit> &&units::traits::is_unit_v<
		time_unit> struct pid_feedback_coefficients {
	using proportional_gain_unit =
		units::compound_unit<output_unit, units::inverse<effect_unit> >;

	using integral_gain_unit = units::compound_unit<
		output_unit,
		units::inverse<units::compound_unit<effect_unit, time_unit> > >;

	using derivative_gain_unit =
		units::compound_unit<units::compound_unit<output_unit, time_unit>,
				     units::inverse<effect_unit> >;

	using proportional_gain_unit_t = units::unit_t<proportional_gain_unit>;
	using integral_gain_unit_t = units::unit_t<integral_gain_unit>;
	using derivative_gain_unit_t = units::unit_t<derivative_gain_unit>;

	proportional_gain_unit_t proportional_gain;
	integral_gain_unit_t integral_gain;
	derivative_gain_unit_t derivative_gain;

	[[nodiscard]] static constexpr auto
	from_dimensionless_values(units::dimensionless_t proportional_gain,
				  units::dimensionless_t integral_gain,
				  units::dimensionless_t derivative_gain)
		-> pid_feedback_coefficients
	{
		return pid_feedback_coefficients{
			.proportional_gain = pid_feedback_coefficients::
				proportional_gain_unit_t{ proportional_gain },

			.integral_gain =
				pid_feedback_coefficients::integral_gain_unit_t{
					integral_gain },

			.derivative_gain =
				pid_feedback_coefficients::derivative_gain_unit_t{
					derivative_gain }
		};
	}
};

template <typename output_unit, typename effect_unit, typename time_unit>
requires units::traits::is_unit_v<output_unit>
	&&units::traits::is_unit_v<effect_unit> &&units::traits::is_unit_v<
		time_unit> struct svag_feedforward_coefficients {
	using gravitational_gain_unit = output_unit;

	using static_gain_unit = output_unit;

	using velocity_gain_unit =
		units::compound_unit<units::compound_unit<output_unit, time_unit>,
				     units::inverse<effect_unit> >;

	using acceleration_gain_unit = units::compound_unit<
		units::compound_unit<output_unit, units::squared<time_unit> >,
		units::inverse<effect_unit> >;

	using gravitational_gain_unit_t =
		units::unit_t<gravitational_gain_unit>;

	using static_gain_unit_t = units::unit_t<static_gain_unit>;

	using velocity_gain_unit_t = units::unit_t<velocity_gain_unit>;

	using acceleration_gain_unit_t = units::unit_t<acceleration_gain_unit>;

	gravitational_gain_unit_t gravitational_gain;
	static_gain_unit_t static_gain;
	velocity_gain_unit_t velocity_gain;
	acceleration_gain_unit_t acceleration_gain;

	[[nodiscard]] static constexpr auto
	from_dimensionless_values(units::dimensionless_t gravitational_gain,
				  units::dimensionless_t static_gain,
				  units::dimensionless_t velocity_gain,
				  units::dimensionless_t acceleration_gain)
		-> svag_feedforward_coefficients
	{
		return svag_feedforward_coefficients{
			.gravitational_gain = svag_feedforward_coefficients::
				gravitational_gain_unit_t{ gravitational_gain },

			.static_gain =
				svag_feedforward_coefficients::static_gain_unit_t{
					static_gain },

			.velocity_gain = svag_feedforward_coefficients::
				velocity_gain_unit_t{ velocity_gain },

			.acceleration_gain = svag_feedforward_coefficients::
				acceleration_gain_unit_t{ acceleration_gain }
		};
	}
};

}