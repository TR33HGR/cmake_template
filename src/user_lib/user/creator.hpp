#pragma once
#include <memory>
#include <string_view>

namespace rnd {
class StringGenerator;
}

namespace usr {

struct User;

class Creator
{
public:
  virtual ~Creator() = default;
  [[nodiscard]] virtual User createUser(std::string_view name) const = 0;
};

std::unique_ptr<Creator> createCreator();
std::unique_ptr<Creator> createCreator(std::unique_ptr<rnd::StringGenerator>);

}// namespace usr