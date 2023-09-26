testList = [ [(0,0),(0,1)], [(1,1),(1,2)], [(1,3)]     ]
testList[0].extend(testList[1])
testList.remove( testList[1]    )
print(testList)