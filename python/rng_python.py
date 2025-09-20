
import sys
import random

# Usage: python3 rng_python.py <seed> <output_file> <mode: chi|ks>

if len(sys.argv)<4:
    print(f"Usage: {sys.argv[0]} <seed> <output_file> <mode: chi|ks>")
    sys.exit(1)
seed = int(sys.argv[1])
filename = sys.argv[2]
mode = sys.argv[3]

random.seed(seed)

try:
    with open(filename, "w") as out:
        out.write(f"#seed = {seed}\n")

        if mode == "chi":
            for _ in range(5000):
                num = random.randint(1, 1000)
                out.write(f"{num}\n")
        elif mode == "ks":
            for _ in range(30):
                num = random.random()*5.0
                out.write(f"{num:.6f}\n")
        else:
            print("Invalid mode. Use chi or ks.")
            sys.exit(1)
except IOError:
    print(f"Cannot open file{filename} for writing")
    sys.exit(1)