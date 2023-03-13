#! /usr/bin/env python

import sys
import matplotlib.pyplot as plt
from math import exp, pow

def f(x, shift, scale):
    return ( pow(( exp((x-shift)/scale) - exp(-(x-shift)/scale)   )/(exp((x-shift)/scale) + exp(-(x-shift)/scale)),4)   )
#############################################################################
#MAIN
##############################################################################
def main(argv): 
    shift = 1450.
    scale = 3500.
    y = [f(x,shift,scale) for x in range(1500,10000)]
    x = [x for x in range(1500,10000)]
    plt.plot(x,y)
    plt.ylabel('HT')
    plt.show()
if __name__ == "__main__":
    main(sys.argv[1:])
