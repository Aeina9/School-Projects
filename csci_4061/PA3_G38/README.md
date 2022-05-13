Test machine: csel-kh1250-01

Group: 38

Members:
Amy Nguyen - nguy2841
Conor Hogan - hogan386
Turner Gravin - gravi022

Group has completed extra credit task of bounded buffer

Individual contributions: 
  * Amy -  Result and log printing and bank asset printing, error checking and documentation across all files, extra credit 
  * Conor - Consumer threads queue checking, parsing, and calculations, extra credit
  * Turner - Thread initializations and argument passing, and set up of shared queue and locks

Assumptions outside this document:
  * print_buff_size - (arbitrary) max length of line printed to result or log

# Project #3 – Multithreading

## Compile
	> make clean
	> make

## Execution
	> make run1
	> make run2 
	...
	> make run5

## Execute and compare output to expected
	> make t1
	> make t2 
	...
	> make t5
	> make test (Execute make t1-t5)


## Execute with printing, bounded buffer, or both
 	> ./bank #consumers inputFile [option] [#queueSize]

  <!-- • The first argument “#consumer” is the number of consumers the program will create.
      • The second argument “filename” is the input file name
      • The third, optional, argument has only three options: “-p”, “-b”, “-bp”.
          o No need to write logs or limit buffer if no option is provided.
          o “-p” means printing, the program will generate log in this case.
          o “-b” means bounded buffer (extra credit), the program will use it instead of unbounded buffer.
          o “-bp” means both bounded buffer and log printing.
        • #queue_Size means the queue size if using bounded buffer (extra credits). -->


