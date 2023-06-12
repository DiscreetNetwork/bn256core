# bn256core
Basic library providing bare-bones, unoptimized operations under pairing-friendly curve bn256. Code mainly adapted from https://github.com/cloudflare/bn256. Uses https://github.com/kokke/tiny-bignum-c for bigints.

# Disclosure
The repository in its current state is experimental and not meant for production use. 32-bit builds of this repository have not been tested.

# Build Instructions
## Linux
Install NASM. Update GCC/G++ to the latest version. Run the makefile; shared library will be in the `linux` subdirectory.

## Windows
Install Visual Studio. Install NASM. Clone repository. Update build configuration for `gfp_items.asm`, i.e. the command `path/to/your/nasm.exe -f win64 gfp_items.asm`. This can be done by right-clicking the file in the solution explorer, clicking "properties", going into "Custom Build Tool" and updating the command as specified in the "Command Line" field. Build solution on Release/x64 configuration.

# Benchmarks
All benchmarks were performed with `Intel(R) Core(TM) i9-10900F CPU @ 2.80GHz`. Benchmarks were performed with randomized data for each operation, calculated prior to the benchmark. 

## Windows benchmarks
```
Fastmul (assembly speedup; BMI2)
Operation    Num ops    Total Time     Time per op
G1           10000      1008ms         0.1008ms
G2           10000      3098ms         0.3098ms
GT           10000      7739ms         0.7739ms
Pair         10000      10202ms        1.0202ms

Fastmul (assembly speedup; regular)
Operation    Num ops    Total Time     Time per op
G1           10000      1080ms         0.1080ms
G2           10000      3408ms         0.3408ms
GT           10000      8485ms         0.8485ms
Pair         10000      11148ms        1.1148ms

Generic (C, no speedup)
Operation    Num ops    Total Time     Time per op
G1           10000      7331ms         0.7331ms
G2           10000      22738ms        2.2738ms
GT           10000      51500ms        5.1500ms
Pair         10000      69951ms        6.9951ms
```

## Linux benchmarks
```
Fastmul (assembly speedup; BMI2)
Operation    Num ops    Total Time     Time per op
G1           10000      981ms          0.0981ms
G2           10000      3036ms         0.3036ms
GT           10000      7496ms         0.7496ms
Pair         10000      9847ms         0.9847ms

Fastmul (assembly speedup; regular)
Operation    Num ops    Total Time     Time per op
G1           10000      1051ms         0.1051ms
G2           10000      3358ms         0.3358ms
GT           10000      8231ms         0.8231ms
Pair         10000      11105ms        1.1105ms

Generic (C, no speedup)
Operation    Num ops    Total Time     Time per op
G1           10000      8352ms         0.8352ms
G2           10000      26049ms        2.6049ms
GT           10000      60258ms        6.0258ms
Pair         10000      80598ms        8.0598ms
```
