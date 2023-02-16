#!/usr/bin/env python3

from sys import argv


def run(in_filename, out_filename):
    fo = open(in_filename)
    fw = open(out_filename, "w")

    ids = []

    i = 0
    for line in fo:
        x = line.index("asin")
        asin = line[x + 8:x + 8 + 10]

        also_viewed = []
        try:
            line = line[line.index("also_viewed"):]
            also_viewed = line[line.index('[') + 1:line.index(']') - 1].replace('\'', '').replace('\"', '').split(", ")
        except:
            pass

        try:
            asin_id = str(ids.index(asin))
            print("well, yes")
        except:
            asin_id = str(len(ids))
            ids.append(asin)

        strr = ""
        for id in also_viewed:
            try:
                pos = str(ids.index(id))
            except:
                pos = str(len(ids))
                ids.append(asin)
            strr = strr + pos + " "
        fw.write(f"{asin_id} {strr}\n")

        i += 1


if __name__ == "__main__":
    if len(argv) < 3:
        print(f"Transform the uncleaned json data to readable adjcacency matrix\nUsage : {argv[0]} <file.json> <file.mat>")
        exit()

    run(argv[1], argv[2])