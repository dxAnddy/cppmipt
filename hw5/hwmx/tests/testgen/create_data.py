import numpy as np

def generate_matrix(n, target_det):
    M = np.eye(n)
    M[0, 0] = target_det
    for _ in range(5 * n):
        i, j = np.random.choice(n, 2, replace = False)
        M[i] += M[j] * np.random.choice([-2, -1, 1, 2])

    np.random.shuffle(M)
    if(round(np.linalg.det(M)) != target_det):
        M[0] *= -1
    return M

def main():
    S = generate_matrix(15, 700)
    print(np.linalg.det(S))
    print(S)

if __name__ == "__main__":
    main()