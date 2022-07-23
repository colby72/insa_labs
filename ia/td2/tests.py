from data import *
from algorithms import *

# test show_path function
"""path = [arad, sibiu, rimnieu, pitesti, bucharest]
show_path(path)"""

# test get_neighbours function
"""neighbours = get_neighbours(arad, bucharest)
for t in neighbours:
    print(t.name, " ", end="")
print()"""

path = find_path_min(arad, bucharest)
show_path(path)
