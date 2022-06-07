

exec: 
	./main
	
run:
	gcc main.c Alunos.c Cursos.c -o main


clean:
	rm -f *.o main