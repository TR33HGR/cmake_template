#include <cstddef>
#include <memory>
#include <random>
#include <string>

#include "string_gen.hpp"

namespace rnd {

namespace {

  class DefaultStringGenerator : public StringGenerator
  {
  public:
    [[nodiscard]] std::string getString(const size_t length) const override
    {
      static const std::string charset =
        "abcdefghijklmnopqrstuvwxyz"
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "0123456789";

      static std::mt19937 rng{ std::random_device{}() };
      static std::uniform_int_distribution<std::size_t> distribution(0, charset.size() - 1);

      std::string result;
      result.reserve(length);

      for (std::size_t i{ 0 }; i < length; ++i) { result += charset[distribution(rng)]; }

      return result;
    }
  };

}// namespace

std::unique_ptr<StringGenerator> createStringGenerator() { return std::make_unique<DefaultStringGenerator>(); }

}// namespace rnd