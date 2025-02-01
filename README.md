[![CMake on Ubuntu (W/ gcc & clang) & Macos (W/ clang)](https://github.com/R-Gld/L3_S6_Sys2_TP1/actions/workflows/cmake-multi-platform.yml/badge.svg)](https://github.com/R-Gld/L3_S6_Sys2_TP1/actions/workflows/cmake-multi-platform.yml)
# L3 S6 - 1st Système 2 TP

## Usage

```bash
mkdir -p build
cd build
cmake ..
make
```

This will generate two executables: `TP1_EX1` and `TP1_EX2`.

## Known bug

After executing `TP1_EX2` in a folder, the `TP1_EX1` fail with the error:
> **shmget**: Invalid argument

You can change the working directory to temporarily avoid this problem.