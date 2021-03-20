class RunRepository:
    def __init__(self, file="Resources/fitness_data.txt"):
        self._file = file
        self._data = []
        self._dronePosition = None
        self._identity = 0

        self.loadData()

    def loadData(self):
        with open(self._file) as file:
            lines = file.readlines()
            tokens = lines[0].split()
            self._dronePosition = (int(tokens[0]), int(tokens[1]))
            for line in lines[1:]:
                tokens = line.split()
                run = {
                    "id": int(tokens[0]),
                    "seed": int(tokens[1]),
                    "fitness": int(tokens[2]),
                    "detectedPositions": int(tokens[3])
                }
                self._data.append(run)
                if run['id'] > self._identity:
                    self._identity = run['id']

    def saveData(self):
        with open(self._file, "w") as file:
            file.write(f"{self._dronePosition[0]} {self._dronePosition[1]}\n")
            for runId, seed, fitness, detectedPositions in \
                    [(run['id'], run['seed'], run['fitness'], run['detectedPositions']) for run in self._data]:
                file.write(f"{runId} {seed} {fitness} {detectedPositions}\n")

    def saveRun(self, seed, fitness, detectedPositions):
        self._identity += 1
        run = {
            "id": self._identity,
            "seed": seed,
            "fitness": fitness,
            "detectedPositions": detectedPositions
        }
        self._data.append(run)
        with open(self._file, "a") as file:
            file.write(f"{self._identity} {seed} {fitness} {detectedPositions}\n")

    @property
    def data(self):
        return self._data

    @property
    def dronePosition(self):
        return self._dronePosition
