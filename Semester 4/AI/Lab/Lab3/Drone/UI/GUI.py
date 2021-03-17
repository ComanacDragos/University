from Drone.Service.Service import *
from time import sleep


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
        dronePosition = None
        while running:
            for event in pygame.event.get():
                if event.type == pygame.QUIT:
                    running = False

                if event.type == pygame.MOUSEBUTTONDOWN:
                    if pygame.mouse.get_pressed()[pygame.BUTTON_RIGHT-1] == 1:
                        y, x = pygame.mouse.get_pos()
                        dronePosition = (x//SQUARE_HEIGHT, y // SQUARE_WIDTH)

            if dronePosition is not None:
                self._service.setDronePosition(dronePosition)
            screen.blit(self._service.mapWithDrone(), (0, 0))
            pygame.display.flip()

        pygame.quit()


