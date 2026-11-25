class MapColoringCSP:

    def __init__(self, regions, neighbors, colors):
        self.neighbors = neighbors
        self.regions = regions
        self.colors = colors
        self.solution  = None

    def is_valid(self, region, color, assignment):
        for neighbor in self.neighbors[region]:
            if neighbor in assignment and assignment[neighbor] == color:
                return False
        return True

    def backtracking_search(self, assignment={}):
        if len(assignment) == len(self.regions):
            return assignment

        unassigned_regions = [r for r in self.regions if r not in assignment]
        current_region = unassigned_regions[0]

        for color in self.colors:
            if self.is_valid(current_region, color, assignment):
                assignment[current_region] = color

                result = self.backtracking_search(assignment)
                if result is not None:
                    return result

                del assignment[current_region]

        return None

    def solve(self):
        self.solution = self.backtracking_search()
        return self.solution

if __name__ == "__main__":
    indian_states = ["Maharashtra", "Goa", "Karnataka", "Kerala", "Tamil Nadu", "Andhra Pradesh", "Telangana", "Madhya Pradesh"]

    state_neighbors = {
        "Maharashtra": ["Goa", "Karnataka", "Telangana", "Madhya Pradesh"],
        "Goa": ["Maharashtra", "Karnataka"],
        "Karnataka": ["Maharashtra", "Goa", "Kerala", "Tamil Nadu", "Andhra Pradesh", "Telangana"],
        "Kerala": ["Karnataka", "Tamil Nadu"],
        "Tamil Nadu": ["Kerala", "Karnataka", "Andhra Pradesh"],
        "Andhra Pradesh": ["Tamil Nadu", "Karnataka", "Telangana", "Madhya Pradesh"],
        "Telangana": ["Maharashtra", "Karnataka", "Andhra Pradesh"],
        "Madhya Pradesh": ["Maharashtra", "Andhra Pradesh"]
    }

    available_colors = ["Red", "Green", "Blue", "Yellow"]

    csp = MapColoringCSP(indian_states, state_neighbors, available_colors)

    solution = csp.solve()

    if solution:
        print("\n Solution found successfully")
        print(f"Minimum colors used constraint satisfied using: {available_colors}\n")
        for state, color in solution.items():
            print(f"{state:<15} ---> Color: {color}")

    else:
        print("\nNo solution found with the given colors")

    

    
    
