# Авиаперелёты
### Задание
Главного конструктора Петю попросили разработать новую модель самолёта для компании «Air Бубундия». Оказалось, что самая 
сложная часть заключается в подборе оптимального размера топливного бака.
Главный картограф «Air Бубундия» Вася составил подробную карту Бубундии. На этой карте он отметил расход топлива для 
перелёта между каждой парой городов.
Петя хочет сделать размер бака минимально возможным, для которого самолёт сможет долететь от любого города в любой другой 
(возможно, с дозаправками в пути).
### Формат ввода
Первая строка входного файла содержит натуральное число n — число городов в Бубундии. Далее идут n строк по n чисел 
каждая. j-е число в i-й строке равно расходу топлива при перелёте из i-го города в j-й. Все числа не меньше нуля и 
меньше 10^9. Гарантируется, что для любого i в i-й строчке i-е число равно нулю.
### Формат вывода
Первая строка выходного файла должна содержать одно число — оптимальный размер бака.
### Пример
#### Ввод
```
4
0 10 12 16
11 0 8 9
10 13 0 22
13 10 17 0

```
#### Вывод
```
10
```