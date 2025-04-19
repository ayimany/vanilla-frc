#pragma once

#include <functional>
#include <chrono>

namespace vanilla::resources
{

enum class resource_execution_status { EXECUTED, NOT_EXECUTED };
enum class resource_load_status { OK, NOT_OK };

class resource {
    public:
	explicit resource(
		std::function<resource_load_status()> executable) noexcept;

	auto load() noexcept -> resource_load_status;

	auto execution_time() const noexcept -> std::chrono::nanoseconds;

	auto has_loaded() const noexcept -> bool;

	auto is_ok() const noexcept -> bool;

    private:
	std::function<resource_load_status()> executable_;
	std::chrono::time_point<std::chrono::system_clock> execution_start_time_;
	std::chrono::time_point<std::chrono::system_clock> execution_end_time_;

	resource_execution_status execution_status_;
	resource_load_status load_status_;
};

class resource_loader {
    public:
	explicit resource_loader() noexcept;

	auto has_loaded_resources() -> bool;

	auto load_resources() -> void;

	auto all_resources_ok() const noexcept -> bool;

	auto
	get_total_execution_time() const noexcept -> std::chrono::nanoseconds;

    private:
	std::vector<resource> resources_;
	bool has_loaded_resources_;
};

}