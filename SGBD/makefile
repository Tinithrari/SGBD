application_test:
	make unit_test
	gcc -g -o DataTest Data.o testData.o
	gcc -g -o ColumnTest Column.o testColumn.o
	gcc -g -o TupleTest Tuple.o testTuple.o
	gcc -g -o TableAndColumnTest Table.o Column.o Tuple.o Data.o testColumnAndTable.o

unit_test:
	make debug
	gcc -c UnitTest/testData.c UnitTest/testColumn.c UnitTest/testTuple.c UnitTest/testColumnAndTable.c
	
debug:
	gcc -DDEBUG -c Model/Data.c Model/Column.c Model/Tuple.c Model/Table.c

clean:
	del *.o
	del *.exe
