# lab-1-polinom

## Cостав команды 
* [Балдин Андрей](https://github.com/Andrew-8705)
* [Левонычев Иван](https://github.com/fartekool)
* [Лукин Иван](https://github.com/elus10n)

# 1. Общие положения
## 1.1. Назначение
Программная система предназначена для выполнения алгебраических операций над полиномами, хранящимися в таблицах под уникальными именами.
## 1.2. Область применения
Система может быть использована в образовательных целях для изучения алгебры, а также в научных исследованиях, где требуется работа с полиномами.

# 2. Требования к системе
## 2.1. Функциональные требования
### Хранение полиномов
- Полиномы должны храниться в виде списка.
- Каждый полином должен иметь уникальное имя (ключ).
- Все полиномы должны храниться одновременно в 6 различных структурах данных (таблицах):
  - Линейная таблица на массиве
  - Линейная таблица на списке
  - Упорядоченная таблица на массиве
  - Дерево (АВЛ или красно-черное)
  - Хеш-таблица с открытой адресацией
  - Хеш-таблица со списками

### Операции над отдельным полиномом
- Вычисление значения полинома в заданной точке (x, y, z).
- Умножение полинома на константу.
- Вычисление частной производной полинома по каждой из переменных (x, y, z).
- Вычисление интеграла полинома по каждой из переменных (x, y, z).

### Операции над выражениями из полиномов
- Сложение полиномов.
- Вычитание полиномов.
- Умножение полинома на константу.
- Умножение полиномов.
- Деление полиномов.
  
### Операции над таблицами
- Добавление нового полинома во все таблицы одновременно.
- Удаление полинома из всех таблиц одновременно по его имени.
- Поиск полинома в активной таблице по имени (используется при вычислении выражений, составленных из имён полиномов).

### Интерфейс пользователя
- Возможность выбора активной таблицы для отображения и операций.
- Таблица должна выводиться на экран в формате, как минимум, двух столбцов: 1) имя полинома, 2) строковое представление полинома.
- Ввод выражений для вычисления.
- Вывод результатов вычислений.
- Сообщения об ошибках (например, при попытке деления на ноль, отсутствии полинома в таблице и т.д.).

### Примеры
1. Исходные данные:
   
   Пусть в таблице хранятся следующие полиномы:
   
| Имя    | Полином                               |
| :----- | :------------------------------------ |
| pol1   | 3.2x^2y^3z^1 – 1.3x^1z^4              |
| pol2   | –3.2x^2y^3z^1 + 1.3x^1z^4             |
| const6 | 6.0                                   |
| q      | 4.0x^2                                |

2. Ввод выражения:
   
   Пользователь вводит следующее выражение для вычисления: \
   __new_pol = 2 * pol1 + 2 * pol2 + 3.6 * q – const6__

3. Обработка и вывод:

- Находит в активной таблице полиномы __pol1, pol2, q и const6__.
- Вычисляет значение выражения, подставляя значения полиномов.
- Формирует новый полином __new_pol = 14.4x^2 – 6.0__.
- Добавляет новый полином __new_pol__ во все таблицы.
- Выводит результат на экран:
     
| Имя     | Полином             |
| :------ | :------------------ |
| new_pol | 14.4x^2 – 6.0       |

4. Примеры ошибок:
- __Ошибка: Деление на ноль.__ \
  Пользователь вводит выражение __pol1 / 0__. \
  Система выводит сообщение об ошибке: __"Ошибка: Деление на ноль."__
  
- __Ошибка: Полином не найден.__ \
  Пользователь вводит выражение __pol3 + pol1__, где __pol3__ отсутствует в таблице. \
  Система выводит сообщение об ошибке: __"Ошибка: Полином 'pol3' не найден в таблице."__
  
# 3. Технические требования
- Язык программирования: C++.
- Среда разработки: Visual Studio.
- Платформа: Windows.

# 4. Этапы разработки
- Проектирование: Разработка детальной структуры программы, выбор алгоритмов и структур данных.
- Реализация: Написание кода программы на выбранном языке программирования.
- Тестирование: Проведение тестирования для выявления и исправления ошибок.
- Документация: Создание документации, описывающей работу с программой.


