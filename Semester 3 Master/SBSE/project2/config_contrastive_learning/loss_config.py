from backend.loss import ContrastiveLoss


class ContrastiveLossConfig:
    TAU = 10

    @staticmethod
    def build():
        return ContrastiveLoss(ContrastiveLossConfig.TAU)
