Стандарт языка С++: Стандарт ISO C++17 (/std:c++17). Нужно установить это в свойствах проекта.\
Программа запускается из консоли в папке со сборкой exe проекта: НазваниеРешения.exe -ffgeom txt -fpgeom geometry2d.txt -ffgrid txt -fpgrid grid2d_params.txt. Например: LabProject.exe -ffgeom txt -fpgeom geometry2d.txt -ffgrid txt -fpgrid grid2d_params.txt.\
В решение использованы модульные тесты BoostTest. Для сборки проекта с модульными тестами желателен Release, а не Debug.\
Описание входящих файлов:
1) Геометрия расчетной области:
* Geometry2D.h содержит описание структуры Geometry2D для хранения информации о геометрии расчетной области. Объявление функций для работы с геометрией, например, для чтения/записи данных;
* Geometry2D.cpp содержит реализаций функций, объявленных в Geometry2D.h. Код, отвечающий за загрузку, обработку и хранение данных о геометрии расчетной области.
2) Описание вычислительной системы:
*	ClusterNode.h содержит описание класса ClusterNode для представления узла вычислительного кластера. Объявление методов для работы с узлом, например, получение информации об устройствах, выделение/освобождение ресурсов и т.д.;
*	ClusterNode.cpp содержит реализация методов, объявленных в ClusterNode.h. Код, отвечающий за управление узлами кластера;
*	Cluster.h содержит описание класса Cluster для представления всего вычислительного кластера. Объявление методов для работы с кластером, например, добавление/удаление узлов, распределение работы между узлами и т.д.;
*	Cluster.cpp содержит реализация методов, объявленных в Cluster.h. Код, отвечающий за управление всем вычислительным кластером;
*	DeviceSpecs.h содержит описание классов GpuSpec, CpuSpec, RamSpec, LanSpec для представления характеристик устройств. Объявление методов для работы с характеристиками устройств;
*	DeviceSpecs.cpp содержит реализация методов, объявленных в DeviceSpecs.h. Код, отвечающий за хранение и управление характеристиками устройств;
*	VectorHCS.h и VectorHCS.cpp – содержат описание и реализацию соответственно класса VectorHCS для работы с векторами, распределенными по узлам кластера.
3) Матрицы:
*	Matrix.h содержит абстрактных класс от которого будут наследоваться BlockMatrix, DenseMatrix и DiagonalMatrix;
*	DenseMatrix.h и DenseMatrix.cpp - объявление методов и операторов для работы с плотными матрицами;
*	DiagonalMatrix.h и DiagonalMatrix.cpp- объявление методов и операторов для работы с диагональными матрицами;
*	BlockMatrix.h и BlockMatrix.cpp- объявление методов и операторов для работы с блочными матрицами, включая метод для умножения матриц Кронекера. Блоки матриц могут состоять как из плотных (DenseMatrix), так и из диагональных матриц (DiaginalMatrix).
Матричные операции для плотных и диагональных матриц поддерживаются только для матриц одинакового размера. Для диагональных матриц количество колонок и столбцов должно быть одинаковым. Для операций над блочными матрицами количество блоков по строкам и столбцам, строк и столбцов в самих матрицах должно совпадать соответственно с параметрами и в другой матрице. Все матричные операции возвращают матрицы.
4) Вспомогательные файлы:
*	AppParams.h и AppParams.cpp - описание класса AppParams для хранения параметров приложения для запуска из консоли;
*	main.cpp - точка входа в программу.
5) Тесты:
*	BoostTest/GeometryTests.cpp - модульные тесты для проверки корректности работы компонентов, связанных с геометрией расчетной области;
*	BoostTest/ClusterTests.cpp - модульные тесты для проверки корректности работы компонентов, связанных с вычислительным кластером;
*	BoostTest/DenseMatrixTests.cpp - модульные тесты для проверки корректности работы класса DenseMatrix;
*	BoostTest/DiagonalMatrixTests.cpp - модульные тесты для проверки корректности работы класса DiagonalMatrix;
*	BoostTest/BlockMatrixTests.cpp - модульные тесты для проверки корректности работы класса BlockMatrix, включая тесты для умножения матриц Кронекера;
*	BoostTest/VectorHCSTests.cpp  - модульные тесты для проверки корректности работы класса VectorHCS, реализовано скалярное произведение и умножение матриц на число.

