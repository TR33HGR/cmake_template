#include <cstddef>
#include <string>

#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers.hpp>
#include <catch2/matchers/catch_matchers_container_properties.hpp>
#include <catch2/matchers/catch_matchers_string.hpp>

#include "random/string_generator.hpp"

namespace rnd::test {

using namespace Catch::Matchers;

TEST_CASE("random string generator string lengths")
{
  GIVEN("a random string generator")
  {
    const auto stringGenerator{ createStringGenerator() };

    WHEN("generating a zero length string")
    {
      const size_t zeroLength{ 0 };
      const std::string generated{ stringGenerator->getString(zeroLength) };

      THEN("generated string is empty") { REQUIRE_THAT(generated, IsEmpty()); }
    }

    WHEN("generating a string of a given length")
    {
      const size_t length{ 1 };
      const std::string generated{ stringGenerator->getString(length) };

      THEN("generated string has given length") { REQUIRE_THAT(generated, SizeIs(length)); }
    }
  }
}

TEST_CASE("random string generator generated strings")
{
  const auto stringGenerator{ createStringGenerator() };
  GIVEN("a randomly generated string of a given length")
  {
    const size_t length{ 10 };
    const std::string generated1{ stringGenerator->getString(length) };

    WHEN("generating a new string of the same length")
    {
      const std::string generated2{ stringGenerator->getString(length) };

      THEN("the strings are not equal") { REQUIRE_THAT(generated1, !Equals(generated2)); }
    }
  }
}

}// namespace rnd::test