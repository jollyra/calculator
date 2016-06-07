main : main.c
	gcc main.c -o main
clean:
	rm main
	rm test_runner
run : main.c
	gcc main.c -o main
	./main
test : test_runner.c
	gcc test_runner.c -o test_runner
	./test_runner
debug_tests : test_runner.c
	gcc -g test_runner.c -o test_runner
	gdb test_runner
