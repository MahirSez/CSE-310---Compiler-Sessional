flex -o wordcount.c wordcount.l
g++ wordcount.c -lfl -o wordcount.out
./wordcount.out wordcount.txt


flex -o scanner.c scanner.l
g++ scanner.c -lfl -o scanner.out
./scanner.out scanner.txt



flex -o demo2.c demo2.l
g++ demo2.c -lfl -o demo2.out
./demo2.out demo2.txt



flex -o state.c state.l
g++ state.c -lfl -o state.out
./state.out state.txt
