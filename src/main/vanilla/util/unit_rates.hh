#pragma once

#include <cstddef>
#include <units/base.h>
#include <tuple>
#include <utility>

namespace vanilla::internal
{
template <typename output_unit, typename differential_unit,
	  std::size_t derivative_count, typename... current_units>
struct differential_unit_sequence;

template <typename output_unit, typename differential_unit,
	  typename... current_units>
struct differential_unit_sequence<output_unit, differential_unit, 0,
				  std::tuple<current_units...> > {
	using type = std::tuple<current_units..., output_unit>;
};

template <typename output_unit, typename differential_unit,
	  std::size_t derivative_count, typename... current_units>
struct differential_unit_sequence<output_unit, differential_unit,
				  derivative_count,
				  std::tuple<current_units...> > {
	using differential =
		units::compound_unit<output_unit,
				     units::inverse<differential_unit> >;

	using type = typename differential_unit_sequence<
		differential, differential_unit, derivative_count - 1,
		std::tuple<current_units..., output_unit> >::type;
};

template <typename output_unit, typename differential_unit,
	  std::size_t derivative_count, typename... current_units>
struct differential_unit_sequence {
	using type = typename differential_unit_sequence<
		output_unit, differential_unit, derivative_count,
		std::tuple<> >::type;
};

template <typename output_unit, typename differential_unit,
	  std::size_t derivative_count, typename... current_units>
using differential_unit_sequence_t =
	typename differential_unit_sequence<output_unit, differential_unit,
					    derivative_count>::type;

template <typename container, typename sequence>
struct solidify_unit_container_impl;

template <typename... container_elements, std::size_t... size>
struct solidify_unit_container_impl<std::tuple<container_elements...>,
				    std::index_sequence<size...> > {
	using type = std::tuple<units::unit_t<std::tuple_element_t<
		size, std::tuple<container_elements...> > >...>;
};

template <typename container> struct solidify_unit_container {
	using type = typename solidify_unit_container_impl<
		container,
		std::make_index_sequence<std::tuple_size_v<container> > >::type;
};

template <typename Tuple>
using solidify_unit_container_t = typename solidify_unit_container<Tuple>::type;

template <typename output_unit, typename differential_unit,
	  std::size_t differential_count>
using solidified_differential_unit_sequence_t =
	solidify_unit_container_t<differential_unit_sequence_t<
		output_unit, differential_unit, differential_count> >;
}

namespace vanilla::control
{

template <typename output_unit, typename rate_unit, std::size_t rate_count>
struct rate_profile {
	using rate_container =
		internal::solidified_differential_unit_sequence_t<
			output_unit, rate_unit, rate_count>;

	explicit constexpr rate_profile(rate_container rates) noexcept
		: rates_{ rates }
	{
	}

	template <std::size_t index>
	using get_derivative_unit = std::tuple_element_t<index, rate_container>;

	template <std::size_t index>
	[[nodiscard]] constexpr auto
	get_rate() const noexcept -> get_derivative_unit<index>
	{
		return std::get<index>(rates_);
	}

    private:
	rate_container rates_;
};

}
