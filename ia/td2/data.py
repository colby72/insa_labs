from Traveler import *
from Town import *


oradea = Town("oradea", "west")
zerind = Town("zerind", "west")
arad = Town("arad", "west")
timisoara = Town("timisoara", "west")
lugoj = Town("lugoj", "west")
drobeta = Town("drobeta", "west")
mehadia = Town("mehadia", "west")
craiova = Town("craiova")
pitesti = Town("pitesti")
rimnieu = Town("rimnieu")
sibiu = Town("sibiu")
fagaras = Town("fagaras")
bucharest = Town("bucharest")
giurgiu = Town("giurgiu")
urziceni = Town("urziceni", "east")
eforic = Town("eforic", "east")
hirsova = Town("hirsova", "east")
vaslui = Town("vaslui", "east")
lasi = Town("lasi", "east")
neamt = Town("neamt", "east")

oradea.distances = {zerind:71, sibiu:151}
zerind.distances = {arad: 75, oradea: 71}
arad.distances = {timisoara:118, zerind: 75, sibiu: 140}
timisoara.distances = {arad: 118, lugoj:111}
lugoj.distances = {timisoara: 111, mehadia: 70}
drobeta.distances = {mehadia: 75, craiova: 120}
mehadia.distances = {lugoj: 70, drobeta: 75}
craiova.distances = {drobeta: 120, pitesti: 138, rimnieu: 146}
pitesti.distances = {rimnieu: 97, bucharest: 101, craiova: 138}
rimnieu.distances = {pitesti: 97, sibiu: 80, craiova: 146}
sibiu.distances = {rimnieu: 80, arad: 140, fagaras: 99, oradea: 151}
fagaras.distances = {sibiu: 99, bucharest: 211}
bucharest.distances = {fagaras: 211, pitesti: 101, giurgiu: 90, urziceni: 85}
giurgiu.distances = {bucharest: 90}
urziceni.distances = {bucharest: 85, hirsova: 98, vaslui: 142}
eforic.distances = {hirsova: 86}
hirsova.distances = {urziceni: 98, eforic: 86}
vaslui.distances = {urziceni: 142, lasi: 92}
lasi.distances = {vaslui: 92, neamt: 87}
neamt.distances = {lasi: 87}

towns_list = [oradea, zerind, arad, timisoara, lugoj, drobeta, mehadia,
craiova, pitesti, rimnieu, sibiu, fagaras, bucharest, giurgiu, urziceni,
eforic, hirsova, vaslui, lasi, neamt]

def distance_made(path):
    dist = 0
    for i in range(len(path)-1):
        dist += path[i].distances[path[i+1]]
    return dist

def show_path(path):
    if path==None:
        print("Sorry !! No path found :(")
    else:
        for t in path[:-1]:
            print(t.name, " ---> ", end="")
        print(path[-1].name)
        print("Total distance : ", distance_made(path))

def reconstruct_path(start, dest, paths):
    path = []
    t = dest
    while t!=start:
        path.append(t)
        t = paths[t]
    path.append(start)
    path.reverse()
    return path
