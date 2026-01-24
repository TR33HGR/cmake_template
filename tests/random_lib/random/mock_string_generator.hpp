#pragma once

#include <trompeloeil/mock.hpp>

#include "random/string_generator.hpp"

namespace rnd::mock {
struct MockStringGenerator : public StringGenerator
{
  MAKE_CONST_MOCK(getString, auto(const size_t length)->std::string, override);
};
}// namespace rnd::mock