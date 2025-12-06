import subprocess
import random
import sys
import matplotlib.pyplot as plt
import numpy as np
from pathlib import Path

"""
graph_comprasion.py

Данная программа выполняет сравнение трёх реализаций кэша:
ARC, LRU и OPT (алгоритм Белади).

Она:
- собирает бинарники через CMake,
- генерирует workload с горячим и холодным набором,
- запускает все кэши для разных размеров,
- строит график Hit Ratio vs. Cache Size,
- сохраняет график в файл и выводит результаты на экран.

"""

BASE_DIR = Path(__file__).resolve().parents[1]
BUILD_DIR = BASE_DIR / 'build'

BUILD_DIR.mkdir(exist_ok = True)

BINARIES = {
    "ARC": BUILD_DIR / "cache_arc",
    "LRU": BUILD_DIR / "cache_lru",
    "OPT": BUILD_DIR / "cache_opt"
}

# -----------------------------
# Сборка через CMake
# -----------------------------
def build_cmake():
    print("Запуск CMake и сборка бинарников...")
    try:
        subprocess.run(["cmake", str(BASE_DIR)], cwd=BUILD_DIR, check=True)
        subprocess.run(["make"], cwd=BUILD_DIR, check=True)
        print("Сборка завершена успешно.")
    except subprocess.CalledProcessError as e:
        print("Ошибка при сборке:")
        sys.exit(1)

# -----------------------------
# Запуск бинарника
# -----------------------------
def run_program(exe_path, cache_size, accesses):
    input_data = f"{cache_size} {len(accesses)}\n" + " ".join(map(str, accesses)) + "\n"
    
    try:
        result = subprocess.run(
            [exe_path],
            input=input_data.encode(),
            stdout=subprocess.PIPE,
            stderr=subprocess.PIPE,
            check=True
        )
    except subprocess.CalledProcessError as e:
        print(f"Ошибка при запуске {exe_path}:")
        print(e.stderr.decode())
        sys.exit(1)
    
    return int(result.stdout.decode().strip())

# -----------------------------
# Генерация паттерна доступа
# -----------------------------
def generate_workload(total_accesses, hot_size, cold_size, hot_freq=0.8):
    hot_set = list(range(1, hot_size + 1))
    cold_set = list(range(hot_size + 1, hot_size + cold_size + 1))
    
    accesses = [random.choice(hot_set) if random.random() < hot_freq
                else random.choice(cold_set) for _ in range(total_accesses)]
    return accesses

# -----------------------------
# Основной тест
# -----------------------------
def main():
    build_cmake()

    total_accesses = 100_000
    hot_size = 1000
    cold_size = 3000
    hot_freq = 0.8
    

    min_cache_size = 50
    max_cache_size = 2000
    cache_sizes = sorted(list({int(2**exp) for exp 
        in np.linspace(np.log2(min_cache_size), np.log2(max_cache_size), 30)}))
    
    programs = {
        "ARC": "./cache_arc",
        "LRU": "./cache_lru",
        "OPT": "./cache_opt"
    }
    
    accesses = generate_workload(total_accesses, hot_size, cold_size, hot_freq)
    
    results = {name: [] for name in BINARIES}
    
    for cache_size in cache_sizes:
        print(f"\n=== cache_size = {cache_size} ===")
        for name, exe in BINARIES.items():
            hits = run_program(exe, cache_size, accesses)
            hit_rate = hits / total_accesses * 100
            results[name].append(hit_rate)
            print(f"{name}: {hit_rate:.2f}% ({hits} hits)")
    
    plt.figure(figsize=(12, 7))
    ax = plt.gca()

    colors = {'ARC': 'blue', 'LRU': 'green', 'OPT': 'red'}
    
    for name in BINARIES:
        ax.plot(cache_sizes, results[name], label = name, linewidth = 2.5,
                marker = 'o', markersize = 6, color = colors[name])
    
    ax.set_title("Hit Ratio vs. Cache Size\n(80% accesses to hot set, 20% to cold set)", fontsize = 16, fontweight='bold')
    ax.set_xlabel("Cache Size (entries)", fontsize = 14)
    ax.set_ylabel("Hit Ratio (%)", fontsize = 14)
    
    ax.set_xscale('log')
    
    tick_positions = cache_sizes[::5]
    ax.set_xticks(tick_positions)
    ax.set_xticklabels([str(x) for x in tick_positions], rotation=45)
    
    ax.grid(which = 'major', linestyle = '--', alpha = 0.6)
    
    ax.legend(fontsize=15, loc='lower right')
    plt.tight_layout()
    
    output_file = "cache_size_comparison.png"
    plt.savefig(output_file, dpi = 300)
    print(f"\nГрафик сохранён как {output_file}")
    plt.show()
    

if __name__ == "__main__":
    main()