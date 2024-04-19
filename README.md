# game-of-life

Игра жизнь.
Для запуска exe файл life.

# Отчет: 
В репозитории представлена реализация игры Жизнь на с++.

# Описание алгоритма
Для игры используется поле размера m*n, которое представляет собой двумерный массив клеток. Клетка - структура содержащая коорданаты и информацию о том, жива клетка или нет.

В начале игры задается стартовый массив клеток, которые размещаются на поле. Для удобства к полю добавляется рамка из всегда мертвых клеток. Теперь при подсчете соседей у крайних клеток не придется проверять граничные условия.

Далее для каждой клетки на поле вычисляется статус 8 ее соседей в соответсвии с правилами игры. И если клетка должа умереть или наоборот ожить, она записывается в вектор клеток подлежащих изменению. Далее меняется статус нужных клеток и получается новое поколение. 

Сложность этого алгоритма для смены одного поколения O(m*n).
