#pragma once
#include <string>
#include <string_view>

namespace usr {

struct User
{
public:
  User(std::string_view id, std::string_view name) : mId{ id }, mName{ name } {};
  const std::string &id() const { return mId; }
  const std::string &name() const { return mName; }

private:
  std::string mId;
  std::string mName;
};

}// namespace usr
