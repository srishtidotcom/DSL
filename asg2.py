import math

def print_board(board):
    print("\n")
    print(f" {board[0]} | {board[1]} | {board[2]} ")
    print("---+---+---")
    print(f" {board[3]} | {board[4]} | {board[5]} ")
    print("---+---+---")
    print(f" {board[6]} | {board[7]} | {board[8]} ")
    print("\n")

def check_winner(board, player):
    win_conditions = [
        [0, 1, 2], [3, 4, 5], [6, 7, 8],
        [0, 3, 6], [1, 4, 7], [2, 5, 8], 
        [0, 4, 8], [2, 4, 6]
    ]
    return any(all(board[i] == player for i in condition) for condition in win_conditions)

def is_board_full(board):
    return " " not in board

def minimax(board, depth, alpha, beta, is_maximizing):
    if check_winner(board, "O"):
        return 10 - depth
    if check_winner(board, "X"):
        return depth - 10
    if is_board_full(board):
        return 0

    if is_maximizing:
        max_eval = -math.inf
        for i in range(9):
            if board[i] == " ":
                board[i] = "O"
                eval = minimax(board, depth + 1, alpha, beta, False)
                board[i] = " "
                max_eval = max(max_eval, eval)
                alpha = max(alpha, eval)
                if beta <= alpha:
                    break #beta cutoff
        return max_eval
    else:
        min_eval = math.inf
        for i in range(9):
            if board[i] == " ":
                board[i] = "X"
                eval = minimax(board, depth + 1, alpha, beta, True)
                board[i] = " "
                min_eval = min(min_eval, eval)
                beta = min(beta, eval)
                if beta <= alpha:
                    break
    return min_eval

def find_best_move(board):
    best_val = -math.inf
    best_move = -1
    alpha = -math.inf
    beta = math.inf

    for i in range(9):
        if board[i] == " ":
            board[i] = "O"
            move_val = minimax(board, 0, alpha, beta, False)
            board[i] = " "
            if move_val > best_val:
                best_val = move_val
                best_move = i

    return best_move

def play_game():
    board = [" " for _ in range(9)]
    print("Tic-Tac-Toe: You(X) vs AI(O)")
    print("Board positions are indexed from 0 to 8 as follows:")
    print(" 0 | 1 | 2")
    print("---+---+---")
    print(" 3 | 4 | 5")
    print("---+---+---")
    print(" 6 | 7 | 8\n")

    while True:
        print_board(board)

        #human turn

        try:
            move = int(input("Enter your move (0-8): "))
            if move < 0 or move > 8 or board[move] != " ":
                print("Invalid move! Position is out of bounds or already taken")
                continue
        except ValueError:
            print("Please enter a valid integer between 0 and 8")
            continue

        board[move] = "X"

        if check_winner(board, "X"):
            print_board(board)
            print("Congratulations! You win")
            break
        if is_board_full(board):
            print_board(board)
            print("It's a tie")
            break

        #AI turn

        print("AI is calculating the optimal move...")
        ai_move = find_best_move(board)
        board[ai_move] = "O"

        if check_winner(board, "O"):
            print_board(board)
            print("AI wins! better luck next time")
            break
        if is_board_full(board):
            print_board(board)
            print("It's a tie")
            break

if __name__ == "__main__":
    play_game()
    
