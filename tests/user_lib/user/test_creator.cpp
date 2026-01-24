#include <memory>
#include <string>
#include <utility>

#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers.hpp>
#include <catch2/matchers/catch_matchers_string.hpp>
#include <trompeloeil/mock.hpp>

#include "user/creator.hpp"

#include "random/mock_string_generator.hpp"
#include "user/user.hpp"

namespace usr::test {

using namespace Catch::Matchers;
using trompeloeil::_;

TEST_CASE("user creator creating users")
{
  const std::string randomId{ "id" };
  auto randomStringGenerator{ std::make_unique<rnd::mock::MockStringGenerator>() };
  ALLOW_CALL(*randomStringGenerator, getString(_)).RETURN(randomId);

  GIVEN("a user creator")
  {
    const auto userCreator{ createCreator(std::move(randomStringGenerator)) };

    WHEN("creating a user with a given name")
    {
      const std::string name{ "name" };
      const User user{ userCreator->createUser(name) };

      THEN("user has given name") { REQUIRE_THAT(user.name(), Equals(name)); }
      THEN("user has a unique id") { REQUIRE_THAT(user.id(), Equals(randomId)); }
    }
  }
}

}// namespace usr::test