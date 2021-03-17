from Drone.Service.Service import *
from time import sleep


class UI:
    def __init__(self):
        self._service = Service()

        pygame.init()
        logo = pygame.image.load("Resources/logo32x32.png")
        pygame.display.set_icon(logo)
        pygame.display.set_caption("Path in simple environment")

        screen = pygame.display.set_mode((SQUARE_WIDTH * WIDTH, SQUARE_HEIGHT * HEIGHT))
        screen.fill(WHITE)

        running = True
        finalPosition = None
        dronePosition = None
        printExecutionTimes = False
        while running:
            for event in pygame.event.get():
                if event.type == pygame.QUIT:
                    running = False
                if event.type == pygame.KEYDOWN:
                    printExecutionTimes = True
                    if pygame.key.get_pressed()[pygame.K_t]:
                        self._service.showTabu = not self._service.showTabu
                    if pygame.key.get_pressed()[pygame.K_s]:
                        self._service.showSimulatedAnnealing = not self._service.showSimulatedAnnealing
                    if pygame.key.get_pressed()[pygame.K_c]:
                        self._service.computeSimulatedAnnealing = not self._service.computeSimulatedAnnealing
                    if pygame.key.get_pressed()[pygame.K_g]:
                        self._service.showGreedyAndAStar = not self._service.showGreedyAndAStar

                if event.type == pygame.MOUSEBUTTONDOWN:
                    printExecutionTimes = True
                    if pygame.mouse.get_pressed()[pygame.BUTTON_LEFT-1] == 1:
                        y, x = pygame.mouse.get_pos()
                        finalPosition = (x//SQUARE_HEIGHT, y // SQUARE_WIDTH)
                    if pygame.mouse.get_pressed()[pygame.BUTTON_RIGHT-1] == 1:
                        y, x = pygame.mouse.get_pos()
                        dronePosition = (x//SQUARE_HEIGHT, y // SQUARE_WIDTH)

            if dronePosition is not None:
                self._service.setDronePosition(dronePosition)
            screen.blit(self._service.mapWithDrone(), (0, 0))
            if finalPosition is not None:
                screen.blit(self._service.mapWithPath(finalPosition), (0, 0))

                if printExecutionTimes:
                    for strategy, (execution_time, length) in self._service.executionTimes.items():
                        print(f"{strategy.ljust(10)}: {execution_time} - {length}")
                    print()
                    printExecutionTimes = False

            pygame.display.flip()

        # pygame.display.flip()
        # sleep(2)
        pygame.quit()


