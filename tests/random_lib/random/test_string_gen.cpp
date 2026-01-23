#include <cstddef>
#include <string>

#include <catch2/catch_test_macros.hpp>

#include "random/string_gen.hpp"

namespace rnd::test {

TEST_CASE("random string generator string lengths")
{
  GIVEN("a random string generator")
  {
    auto stringGenerator{ createStringGenerator() };
    WHEN("generating a zero length string")
    {
      const size_t zeroLength{ 0 };
      const std::string generated{ stringGenerator->getString(zeroLength) };

      THEN("generated string is empty") { REQUIRE(generated.empty()); }
    }
  }
}

}// namespace rnd::test