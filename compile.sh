echo "Очистка прошлых генераций"
if [ -f ./graph_compiler_optimized_pro-graph_unoptimized.gcda ]; then
	rm ./graph_compiler_optimized_pro-graph_unoptimized.gcda 
fi

if [ -f ./graph_max_optimized_pro-graph_optimized.gcda ]; then
	rm ./graph_max_optimized_pro-graph_optimized.gcda 
fi

if [ -f ./graph_unoptimized ]; then
	rm ./graph_unoptimized 
fi
if [ -f ./graph_compiler_optimized ]; then
	rm ./graph_compiler_optimized 
fi

if [ -f ./graph_compiler_optimized_pro ]; then
	rm ./graph_compiler_optimized_pro 
fi

if [ -f ./graph_max_optimized ]; then
	rm ./graph_max_optimized 
fi

if [ -f ./graph_max_optimized_pro ]; then
	rm ./graph_max_optimized_pro 
fi

echo "Компиляция кода без оптимизации"
g++ graph_unoptimized.cpp -std=c++20 -o graph_unoptimized
echo "Компиляция кода с оптимизации с помощью компилятора без профиля"
g++ graph_unoptimized.cpp -std=c++20 -O3 -fprofile-generate -march=native -o graph_compiler_optimized_pro
echo "Создание профиля программы без векторизации"
./graph_compiler_optimized_pro > /dev/null
./graph_compiler_optimized_pro > /dev/null
./graph_compiler_optimized_pro > /dev/null
./graph_compiler_optimized_pro > /dev/null
./graph_compiler_optimized_pro > /dev/null
cp ./graph_compiler_optimized_pro graph_compiler_optimized
if [ -f ./graph_compiler_optimized_pro-graph_unoptimized.gcda ]; then
	echo "Компиляция кода с оптимизацией с помощью компилятора с профилем"
	g++ graph_unoptimized.cpp -std=c++20 -O3 -fprofile-use -march=native -o graph_compiler_optimized_pro
fi

echo "Компиляция кода с оптимизации с помощью компилятора и векторизации без профиля"
g++ graph_optimized.cpp -std=c++20 -O3 -fopenmp -fprofile-generate -march=native -o graph_max_optimized_pro
echo "Создание профиля программы с векторизацией"
./graph_max_optimized_pro > /dev/null
./graph_max_optimized_pro > /dev/null
./graph_max_optimized_pro > /dev/null
./graph_max_optimized_pro > /dev/null
./graph_max_optimized_pro > /dev/null
cp ./graph_max_optimized_pro graph_max_optimized
if [ -f ./graph_max_optimized_pro-graph_optimized.gcda ]; then
	echo "Компиляция кода с оптимизации с помощью компилятора и векторизации с профилем"
	g++ graph_optimized.cpp -std=c++20 -O3 -fopenmp -fprofile-use -march=native -o graph_max_optimized_pro
fi

echo "Выполнение программы без оптимизации:"
./graph_unoptimized

echo "Выполнение программы c оптимизацией с помощью компилятора без профиля:"
./graph_compiler_optimized
echo "Выполнение программы c оптимизацией с помощью компилятора с профилем:"
./graph_compiler_optimized_pro

echo "Выполнение программы c оптимизацией с помощью компилятора и векторизацией без профиля:"
./graph_max_optimized
echo "Выполнение программы c оптимизацией с помощью компилятора с профилем:"
./graph_max_optimized_pro