from Agent import Agent, AgentGreedy
from WarehouseEnv import WarehouseEnv, manhattan_distance
import random
from func_timeout import func_timeout, FunctionTimedOut
import math


def calc_g(env: WarehouseEnv, robot_id: int):
    min_battery = 6
    max_battery = 20
    robot = env.get_robot(robot_id)
    other_robot = env.get_robot((robot_id + 1) % 2)
    if(robot.credit < other_robot.credit and robot.battery <= min_battery and robot.credit > min_battery):
        return -max_battery - min(manhattan_distance(robot.position, env.charge_stations[0].position), manhattan_distance(robot.position, env.charge_stations[1].position))
    elif(robot.package is None):
        free_packages = [package for package in env.packages if package.on_board == True]
        free_packages_dist = [manhattan_distance(robot.position, package.position) for package in free_packages]
        return robot.credit - min(free_packages_dist)/10
    else:
        return robot.credit - manhattan_distance(robot.position, robot.package.destination)/10 + manhattan_distance(robot.package.position, robot.package.destination)/2
# TODO: section a : 3
def smart_heuristic(env: WarehouseEnv, robot_id: int):
    if env.done():
        return (env.robots[robot_id].credit - env.robots[(robot_id + 1) % 2].credit)*10
    g0 = calc_g(env, robot_id)
    g1 = calc_g(env, (robot_id + 1) % 2)
    return (g0-g1)
   

class AgentGreedyImproved(AgentGreedy):
    def heuristic(self, env: WarehouseEnv, robot_id: int):
        return smart_heuristic(env, robot_id)


class AgentMinimax(Agent):
    # TODO: section b : 1
    def run_step(self, env: WarehouseEnv, agent_id, time_limit):
        operators, _ = self.successors(env, agent_id)
        self.operator = random.choice(operators)
        try:
            func_timeout(0.7*time_limit, self.anyTime_mini_max, args=(env,agent_id), kwargs=None)
            return self.operator
        except FunctionTimedOut:
            return self.operator
        
    def rb_mini_max(self, env: WarehouseEnv,orig_agent_id, curr_agent_id, d):
        if env.done() or d == 0:
            return smart_heuristic(env, orig_agent_id)
        operators = env.get_legal_operators(curr_agent_id)
        children = [env.clone() for _ in operators]
        next_id = (curr_agent_id + 1)%2
        if env.robots[next_id].battery <= 0:
            next_id = curr_agent_id
        for child, op in zip(children, operators):
            child.apply_operator(curr_agent_id, op)
        children_heuristics = [self.rb_mini_max(child, orig_agent_id, next_id, d-1) for child in children]
        
        if curr_agent_id == orig_agent_id: #max player
            return max(children_heuristics)

        else: #min player
            return min(children_heuristics)         
    

    def anyTime_mini_max(self, env: WarehouseEnv, agent_id):
        
        d = 1
        operators = env.get_legal_operators(agent_id)
        children = [env.clone() for _ in operators]
        for child, op in zip(children, operators):
            child.apply_operator(agent_id, op)
        while True:
            children_heuristics = [self.rb_mini_max(child,agent_id, (agent_id+1)%2, d-1) for child in children]
            self.operator = operators[children_heuristics.index(max(children_heuristics))] 
            d = d + 1
            
            

