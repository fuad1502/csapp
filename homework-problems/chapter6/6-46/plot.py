import matplotlib.pyplot as plt
import csv
import sys
import subprocess

block_sizes = [2, 4, 8, 16]
legends = [f"block_size={block_size}" for block_size in block_sizes]
legends.insert(0, "naive")

for block_size in block_sizes:
    out_file = f"output/block_size_{block_size}.csv"
    subprocess.run("make clean", shell=True)
    subprocess.run(f"make BLOCK_SIZE={block_size}", shell=True)
    subprocess.run(f"make run OUTFILE={out_file}", shell=True)
    with open(out_file) as f:
        csv_reader = csv.reader(f)
        f_names = csv_reader.__next__()[1:-1]
        print(f_names)
        x = []
        ys = [[] for _ in range(0,len(f_names))]
        for row in csv_reader:
            x.append(int(row[0]))
            for (i, y) in enumerate(ys):
                ys[i].append(float(row[i + 1]))
        for (y, f_name) in zip(ys, f_names):
            if f_name == f_names[0] and block_size != block_sizes[0]:
                continue
            plt.plot(x, y)

plt.legend(legends)
plt.show()
