#compilar_windows:
#	gcc SOIL/*.c -c
#	gcc *.c -c -g
#	gcc *.o -o tp -lm -lfreeglut -lopengl32 -lglu32 -lglew32

compilar:
	gcc -o main main.c -o tp2 -lm -lGL -lGLU -lglfw -lGLEW -lglut -lSOIL

executar: compilar
	./tp2

#limpar_windows:
#	del -rf tp *.o
#	del -rf tp *.exe

limpar:
	rm -f *.o
	rm -f *.exe