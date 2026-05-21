import numpy as np

def read_matrix_from_file(filename):
    with open(filename, 'r') as file:
        n = int(file.readline().strip())
        matrix = np.zeros((n, n))
        for i in range(n):
            row = list(map(float, file.readline().strip().split()))
            matrix[i] = row
    return matrix

# Чтение матриц
A = read_matrix_from_file('matrix_A.txt')
B = read_matrix_from_file('matrix_B.txt')
C_cpp = read_matrix_from_file('result_matrix.txt')

# Вычисление правильного результата
C_correct = np.dot(A, B)

# Сравнение с допуском на погрешность
tolerance = 1e-10
difference = np.max(np.abs(C_cpp - C_correct))

if difference < tolerance:
    print("Verification PASSED: Results match within tolerance")
else:
    print(f"Verification FAILED: Maximum difference = {difference}")

print(f"Maximum difference: {difference}")
