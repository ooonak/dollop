#pragma once

#include <memory>
#include <string>

namespace spdlog
{
class logger;
}  // namespace spdlog

namespace dp
{

class ControllerImpl;

class Controller
{
 public:
  explicit Controller(const std::string &configFile,
                      const std::shared_ptr<spdlog::logger> &logger);

  ~Controller();

 private:
  std::unique_ptr<ControllerImpl> impl_;
};

}  // namespace dp
