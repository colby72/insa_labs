# search.py
# ---------
# Licensing Information:  You are free to use or extend these projects for
# educational purposes provided that (1) you do not distribute or publish
# solutions, (2) you retain this notice, and (3) you provide clear
# attribution to UC Berkeley, including a link to http://ai.berkeley.edu.
#
# Attribution Information: The Pacman AI projects were developed at UC Berkeley.
# The core projects and autograders were primarily created by John DeNero
# (denero@cs.berkeley.edu) and Dan Klein (klein@cs.berkeley.edu).
# Student side autograding was added by Brad Miller, Nick Hay, and
# Pieter Abbeel (pabbeel@cs.berkeley.edu).


"""
In search.py, you will implement generic search algorithms which are called by
Pacman agents (in searchAgents.py).
"""

import util

class SearchProblem:
    """
    This class outlines the structure of a search problem, but doesn't implement
    any of the methods (in object-oriented terminology: an abstract class).

    You do not need to change anything in this class, ever.
    """

    def getStartState(self):
        """
        Returns the start state for the search problem.
        """
        util.raiseNotDefined()

    def isGoalState(self, state):
        """
          state: Search state

        Returns True if and only if the state is a valid goal state.
        """
        util.raiseNotDefined()

    def getSuccessors(self, state):
        """
          state: Search state

        For a given state, this should return a list of triples, (successor,
        action, stepCost), where 'successor' is a successor to the current
        state, 'action' is the action required to get there, and 'stepCost' is
        the incremental cost of expanding to that successor.
        """
        util.raiseNotDefined()

    def getCostOfActions(self, actions):
        """
         actions: A list of actions to take

        This method returns the total cost of a particular sequence of actions.
        The sequence must be composed of legal moves.
        """
        util.raiseNotDefined()


def tinyMazeSearch(problem):
    """
    Returns a sequence of moves that solves tinyMaze.  For any other maze, the
    sequence of moves will be incorrect, so only use this for tinyMaze.
    """
    from game import Directions
    s = Directions.SOUTH
    w = Directions.WEST
    return  [s, s, w, s, w, w, s, w]

def action_path(state, meta, root):
    """
    retourne la liste des actions comprehensibles
    on part de l'objectif et on desend jusqu'au noeud root en passaaStarSearchnt de pere en pere
    """
    from game import Directions
    n = Directions.NORTH
    s = Directions.SOUTH
    w = Directions.WEST
    e = Directions.EAST
    actions = list()
    while state != root:
        row = meta[state]
        if row[1] == "North":
            actions.append(n)
        elif row[1] == "West":
            actions.append(w)
        elif row[1] == "South":
            actions.append(s)
        elif row[1] == "East":
            actions.append(e)
        state = row[0]
    actions.reverse()
    return actions

def depthFirstSearch(problem):
    """
    Search the deepest nodes in the search tree first.

    Your search algorithm needs to return a list of actions that reaches the
    goal. Make sure to implement a graph search algorithm.

    To get started, you might want to try some of these simple commands to
    understand the search problem that is being passed in:

    print "Start:", problem.getStartState()
    print "Is the start a goal?", problem.isGoalState(problem.getStartState())
    print "Start's successors:", problem.getSuccessors(problem.getStartState())
    """
    "*** YOUR CODE HERE ***"

    visited = [] # noeuds déjà explorés
    root = problem.getStartState() # la racine du graphe modélisant notre problème
    path = dict() # un dictionnaire qui renseigne pour chaque noeud, le noeud qui le précède dans le chemin choisi
    path[root] = (None, None) 
    explore = util.Stack() # une pile des noeuds à explorer
    explore.push(root) # on commence par rajouter la racine à la pile d'exploration

    while not explore.isEmpty(): # tant qu'il nous reste des à explorer
        s = explore.list[-1] # on récupère la tête de la pile
        explore.pop()
        for s1 in problem.getSuccessors(s):
            if problem.isGoalState(s1[0]): # si on tombe sur la destination, on arrête et on retourne notre dictionnaire des chemins
                path[s1[0]] = (s, s1[1]) # on rajoute la dernière étape du chemin, celle entre la destination et noeud juste avant
                return action_path(s1[0], path, root)
            if s1[0] not in visited:
                explore.push(s1[0]) # si on n'a pas encore exploré le noeud, on l'empile à la pile des noeuds à explorer
                path[s1[0]] = (s, s1[1]) # on met à jour le dictionnaire des chemins pour indiquer comment on est arrivé à ce noeud
                visited.append(s1[0]) # on rajoute le noeud à la liste des noeuds explorés

def breadthFirstSearch(problem):
    """Search the shallowest nodes in the search tree first."""
    "*** YOUR CODE HERE ***"
    from util import Queue
    from game import Directions
    opened_set = Queue()
    closed_set = set()
    meta = dict()
    root = problem.getStartState()
    meta[root] = (None, None)
    opened_set.push(root)

    while not opened_set.isEmpty():
        subtree_root = opened_set.pop()
        if problem.isGoalState(subtree_root):
                return action_path(subtree_root, meta,root)

        for (a,b,c) in problem.getSuccessors(subtree_root):
            if (a in closed_set):
                continue
            if (a not in opened_set.list):
                meta[a] = (subtree_root , b)
                opened_set.push(a)

        closed_set.add(subtree_root)

def uniformCostSearch(problem):
    """Search the node of least total cost first."""
    "*** YOUR CODE HERE ***"
    #util.raiseNotDefined()
    root = problem.getStartState()
    path = dict()
    #visited = []
    cost = dict()
    explore = util.PriorityQueue()
    path[root] = (None, None)
    cost[root] = 0
    explore.push(root, cost[root])
    while not explore.isEmpty():
        s = explore.pop()
        if problem.isGoalState(s):
            return action_path(s, path, root)
        for s1 in problem.getSuccessors(s):
            if (s1[0] in cost.keys()) and ((cost[s]+s1[2])>cost[s1[0]]):
                continue
            cost[s1[0]] = cost[s] + s1[2]
            explore.update(s1[0], cost[s1[0]])
            path[s1[0]] = (s, s1[1])

def nullHeuristic(state, problem=None):
    """
    A heuristic function estimates the cost from the current state to the nearest
    goal in the provided SearchProblem.  This heuristic is trivial.
    """
    return 0

def aStarSearch(problem, heuristic=nullHeuristic):
    """Search the node that has the lowest combined cost and heuristic first."""
    "*** YOUR CODE HERE ***"
    from util import PriorityQueue
    from game import Directions

    frontier = PriorityQueue()
    start = problem.getStartState()
    frontier.push(start, 0)
    came_from = {} 
    cost_so_far = {} 
    #Set start state in the PriorityQueue
    came_from[start] = (None , None)
    cost_so_far[start] = 0


    while not frontier.isEmpty():
        current = frontier.pop() 
        if problem.isGoalState(current):
            return action_path(current, came_from, start)
        for (a,b,c) in problem.getSuccessors(current):
                new_cost = cost_so_far[current] + c
                if a in cost_so_far.keys(): 
                    if new_cost < cost_so_far[a]:
                       cost_so_far[a] = new_cost 
                       priority = new_cost + heuristic(a, problem) 
                       frontier.update(a, priority )
                       came_from[a] = (current,b)
                    else:
                       continue
                else:
                    cost_so_far[a] = new_cost
                    frontier.update(a, new_cost + heuristic(a, problem))
                    came_from[a] = (current,b)


# Abbreviations
bfs = breadthFirstSearch
dfs = depthFirstSearch
astar = aStarSearch
ucs = uniformCostSearch
