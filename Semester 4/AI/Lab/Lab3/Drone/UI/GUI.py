from Drone.Service.Service import *
from time import sleep
from random import seed
import matplotlib.pyplot as plt

class GUI:
    def __init__(self):
        self._service = Service()

        pygame.init()
        logo = pygame.image.load("Resources/logo32x32.png")
        pygame.display.set_icon(logo)
        pygame.display.set_caption("GA")

        screen = pygame.display.set_mode((SQUARE_WIDTH * WIDTH, SQUARE_HEIGHT * HEIGHT))
        screen.fill(WHITE)

        running = True
        path = []
        detectedPositions = []
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
            image = self._service.mapWithPath(path, self._service.mapWithPath(detectedPositions), color=RED)
            screen.blit(self._service.mapWithDrone(image), (0, 0))
            pygame.display.flip()
            plt.show()
        pygame.quit()


