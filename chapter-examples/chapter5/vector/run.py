import subprocess
import csv
import matplotlib.pyplot as plt

optmization_levels = ["1"]
operations = ["ADD"]
data_types = ["long"]

legends = []
for optmization_level in optmization_levels:
    for operation in operations:
        for data_type in data_types:
            # Clean build
            subprocess.run("make clean", shell=True)
            # Build the executable
            subprocess.run("make OPTIMIZATION_LEVEL={0} OPSTR={1} DATA_T={2}".format(optmization_level, operation, data_type), shell=True)
            # Run the executable
            outfile = "benchmark_{0}_{1}_{2}.txt".format(optmization_level, operation, data_type)
            subprocess.run("make run OUTFILE={0}".format(outfile), shell=True)
            # Parse the output file
            x = []
            y = []
            N_f = 4;
            for i in range(N_f):
                y.append([]);
            with open("output/" + outfile, "r") as f:
                reader = csv.reader(f)
                next(reader)
                for row in reader:
                    x.append(int(row[0]))
                    for i in range(N_f):
                        y[i].append(int(row[i + 1]))   
            # Plot the data
            for i in range(N_f):
                plt.plot(x, y[i])
                legends.append("combine{0}_{1}_{2}_{3}".format(i + 1, optmization_level, operation, data_type))

plt.legend(legends)
plt.show()
