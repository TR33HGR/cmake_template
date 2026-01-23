#include <CLI/CLI.hpp>
#include <exception>
#include <spdlog/spdlog.h>

int main(int argc, const char **argv)
{
  try {
    CLI::App app{ "A simple example project" };

    std::string username;
    app.add_option("--username", username, "The username you would like to use");

    CLI11_PARSE(app, argc, argv);

  } catch (const std::exception &e) {
    spdlog::error("Unhandled exception in main: {}", e.what());
  }
}
