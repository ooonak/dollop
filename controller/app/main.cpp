#include <cstdlib>
#include <iostream>
#include <memory>

#include "dp/Controller.hpp"
#include "spdlog/sinks/stdout_color_sinks.h"
#include "spdlog/spdlog.h"

void setupLogging(std::vector<spdlog::sink_ptr> &sinks)
{
  try
  {
    auto console_sink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
    console_sink->set_level(spdlog::level::debug);
    sinks.push_back(console_sink);

    auto logger = std::make_shared<spdlog::logger>(
        "controller", std::begin(sinks), std::end(sinks));
    logger->set_level(spdlog::level::debug);
    spdlog::register_logger(logger);
  }
  catch (const spdlog::spdlog_ex &ex)
  {
    std::cout << "Log initialization failed: " << ex.what() << std::endl;
  }
}

int main()
{
  std::vector<spdlog::sink_ptr> sinks;
  setupLogging(sinks);

  try
  {
    dp::Controller controller{"dollopController.conf",
                              spdlog::get("controller")};
  }
  catch (const std::exception &exc)
  {
    std::cerr << exc.what() << std::endl;
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}
