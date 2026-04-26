import numpy as np
import os

def get_prime_factors(n):
    if n == 0:
        return 0
    if abs(n) == 1:
        return [1] if n == 1 else [-1]

    factors = []
    num = abs(n)
    while(num % 2 == 0):
        factors.append(2)
        num //= 2
    p = 3
    while p * p <= num:
        while num % p == 0:
            factors.append(p)
            num //= p
        p += 2

    if num > 1:
        factors.append(num)

    if n < 0:
        factors[0] = -factors[0]
    return factors

def get_diag_factors(target_det, n):

    if target_det == 0:
        return [0] + [1] * (n - 1)

    factors = get_prime_factors(target_det)

    while(len(factors) > n):
        idx1, idx2 = np.random.choice(len(factors), 2, replace = False)
        product = factors[idx1] * factors[idx2]
        factors = [factors[i] for i in range(len(factors)) if i not in (idx1, idx2)]
        factors.append(product)

    while(len(factors) < n):
        factors.append(1)

    np.random.shuffle(factors)
    return factors    


def generate_matrix(n, target_det):
    diag = get_diag_factors(target_det, n)
    M = np.diag(diag)
    
    for _ in range(7 * n):
        i, j = np.random.choice(n, 2, replace = False)
        M[i] += M[j] * np.random.choice([-2, -1, 1, 2])

    np.random.shuffle(M)
    if(round(np.linalg.det(M)) != target_det):
        M[0] *= -1
    return M

def save_matrix(M, det, index, output_dir = "../e2e"):
    os.makedirs(output_dir, exist_ok = True)

    filename = f"{index:03d}"
    n = M.shape[0]

    dat_path = os.path.join(output_dir, f"{filename}.dat")
    with open(dat_path, 'w') as fd:
        fd.write(f"{n}\n")
        for i in range(n):
            for j in range(n):
                fd.write(f"{M[i][j]} ")
            fd.write("\n")

    ans_path = os.path.join(output_dir, f"{filename}.ans")
    with open(ans_path, 'w') as fa:
        fa.write(f"{det}")

def main():
    file_index = 0
    for i in range(10, 101, 10):
        det = np.random.randint(-30, 30)
        while det == 0:
            det = np.random.randint(-30, 30)
        M = generate_matrix(i, det)
        save_matrix(M, det, file_index)
        file_index += 1

if __name__ == "__main__":
    main()