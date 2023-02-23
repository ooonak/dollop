#include "CommunicatorAsio.hpp"


dp::CommunicatorAsio::CommunicatorAsio(const std::shared_ptr<spdlog::logger> &logger)
    : logger_{logger}
{

}

dp::CommunicatorAsio::~CommunicatorAsio()
{

}

void dp::CommunicatorAsio::send(const Message &msg)
{
  const std::string tmp = msg.data();
  logger_->debug(tmp);
}
