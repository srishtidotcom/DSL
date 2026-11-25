import heapq

class NPuzzleSolver:
    def __init__(self, n, initial_state):
        self.n = n
        self.initial_state = tuple(initial_state)
        # Standard goal state: 1, 2, ..., N*N-1, with 0 (vacant space) at the end
        self.goal_state = tuple(list(range(1, n * n)) + [0])

    def manhattan_distance(self, state):
        """Calculates the Manhattan distance heuristic for a given board state."""
        distance = 0
        for i, tile in enumerate(state):
            if tile == 0:  # Skip the vacant space
                continue
            # Target index for tile t is t - 1
            target_idx = tile - 1
            curr_r, curr_c = divmod(i, self.n)
            goal_r, goal_c = divmod(target_idx, self.n)
            distance += abs(curr_r - goal_r) + abs(curr_c - goal_c)
        return distance

    def get_neighbors(self, state):
        """Generates valid neighboring states by sliding the vacant space (0)."""
        neighbors = []
        zero_idx = state.index(0)
        r, c = divmod(zero_idx, self.n)
        
        # Possible directions for the empty space to move
        directions = [(-1, 0, "Move Up"), (1, 0, "Move Down"), (0, -1, "Move Left"), (0, 1, "Move Right")]
        
        for dr, dc, move_desc in directions:
            nr, nc = r + dr, c + dc
            if 0 <= nr < self.n and 0 <= nc < self.n:
                new_zero_idx = nr * self.n + nc
                state_list = list(state)
                # Swap empty space with the adjacent tile
                state_list[zero_idx], state_list[new_zero_idx] = state_list[new_zero_idx], state_list[zero_idx]
                neighbors.append((tuple(state_list), move_desc))
                
        return neighbors

    def solve(self):
        """Executes A* search to find the optimal path to the goal state."""
        pq = []
        g_score = 0
        h_score = self.manhattan_distance(self.initial_state)
        f_score = g_score + h_score
        
        counter = 0  # Tie-breaker for heap queue
        # Heap stores: (f_score, g_score, counter, current_state, path_states_list)
        heapq.heappush(pq, (f_score, g_score, counter, self.initial_state, [self.initial_state]))
        
        closed_set = set()
        
        while pq:
            f, g, _, current_state, path = heapq.heappop(pq)
            
            if current_state == self.goal_state:
                return path
            
            if current_state in closed_set:
                continue
            closed_set.add(current_state)
            
            for neighbor_state, _ in self.get_neighbors(current_state):
                if neighbor_state in closed_set:
                    continue
                
                new_g = g + 1
                new_h = self.manhattan_distance(neighbor_state)
                new_f = new_g + new_h
                
                counter += 1
                heapq.heappush(pq, (new_f, new_g, counter, neighbor_state, path + [neighbor_state]))
                
        return None

    def print_board(self, state):
        """Utility method to print the board state nicely."""
        print("-" * (self.n * 4 + 1))
        for i in range(0, len(state), self.n):
            row = state[i:i + self.n]
            row_str = " | ".join(str(x) if x != 0 else " " for x in row)
            print(f"| {row_str} |")
        print("-" * (self.n * 4 + 1))


# --- User Input & Execution ---
if __name__ == "__main__":
    print("=== N-Puzzle Solver (A* Search & Manhattan Distance) ===")
    n = int(input("Enter board size N (e.g., 3 for 3x3, 4 for 4x4): "))
    
    total_tiles = n * n
    print(f"\nEnter the initial configuration of {total_tiles} tiles row by row.")
    print(f"Use numbers from 1 to {total_tiles - 1}, and use '0' for the vacant space.")
    
    initial_state = []
    for i in range(n):
        row_input = input(f"Row {i+1} (space-separated values): ")
        row_values = [int(val) for val in row_input.split()]
        initial_state.extend(row_values)
        
    if len(initial_state) != total_tiles:
        print(f"Error: Expected {total_tiles} values, but got {len(initial_state)}.")
    else:
        solver = NPuzzleSolver(n, initial_state)
        print("\nSolving puzzle... Please wait.")
        
        solution_path = solver.solve()
        
        if solution_path:
            print(f"\nSolution found in {len(solution_path) - 1} steps!\n")
            for step_num, state in enumerate(solution_path):
                print(f"Step {step_num}:")
                solver.print_board(state)
        else:
            print("\nNo solution exists for the given initial configuration (it may be unsolvable).")
