# search.py
import heapq
import random

from problem import SearchProblem


class Search:
    """
    General search class providing reference implementations for DFS and A*.
    """

    @staticmethod
    def depth_first_search(problem: SearchProblem):
        """
        Implements Depth-First Search (DFS) using a stack (Last-In-First-Out).

        TODO:
        - Use a stack to manage the search frontier.
        - Maintain a set of visited states to avoid re-exploration.
        - Use `problem.get_start_state()` to get the initial state.
        - Use `problem.is_goal_state(state)` to check if the goal is reached.
        - Use `problem.get_successors(state)` to expand the search tree.

        Implementation Notes:
        - Yield each visited state to allow step-by-step visualization.
        - Return a tuple: (path from start to goal, set of visited states).
        - If no path is found, return (None, visited).
        """
        # TODO: Implement DFS here
        start = problem.get_start_state()
        visited = set()
        stack = [(start, [])]
        while stack:
            current_state, path = stack.pop()
            if current_state in visited:
                continue
            visited.add(current_state)
            yield current_state  # Yield current state for visualization

            if problem.is_goal_state(current_state):
                return (path + [current_state], visited)
            for successor, _ in problem.get_successors(current_state):  # Maintain order by reversing
                if successor not in visited:
                    stack.append((successor, path + [current_state]))

        yield (None, visited)  # No path found
    @staticmethod
    def heuristic(goals, state):
        """
        Heuristic function used in A* search.

        TODO:
        - Implement a heuristic to estimate the cost from the current state to the goal.
        - A simple option is the Manhattan distance to the nearest uncollected goal.
        """
        # TODO: Implement heuristic function here
        # manhattan distance
        (r,c,collected) = state
        uncollected_goals = goals - collected
        if not uncollected_goals:
            return 0
        return min(abs(r - gr) + abs(c - gc) for gr, gc in uncollected_goals)


    @staticmethod
    def a_star_search(problem: SearchProblem):
        """
        Implements A* search using a priority queue.

        TODO:
        - Use a priority queue (heap) to prioritize states based on f = g + h.
        - g(n): The actual cost from the start state to the current state.
        - h(n): The heuristic estimate of the remaining cost to the goal.
        - Use `problem.get_start_state()` to get the initial state.
        - Use `problem.is_goal_state(state)` to check if the goal is reached.
        - Use `problem.get_successors(state)` to expand the search tree.

        Implementation Notes:
        - Yield each visited state to allow step-by-step visualization.
        - Return a tuple: (path from start to goal, set of visited states).
        - If no path is found, return (None, visited).
        """
        # TODO: Implement A* search here
        # init
        start = problem.get_start_state()
        goals = problem.goals
        visited = set()
        heap = []
        heapq.heappush(heap, (0, 0, start, []))
        g_values = {start: 0}

        while heap:
            f, g, current_state, path = heapq.heappop(heap)
            if current_state in visited:
                continue
            visited.add(current_state)
            yield current_state  # Yield current state

            if problem.is_goal_state(current_state):
                return (path + [current_state], visited)

            for successor, cost in problem.get_successors(current_state):
                new_g = g + cost
                if successor not in g_values or new_g < g_values.get(successor, float('inf')):
                    g_values[successor] = new_g
                    h = Search.heuristic(goals, successor)
                    new_f = new_g + h
                    heapq.heappush(heap, (new_f, new_g, successor, path + [current_state]))

        yield (None, visited)  # No path found



    @staticmethod
    def random_search(problem: SearchProblem):
        """
        A simple random walk search algorithm.

        This method demonstrates an uninformed search strategy where the agent
        moves randomly without considering an optimal path.

        Implementation:
        - Start from `problem.get_start_state()`.
        - Randomly select a successor from `problem.get_successors(state)`.
        - Continue until reaching a goal state.

        Returns:
        - A tuple: (random path from start to goal, set of visited states).
        - If no path is found, return (None, visited).
        """
        start = problem.get_start_state()
        if problem.is_goal_state(start):
            return [], {start}

        visited = set()
        state = start
        path = []

        while True:
            visited.add(state)
            yield state  # Yield the current state for visualization

            if problem.is_goal_state(state):
                return path, visited  # Return the discovered path

            successors = problem.get_successors(state)
            if not successors:
                break  # No available moves, terminate search

            # Randomly select the next move from available successors
            next_state, _ = random.choice(successors)

            # Prevent getting stuck by revisiting the last state too frequently
            if len(path) > 1 and next_state == path[-1]:
                continue  # Try another random move instead of oscillating

            path.append(next_state)
            state = next_state  # Move to the new state

        return None, visited  # No valid path found
