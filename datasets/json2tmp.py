#!/usr/bin/env python3

import json

fo = open("datasets/metadata.json", "r")

i = 0

for line in fo:
    # asin = line.index("\"asin\": \"")
    x = line.index("asin")
    # "asin": "0001048791"
    asin = line[x + 8:x + 8 + 10]

    also_viewed = []
    try:
        # y = line.index("also_viewed")
        # print(y)
        line = line[line.index("also_viewed"):]
        also_viewed = line[line.index('[') + 1:line.index(']') - 1].replace('\'', '').split(", ")
    except:
        pass

    print(f"{asin} {' '.join(also_viewed)}")
    i+= 1
    # if i % 100000 == 0: print(i)

fo.close()