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
        while running:
            for event in pygame.event.get():
                if event.type == pygame.QUIT:
                    running = False
                if event.type == pygame.MOUSEBUTTONUP:
                    y, x = pygame.mouse.get_pos()
                    finalPosition = (x//SQUARE_HEIGHT, y // SQUARE_WIDTH)

            screen.blit(self._service.mapWithDrone(), (0, 0))
            if finalPosition is not None:
                screen.blit(self._service.mapWithPath(finalPosition), (0, 0))

            pygame.display.flip()

        # pygame.display.flip()
        # sleep(2)
        pygame.quit()


