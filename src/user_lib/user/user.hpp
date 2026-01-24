#pragma once
#include <string>

namespace usr {

struct User
{
public:
  User(const std::string &id, const std::string &name) : mId{ id }, mName{ name } {};
  const std::string &id() const { return mId; }
  const std::string &name() const { return mName; }

private:
  std::string mId;
  std::string mName;
};

}// namespace usr
