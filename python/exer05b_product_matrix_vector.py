'''
MATRIX-MATRIX MULTIPLICATION (DOT PRODUCT)
'''

import threading



def get_scalar_product(u: list, v: list):
    s = sum(a * b for a, b in zip(u, v))
    return s



def scalar_thfunc(u: list, v: list, res: list, idx_res: int):
    scalar_prod = get_scalar_product(u, v)
    res[idx_res] = scalar_prod



def get_transpose_matrix(mat: list[list]) -> list[list]:
    num_row = len(mat)
    num_col = len(mat[0])

    res = [[0] * num_row for _ in range(num_col)]

    for i in range(num_row):
        for j in range(num_col):
            res[j][i] = mat[i][j]

    return res



def get_str_matrix(mat: list[list]):
    return '\n'.join(
        ' '.join(f'{val:>5}' for val in row)
        for row in mat
    )



def get_product(mata: list[list], matb: list[list]) -> list[list]:
    # Assume that size of mat and vec are both eligible
    size_row_a = len(mata)
    size_col_b = len(matb[0])

    res = [[0] * size_col_b for _ in range(size_row_a)]
    matbt = get_transpose_matrix(matb)
    lstth = []

    for i in range(size_row_a):
        for j in range(size_col_b):
            lstth.append(
                threading.Thread(target=scalar_thfunc, args=(mata[i], matbt[j], res[i], j))
            )

    for th in lstth:
        th.start()

    for th in lstth:
        th.join()

    return res



A = [
    [ 1, 3, 5 ],
    [ 2, 4, 6 ]
]

B = [
    [ 1, 0, 1, 0 ],
    [ 0, 1, 0, 1 ],
    [ 1, 0, 0, -2 ]
]

result = get_product(A, B)

print(get_str_matrix(result))
