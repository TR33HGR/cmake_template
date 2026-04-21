#pragma once

namespace rst {

class Restaurant;

struct Table
{
public:
  constexpr size_t index() const { return mIndex; };
  constexpr size_t size() const { return mSize; };
  constexpr bool operator<(const Table &other) const noexcept { return mIndex < other.index(); }

private:
  Table(const size_t index, const size_t size) : mIndex{ index }, mSize{ size } {};
  size_t mIndex;
  size_t mSize;

  friend class Restaurant;
};

}// namespace rst
