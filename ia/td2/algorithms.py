from data import *

def get_neighbours(start, dest):
    neighbours = list(start.distances.keys())
    k = 0
    j = 0
    for i in range(1, len(neighbours)):
        if neighbours[i].region==dest.region:
            (neighbours[k], neighbours[i]) = (neighbours[i], neighbours[k])
            k += 1
    for i in range(1, k):
        if start.distances[neighbours[i]] < start.distances[neighbours[j]]:
            (neighbours[i], neighbours[j]) = (neighbours[j], neighbours[i])
            j += 1
    return neighbours

def get_neighbours_opt(start, dest):
    if (start.region==dest.region):
        return get_neighbours(start, dest)
    neighbours = list(start.distances.keys())
    k = 0
    j = 0
    if (start.region=="centre") or (start.region=="west" and dest.region=="east") or (start.region=="east" and dest.region=="west"):
        for i in range(1, len(neighbours)):
            if neighbours[i].region==dest.region:
                (neighbours[k], neighbours[i]) = (neighbours[i], neighbours[k])
                k += 1
        l = k
        for i in range(k, len(neighbours)):
            if neighbours[i].region=="centre":
                (neighbours[i], neighbours[l]) = (neighbours[l], neighbours[i])
                l += 1
        for i in range(1, k):
            if start.distances[neighbours[i]]<start.distances[neighbours[j]]:
                (neighbours[i], neighbours[j]) = (neighbours[i], neighbours[j])
                j +=1
        j = k
        for i in range(k+1, l):
            if start.distances[neighbours[i]]<start.distances[neighbours[j]]:
                (neighbours[i], neighbours[j]) = (neighbours[i], neighbours[j])
                j += 1
    if (start.region!="centre" and dest.region=="centre"):
        for i in range(1, len(neighbours)):
            if neighbours[i].region==dest.region:
                (neighbours[k], neighbours[i]) = (neighbours[i], neighbours[k])
                k += 1
        l = k
        for i in range(k, len(neighbours)):
            if neighbours[i].region==start.region:
                (neighbours[i], neighbours[l]) = (neighbours[l], neighbours[i])
                l += 1
        for i in range(1, k):
            if start.distances[neighbours[i]]<start.distances[neighbours[j]]:
                (neighbours[i], neighbours[j]) = (neighbours[i], neighbours[j])
                j +=1
        j = k
        for i in range(k+1, l):
            if start.distances[neighbours[i]]<start.distances[neighbours[j]]:
                (neighbours[i], neighbours[j]) = (neighbours[i], neighbours[j])
                j += 1
    return neighbours

def find_path_min(start, dest, path=[], shots=0):
    neighbours = get_neighbours(start, dest)
    path.append(start)
    if dest in neighbours:
        path.append(dest)
        shots += 1
        print("Total shots : ", shots)
        return path
    for neib in neighbours:
        if not (neib in path):
            shots += 1
            path = find_path_min(neib, dest, path, shots)
            return path

def find_path_min_opt(start, dest, path=[], shots=0):
    neighbours = get_neighbours_opt(start, dest)
    path.append(start)
    if dest in neighbours:
        path.append(dest)
        shots += 1
        print("Total shots : ", shots)
        return path
    for neib in neighbours:
        if not (neib in path):
            shots += 1
            path = find_path_min(neib, dest, path, shots)
            return path

def find_path_opt(start, dest):
    neighbours = get_neighbours_opt(start, dest)

def find_meeting_path_min(start, dest):
    choices = []
    neighbours = get_neighbours_opt(start, dest)
    for neib in neighbours:
        path = find_path_min_opt(neib, dest)
        if (type(path) is list) and (len(path)>0) and (path[-1]==dest):
            choices.append(path)
            print("*********")
            show_path(path)
            print("*********")
    min = len(choices[0])
    for p in choices:
        print("_*_*__*")
        show_path(p)
        print("_*_*__*")
        l = len(p)
        if (l%2!=0) and (l>min):
            choices.remove(p)
        else:
            if start in p:
                i=0
                while (len(p)<i) and (p[i]!=start):
                    p.pop(i)
                    i += 1
            p.insert(0, start)
            min = l
    if len(choices)>0:
        return choices[0]
    else:
        return None

def bfs(start, dest):
    explore = []
    explore.append(start)
    explored = []
    path = dict()
    while len(explore)>0:
        s = explore[0]
        explore.remove(s)
        subs = get_neighbours(s, dest)
        for sub in subs:
            if (sub not in explored) and (sub not in explore):
                explore.append(sub)
                path[sub] = s
                if sub==dest:
                    return path
        explored.append(s)
    return None

def bfs_search(start, dest):
    paths = bfs(start, dest)
    if paths==None:
        return None
    path = reconstruct_path(start, dest, paths)
    return path

def dfs(start, dest):
    explored = []
    explore = []
    path = dict()
    explore.append(start)
    while len(explore)>0:
        s = explore[-1]
        explore.remove(s)
        subs = get_neighbours(s, dest)
        for sub in subs:
            if sub not in explored:
                explore.append(sub)
                path[sub] = s
                explored.append(sub)
            if sub==dest:
                return path
    return None

def dfs_search(start, dest):
    paths = dfs(start, dest)
    if paths==None:
        return None
    path = reconstruct_path(start, dest, paths)
    return path

def dijkstra(start, dest):
    explore = []
    explored = []
    path = dict()
    explore.append((start, 0))
    while len(explore)>0:
        print("halo")
        s = explore[0] # get the nearest frontier node so far
        subs = get_neighbours(s[0], dest)

        # for every neighbour of the node
        for sub in subs:
            if (sub not in explored) and (sub not in explore):
                # do the path and calculate its distance from start node
                path[sub] = s[0]
                if sub==dest:
                    return path
                path_sub = reconstruct_path(start, sub, path)
                sub_dist = distance_made(path_sub)

                # insert the sub tuple in explore correctly (by order)
                min_dist = explore[0][1]
                i = 0
                print("a", sub_dist)
                print("b", explore[i][1])
                print("c", sub_dist>explore[i][1])
                while (i<len(explore)) and (sub_dist>explore[i][1]):
                    i += 1
                if i<len(explore):
                    explore.insert(i, (sub, sub_dist))
                else:
                    explore.append((sub, sub_dist))
        explored.append(s)
        explore.remove(explore[0])
    return None

def dijkstra_search(start, dest):
    paths = dijkstra(start, dest)
    if paths==None:
        return None
    path = reconstruct_path(start, dest, paths)
    return path
