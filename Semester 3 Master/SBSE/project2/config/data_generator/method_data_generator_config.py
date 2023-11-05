from backend.data_generator import MethodDataGenerator
from backend.enums import Stage


class MethodDataGeneratorConfig:
    ROOT = 'data/methods'
    CSV_PATH = 'data/csvs/duplicate.csv'
    BATCH_SIZE = 32
    ALPHABET = """!"%&'()*+,-./0123456789:;<=>?@[\\]^_abcdefghijklmnopqrstuvwxyz{|}\n"""
    MAX_LENGTH = 1024

    @staticmethod
    def build(stage: Stage):
        return MethodDataGenerator(
            root=MethodDataGeneratorConfig.ROOT,
            csv_path=MethodDataGeneratorConfig.CSV_PATH,
            batch_size=MethodDataGeneratorConfig.BATCH_SIZE,
            stage=stage,
            alphabet=MethodDataGeneratorConfig.ALPHABET,
            max_length=MethodDataGeneratorConfig.MAX_LENGTH
        )


if __name__ == '__main__':
    print("Starting")
    MethodDataGeneratorConfig.BATCH_SIZE = 181
    db = MethodDataGeneratorConfig.build(Stage.VAL)
    print(len(db))
    original, duplicate, not_duplicate = db[1]

    import matplotlib.pyplot as plt

    plt.imshow(original[0], cmap='gray')
    plt.show()

    text = db.decode_gt(original[0])
    print(text)
    print('\n\n')

    text = db.decode_gt(duplicate[0])
    print(text)
    print('\n\n')

    text = db.decode_gt(not_duplicate[0])
    print(text)
    print('\n\n')


