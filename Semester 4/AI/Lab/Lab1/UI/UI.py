from Service.Service import *


class UI:
    def __init__(self):
        self.service = Service()
        # self.service.loadEnvironment("Resources/test2.map")

    def run(self):
        pygame.init()
        logo = pygame.image.load("Resources/logo32x32.png")
        pygame.display.set_icon(logo)
        pygame.display.set_caption("Resources/drone exploration")

        screen = pygame.display.set_mode((800, 400))
        screen.fill(WHITE)
        screen.blit(self.service.environmentImage, (0, 0))

        running = True
        self.service.markDetectableWalls()

        while running:
            for event in pygame.event.get():
                if event.type == pygame.QUIT:
                    running = False
                if event.type == KEYDOWN:
                    if pygame.key.get_pressed()[K_LEFT]:
                        self.service.slow_down()
                    if pygame.key.get_pressed()[K_RIGHT]:
                        self.service.speed_up()

            self.service.moveDFS()

            screen.blit(self.service.detectedMapImage, (400, 0))
            pygame.display.flip()

        pygame.quit()
