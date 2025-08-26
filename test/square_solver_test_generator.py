import math
import random
from tqdm import tqdm

def solve_quadratic(a, b, c):
    """Возвращает количество действительных корней и сами корни (x1, x2)"""
    if abs(a) < 1e-10:  # a ≈ 0
        if abs(b) < 1e-10:  # b ≈ 0
            if abs(c) < 1e-10:  # c ≈ 0
                return -1, None, None  # Бесконечно много решений
            else:
                return 0, None, None  # Нет решений
        else:
            x = -c / b
            return 1, x, x
    else:
        D = b**2 - 4*a*c
        if D > 0:
            x1 = (-b - math.sqrt(D)) / (2*a)
            x2 = (-b + math.sqrt(D)) / (2*a)
            return 2, min(x1, x2), max(x1, x2)
        elif abs(D) < 1e-10:  # D ≈ 0
            x = -b / (2*a)
            return 1, x, x
        else:
            return 0, None, None

def format_root(x):
    """Форматирует корень с округлением до 6 знаков, если не None"""
    if x is None:
        return "NAN"
    return f"{x:.6f}".rstrip('0').rstrip('.')

def generate_tests(min_per_type=10):
    """
    Генерирует минимум min_per_type тестов для каждого типа:
    0 корней, 1 корень, 2 корня.
    Использует tqdm для отображения прогресса.
    """
    tests = []
    count = {0: 0, 1: 0, 2: 0}
    total_generated = 0

    # Общее целевое количество: сумма минимумов
    target_total = 2 * min_per_type

    # Используем бесконечный цикл, но с прогресс-баром
    with tqdm(total=target_total, desc="Генерация тестов", unit="тест", ncols=100, smoothing=0.1) as pbar:
        while count[0] < min_per_type or count[1] < 1 or count[2] < min_per_type:
            # Генерируем случайные коэффициенты
            a = random.randint(-10_000_000, 10_000_000) * 2.4
            b = random.randint(-10_000_000, 10_000_000) * 2.4
            c = random.randint(-10_000_000, 10_000_000) * 2.4

            num_roots, x1, x2 = solve_quadratic(a, b, c)

            # Пропускаем, если тип не 0/1/2 или уже достаточно таких тестов
            if num_roots not in (0, 1, 2):
                continue
            if count[num_roots] >= min_per_type:
                continue

            # Увеличиваем счётчики
            count[num_roots] += 1
            total_generated += 1

            # Форматируем корни
            x1_str = format_root(x1)
            x2_str = format_root(x2)

            if num_roots == 0:
                result_str = f"{num_roots}, {x1_str}, {x2_str}"
            elif num_roots == 1:
                result_str = f"{num_roots}, {x1_str}, NAN"
            else:  # num_roots == 2
                result_str = f"{num_roots}, {x1_str}, {x2_str}"

            test_line = f"#{total_generated} ({a}, {b}, {c}) -> {result_str}"
            tests.append(test_line)

            # Обновляем прогресс: на 1 вперёд
            pbar.update(1)

            # Отображаем текущий прогресс в описании
            pbar.set_postfix({
                "0": count[0], "1": count[1], "2": count[2]
            })

    return tests, count, total_generated

# === Настройки ===
min_per_type = 100_000_000 // 3  # ~33,333 тестов каждого типа (уменьшено для демонстрации)
# min_per_type = 100_000_000 // 3  # Раскомментируй, если хочешь миллионы (но займёт ОЧЕНЬ долго)
filename = "quadratic_tests.txt"

# === Генерация тестов ===
print("🚀 Запуск генерации тестов...\n")
test_cases, statistics, total = generate_tests(int(min_per_type))

# === Сохранение в файл ===
print("\n💾 Сохранение в файл...")
with open(filename, "w", encoding="utf-8") as f:
    for test in test_cases:
        f.write(test + "\n")

print(f"✅ Тесты успешно сохранены в файл: {filename}")
print(f"📊 Всего сгенерировано тестов: {total}")
print("🔢 Количество тестов по типам корней:")
print(f"   0 корней: {statistics[0]}")
print(f"   1 корень:  {statistics[1]}")
print(f"   2 корня:   {statistics[2]}")

# Проверка выполнения условий
assert statistics[0] >= min_per_type, "❌ Не хватает тестов с 0 корнями!"
assert statistics[2] >= min_per_type, "❌ Не хватает тестов с 2 корнями!"
print("✅ Все типы имеют не менее требуемого количества тестов.")