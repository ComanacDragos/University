from Drone.Service.Service import *
from time import sleep
from random import seed
import matplotlib.pyplot as plt


class GUI:
    def __init__(self):
        self._service = Service()
        self._sleepTime = 0.5
        pygame.init()
        logo = pygame.image.load("Resources/logo32x32.png")
        pygame.display.set_icon(logo)
        pygame.display.set_caption("GA")

        screen = pygame.display.set_mode((SQUARE_WIDTH * WIDTH, SQUARE_HEIGHT * HEIGHT))
        screen.fill(WHITE)

        running = True
        path = []
        detectedPositions = []
        pathIndex = None
        while running:
            for event in pygame.event.get():
                if event.type == pygame.QUIT:
                    running = False

                if event.type == pygame.MOUSEBUTTONDOWN:
                    if pygame.mouse.get_pressed()[pygame.BUTTON_RIGHT-1] == 1:
                        y, x = pygame.mouse.get_pos()
                        dronePosition = (x//SQUARE_HEIGHT, y // SQUARE_WIDTH)

                        try:
                            self._service.setDronePosition(dronePosition)
                            print("Starting...")
                            data, path, detectedPositions, averages, bests = self._service.solver()
                            for info, value in data.items():
                                print(f"{info}: {value}")

                            fig, (ax1, ax2) = plt.subplots(1, 2)
                            fig.suptitle("Averages -- Bests")
                            ax1.plot(range(1, len(averages) + 1), averages, 'o', color='black')
                            ax2.plot(range(1, len(bests) + 1), bests, 'o', color='black')
                        except Exception as exc:
                            print(exc)
                if event.type == pygame.KEYDOWN:
                    if pygame.key.get_pressed()[pygame.K_SPACE]:
                        pathIndex = 0
                    if pygame.key.get_pressed()[pygame.K_s] and not pygame.key.get_pressed()[pygame.K_LCTRL]:
                        (fitnessAvg, fitnessStd), (detectedPositionsAvg, detectedPositionsStd) = \
                            self._service.computeStats("fitness"), self._service.computeStats("detectedPositions")
                        print(f"Fitness average: {fitnessAvg}, detected positions average: {detectedPositionsAvg}")
                        print(f"Fitness std: {fitnessStd}, detected positions std: {detectedPositionsStd}")
                    if pygame.key.get_pressed()[pygame.K_LEFT]:
                        self.slow_down()
                    if pygame.key.get_pressed()[pygame.K_RIGHT]:
                        self.speed_up()

                    if pygame.key.get_pressed()[pygame.K_l] and pygame.key.get_pressed()[pygame.K_LCTRL]:
                        try:
                            path = self._service.loadPath("Resources/Paths/" + input("Path to load: ") + ".path")
                            detectedPositions = self._service.detectedPositions(path)
                            self._service.setDronePosition(path[0])
                        except Exception as exc:
                            print(exc)

                    if pygame.key.get_pressed()[pygame.K_s] and pygame.key.get_pressed()[pygame.K_LCTRL]:
                        try:
                            self._service.savePath(path, "Resources/Paths/" + input("Path to save: ") + ".path")
                        except Exception as exc:
                            print(exc)

            if pathIndex is not None:
                if pathIndex == len(path):
                    pathIndex = None
                else:
                    self._service.setDronePosition(path[pathIndex], self._sleepTime)
                    pathIndex += 1

            image = self._service.mapWithPath(path, self._service.mapWithPath(detectedPositions), color=RED)
            image = self._service.mapWithPath(path[-1:], image, color=PURPLE)
            screen.blit(self._service.mapWithDrone(image), (0, 0))
            pygame.display.flip()
            plt.show()
        pygame.quit()

    def speed_up(self):
        if self._sleepTime > 0.1:
            self._sleepTime -= 0.1

    def slow_down(self):
        self._sleepTime += 0.1
