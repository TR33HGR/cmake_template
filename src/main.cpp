#include <CLI/CLI.hpp>
#include <exception>
#include <spdlog/spdlog.h>
#include <string>

#include "user/creator.hpp"
#include "user/user.hpp"

namespace {

struct Args
{
  std::string username;
};

void run(const Args &args)
{
  const auto userCreator{ usr::createCreator() };
  const usr::User user{ userCreator->createUser(args.username) };

  spdlog::info("User created with id: {}, name: {}", user.id(), user.name());
}

}// namespace

int main(int argc, const char **argv)
{
  try {
    CLI::App app{ "A simple example project" };

    Args args;

    app.add_option("--username", args.username, "The username you would like to use.")->required();

    CLI11_PARSE(app, argc, argv);

    run(args);

  } catch (const std::exception &e) {
    spdlog::error("Unhandled exception in main: {}", e.what());
  }
}