Материалы:
1)	https://metanit.com/cpp/tutorial/7.14.php - использование библиотеки для карт в С++;
2)	https://iq.opengenus.org/unordered-map-cpp-stl/ - использование библиотеки STL «unordered_map»;
3)	https://www.geeksforgeeks.org/cpp-program-for-kronecker-product-of-two-matrices/ - произведение Кронекера двух матриц в C++;
4)	Использование iterator для std::map: https://stackoverflow.com/questions/26281979/how-do-you-loop-through-a-stdmap
5)	Снова про итераторы: https://metanit.com/cpp/tutorial/7.3.php
6)	Использование ассоциативных контейнеров: https://education.yandex.ru/handbook/cpp/article/associative-containers
7)	Про second и first в map: https://ci-plus-plus-snachala.ru/?p=3572 
8)	Использованы выбросы исключений с ошибками (библиотека stdexcept): https://www.studyplan.dev/pro-cpp/exception-types 
9)	Справочник по перегрузке операторов: https://en.cppreference.com/w/cpp/language/operators 
10)	Справочник по стандарту языка С++: https://scrutator.me/post/2017/10/07/cpp17_lang_features_p2.aspx?ysclid=m3z0kd0qgj432146158 
11)	Когда я читала статьи по созданию матриц мне попалась статья про шаблоны классов, там была реализована матрицы, от туда я взяла идею о модифицируемом и константном операторе () доступа в матрицах: https://education.yandex.ru/handbook/cpp/article/template-classes 
Вот еще одна ссылка по перегрузке: https://sysprog.ru/post/peregruzka-operatorov-v-yazyke-c#brace

12)	Использование initializer_list для заполнения матриц, очень удобная вещь, вот короткая статья про использование: https://en.cppreference.com/w/cpp/utility/initializer_list 
На этом сайте написана тоже неплохая статья: https://www.cppstories.com/2023/initializer_list_basics/ 
13)	Очень классная статья, связанная с логированием: https://htrd.su/blog/2016/03/15/std_cout_std_cerr_i_std_clog/
14)	Различные числовые типы данных я брала здесь: https://metanit.com/cpp/tutorial/2.3.php 
15)	Работа с классом std::vector: https://metanit.com/cpp/tutorial/7.4.php 
16)	Подробности  по подключению BoostTest: https://learn.microsoft.com/ru-ru/visualstudio/test/how-to-use-boost-test-for-cpp?view=vs-2022
17)	Использование BoostTest: https://www.boost.io/doc/user-guide/boost-test-tutorial.html
Еще одна ссылка: https://www.boost.org/doc/libs/1_32_0/libs/test/doc/components/test_tools/reference/BOOST_CHECK_EQUAL.html 
https://manpages.debian.org/jessie/mlpack-doc/old_boost_test_definitions.hpp.3 
18)	Boost Test и вылавливание ошибок из исключений в тестах (stdexcept):https://www.boost.org/doc/libs/master/libs/test/doc/html/boost_test/testing_tools/exception_correctness.html
19)	Статья про явные преобразования типов: https://metanit.com/cpp/tutorial/2.4.php 
20)	Явное объявление типов шаблона: https://habr.com/ru/articles/235831/ 
https://spec-zone.ru/cpp/language/class_template
21) Это про оформление README.md: https://skillbox.ru/media/code/yazyk-razmetki-markdown-shpargalka-po-sintaksisu-s-primerami/#stk-12
