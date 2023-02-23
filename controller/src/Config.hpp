#pragma once

#define TOML11_PRESERVE_COMMENTS_BY_DEFAULT
#include <fstream>
#include <string>

#include "toml.hpp"

namespace dp
{

struct Config
{
  std::string multicastGroup;
  int port;
};

}  // namespace dp

TOML11_DEFINE_CONVERSION_NON_INTRUSIVE(dp::Config, multicastGroup, port)
