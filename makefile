main : main.c linked_list.c
	gcc main.c linked_list.c -o main
clean:
	rm main
	rm test_runner
run : main.c
	gcc main.c linked_list.c -o main
	./main
test : test_runner.c linked_list.c
	gcc test_runner.c linked_list.c -o test_runner
	./test_runner
debug_test : test_runner.c linked_list.c
	gcc -g test_runner.c linked_list.c -o test_runner
	gdb test_runner
