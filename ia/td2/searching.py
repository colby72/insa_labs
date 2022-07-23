from data import *
from algorithms import *

name = input("Enter traveler name : ")
print("--------------------------------------")
print("MAP : Towns list")
print("--------------------------------------")
i = 0
for t in towns_list:
    print(t.name, " ", end="")
    i += 1
    if i%7==0:
        print()

print("\n\n--------------------------------------")
print("Selecting the initial start town")
print("--------------------------------------")
#scountry_name = input("Enter the country's name : ")
stown_name = input("Enter the town's name : ")

print("\n--------------------------------------")
print("Selecting the destination town")
print("--------------------------------------")
#dcountry_name = input("Enter the country's name : ")
dtown_name = input("Enter the town's name : ")
print()

for t in towns_list:
    if t.name==stown_name:
        stown = t
    if t.name==dtown_name:
        dtown = t

traveler = Traveler(name, stown, dtown)
traveler.update_status()
traveler.show_status()

print("\n--------------------------------------")
print("MAP : Found paths")
print("--------------------------------------")
path = bfs_search(stown, dtown)
print("Found path with BFS")
show_path(path)
print()
path = dfs_search(stown, dtown)
print("Found path with DFS")
show_path(path)
print()
#path = dijkstra_search(stown, dtown)
print("Found path with Dijkstra")
show_path(None)
