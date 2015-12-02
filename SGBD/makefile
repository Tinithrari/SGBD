install:
	make view
	make controler
	make model
view:
	gcc -c -g View/ConsoleView.c 
model:
	gcc -c -g Model/Data.c Model/Column.c Model/Tuple.c Model/Table.c Model/Database.c
application_test:
	make debug
	make unit_test
	gcc -g -o DataTest Data.o testData.o
	gcc -g -o ColumnTest Column.o testColumn.o
	gcc -g -o TupleTest Data.o Tuple.o testTuple.o
	gcc -g -o TableAndColumnTest Table.o Column.o Tuple.o Data.o testColumnAndTable.o
	gcc -g -o VectorTest StringVector.o testVector.o

unit_test:
	make debug
	gcc -g -c UnitTest/testData.c UnitTest/testColumn.c UnitTest/testTuple.c UnitTest/testColumnAndTable.c UnitTest/testVector.c
	
debug:
	gcc -DDEBUG -c -g Model/Data.c Model/Column.c Model/Tuple.c Model/Table.c Model/Database.c Utilities/StringVector.c

clean:
	rm *.o
	rm *Test
