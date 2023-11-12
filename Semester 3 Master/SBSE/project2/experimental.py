print("Start")
import time

start = time.perf_counter()
import tensorflow
from tqdm import tqdm
end = time.perf_counter()
print("works!", end-start)