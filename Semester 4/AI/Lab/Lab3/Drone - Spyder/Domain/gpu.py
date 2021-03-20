from settings import *
import numpy as np
from numba import jit

@jit(nopython=True)  
def generateIndividual():
    while len(repres) < INDIVIDUAL_SIZE:
        geneStrength = np.random.randint(1, GENE_STRENGTH + 1)
        gene = DIRECTIONS[np.random.randint(0, 4)]
        repres += [gene[:] for _ in range(geneStrength)]
        
    return repres[:INDIVIDUAL_SIZE]


print(generateIndividual())