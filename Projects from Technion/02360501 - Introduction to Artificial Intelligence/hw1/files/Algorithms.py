import numpy as np

from CampusEnv import CampusEnv
from typing import List, Tuple
import heapdict


class Node():
    def __init__(self, state=0, cost=0, father=None, step=0, h=0):
        self.state = state
        self.cost_to_node = cost
        self.father = father
        self.last_step = step
        self.h_val = h
    def __eq__(self, other):
        return self.state == other.state
    
    def __ne__(self, other):
        return not (self.state == other.state)
    
    def calc_path_from_root(self):
        if self.father is None:
            return []
        path = [self.last_step]
        curr = self.father
        while not(curr.father is None):
            path.append(curr.last_step) 
            curr = curr.father
        path.reverse()
        return path
        


class DFSGAgent():
    def __init__(self) -> None:
        self.num_expended = 0
    
    def search(self, env: CampusEnv) -> Tuple[List[int], float, int]:
        self.num_expended = 0
        open = [Node(env.get_initial_state())]
        close = []
        actions = []
        return self.recursive_search(env, open, close)[0]
    
    def recursive_search(self, env: CampusEnv, open, close):
        curr_node = open.pop()
        curr_state = curr_node.state
        close.append(curr_node)
        if env.is_final_state(curr_state):
            return [(curr_node.calc_path_from_root(), curr_node.cost_to_node, self.num_expended), True]
        self.num_expended+=1

        for action, successor in env.succ(curr_state).items():
            if (Node(successor[0]) not in open) and (Node(successor[0]) not in close):
                if successor[2] == None:
                    return [([], 0 , 0), False]
                open.append(Node(state=successor[0], cost=curr_node.cost_to_node+successor[1], father=curr_node, step=action))
                result = self.recursive_search(env, open, close)
                if result[1] == True:
                    return result
        return [([], 0 , 0), False]

        
class UCSAgent():

    def __init__(self) -> None:
        self.path_to_goal = []
        self.cost_to_goal = 0
        self.expanded_nodes = 0

    def search(self, env: CampusEnv) -> Tuple[List[int], float, int]:
        self.path_to_goal = []
        self.cost_to_goal = 0
        self.expanded_nodes = 0
        open = heapdict.heapdict()
        open[env.get_initial_state()] = (0,0)
        open_nodes = {env.get_initial_state() : Node(state=env.get_initial_state(), cost=0)}
        close = set()
        self.expanded_nodes = 0

        while True:
            try:
                current = open.popitem()
                close.add(current[0])
                if env.is_final_state(current[0]):
                    self.cost_to_goal = current[1][0]
                    self.path_to_goal = open_nodes[current[0]].calc_path_from_root()
                    return (self.path_to_goal, self.cost_to_goal, self.expanded_nodes)
                self.expanded_nodes+=1
                for action, successor in env.succ(current[0]).items():
                    new_cost = current[1][0] + successor[1]
                    child = Node(state=successor[0], father=open_nodes[current[0]], cost=new_cost, step=action)
                    if child.state not in close and child.state not in open:
                       open[child.state] = (new_cost,child.state)
                       open_nodes[child.state] = child
                    elif child.state in open and open.get(child.state)[0] > new_cost:
                        open[child.state] = (new_cost,child.state)
                        open_nodes[child.state] = child
                        
            except KeyError:
                return None


class WeightedAStarAgent():
    
    def __init__(self):
        self.path_to_goal = []
        self.cost_to_goal = 0
        self.expanded_nodes = 0
    
    def calc_man_dist(self, point1, point2):
        return abs(point1[0] - point2[0]) + abs(point1[1] - point2[1])
    
    def calc_h(self, state, env):
        portal_price = 100
        state_point = env.to_row_col(state)
        man_distances = [self.calc_man_dist(state_point,env.to_row_col(goal_point)) for goal_point in env.get_goal_states()]
        man_distances.append(portal_price)
        return min(man_distances)
    
    def search(self, env: CampusEnv, h_weight) -> Tuple[List[int], float, int]:
        self.path_to_goal = []
        self.cost_to_goal = 0
        self.expanded_nodes = 0
        open = heapdict.heapdict()
        open[env.get_initial_state()] = (h_weight*self.calc_h(env.get_initial_state(),env),env.get_initial_state())
        open_nodes = {env.get_initial_state() : Node(state=env.get_initial_state(), cost=0)}
        close = {}
        while True:
            try:
                current = open.popitem()
                current_node = open_nodes[current[0]]
                open_nodes.pop(current[0])
                close[current[0]] = current_node
                if env.is_final_state(current_node.state):
                    self.cost_to_goal = current_node.cost_to_node
                    self.path_to_goal = current_node.calc_path_from_root()
                    return (self.path_to_goal, self.cost_to_goal, self.expanded_nodes)
                self.expanded_nodes+=1
                for action, successor in env.succ(current_node.state).items():
                    new_cost = current_node.cost_to_node + successor[1]
                    child = Node(state=successor[0], father=current_node, cost=new_cost, step=action)
                    if child.state not in close and child.state not in open:
                       open[child.state] = (h_weight*self.calc_h(child.state, env) + (1-h_weight)*child.cost_to_node, child.state)
                       open_nodes[child.state] = child
                    elif child.state in open:
                        if open_nodes[child.state].cost_to_node > new_cost:
                            open[child.state] = (h_weight*self.calc_h(child.state,env) + (1-h_weight)*new_cost, child.state)
                            open_nodes[child.state].cost_to_node = child.cost_to_node
                            open_nodes[child.state].last_step = child.last_step
                            open_nodes[child.state].father = child.father
                    else:
                        curr = close[child.state]
                        if curr.cost_to_node > new_cost:
                            curr.cost_to_node = child.cost_to_node
                            curr.last_step = child.last_step
                            curr.father = child.father
                            open[child.state] = (h_weight*self.calc_h(child.state,env) + (1-h_weight)*new_cost , child.state)
                            open_nodes[child.state] = curr
                            close.pop(child.state)
                        
            except KeyError:
                return None   



class AStarAgent():
    
    def __init__(self):
        self.w_a_star = WeightedAStarAgent()

    def search(self, env: CampusEnv) -> Tuple[List[int], float, int]:
        return self.w_a_star.search(env, h_weight=0.5)

