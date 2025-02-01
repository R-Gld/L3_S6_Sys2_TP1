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