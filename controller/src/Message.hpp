#pragma once

#include <cstddef>

namespace dp {

class Message {
 public:
  virtual ~Message() = default;

  virtual std::size_t size() = 0;

  virtual const char* data() = 0;

};

} // namespace dp
