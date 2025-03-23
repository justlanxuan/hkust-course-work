# problem.py
# Define the SearchProblem interface.


class SearchProblem:
    def get_start_state(self) -> tuple[int, int, frozenset]:
        """
        Retrieves the initial state of the search problem.

        Functionality:
        This function returns the initial state of the agent in the maze,
        which consists of its starting position and the initially collected goals.

        Parameters:
        - None

        Returns:
        - tuple[int, int, frozenset]:
        A tuple representing the starting state, structured as:
            - row (int): The row index of the starting position.
            - col (int): The column index of the starting position.
            - collected_goals (frozenset): A frozenset containing the initially collected goal positions.
        """
        raise NotImplementedError

    def is_goal_state(self, state: tuple[int, int, frozenset]) -> bool:
        """
        Checks whether the given state is a goal state.

        Functionality:
        The function determines whether the agent has collected all goal points ('C')
        in the maze. If the number of collected goals equals the total number of goals,
        the state is considered a goal state.

        Parameters:
        - state (tuple[int, int, frozenset]):
        A tuple representing the current state, structured as:
            - row (int): The row index of the agent's position.
            - col (int): The column index of the agent's position.
            - collected_goals (frozenset): A frozenset containing the positions of collected goal points.

        Returns:
        - bool:
        Returns `True` if all goal points have been collected, otherwise returns `False`.
        """
        raise NotImplementedError

    def get_successors(
        self, state: tuple[int, int, frozenset]
    ) -> list[tuple[tuple[int, int, frozenset], int]]:
        """
        Generates and returns the possible successor states from the given state.

        Functionality:
        The function explores all possible movements (up, down, left, right) from the current state,
        ensuring the agent does not move into walls ('#'). If the agent moves onto a goal ('C')
        that has not been collected, it is added to the collected goals set. Each valid move
        results in a new state with an associated cost of 1.

        Parameters:
        - state (tuple[int, int, frozenset]):
        A tuple representing the current state, structured as:
            - row (int): The row index of the agent's position.
            - col (int): The column index of the agent's position.
            - collected_goals (frozenset): A frozenset containing the positions of collected goal points.

        Returns:
        - list[tuple[tuple[int, int, frozenset], int]]:
        A list of tuples, where each tuple consists of:
            - next_state (tuple[int, int, frozenset]): The new state after moving.
            - cost (int): The cost of moving to the new state (always 1).
        """
        raise NotImplementedError
