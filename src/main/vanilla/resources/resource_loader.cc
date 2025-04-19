#include "resource_loader.hh"

#include <iostream>
#include <numeric>
#include <execution>

namespace vanilla::resources
{

resource::resource(std::function<resource_load_status()> executable) noexcept
	: executable_{ executable },
	  execution_status_{ resource_execution_status::NOT_EXECUTED },
	  load_status_{ resource_load_status::NOT_OK }
{
}

auto resource::load() noexcept -> resource_load_status
{
	load_status_ = resource_load_status::NOT_OK;
	execution_status_ = resource_execution_status::EXECUTED;

	execution_start_time_ = std::chrono::system_clock::now();

	try {
		load_status_ = executable_();
	} catch (const std::exception &e) {
		std::cerr << "Error while loading resource: " << e.what();
	}

	execution_end_time_ = std::chrono::system_clock::now();

	return load_status_;
}

auto resource::execution_time() const noexcept -> std::chrono::nanoseconds
{
	return execution_end_time_ - execution_start_time_;
}

auto resource::has_loaded() const noexcept -> bool
{
	return execution_status_ == resource_execution_status::EXECUTED;
}

auto resource::is_ok() const noexcept -> bool
{
	return load_status_ == resource_load_status::OK;
}

resource_loader::resource_loader() noexcept : has_loaded_resources_{ false }
{
}

auto resource_loader::has_loaded_resources() -> bool
{
	return has_loaded_resources_;
}

auto resource_loader::load_resources() -> void
{
	for (auto &resource : resources_) {
		resource.load();
	}
}

auto resource_loader::all_resources_ok() const noexcept -> bool
{
	return std::transform_reduce(
		std::execution::par_unseq, resources_.begin(), resources_.end(),
		true, std::logical_and<>(), [](const resource &res) {
			return res.has_loaded() && res.is_ok();
		});
}

auto resource_loader::get_total_execution_time() const noexcept
	-> std::chrono::nanoseconds
{
	return std::transform_reduce(
		std::execution::par_unseq, resources_.begin(), resources_.end(),
		std::chrono::nanoseconds{ 0 }, std::plus<>(),
		[](const resource &res) { return res.execution_time(); });
}
}
