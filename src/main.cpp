#include <CLI/CLI.hpp>
#include <exception>
#include <spdlog/spdlog.h>
#include <string>

namespace {

struct Args
{
};

void run() {}

}// namespace

int main(int argc, const char **argv)
{
  try {
    CLI::App app{ "A simple example project" };

    CLI11_PARSE(app, argc, argv);

    run();

  } catch (const std::exception &e) {
    spdlog::error("Unhandled exception in main: {}", e.what());
  }
}
