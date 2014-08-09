CONTENTS:
readme.txt     - This explanation file
report.docx    - The report for the project in a docx
run_times.xlsx - The excel sheet used to record timings for runs
driver.cpp     - The driver source code for the program
N128M_P16.o75200 - The output for submission for bonus
  
COMPILATION:
mpiCC -o BITONIC driver.cpp

EXECUTION:
./BITONIC 0 <number of numbers to randomly generate and sort>
ie,
./BITONIC 0 800
to generate and sort 800 numbers

./BITONIC 1 <inputfilename>
ie,
./BITONIC 1 "input.400K"
to read in the file and sort its numbers.
NOTE: The file must have a blank line at the end (to make the number of \ns in the
  file even!)

BONUS:
The output file N128M_P16.o75200 contains the best timing for 128 million, 16 process set.
