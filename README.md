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

# Algorithm to decide buffer split
Assume block size = buffer size (B).<br/>
Let there are n blocks (without counting overflow blocks) and r records at some instant.<br/>
Let r0 be the maximum records that can fit in a block.<br/>
Split occupancy = `r/(n*r0)`. Setting threshold to 0.75. This means split happens when occupancy >= 0.75.<br/>
To calculate r0:-<br/>
if each block has space for n keys and n+1 pointers then size occupied = `4*(n)+8*(n+1)` [if keys are integer]</br>
Let this be called "S". Thus, picking the maximum value of n such that S<=B (block size).<br/>
This maximum value of n is our r0.

