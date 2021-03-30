from Service.Service import *


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
        while running:
            for event in pygame.event.get():
                if event.type == pygame.QUIT:
                    running = False
                if event.type == pygame.KEYDOWN:
                    if pygame.key.get_pressed()[pygame.K_SPACE]:
                        start = time.time()
                        path = self._service.solver()
                        print(time.time()-start)
                        print(len(path))
                        print(len(set(path)))

            image = self._service.mapWithPath(path)
            image = self._service.mapWithDrone(image)
            image = self._service.mapWithSensors(image)
            screen.blit(image, (0, 0))
            pygame.display.flip()
        pygame.quit()

    def speed_up(self):
        if self._sleepTime > 0.1:
            self._sleepTime -= 0.1

    def slow_down(self):
        self._sleepTime += 0.1
