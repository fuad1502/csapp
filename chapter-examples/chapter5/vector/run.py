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
            y1 = []
            y2 = []
            with open("output/" + outfile, "r") as f:
                reader = csv.reader(f)
                next(reader)
                for row in reader:
                    x.append(int(row[0]))
                    y1.append(int(row[1]))   
                    y2.append(int(row[2]))
            # Plot the data
            plt.plot(x, y1)
            legends.append("combine1_{0}_{1}_{2}".format(optmization_level, operation, data_type))
            plt.plot(x, y2)
            legends.append("combine2_{0}_{1}_{2}".format(optmization_level, operation, data_type))

plt.legend(legends)
plt.show()
