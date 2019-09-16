flex -o Analyzer.c Analyzer.l
g++ Analyzer.c -lfl -o Analyzer.out
./Analyzer.out Analyzer.txt
