# Linear Hashing
Implementation of linear hashing algorithm of [paper](https://hackthology.com/pdfs/Litwin-1980-Linear_Hashing.pdf) to handle duplicate elimination using c++ language.

# Input
<Filename,M,B> as command line arguements. "M" is the number of buffers. "B" is the buffer size and "filename" is the name of input file whose each line consists one of single integer x (-10^9 <= x <= 10^9).

# Output
After reading every line (call it record), If record is not inserted into data structure, print it and
insert it into data structure.

# NOTE
1. M denotes the number of buffers and B denotes the buffer size (M>=2 and M*B<=10^6).
2. Out of the M buffers, M-1 Buffers will be used as input buffers (which will hold the records from the input file), 1 buffer will be used as output buffer (holds the distinctrecords).
3. If the output buffer gets filled, it should be flushed to the output. If the input buffers get empty, next chunk of records should be read from the input file.
