from Service.Service import *
import traceback


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
        pathIndex = None
        while running:
            for event in pygame.event.get():
                if event.type == pygame.QUIT:
                    running = False
                if event.type == pygame.KEYDOWN:
                    if pygame.key.get_pressed()[pygame.K_SPACE]:
                        pathIndex = 0

                    if pygame.key.get_pressed()[pygame.K_LEFT]:
                        self.slow_down()
                    if pygame.key.get_pressed()[pygame.K_RIGHT]:
                        self.speed_up()
                    if pygame.key.get_pressed()[pygame.K_r]:
                        self._service = Service()
                        pathIndex = None
                        path = []
                    if pygame.key.get_pressed()[pygame.K_d]:
                        self._service.displaySensorStrengths = not self._service.displaySensorStrengths
                if event.type == pygame.MOUSEBUTTONDOWN:
                    if pygame.mouse.get_pressed()[pygame.BUTTON_RIGHT - 1] == 1:
                        y, x = pygame.mouse.get_pos()
                        dronePosition = (x // SQUARE_HEIGHT, y // SQUARE_WIDTH)

                        try:
                            self._service.setDronePosition(dronePosition)
                            print("Starting...")

                            start = time.time()
                            path = self._service.solver()
                            print(time.time() - start)
                            print(path[0], path[-1])
                            print(len(path))
                            print(len(set(path)))
                        except Exception as exc:
                            traceback.print_exc()

            if pathIndex is not None:
                if pathIndex == len(path):
                    pathIndex = None
                else:
                    self._service.setDronePosition(path[pathIndex], self._sleepTime)
                    pathIndex += 1

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
