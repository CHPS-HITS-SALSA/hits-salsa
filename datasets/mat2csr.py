#!/usr/bin/env python3

import numpy as np
from sys import argv

def run(filein, fileout):
    fo = open(filein)
    fw = open(fileout, "w")

    values = []
    cols = []
    rows = [0]

    for line in fo.readlines():
        strr = line[:-1].split(" ")[:-1]
        # print(strr)
        if len(strr) > 1:
            values.extend(np.arange(1, len(strr[1:]) - 1) / len(strr))
            cols.extend(strr[1:])
            rows.append(rows[-1] + len(strr[1:]))

    fw.write(f"{len(values)} {len(cols)} {len(rows)}\n")
    fw.write(" ".join([f"{v:.6f}" for v in values]))
    fw.write("\n")
    fw.write(" ".join(cols))
    fw.write("\n")
    fw.write(" ".join([str(r) for r in rows]))
    fw.write("\n")

if __name__ == "__main__":
    if len(argv) < 3:
        print(f"Transform .mat files in CSR format\nUsage : {argv[0]} <file.mat> <file.csr>")
        exit()

    run(argv[1], argv[2])