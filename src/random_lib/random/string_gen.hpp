#pragma once
#include <memory>
#include <string>

namespace rnd {

class StringGenerator
{
public:
  virtual ~StringGenerator() = default;
  [[nodiscard]] virtual std::string getString(const size_t length) const = 0;
};

std::unique_ptr<StringGenerator> createStringGenerator();

}// namespace rnd