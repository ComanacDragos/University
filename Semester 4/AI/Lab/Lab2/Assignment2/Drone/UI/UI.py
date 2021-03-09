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
        while running:
            for event in pygame.event.get():
                if event.type == pygame.QUIT:
                    running = False
                if event.type == pygame.KEYDOWN:
                    if pygame.key.get_pressed()[pygame.K_t]:
                        self._service.showTabu = not self._service.showTabu

                if event.type == pygame.MOUSEBUTTONDOWN:
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

                for strategy, (execution_time, length) in self._service.executionTimes.items():
                    print(f"{strategy.ljust(10)}: {execution_time} - {length}")
                if self._service.executionTimes:
                    print()

            pygame.display.flip()

        # pygame.display.flip()
        # sleep(2)
        pygame.quit()


