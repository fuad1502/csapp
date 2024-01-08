import glob
import subprocess
import csv
import numpy as np

# Run benchmark
subprocess.run(f"make run", shell=True)

# Parse output
function_names = [];
results = []
with open("output/benchmark.txt") as f:
    csv_reader = csv.reader(f);
    function_names = csv_reader.__next__()[1:-1].copy()
    y = [[] for _ in function_names]
    x = [];
    for row in csv_reader:
        x.append(int(row[0]))
        for i, value in enumerate(row[1:-1]):
            y[i].append(int(value))
    for i, f_name in enumerate(function_names):
        (m, c) = np.polyfit(x, y[i], 1)
        results.append(m)

# Print result table top border
print("+{:^20}+{:^20}+".format("-" * 20, "-" * 20), end="")
print("")

# Print result header
# 1
print("|{:^20}|{:^20}|".format("Function", "CPE"), end="")
print("")
# 2
print("|{:^20}|{:^20}|".format("=" * 20, "=" * 20), end="")
print("")

# Print result
for f_name, result in zip(function_names, results):
    print(f"|{f_name:^20}|{result:^20.6}|", end="")
    print("") 

# Print result table bottom border
print("+{:^20}+{:^20}+".format("-" * 20, "-" * 20), end="")
print("")
