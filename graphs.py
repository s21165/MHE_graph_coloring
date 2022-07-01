import csv
import matplotlib.pyplot as plt

X = []
y = []

with open(file='D:/download/AI C++/cmake-build-debug/HillClimbing.csv', mode='r') as newFile:
    plots = csv.reader(newFile, delimiter=',')
    has_header = csv.Sniffer().has_header(newFile.read(1024))
    newFile.seek(0)
    if has_header:
        next(plots)
    for row in plots:
        y.append(int(row[1]))

plt.plot(y)
# naming the x axis
plt.xlabel('0.072999 Seconds')
# naming the y axis
plt.ylabel('Score')

# giving a title to my graph
plt.title('Hill Climbing')

# function to show the plot
plt.show()

X = []
y = []

with open(file='D:/download/AI C++/cmake-build-debug/HillClimbingBest.csv', mode='r') as newFile:
    plots = csv.reader(newFile, delimiter=',')
    has_header = csv.Sniffer().has_header(newFile.read(1024))
    newFile.seek(0)
    if has_header:
        next(plots)
    for row in plots:
        y.append(int(row[1]))

plt.plot(y)
# naming the x axis
plt.xlabel('0.575002 Seconds')
# naming the y axis
plt.ylabel('Score')

# giving a title to my graph
plt.title('Hill Climbing Best Point')

# function to show the plot
plt.show()

X = []
y = []

with open(file='D:/download/AI C++/cmake-build-debug/TabuSearch.csv', mode='r') as newFile:
    plots = csv.reader(newFile, delimiter=',')
    has_header = csv.Sniffer().has_header(newFile.read(1024))
    newFile.seek(0)
    if has_header:
        next(plots)
    for row in plots:
        y.append(int(row[1]))

plt.plot(y)
# naming the x axis
plt.xlabel('0.589002 Seconds')
# naming the y axis
plt.ylabel('Score')

# giving a title to my graph
plt.title('TabuSearch')

# function to show the plot
plt.show()

X = []
y = []

with open(file='D:/download/AI C++/cmake-build-debug/TabuSearchBack.csv', mode='r') as newFile:
    plots = csv.reader(newFile, delimiter=',')
    has_header = csv.Sniffer().has_header(newFile.read(1024))
    newFile.seek(0)
    if has_header:
        next(plots)
    for row in plots:
        y.append(int(row[1]))

plt.plot(y)
# naming the x axis
plt.xlabel('49.3013 Seconds')
# naming the y axis
plt.ylabel('Score')

# giving a title to my graph
plt.title('TabuSearchBack')

# function to show the plot
plt.show()

with open(file='D:/download/AI C++/cmake-build-debug/SimulatedAnnealing.csv', mode='r') as newFile:
    plots = csv.reader(newFile, delimiter=',')
    has_header = csv.Sniffer().has_header(newFile.read(1024))
    newFile.seek(0)
    if has_header:
        next(plots)
    for row in plots:
        y.append(int(row[1]))

plt.plot(y)
# naming the x axis
plt.xlabel('0.579998 Seconds')
# naming the y axis
plt.ylabel('Score')

# giving a title to my graph
plt.title('SimulatedAnnealing')

# function to show the plot
plt.show()

with open(file='D:/download/AI C++/cmake-build-debug/GeneticAlgorithmCutmode0Mutacionmode0.csv', mode='r') as newFile:
    plots = csv.reader(newFile, delimiter=',')
    has_header = csv.Sniffer().has_header(newFile.read(1024))
    newFile.seek(0)
    if has_header:
        next(plots)
    for row in plots:
        y.append(int(row[1]))

plt.plot(y)
# naming the x axis
plt.xlabel('0.108374 Seconds')
# naming the y axis
plt.ylabel('Score')

# giving a title to my graph
plt.title('GeneticAlgorithmCutmode0Mutacionmode0')

# function to show the plot
plt.show()

with open(file='D:/download/AI C++/cmake-build-debug/GeneticAlgorithmCutmode0Mutacionmode0.csv', mode='r') as newFile:
    plots = csv.reader(newFile, delimiter=',')
    has_header = csv.Sniffer().has_header(newFile.read(1024))
    newFile.seek(0)
    if has_header:
        next(plots)
    for row in plots:
        y.append(int(row[1]))

plt.plot(y)
# naming the x axis
plt.xlabel('0.10420 Seconds')
# naming the y axis
plt.ylabel('Score')

# giving a title to my graph
plt.title('GeneticAlgorithmCutmode1Mutacionmode0')

# function to show the plot
plt.show()

with open(file='D:/download/AI C++/cmake-build-debug/GeneticAlgorithmCutmode0Mutacionmode1.csv', mode='r') as newFile:
    plots = csv.reader(newFile, delimiter=',')
    has_header = csv.Sniffer().has_header(newFile.read(1024))
    newFile.seek(0)
    if has_header:
        next(plots)
    for row in plots:
        y.append(int(row[1]))

plt.plot(y)
# naming the x axis
plt.xlabel('0.102 Seconds')
# naming the y axis
plt.ylabel('Score')

# giving a title to my graph
plt.title('GeneticAlgorithmCutmode0Mutacionmode1')

# function to show the plot
plt.show()

with open(file='D:/download/AI C++/cmake-build-debug/GeneticAlgorithmCutmod1Mutacionmode1.csv', mode='r') as newFile:
    plots = csv.reader(newFile, delimiter=',')
    has_header = csv.Sniffer().has_header(newFile.read(1024))
    newFile.seek(0)
    if has_header:
        next(plots)
    for row in plots:
        y.append(int(row[1]))

plt.plot(y)
# naming the x axis
plt.xlabel('0.200975 Seconds')
# naming the y axis
plt.ylabel('Score')

# giving a title to my graph
plt.title('GeneticAlgorithmCutmode1Mutacionmode1')

# function to show the plot
plt.show()
