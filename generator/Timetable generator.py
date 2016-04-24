from random import randrange
from random import shuffle
numberOfstations = eval(input("Input number of stations: "))
numberOfTrains = eval(input("Input number of trains: "))
numberOfStationsPerTrains = eval(input("Input average number of stations per trains: "))
fileName = str(input("Input file name to save result: "))
allStations = ["Town " + str(i) for i in range(1, numberOfstations + 1)]
allTrains = [str(i) for i in range(1, numberOfTrains + 1)]
allTrainsTimetables = {}
for element in allTrains:
     allTrainsTimetables[element] = []
     time = randrange(30)
     stationsForTrain = numberOfStationsPerTrains + randrange(-numberOfStationsPerTrains // 5, numberOfStationsPerTrains // 5 + 1)
     for j in range(stationsForTrain):
         time += (1410 - time) // (stationsForTrain - j) + randrange(-((1410 - time) // 5) // (stationsForTrain - j), ((1410 - time) // 5) // (stationsForTrain - j) + 1) - 5
         pause = randrange(1, 6)
         record = [allStations[randrange(numberOfstations)], time // 60, time % 60, (time + pause) // 60, (time + pause) % 60]
         time += pause
         allTrainsTimetables[element].append(record)
file = open(fileName + ".txt", "w")
file.write("Timetable generated by Timetable generator, all right reserved (C);" + allStations[0])
for i in range(1, numberOfstations - 1):
    file.write("-" + allStations[i])
file.write("-" + allStations[numberOfstations - 1] + ";\n")
recordNumber = 0
for element in allTrains:
    for i in range(len(allTrainsTimetables[element])):
        file.write(element + ";" + allTrainsTimetables[element][i][0] + ";" + str(allTrainsTimetables[element][i][1]) + ":" + str(allTrainsTimetables[element][i][2]) + ";" +
                                                                              str(allTrainsTimetables[element][i][3]) + ":" + str(allTrainsTimetables[element][i][4]) + ";\n")
        recordNumber += 1
file.write(str(numberOfTrains) + ";" + str(recordNumber) + ";")
file.close()
randomize = str(input("Create a shuffled version of your file? Print 'OK' to create: "))
if randomize == "ok" or randomize == "OK":
    file = open(fileName + ".txt")
    container = file.readlines()
    file.close()
    file = open(fileName + "Shuffled.txt", "w")
    file.write(container[0])
    del container[0]
    footer = container[len(container) - 1]
    del container[len(container) - 1]
    shuffle(container)
    for line in container:
        file.write(line)
    file.write(footer)
    file.close()