main : main.c linked_list.c
	gcc main.c linked_list.c -o main
clean:
	rm main
	rm test_runner
run : main.c
	gcc main.c linked_list.c -o main
	./main
