# SelSQL
[![Status](https://github.com/quiksilver4210/SelSQL/workflows/Tests/badge.svg)](https://github.com/quiksilver4210/SelSQL/actions)

## Участники
- Хачатрян Илья https://github.com/quiksilver4210
- Пенюгин Антон https://github.com/antons201
- Михайленко Антон https://github.com/sapiest
## Документация
**SelSQL** – СУБД, разрабатываемая студентами 3 курса ПМИ.

Поддерживаемые команды:

1\.	**CREATE TABLE table_name (col_name col_type constraints, …);**  

Создает новую таблицу. ***table_name*** – название таблицы, ***col_name*** – название колонки, ***col_type*** – тип содержимого колонки таблицы, ***constraints*** – ограничения.

В названии таблицы и колонки (***table_name, col_name***) можно использовать латинские заглавные и строчные буквы, а также цифры. Ограничение по длине – 256 символов(строки большей длины будут обрезаны).

Доступные типы содержимого ячеек таблицы (***col_type***): 
* INT – целочисленные значения, 
* FLOAT – числа с плавающей точкой, 
* CHAR(n) – строка(n - длина строки), 
* BOOLEAN – логические значения.

Доступные ограничения (***constraints***):
* NOT NULL – содержимое ячейки в колонке не может быть NULL, 
* UNIQUE - содержимое ячейки в колонке должно быть уникальным, 
* PRIMARY KEY – первичный ключ. Однозначно идентифицирует каждую строку/запись в таблице.

Если PRIMARY KEY указать сразу у нескольких столбцов, то ключ будет составным. 
Названия колонок в одной таблице повторяться не могут. Два раза указывать одно и то же ограничение для одного столбца нельзя. 

2\. **SHOW CREATE TABLE table_name;**

Показывает оператор CREATE TABLE, который будет создавать данную таблицу (с названием ***table_name***).
Ограничение на использование символов в названии таблицы(***table_name***) аналогичны вышеперечисленным.

3\.	**DROP TABLE table_name;**

Удаляет таблицу с названием ***table_name***. 
Ограничение на использование символов в названии таблицы(***table_name***) аналогичны вышеперечисленным.

4\. **SELECT col_name1, col_name2,... FROM table_name;** 

Выполняет выборку данных из таблицы. ***col_name*** - колонки, значения которых необходимо вывести.
Если необходимо вывести значения во всех колонках, то необходимо использовать символ *.
***table_name*** - таблица, из которой производится выборка. 

5\. **INSERT INTO table_name (col_name1, col_name2,...) VALUES (val1, val2, ...);**

Вставляет значения в таблицу с названием ***table_name***. ***col_name*** - колонки, в которые мы хотим 
добавить значения. Если указать не все колонки, существующие в таблице, то в оставшиеся заишется NULL. 
Если необходимо записать данные во все колонки, то указывать список колонок не обязательно, в таком 
случае запрос будет выглядеть следующим образом: ***INSERT INTO table_name VALUES (val1, val2, ...);***
В колонки с ограничениями NOT NULL или PRIMARY KEY значения добавлять обязательно.<br>
***val*** - значения, которые будут добавлены в таблицу в соответствии с указанными колонками. 
Значения должны соответствовать типам добавляемых колонок и их ограничениям. Число значений должно быть
равно числу перечисленных колонок(либо числу существующих колонок, если они не указываюстя в запросе).

6\. **DELETE FROM table_name;**

Удаляет строки из таблицы ***table_name***.

7\. **UPDATE table_name SET col_name1 = val1, ...;**

Обновляет значения колонок ***col_name*** в таблице с названием ***table_name***. 
***col_name*** - обновляемые колонки, ***val*** - новое значение для колонки ***col_name***.
Значения должны соответствовать типам обновляемых колонок и их ограничениям.

К командам 4, 6, 7 также можно добавлять условие ***WHERE***. Оно позволяет производить действия не над
всей таблицей, а только над строками, подходящими под условия. 

Структура условия ***WHERE***:<br>
WHERE expr sign expr logic not expr sign expr

expr - выражение, которое может включать в себя арифметические операции (+, -, *, /) над числам и значениями
колонок. Разрешено использовать скобки. sign - знак неравенства(=, !=, >, <, >=, <=). logic - логическая
операция(and, or), применяемая к двум выражениям вида expr sign expr. Для логических операций также разрешены 
скобки. not - отрицание выражения. Использование арифметических, логических операций, отрицания не обязательно.
К строкам арифметические операции применять нельзя. Условие WHERE пишется после запроса(но до ;). <br>
Пример корректного запроса: ***SELECT \* FROM t WHERE (id = 2+2*2 or name != 'Vasya') and NOT(age + 5 = 8);**

**Установка.  
GOOGLE TESTS.**
1. Скачать библиотеку. https://github.com/google/googletest
2. Распаковать в пакет {project_name}/lib

