# GPU-Accelerated Source Engine Lightmap Compilation
**Ryan Lam (rwl) and Lucy Tan (jltan)**
this fork added automatic compilation and upgraded windows sdk from 17134 to 17763
## COMPILING
pretty straightforward:
1. install cuda sdk 10.0
2. install visual studio 2017
3. open the solution
4. compile preferably with release.
## WORKSPLIT 
maksw2: automatic compilation and some fixes.
Ryan: Reverse engineering file format, file read and write, direct and ambient lighting
Lucy: Light bouncing
