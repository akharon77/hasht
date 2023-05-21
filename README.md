# Содержание
1. [Цель работы](#цель-работы)
2. [Введение](#введение)
	1. [Теоретическая справка](#теор-справка)
	2. [Постановка задачи](#постановка)
3. [Материалы и методы](#мат-и-мет)
	1. [Хеш-функции](#хеш-функции)
4. [Ход работы](#ход-работы)

# Цель работы  <a name="цель-работы"/>

Изучить устройство хеш-таблиц и способы их оптимизации на конкретной задаче поиска слов во множестве.

# Введение <a name="введение" />

## Теоретическая справка <a name="теор-справка" />

***Хеш-таблица*** - это структура данных, позволяющая отображать множество ключей на множество значений, то есть сопоставлять введённым ключам определенные значения.

Она позволяет осуществлять следующие операции:
1. Добавить пару ключ-значение в таблицу
2. Проверить наличие ключа в таблице и, если есть, получить значение по ключу

***Хеш-функция*** - это функция, с помощью которой и осуществляется отображение. Она принимает на вход ключ и выдаёт число, по которому во внутренней структуре хеш-таблицы осуществляется поиск элемента.

К сожалению, хеш-функция не всегда осуществляет однозначное отображение, она может для разных объектов выдать одинаковое число. Такая ситуация называется ***коллизией***.
Эта функция должна равномерно распределять множество ключей по таблице. Равномерно в данном случае обозначает то, что в таблице не должно быть больших скоплений элементов в одной части таблицы.

Для разрешения коллизий существует ***метод цепочек***. Он заключается в том, что в каждой ячейке таблицы мы храним список, в котором перечислены все элементы, имеющие данное значение хеша. Тогда при поиске элемента осуществляется вычисление хеша и поиск в соответствующем списке.

Таким образом, чтобы обеспечить низкое время доступа к элементу, необходимо делать длину списков такой маленькой, насколько это возможно.

Ещё одно важное понятие, к которому мы будем обращаться в работе в дальнейшем, это операция ***рехеширования***. Это происходит путём увеличения размера таблицы и перераспределения по ней уже имеющихся элементов. Эта процедура, в основном, используется для уменьшения длин итоговых списков. 

## Постановка задачи <a name="постановка" />

В рамках данной работы хеш-таблица будет рассматриваться не в качестве словаря, который позволяет по ключу получать значение, а в качестве множества, в котором можно быстро проверять наличие требуемого элемента. Таким образом, вместо пары ключ-значение будет использоваться всего лишь ключ, так как значение с ним совпадает. 

Работа состоит из двух частей. В **первой части** исследуется набор хеш-функций, конкретно то, как они распределяют введенные ключи по таблице. 
Во **второй части** производится оптимизация работы хеш-таблицы на тесте, заключающемся в поиске случайных слов по таблице.

# Материалы и методы <a name="мат-и-мет" />

## Хеш-функции <a name="хеш-функции" />

Для анализа были выбраны следующие хеш-функции:
1. **const** - функция, возвращающая всегда число 1
2. **first_char** - возвращает ASCII-код первого символа строки
3. **strlen** - возвращает длину строки
4. **sum_char** - возвращает сумму ASCII-кодов символов строки
5. **rotr** - функция, устроенная следующим образом:

Пусть `h[0] = 0`. Тогда `h[i] = ROTR(h[i - 1]) XOR str[i - 1]`, где

`ROTR` - функция, осуществляющая циклический побитовый сдвиг вправо. Например, 8-битное беззнаковое число 43, которое имеет в двоичной записи вид 00101011, превращается в 10010101, равное 149
 
 `str` - строка, хеш которой считается
 
 В итоге хеш-функция **hash_rotr** возвращает `h[n]`, где `n` - длина строки

6. **rotl** - функция, аналогичная предыдущей, только с использованием циклического побитового сдвига влево
7. **crc32** - расшифровка: **C**yclic **R**edundancy **C**ode, или циклический избыточный код

Для ознакомления с последней хеш-функцией заинтересованному читателю предлагается прочитать следующие материалы:
- [A painless guide to CRC error detection algorithms](http://www.ross.net/crc/download/crc_v3.txt)
- [Английская википедия](https://en.wikipedia.org/wiki/Computation_of_cyclic_redundancy_checks)

В статье не будет описан принцип работы последней функции, как и не будет поясняться код для её вычисления. Так же будет использоваться тот факт, что инженеры процессоров за нас предусмотрели аппаратную возможность вычисления этой функции
	
# Ход работы <a name="ход-работы" />

1. Была реализована хеш-таблица с использованием cache-friendly списков, написанных отдельным проектом в первом семестре
2. Списки были переписаны с идеей собственного аллокатора, то есть отдельной структуры, которая отвечает за выделение памяти под элементы массива в едином связном куске памяти
3. Хеш-таблица была протестированы с использованием набора функций, представленных выше
4. Длины каждого из списков были записаны в отдельный файл и представлены в виде столбчатых диаграмм
5. Были произведены повторные замеры с увеличенным размером таблицы
6. Была выбрана наиболее оптимальная хеш-функция под задачу
7. На хеш-таблице с выбранной хеш-функцией были произведены тесты по поиску элементов
8. Полученные результаты записаны как результаты ***базовой версии***
9. Произведено профилирование ***базовой версии*** с целью выявления наиболее времязатратных мест программы. 

*Пояснение*: в дальнейшем шаги записи результатов теста и профилирования программы после них предполагаются по умолчанию

10. Была переписана структура хранения слов в программе и функция поиска элемента в таблице, в частности часть процедуры сравнения строк
11. Полученная ***оптимизированная версия номер 1*** перетестирована
12. Была переписана функция хеширования
13. Полученная ***оптимизированная версия номер 2*** перетестирована
14. Была переписана функция определения длины строки и в связи с этим также была оптимизирована логика функции хеширования
15. Полученная ***оптимизированная версия номер 3*** перетестирована
16. Все результаты тестирования были внесены в общую таблицу для сравнения и определения ускорения, которого мы добились в ходе оптимизаций
17. Получен вывод и идеи по дальнейшей оптимизации хеш-таблиц