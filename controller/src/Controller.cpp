#include "dp/Controller.hpp"

#include <sodium.h>

#include <exception>
#include <filesystem>

#include "Config.hpp"
#include "msgpack.hpp"
#include "spdlog/spdlog.h"

bool toFile(const dp::Config &config, const std::string &file)
{
  bool result = false;

  try
  {
    toml::value data;
    data["Dollop"] = toml::value(config);

    std::ofstream out(file);
    if (out.good())
    {
      out << data;
      out.close();
      result = true;
    }
  }
  catch (const std::exception &exc)
  {
  }

  return result;
}

bool fromFile(dp::Config &config, const std::string &file)
{
  bool result = false;

  try
  {
    const auto data = toml::parse(file);
    config = toml::find<dp::Config>(data, "Dollop");
    result = true;
  }
  catch (const std::exception &exc)
  {
  }

  return result;
}

class dp::ControllerImpl
{
 public:
  explicit ControllerImpl(const std::string &configFile,
                          const std::shared_ptr<spdlog::logger> &logger)
      : configFile_{configFile}, logger_{logger}
  {
    if (logger_ == nullptr)
    {
      throw std::runtime_error("No logger.");
    }

    if (!exists(std::filesystem::path(configFile_)))
    {
      logger_->info(
          "Configuration file not found, will write a new default one into {}.",
          configFile_);

      dp::Config defaultConfig;
      defaultConfig.multicastGroup = "1.2.3.4";
      defaultConfig.port = 1234;

      if (!toFile(defaultConfig, configFile_))
      {
        logger_->error("Could not write new default configuration to {}.",
                       configFile_);
        throw std::runtime_error("Could not write new default configuration.");
      }
    }

    if (!fromFile(config_, configFile_))
    {
      logger_->error("Failed to load configuration from {}.", configFile_);
      throw std::runtime_error("Failed to load configuration.");
    }

    logger_->debug("Loaded configuration...");
  }

  ~ControllerImpl() = default;

 private:
  const std::string configFile_;
  const std::shared_ptr<spdlog::logger> logger_;
  dp::Config config_;
};

dp::Controller::Controller(const std::string &configFile,
                           const std::shared_ptr<spdlog::logger> &logger)
    : impl_{std::make_unique<dp::ControllerImpl>(configFile, logger)}
{
}

dp::Controller::~Controller() = default;
