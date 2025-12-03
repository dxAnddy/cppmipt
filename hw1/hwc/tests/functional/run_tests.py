import subprocess
import os
from pathlib import Path

BASE_DIR = Path(__file__).resolve().parent
PROJECT_ROOT = BASE_DIR.parents[1]
BUILD_DIR = PROJECT_ROOT / 'build'
DATA_DIR = BASE_DIR / 'data'
BINARY_PATH = BUILD_DIR / 'cache_lru'

BUILD_DIR.mkdir(exist_ok = True)

subprocess.run(["cmake", ".."], cwd = BUILD_DIR, check = True)

subprocess.run(['make'], cwd = BUILD_DIR, check = True)

i = 1
while(True):
    dat = DATA_DIR / f"{i:03d}.dat"
    ans = DATA_DIR / f"{i:03d}.ans"

    if not dat.exists() or not ans.exists():
        break
    
    with open(dat, 'r', encoding = 'utf-8') as f:
        input_data = f.read()
    
    result = subprocess.run([str(BINARY_PATH)], input = input_data, text = True, capture_output = True).stdout.strip()

    with open(ans, 'r', encoding = 'utf-8') as f:
        expected = f.read().strip()
    
    if result == expected:
        print(f"Test number: {i:03d} passed")
    else:
        print(f"Test number: {i:03d} failed")
        print(f"Expected: {expected}")
        print(f"Got: {result}")
        raise AssertionError("Test number: {i:03d} failed")
    i += 1

