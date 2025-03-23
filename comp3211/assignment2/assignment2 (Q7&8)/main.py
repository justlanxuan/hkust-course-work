import argparse
import sys

import pygame
from problem import SearchProblem
from search import Search

from maze_maps import MAZE_MAPS

# Color definitions
BLACK = (0, 0, 0)
WHITE = (255, 255, 255)
BLUE = (0, 0, 255)
GREEN = (0, 255, 0)
RED = (255, 0, 0)
YELLOW = (255, 255, 0)

TILE_SIZE = 30


class MazeProblemMultiGoal(SearchProblem):
    """
    A search problem where all 'C' in the map must be collected to complete.

    State structure: (row, col, collected_goals)
      - row, col:  The current grid position of the agent
      - collected_goals: frozenset, a set of coordinates for collected goal points
    """

    def __init__(self, maze):
        self.maze = maze
        self.rows = len(maze)
        self.cols = len(maze[0])

        # Collect all goal positions marked as 'C'
        self.goals = set()
        for r in range(self.rows):
            for c in range(self.cols):
                if self.maze[r][c] == "C":
                    self.goals.add((r, c))

        # Find a starting position, choosing the first non-wall tile
        self.start_pos = None
        for r in range(self.rows):
            for c in range(self.cols):
                if self.maze[r][c] != "#":  # Any non-wall tile is considered a start
                    self.start_pos = (r, c)
                    break
            if self.start_pos is not None:
                break

        # If the starting position itself is a 'C', count it as collected
        start_collected = set()
        if self.start_pos in self.goals:
            start_collected.add(self.start_pos)

        # Store the initial state
        self.start_state = (
            self.start_pos[0],
            self.start_pos[1],
            frozenset(start_collected),
        )

    def get_start_state(self):
        return self.start_state

    def is_goal_state(self, state):
        """
        The goal state is reached when the number of collected goal points equals the total goal points.
        """
        (r, c, collected) = state
        return len(collected) == len(self.goals)

    def get_successors(self, state):
        """
        Returns a list of possible next states, updating collected 'C' if applicable.
        """
        (r, c, collected) = state
        successors = []
        directions = [(-1, 0), (1, 0), (0, -1), (0, 1)]
        for dr, dc in directions:
            nr, nc = r + dr, c + dc
            if 0 <= nr < self.rows and 0 <= nc < self.cols:
                if self.maze[nr][nc] != "#":  # Can move if it's not a wall
                    new_collected = set(collected)
                    # If the new position is an uncollected 'C', add it to the collected set
                    if (nr, nc) in self.goals and (nr, nc) not in new_collected:
                        new_collected.add((nr, nc))
                    successors.append(((nr, nc, frozenset(new_collected)), 1))
        return successors


def parse_args():
    parser = argparse.ArgumentParser(description="Maze Search Algorithm")
    parser.add_argument(
        "--algorithm",
        choices=["dfs", "astar", "random"],
        default="random",
        help="Search algorithm to use (dfs or astar)",
    )
    parser.add_argument(
        "--map", type=int, default=0, help="Index of the maze map to use"
    )
    parser.add_argument(
        "--tick", type=int, default=10, help="Clock tick speed for animation"
    )
    return parser.parse_args()


def main():
    args = parse_args()

    pygame.init()
    clock = pygame.time.Clock()

    # Select the maze map
    maze = MAZE_MAPS[args.map]
    problem = MazeProblemMultiGoal(maze)

    # Choose the search algorithm:
    if args.algorithm == "random":
        search_generator = Search.random_search(problem)
        algo_name = "Random"
    elif args.algorithm == "astar":
        search_generator = Search.a_star_search(problem)
        algo_name = "A*"
    elif args.algorithm == "dfs":
        search_generator = Search.depth_first_search(problem)
        algo_name = "DFS"
    else:
        raise ValueError(f"Invalid algorithm: {args.algorithm}")

    # Compute window size
    width = len(maze[0]) * TILE_SIZE
    height = len(maze) * TILE_SIZE
    screen = pygame.display.set_mode((width, height))
    pygame.display.set_caption(f"Maze Search ({algo_name} - Collect All C)")

    path = []
    visited = set()
    agent_pos = problem.start_state[:2]

    running = True
    while running:
        clock.tick(args.tick)

        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                running = False

        screen.fill(BLACK)

        # Draw the map
        for r in range(problem.rows):
            for c in range(problem.cols):
                cell = maze[r][c]
                color = WHITE if cell != "#" else BLACK
                if cell == "C":
                    color = GREEN
                rect = pygame.Rect(c * TILE_SIZE, r * TILE_SIZE, TILE_SIZE, TILE_SIZE)
                pygame.draw.rect(screen, color, rect)

        # Draw visited nodes (blue)
        for vr, vc, _ in visited:
            if maze[vr][vc] == "C":
                continue
            rect = pygame.Rect(vc * TILE_SIZE, vr * TILE_SIZE, TILE_SIZE, TILE_SIZE)
            pygame.draw.rect(screen, BLUE, rect)

        # Process the search step by step
        try:
            current_state = next(search_generator)
            visited.add(current_state)
            agent_pos = current_state[:2]
        except StopIteration as result:
            path = result.value[0] if result.value else []
            break

        # Highlight the currently visited node (yellow)
        if agent_pos:
            ar, ac = agent_pos
            agent_rect = pygame.Rect(
                ac * TILE_SIZE, ar * TILE_SIZE, TILE_SIZE, TILE_SIZE
            )
            pygame.draw.rect(screen, YELLOW, agent_rect)

        pygame.display.flip()

    # Move the agent along the path
    agent_index = 0
    while agent_index < len(path) and running:
        clock.tick(args.tick)
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                running = False

        screen.fill(BLACK)

        for r in range(problem.rows):
            for c in range(problem.cols):
                cell = maze[r][c]
                color = WHITE if cell != "#" else BLACK
                if cell == "C":
                    color = GREEN
                rect = pygame.Rect(c * TILE_SIZE, r * TILE_SIZE, TILE_SIZE, TILE_SIZE)
                pygame.draw.rect(screen, color, rect)

        for vr, vc, _ in visited:
            if maze[vr][vc] == "C":
                continue
            rect = pygame.Rect(vc * TILE_SIZE, vr * TILE_SIZE, TILE_SIZE, TILE_SIZE)
            pygame.draw.rect(screen, BLUE, rect)

        if agent_index < len(path):
            ar, ac, _ = path[agent_index]
            agent_pos = (ar, ac)
            agent_rect = pygame.Rect(
                ac * TILE_SIZE, ar * TILE_SIZE, TILE_SIZE, TILE_SIZE
            )
            pygame.draw.rect(screen, RED, agent_rect)
            agent_index += 1

        pygame.display.flip()

    pygame.quit()
    sys.exit()


if __name__ == "__main__":
    main()
