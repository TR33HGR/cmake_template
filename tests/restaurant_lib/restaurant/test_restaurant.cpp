#include <cstddef>
#include <iterator>
#include <memory>
#include <set>
#include <vector>

#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers.hpp>
#include <catch2/matchers/catch_matchers_container_properties.hpp>

#include "customer/group.hpp"
#include "restaurant/restaurant.hpp"
#include "restaurant/table.hpp"

namespace rst::test {

using namespace Catch::Matchers;

constexpr size_t NUM_TABLES{ 10 };

TEST_CASE("initialise restaurant")
{
  GIVEN("a restaurant in initial state")
  {
    auto restaurant{ create(NUM_TABLES) };
    THEN("all tables are free")
    {
      std::set<Table> freeTables{ restaurant->freeTables() };
      REQUIRE_THAT(freeTables, SizeIs(1));
      const auto table{ freeTables.begin() };
      REQUIRE(table->size() == NUM_TABLES);
    }
  }
}

struct EmptyRestaurant
{
  std::unique_ptr<Restaurant> restaurant{ create(NUM_TABLES) };
};

// NOLINTNEXTLINE(readability-function-cognitive-complexity)
TEST_CASE_METHOD(EmptyRestaurant, "requesting tables", "")
{
  GIVEN("an empty restaurant")
  {
    WHEN("an even number group requests a table within free table size")
    {
      constexpr cstmr::Group group{ 4 };
      constexpr size_t expectedNumTables{ group.size / 2 };

      const auto assignedTable{ restaurant->assignTable(group) };
      THEN("a table is assigned for each pair at the front of the restaurant")
      {
        REQUIRE(assignedTable.has_value());
        if (assignedTable.has_value()) {
          REQUIRE(assignedTable.value().index() == 0);
          REQUIRE(assignedTable.value().size() == expectedNumTables);
        }
      }
      AND_THEN("that table is not free")
      {
        const auto freeTables{ restaurant->freeTables() };
        REQUIRE_THAT(freeTables, SizeIs(1));

        const auto table{ freeTables.begin() };
        REQUIRE(table->index() == expectedNumTables);
        REQUIRE(table->size() == NUM_TABLES - expectedNumTables);
      }
    }

    WHEN("an odd number group requests a table within free table size")
    {
      constexpr cstmr::Group group{ 3 };
      constexpr size_t expectedNumTables{ (group.size + 1) / 2 };

      const auto assignedTable{ restaurant->assignTable(group) };
      THEN("a table is assigned for each pair plus one at the front of the restaurant")
      {
        REQUIRE(assignedTable.has_value());
        if (assignedTable.has_value()) {
          REQUIRE(assignedTable.value().index() == 0);
          REQUIRE(assignedTable.value().size() == expectedNumTables);
        }
      }
      AND_THEN("that table is not free")
      {
        const auto freeTables{ restaurant->freeTables() };
        REQUIRE_THAT(freeTables, SizeIs(1));

        const auto table{ freeTables.begin() };
        REQUIRE(table->index() == expectedNumTables);
        REQUIRE(table->size() == NUM_TABLES - expectedNumTables);
      }
    }

    WHEN("a group larger than the restaurant can fit requests a table")
    {
      constexpr cstmr::Group group{ 1 + NUM_TABLES * 2 };

      const auto assignedTable{ restaurant->assignTable(group) };
      THEN("no table is assigned") { REQUIRE(!assignedTable.has_value()); }
    }
  }
}

struct RestaurantWithCustomers : public EmptyRestaurant
{
  cstmr::Group seatedCustomers{ 1 };
  // NOLINTNEXTLINE(bugprone-unchecked-optional-access)
  Table takenTable{ restaurant->assignTable(seatedCustomers).value() };
};

// NOLINTNEXTLINE(readability-function-cognitive-complexity)
TEST_CASE_METHOD(RestaurantWithCustomers, "requesting tables", "")
{
  GIVEN("a restaurant with customers")
  {
    WHEN("a group requests a table within remaining free tables")
    {
      constexpr cstmr::Group group{ 2 };
      constexpr size_t expectedNumTables{ group.size / 2 };

      const auto assignedTable{ restaurant->assignTable(group) };
      THEN("a table is assigned for each pair as close to the front as possible")
      {
        REQUIRE(assignedTable.has_value());
        if (assignedTable.has_value()) {
          REQUIRE(assignedTable.value().index() == takenTable.index() + takenTable.size());
          REQUIRE(assignedTable.value().size() == expectedNumTables);
        }
      }
      AND_THEN("that table is also not free")
      {
        const auto freeTables{ restaurant->freeTables() };
        REQUIRE_THAT(freeTables, SizeIs(1));

        const auto table{ freeTables.begin() };
        const size_t numAssignedTables = takenTable.size() + expectedNumTables;
        REQUIRE(table->index() == numAssignedTables);
        REQUIRE(table->size() == NUM_TABLES - numAssignedTables);
      }
    }
  }
}

struct FullRestaurant : public EmptyRestaurant
{
  cstmr::Group seatedCustomers{ NUM_TABLES * 2 };
  // NOLINTNEXTLINE(bugprone-unchecked-optional-access)
  Table takenTable{ restaurant->assignTable(seatedCustomers).value() };
};

TEST_CASE_METHOD(FullRestaurant, "requesting tables", "")
{
  GIVEN("a full restaurant")
  {
    THEN("there are no free tables")
    {
      const auto freeTables{ restaurant->freeTables() };
      REQUIRE_THAT(freeTables, IsEmpty());
    }
    AND_WHEN("a group requests a table")
    {
      const cstmr::Group group{ 2 };

      const auto assignedTable{ restaurant->assignTable(group) };
      THEN("no table is assigned") { REQUIRE(!assignedTable.has_value()); }
    }
  }
}

TEST_CASE_METHOD(FullRestaurant, "clearing all tables", "")
{
  GIVEN("a full restaurant")
  {
    WHEN("clearing all tables")
    {
      restaurant->clearTable(takenTable);
      THEN("all tables are cleared")
      {
        std::set<Table> freeTables{ restaurant->freeTables() };
        REQUIRE_THAT(freeTables, SizeIs(1));
        const auto table{ freeTables.begin() };
        REQUIRE(table->size() == NUM_TABLES);
      }
      AND_WHEN("clearing all tables again")
      {
        restaurant->clearTable(takenTable);
        THEN("all tables are cleared")
        {
          std::set<Table> freeTables{ restaurant->freeTables() };
          REQUIRE_THAT(freeTables, SizeIs(1));
          const auto table{ freeTables.begin() };
          REQUIRE(table->size() == NUM_TABLES);
        }
      }
    }
  }
}

TEST_CASE_METHOD(RestaurantWithCustomers, "clearing tables", "")
{
  GIVEN("a restaurant with customers")
  {
    WHEN("clearing all customer tables")
    {
      restaurant->clearTable(takenTable);
      THEN("all tables are cleared")
      {
        std::set<Table> freeTables{ restaurant->freeTables() };
        REQUIRE_THAT(freeTables, SizeIs(1));
        const auto table{ freeTables.begin() };
        REQUIRE(table->size() == NUM_TABLES);
      }
    }
  }
}

struct RestaurantWithMultipleCustomers : public EmptyRestaurant
{
  RestaurantWithMultipleCustomers()
  {
    tables.reserve(seatedCustomers.size());
    for (const auto customer : seatedCustomers) {
      // NOLINTNEXTLINE(bugprone-unchecked-optional-access)
      tables.push_back(restaurant->assignTable(customer).value());
    }

    // NOLINTNEXTLINE(cppcoreguidelines-prefer-member-initializer)
    freeTableIndex = tables.back().index() + tables.back().size();
  };
  std::vector<cstmr::Group> seatedCustomers{ { 1 }, { 2 }, { 3 } };
  std::vector<Table> tables;
  size_t freeTableIndex;
};

TEST_CASE_METHOD(RestaurantWithMultipleCustomers, "clearing tables", "")
{
  GIVEN("a restaurant with customers")
  {
    WHEN("clearing the last customer table")
    {
      restaurant->clearTable(tables.back());
      THEN("that table is added to empty tables")
      {
        const auto freeTables{ restaurant->freeTables() };
        REQUIRE_THAT(freeTables, SizeIs(1));

        const auto table{ freeTables.begin() };
        REQUIRE(table->index() == tables.back().index());
        REQUIRE(table->size() == NUM_TABLES - tables.back().size());
      }
    }

    WHEN("clearing the first customer table")
    {
      restaurant->clearTable(tables.at(0));
      THEN("that table is added to the groups of free tables")
      {
        const auto freeTables{ restaurant->freeTables() };
        REQUIRE_THAT(freeTables, SizeIs(2));

        auto freeTable{ freeTables.begin() };
        REQUIRE(freeTable->index() == 0);
        REQUIRE(freeTable->size() == tables.at(0).size());

        freeTable = std::next(freeTable);
        REQUIRE(freeTable->index() == freeTableIndex);
        REQUIRE(freeTable->size() == NUM_TABLES - freeTableIndex);
      }
      AND_WHEN("clearing the second customer table")
      {
        restaurant->clearTable(tables.at(1));
        THEN("that table is added to the groups of free tables")
        {
          const auto freeTables{ restaurant->freeTables() };
          REQUIRE_THAT(freeTables, SizeIs(2));

          auto freeTable{ freeTables.begin() };
          REQUIRE(freeTable->index() == 0);
          REQUIRE(freeTable->size() == tables.at(0).size() + tables.at(1).size());

          freeTable = std::next(freeTable);
          REQUIRE(freeTable->index() == freeTableIndex);
          REQUIRE(freeTable->size() == NUM_TABLES - freeTableIndex);
        }
        AND_WHEN("clearing the last customer table")
        {
          restaurant->clearTable(tables.back());
          THEN("all tables are free")
          {
            const auto freeTables{ restaurant->freeTables() };
            REQUIRE_THAT(freeTables, SizeIs(1));

            auto freeTable{ freeTables.begin() };
            REQUIRE(freeTable->index() == 0);
            REQUIRE(freeTable->size() == NUM_TABLES);
          }
        }
      }
    }

    WHEN("clearing the middle customer table")
    {
      restaurant->clearTable(tables.at(1));
      THEN("that table is added to the groups of free tables")
      {
        const auto freeTables{ restaurant->freeTables() };
        REQUIRE_THAT(freeTables, SizeIs(2));

        auto freeTable{ freeTables.begin() };
        REQUIRE(freeTable->index() == tables.at(1).index());
        REQUIRE(freeTable->size() == tables.at(1).size());

        freeTable = std::next(freeTable);
        REQUIRE(freeTable->index() == freeTableIndex);
        REQUIRE(freeTable->size() == NUM_TABLES - freeTableIndex);
      }
    }
  }
}

}// namespace rst::test