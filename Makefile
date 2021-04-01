build:
	g++ -g main.cpp SingleRune.cpp WyrdRune.cpp -o rreader.bin -lsfml-graphics -lsfml-window -lsfml-system
	echo "Done successfully..."