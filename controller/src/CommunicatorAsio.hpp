#pragma once

#include <boost/asio.hpp>
#include "spdlog/spdlog.h"

#include "Communicator.hpp"

namespace dp {

class CommunicatorAsio : public Communicator {
 public:
  explicit CommunicatorAsio(const std::shared_ptr<spdlog::logger> &logger);

  ~CommunicatorAsio() override;

  void send(const Message &msg) override;

 private:
  const std::shared_ptr<spdlog::logger> logger_;
};

} // namespace dp