class AgentAlphaBeta(Agent):
    # TODO: section c : 1
    def run_step(self, env: WarehouseEnv, agent_id, time_limit):
        operators, _ = self.successors(env, agent_id)
        self.operator = random.choice(operators)
        try:
            func_timeout(0.7*time_limit, self.anyTime_alpha_beta, args=(env,agent_id), kwargs=None)
            return self.operator
        except FunctionTimedOut:
            return self.operator
        
    def rb__alpha_beta(self, env: WarehouseEnv,orig_agent_id, curr_agent_id, d, alpha, beta):
        if env.done() or d == 0:
            return smart_heuristic(env, orig_agent_id)
        operators = env.get_legal_operators(curr_agent_id)
        children = [env.clone() for _ in operators]
        next_id = (curr_agent_id + 1)%2
        if env.robots[next_id].battery <= 0:
            next_id = curr_agent_id
            
        if curr_agent_id == orig_agent_id: #max player
            curr_max = -math.inf
            for child, op in zip(children, operators):
                child.apply_operator(curr_agent_id, op)
                v = self.rb__alpha_beta(child, orig_agent_id, next_id, d-1, alpha, beta)
                curr_max = max([curr_max, v])
                alpha = max([curr_max, alpha])
                if curr_max >=beta:
                    return math.inf
            return curr_max
        else: #min player
            curr_min = math.inf
            for child, op in zip(children, operators):
                child.apply_operator(curr_agent_id, op)
                v = self.rb__alpha_beta(child, orig_agent_id, next_id, d-1, alpha, beta)
                curr_min = min([curr_min, v])
                beta = min([curr_min,beta])
                if curr_min <= alpha:
                    return -math.inf
            return curr_min         
    

    def anyTime_alpha_beta(self, env: WarehouseEnv, agent_id):
        
        d = 1
        operators = env.get_legal_operators(agent_id)
        children = [env.clone() for _ in operators]
        for child, op in zip(children, operators):
            child.apply_operator(agent_id, op)
        while True:
            children_heuristics = [self.rb__alpha_beta(child,agent_id, (agent_id+1)%2, d-1, -math.inf, math.inf) for child in children]
            self.operator = operators[children_heuristics.index(max(children_heuristics))] 
            d = d + 1


class AgentExpectimax(Agent):
    # TODO: section d : 1
    def run_step(self, env: WarehouseEnv, agent_id, time_limit):
        operators, _ = self.successors(env, agent_id)
        self.operator = random.choice(operators)
        try:
            func_timeout(0.7*time_limit, self.anyTime_expectimax, args=(env,agent_id), kwargs=None)
            return self.operator
        except FunctionTimedOut:
            return self.operator
        
    def rb__expectimax(self, env: WarehouseEnv,orig_agent_id, curr_agent_id, d):
        if env.done() or d == 0:
            return smart_heuristic(env, orig_agent_id)
        operators = env.get_legal_operators(curr_agent_id)
        children = [env.clone() for _ in operators]
        next_id = (curr_agent_id + 1)%2
        if env.robots[next_id].battery <= 0:
            next_id = curr_agent_id
            
        if curr_agent_id == orig_agent_id: #max player
            curr_max = -math.inf
            for child, op in zip(children, operators):
                child.apply_operator(curr_agent_id, op)
                v = self.rb__expectimax(child, orig_agent_id, next_id, d-1)
                curr_max = max([curr_max, v])
            return curr_max
        else: #min player
            num = len(operators)
            if 'pick up' in operators:
                num+=1
            if 'move east' in operators:
                num+=1
            v = 0
            for child, op in zip(children, operators):
                child.apply_operator(curr_agent_id, op)
                if (op == 'move east') or (op == 'pick up'):
                    v += (2/num)*self.rb__expectimax(child, orig_agent_id, next_id, d-1)
                else:
                    v += (1/num)*self.rb__expectimax(child, orig_agent_id, next_id, d-1)
            return v         
    

    def anyTime_expectimax(self, env: WarehouseEnv, agent_id):
        
        d = 1
        operators = env.get_legal_operators(agent_id)
        children = [env.clone() for _ in operators]
        for child, op in zip(children, operators):
            child.apply_operator(agent_id, op)
        while True:
            children_heuristics = [self.rb__expectimax(child,agent_id, (agent_id+1)%2, d-1) for child in children]
            self.operator = operators[children_heuristics.index(max(children_heuristics))] 
            d = d + 1


# here you can check specific paths to get to know the environment
class AgentHardCoded(Agent):
    def __init__(self):
        self.step = 0
        # specifiy the path you want to check - if a move is illegal - the agent will choose a random move
        self.trajectory = ["move north", "move east", "move north", "move north", "pick_up", "move east", "move east",
                           "move south", "move south", "move south", "move south", "drop_off"]

    def run_step(self, env: WarehouseEnv, robot_id, time_limit):
        if self.step == len(self.trajectory):
            return self.run_random_step(env, robot_id, time_limit)
        else:
            op = self.trajectory[self.step]
            if op not in env.get_legal_operators(robot_id):
                op = self.run_random_step(env, robot_id, time_limit)
            self.step += 1
            return op

    def run_random_step(self, env: WarehouseEnv, robot_id, time_limit):
        operators, _ = self.successors(env, robot_id)

        return random.choice(operators)