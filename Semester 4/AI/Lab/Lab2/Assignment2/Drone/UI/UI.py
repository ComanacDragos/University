from Drone.Service.Service import *
from time import sleep


class UI:
    def __init__(self):
        self._service = Service()

        pygame.init()
        logo = pygame.image.load("Resources/logo32x32.png")
        pygame.display.set_icon(logo)
        pygame.display.set_caption("Path in simple environment")

        # create a surface on screen that has the size of 400 x 480
        screen = pygame.display.set_mode((SQUARE_WIDTH * WIDTH, SQUARE_HEIGHT * HEIGHT))
        screen.fill(WHITE)

        running = True

        while running:
            for event in pygame.event.get():
                if event.type == pygame.QUIT:
                    running = False

            screen.blit(self._service.mapWithDrone(), (0, 0))
            screen.blit(self._service.mapWithPath(), (0, 0))
            pygame.display.flip()

        # pygame.display.flip()
        # sleep(2)
        pygame.quit()


