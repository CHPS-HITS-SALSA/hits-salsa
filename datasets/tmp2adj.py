#!/usr/bin/env python3

from sys import argv


def run(filename):
    fo = open(filename)

    ids = []

    for line in fo:
        l = line[:-2].split(" ")

        strr = ""
        for ll in l:
            try:
                pos = str(ids.index(ll))
            except:
                pos = str(len(ids))
                ids.append(ll)
            strr += pos
            strr += " "
        print(strr)

    fo.close()


if __name__ == "__main__":
    if len(argv) < 2:
        print(f"Usage : {argv[0]} <file.mat>")
        exit()

    file = argv[1]
    run(file)