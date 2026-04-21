#pragma once

#include <memory>
#include <optional>
#include <set>

#include "table.hpp"

namespace cstmr {
struct Group;
}

namespace rst {

constexpr size_t NUM_TABLES{ 1200 };

class Restaurant
{
public:
  virtual ~Restaurant() = default;
  [[nodiscard]] virtual std::optional<Table> assignTable(cstmr::Group) = 0;
  virtual void clearTable(Table) = 0;

  virtual const std::set<Table> &freeTables() const = 0;

protected:
  static Table createTable(const size_t index, const size_t size) { return Table{ index, size }; }
};

std::unique_ptr<Restaurant> create(const size_t numTables = NUM_TABLES);

}// namespace rst