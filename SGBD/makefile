install:
	make view
	make controler
	make model
	make utilities
	gcc -DUNIX -c -g db_console.c
	gcc -DUNIX -o SGBD *.o -lm
view:
	gcc -DUNIX -c View/*.c
model:
	gcc -c Model/*.c
controler:
	gcc -c Controler/*.c
utilities:
	gcc -c Utilities/*.c

install_debug:
	make view_debug
	make controler_debug
	make model_debug
	make utilities_debug
	gcc -DUNIX -c -g db_console.c
	gcc -g -o SGBD *.o -lm
view_debug:
	gcc -DUNIX -g -c View/*.c
model_debug:
	gcc -g -c Model/*.c
controler_debug:
	gcc -g -c Controler/*.c
utilities_debug:
	gcc -g -c Utilities/*.c
clean:
	rm *.o
	rm ./SGBD
