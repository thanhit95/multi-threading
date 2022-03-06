'''
MATRIX-VECTOR MULTIPLICATION
'''

import threading



def get_scalar_product(u: list, v: list):
    s = sum(a * b for a, b in zip(u, v))
    return s



def scalar_thfunc(u: list, v: list, res: list, idx_res: int):
    scalar_prod = get_scalar_product(u, v)
    res[idx_res] = scalar_prod



def get_product(mat: list[list], vec: list) -> list:
    # Assume that size of mat and vec are both eligible
    size_row_mat = len(mat)
    # size_col_mat = len(mat[0])
    # size_vec = len(vec)

    res = [0] * size_row_mat
    lstth = []

    for i in range(size_row_mat):
        lstth.append(threading.Thread(target=scalar_thfunc, args=(mat[i], vec, res, i)))

    for th in lstth:
        th.start()

    for th in lstth:
        th.join()

    return res



A = [
    [ 1, 2, 3 ],
    [ 4, 5, 6 ],
    [ 7, 8, 9 ]
]

b = [
    3,
    -1,
    0
]

result = get_product(A, b)
print(result)
