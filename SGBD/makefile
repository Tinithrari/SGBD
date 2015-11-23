install:
	make view
	make controler
	make model
	gcc -g -c db_console.c CommandControler.o ModelControler.o CommandControler.o ConsoleView.o Table.o Column.o Tuple.o Data.o Database.o
	gcc -g -o SGBD ModelControler.o CommandControler.o ConsoleView.o Table.o Column.o Tuple.o Data.o Database.o db_console.o
view:
	gcc -c -g View/ConsoleView.c 
controler:
	gcc -c -g Controler/ModelControler.c Controler/CommandControler.c 
model:
	gcc -c -g Model/Data.c Model/Column.c Model/Tuple.c Model/Table.c Model/Database.c
application_test:
	make unit_test
	gcc -g -o DataTest Data.o testData.o
	gcc -g -o ColumnTest Column.o testColumn.o
	gcc -g -o TupleTest Data.o Tuple.o testTuple.o
	gcc -g -o TableAndColumnTest Table.o Column.o Tuple.o Data.o testColumnAndTable.o

unit_test:
	make debug
	gcc -g -c UnitTest/testData.c UnitTest/testColumn.c UnitTest/testTuple.c UnitTest/testColumnAndTable.c
	
debug:
	gcc -DDEBUG -c -g Model/Data.c Model/Column.c Model/Tuple.c Model/Table.c Model/Database.c

clean:
	rm *.o
	rm *Test
