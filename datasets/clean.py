import json
import ast
from sys import argv
# import subprocess

if len(argv) < 3:
    print(f"Usage : {argv[0]} input.json output.json")
    exit()

fo = open(argv[1], "r")
fw = open(argv[2], "w")

# p = subprocess.run(f"wc -l {argv[1]}".split(), capture_output=True)
# result = p.stdout.decode()
# max = int(result.split(" ")[0])

max = sum(1 for _ in open(argv[1])) # Definitly slower, but is portable.
i = 0

for line in fo:
    jdump = json.dumps(ast.literal_eval(line))
    jload = json.loads(jdump)
    json.dump(jload, fw)
    fw.write("\n")
    i += 1
    print(f"[{i/max*100:2.2f}%] {i}/{max}", end="\r")

print("")

fw.close()
fo.close()