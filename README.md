# post_machine
Машина Поста состоит из каретки (или считывающей и записывающей головки) и разбитой на ячейки бесконечной в обе стороны ленты. Каждая ячейка ленты может находиться в 2 состояниях — быть либо пустой — 0, либо помеченной меткой 1. За такт работы машины каретка может сдвинуться на одну позицию влево или вправо, считать, изменить символ в своей текущей позиции.

Работа машины Поста определяется программой, состоящей из конечного числа строк. Для работы машины нужно задать программу и её начальное состояние (то есть состояние ленты и позицию каретки). Кареткой управляет программа, состоящая из пронумерованных не обязательно упорядоченных строк команд, если в каждой команде указана строка, на которую нужно перейти. Обычно принимается, что если в команде переход не указан, то переход происходит на следующую строку. Каждая команда имеет следующий синтаксис:

i. K j
где i — номер команды, K — действие каретки, j — номер следующей команды (отсылка).

Всего для машины Поста существует шесть типов команд:

V j — поставить метку, перейти к j-й строке программы;
X j — стереть метку, перейти к j-й строке;
← j — сдвинуться влево, перейти к j-й строке;
→ j — сдвинуться вправо, перейти к j-й строке;
? j1; j2 — если в ячейке нет метки, то перейти к j1-й строке программы, иначе перейти к j2-й строке;
! — конец программы («стоп», останов).

# Example
1. ←      — шаг влево
2. ? 1; 3 — если в ячейке пусто, перейти к 1-шагу, если нет — к 3
3. X      — удалить метку
4. →      — шаг вправо
5. ? 4; 6 — если в ячейке пусто, перейти к 4-шагу, если нет — к 6
6. X      — удалить метку
7. →      — шаг вправо
8. ? 9; 1 — если в ячейке пусто, перейти к 9 шагу, если нет — к 1
9. !      — конец
