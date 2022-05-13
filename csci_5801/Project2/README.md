Project 2: Agile Scrum

## How to run the system
	(From src dir)
	> make
	> One file:
	  ./build/final_program ../testing/<Name of the file>
	> Multiple files:
	  ./build/final_program ../testing/<Name of the file> ../testing/<Name of the file>
	> make clean

## How to toggle IRV shuffle
	(From src dir)
	> make
	> ./build/final_program ../testing/<Name of the file> -sh
	> make clean

## How to run google tests
	(From src dir)
	> make -f test.mk
	> ./all_test
	> make clean -f test.mk