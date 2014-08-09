CONTENTS:
readme.txt     - This explanation file
report.pdf     - The report for the project in a pdf
report.docx    - The report for the project in a docx
run_times.xlsx - The excel sheet used to record timings for runs
source.zip     - The 3 source files for the project
  prime_sieve_opt.cpp - The "optimized" version of the code
  prime_sieve_no-opt.cpp - The unoptimized version of the code
  numeric_types.h - Custom numeric types for clarification of bitwidths
/output/
  The raw output files from each run, mostly appropriately named
/exec_scripts/
  The different scripts to run the program with different N and P variances.
  Ex: N4B_P16_NO runs with N=4 billion, P=16 processes, and no optimization
      N4B_P16_O  runs with n=4 billion, P=16 processes, and "optimizations"
  
COMPILATION:
For the "optimized" version (which runs slower than the unoptimized):
mpiCC -o PRIME prime_sieve_opt.cpp

For the unoptimized version (used to generate almost all timings):
mpiCC -o PRIME prime_sieve_no-opt.cpp

EXECUTION:
./PRIME <Global Upper Bound N>
ie,
./PRIME 10000
to search to ten thousand.

To edit how many primes and after which number the program outputs, see lines
26 and 27 in the source files.

BONUS:
The output file N10B_P16_NO.o69325 contains the best timing for the 10 billion
set. It should be noted that the output of bounds and the greatest prime found
is cast to a 32 bit unsigned int and doesn't display correctly in the output 
file, but the time taken to complete is correct.

https://docs.google.com/leaf?id=0B_s5yMVHMC16YzI0ZDE4NjEtYzgwYy00NGZmLTkxMmYtMWIxOTVhZmU4YjUw&hl=en
Contains a copy of the important files.