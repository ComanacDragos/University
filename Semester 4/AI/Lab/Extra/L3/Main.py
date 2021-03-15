from Service import *


class Main:
    def __init__(self, gmlFile, settingsFile, logFile, outputFile):
        self._ga = GA(gmlFile, settingsFile)
        best = self._ga.bestChromosome(), 0
        with open(logFile, "w") as log, open(outputFile, "w") as output:
            for generation in range(self._ga.noGen):
                self._ga.oneGeneration()
                # ga.oneGenerationElitism()
                # ga.oneGenerationSteadyState()

                bestChromo = self._ga.bestChromosome()

                if bestChromo.fitness < best[0].fitness:
                    best = bestChromo, generation

                if generation % 10 == 0:
                    currentSolString = f"Best solution in generation {generation}:\nx = {bestChromo.repres}\nf(x) = {-bestChromo.fitness}\n{len(set(bestChromo.repres))}"
                    #print(currentSolString)
                    log.write(currentSolString + "\n")

                if generation % 5 == 0:
                    bestSolString = f"Best up until now found at: {best[1]}, at {generation}:\nx = {best[0].repres}\nf(x) = {-best[0].fitness}\n{len(set(best[0].repres))}\n\n"
                    print(bestSolString)
                    log.write(bestSolString + "\n")

            bestSolString = f"Best up until now found at: {best[1]}:\nx = {best[0].repres}\nf(x) = {-best[0].fitness}\n{len(set(best[0].repres))}\n\n"
            log.write(bestSolString + "\n")
            print(bestSolString)

            interpretedSol = interpretLabels(best[0].repres)
            communities = len(set(interpretedSol))
            output.write(str(communities) + "\n")
            for node, community in enumerate(interpretedSol, start=1):
                output.write(f"{node} {community}\n")


if __name__ == '__main__':
    gmlDolphinsFile = "real/dolphins/dolphins.gml"
    gmlFootballFile = "real/football/football.gml"
    gmlFootballV2File = "real/footballv2/football.gml"

    gmlKarateFile = "real/karate/karate.gml"
    gmlKrebsFile = "real/krebs/krebs.gml"

    customGraphFile = "graph.gml"
    customGraph2File = "graph2.gml"
    customGraph3File = "graph3.gml"

    settingsFile = "settings.json"
    logFile = "log.txt"
    outputFile = "output.txt"
    Main(customGraph3File, settingsFile, logFile, outputFile)
