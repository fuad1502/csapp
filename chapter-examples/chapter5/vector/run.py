import subprocess
import csv
import numpy as np

optmization_levels = ["1","2"]
operations = ["ADD", "MUL"]
data_types = ["LONG", "DOUBLE", "INT"]

# Run benchmark
for opt in optmization_levels:
    for dt in data_types:
        for op in operations:
            # Clean build
            subprocess.run("make clean", shell=True)
            # Build the executable
            subprocess.run(f"make OPTIMIZATION_LEVEL={opt} OPSTR={op} DATA_T={dt}", shell=True)
            # Run the executable
            outfile = f"benchmark_{opt}_{op}_{dt}.txt"
            subprocess.run(f"make run OUTFILE={outfile}", shell=True)

# Parse output
function_names = [];
result = {}
for opt in optmization_levels:
    for dt in data_types:
        for op in operations:
            outfile = f"benchmark_{opt}_{op}_{dt}.txt"
            with open("output/" + outfile) as f:
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
                    id = (opt, f_name, dt, op)
                    result[id] = m

# Print result table top border
print("+{:^20}+{:^20}+".format("-" * 20, "-" * 20), end="")
for dt in data_types:
    format_string = "{:^" + str(11 * len(operations) - 1) + "}+"
    print(format_string.format("-" * (11 * len(operations) - 1)), end="");
print("")

# Print result header
# 1
print("|{:20}|{:20}|".format("",""), end="")
for dt in data_types:
    format_string = "{:^" + str(11 * len(operations) - 1) + "}|"
    print(format_string.format(dt), end="");
print("")
# 2
print("|{:^20}|{:^20}|".format("Function", "Optimization"), end="")
for dt in data_types:
    for op in operations:
        print("{:^10}|".format(op), end="")
print("")
# 3
print("|{:^20}|{:^20}|".format("=" * 20, "=" * 20), end="")
for dt in data_types:
    for op in operations:
        print("{:^10}|".format("=" * 10), end="")
print("")

# Print result
for opt in optmization_levels:
    for f_name in function_names:
        print(f"|{f_name:^20}|{opt:^20}|", end="")
        for dt in data_types:
            for op in operations:
                id = (opt, f_name, dt, op)
                print(f"{result[id]:^10.3f}|", end="")
        print("") 

# Print result table bottom border
print("+{:^20}+{:^20}+".format("-" * 20, "-" * 20), end="")
for dt in data_types:
    for op in operations:
        print("{:^10}+".format("-" * 10), end="")
print("")
