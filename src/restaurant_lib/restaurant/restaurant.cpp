#include <algorithm>
#include <cstddef>
#include <iterator>
#include <memory>
#include <optional>
#include <set>

#include "restaurant.hpp"
#include "table.hpp"

#include "customer/group.hpp"

namespace rst {

namespace {

  class DefaultRestaurant : public Restaurant
  {
  public:
    explicit DefaultRestaurant(const size_t numTables) : mFreeTables{ createTable(0, numTables) } {}

    [[nodiscard]] std::optional<Table> assignTable(const cstmr::Group group) override
    {
      const size_t requiredTables{ (group.size + 1) / 2 };

      auto freeTable = std::find_if(
        mFreeTables.begin(), mFreeTables.end(), [&](const Table &table) { return table.size() >= requiredTables; });
      if (freeTable == mFreeTables.end()) { return std::nullopt; }

      return takeTable(freeTable, requiredTables);
    }

    void clearTable(Table table) override
    {
      mFreeTables.insert(table);
      mergeFreeTables();
    }

    [[nodiscard]] const std::set<Table> &freeTables() const override { return mFreeTables; }

  private:
    std::set<Table> mFreeTables;

    Table takeTable(std::set<Table>::iterator freeTable, const size_t requiredSize)
    {
      auto chosenTable = mFreeTables.extract(freeTable).value();
      if (chosenTable.size() > requiredSize) {
        mFreeTables.insert(createTable(chosenTable.index() + requiredSize, chosenTable.size() - requiredSize));
        chosenTable = createTable(chosenTable.index(), requiredSize);
      }
      return chosenTable;
    }

    void mergeFreeTables()
    {
      std::set<Table> tempFreeTables;
      std::optional<Table> merging{};
      for (auto table{ mFreeTables.begin() }; table != mFreeTables.end(); ++table) {
        auto nextTable = std::next(table);
        auto currentTable = merging.value_or(*table);
        if (nextTable == mFreeTables.end()) {
          tempFreeTables.insert(currentTable);
          break;
        }

        if (currentTable.index() + currentTable.size() == nextTable->index()) {
          merging = createTable(currentTable.index(), currentTable.size() + nextTable->size());
        } else {
          tempFreeTables.insert(currentTable);
          merging = std::nullopt;
        }
      }
      mFreeTables.swap(tempFreeTables);
    }
  };

}// namespace

std::unique_ptr<Restaurant> create(const size_t numTables) { return std::make_unique<DefaultRestaurant>(numTables); }


}// namespace rst