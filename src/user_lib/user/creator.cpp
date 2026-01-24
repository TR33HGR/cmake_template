#include <cstddef>
#include <memory>
#include <string>
#include <utility>

#include "creator.hpp"

#include "random/string_generator.hpp"
#include "user.hpp"

namespace usr {

namespace {

  constexpr size_t ID_LENGTH{ 12 };

  class DefaultCreator : public Creator
  {
  public:
    DefaultCreator() : mRandomStringGenerator{ rnd::createStringGenerator() } {}
    explicit DefaultCreator(std::unique_ptr<rnd::StringGenerator> randomStringGenerator)
      : mRandomStringGenerator{ std::move(randomStringGenerator) }
    {}
    [[nodiscard]] User createUser(const std::string &name) const override
    {
      return { mRandomStringGenerator->getString(ID_LENGTH), name };
    }

  private:
    std::unique_ptr<rnd::StringGenerator> mRandomStringGenerator;
  };

}// namespace

std::unique_ptr<Creator> createCreator() { return std::make_unique<DefaultCreator>(); }
std::unique_ptr<Creator> createCreator(std::unique_ptr<rnd::StringGenerator> randomStringGenerator)
{
  return std::make_unique<DefaultCreator>(std::move(randomStringGenerator));
}


}// namespace usr