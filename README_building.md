# Build Instructions
## Configure
From the top-level directory, run:
```shell
cmake -S . -B ./build
```
### Optional
You can optionally run with a preset if you don't want to use your default compiler.

To see available presets, run:
```shell
cmake --list-presets
```
Then to use a preset, run:
```shell
cmake -S . -B ./build --preset <preset>
```

## Building
To build, run:
```shell
cmake --build ./build
```

## Running the tests
You can use the `ctest` command run the tests.
```shell
cd ./build
ctest -C Debug
```