import matplotlib.pyplot as plt
import csv
import sys

if len(sys.argv) != 2:
    print(f"Usage: {sys.argv[0]} <output file>\n")

with open(sys.argv[1]) as f:
    csv_reader = csv.reader(f)
    f_names = csv_reader.__next__()[1:-1]
    print(f_names)
    x = []
    ys = [[] for _ in range(0,len(f_names))]
    for row in csv_reader:
        x.append(int(row[0]))
        for (i, y) in enumerate(ys):
            ys[i].append(int(row[i + 1]))
    for (y, f_name) in zip(ys, f_names):
        plt.plot(x, y)

plt.show()
