#! /usr/bin/env python

import sys

def dirReduc(plan):
    opposite = {'NORTH': 'SOUTH', 'EAST': 'WEST', 'SOUTH': 'NORTH', 'WEST': 'EAST'}

    new_plan = []
    for d in plan:
        if new_plan and new_plan[-1] == opposite[d]:
            print("new_plan is ", new_plan, " opposite[d] is ", opposite[d])
            new_plan.pop()
        else:
            print("Appending ", d)
            new_plan.append(d)
    return new_plan
##############################################################################
#MAIN
##############################################################################
def main(argv): 
    val = dirReduc(["NORTH", "SOUTH", "SOUTH", "EAST", "WEST", "NORTH", "WEST"])
if __name__ == "__main__":
    main(sys.argv[1:])
