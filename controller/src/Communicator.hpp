#pragma once

#include "Message.hpp"

namespace dp {

class Communicator {
 public:
  virtual ~Communicator() = default;

  virtual void send(const Message &msg) = 0;

};

} // namespace dp
