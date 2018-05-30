import os
import sys
import math

if len(sys.argv) > 1:
    input_dir = sys.argv[1]
    output_dir = sys.argv[2]
else:
    input_dir = "tests"
    output_dir = "output"


input_files = os.listdir(input_dir)
output_files = os.listdir(output_dir)

input_files = [os.path.join(input_dir, f) for f in input_files]
output_files = [os.path.join(output_dir, f) for f in output_files]

input_files = sorted(input_files, key=lambda x: int(x.split("/")[1].split(".")[0]))
output_files = sorted(output_files, key=lambda x: int(x.split("/")[1].split(".")[0]))

def calc_penalty(in_file, out_file):
    with open(in_file) as f:
        T = int(f.readline())
        for i in range(T):
            f.readline()

        P = int(f.readline())

    penalty = 0


    with open(out_file) as f:
        move_cnt = int(f.readline().strip())

        for i in range(move_cnt):
            move_descr = f.readline()
            if move_descr == "":
                break
            move_descr_parts = move_descr.split()
            dx = int(move_descr_parts[1])
            dy = int(move_descr_parts[2])
            k = int(move_descr_parts[3])
            penalty += math.sqrt(dx * dx + dy * dy) * (T + k)

    return penalty


counter = 1
for in_file, out_file in zip(input_files, output_files):
    print(counter, calc_penalty(in_file, out_file))
    counter += 1
