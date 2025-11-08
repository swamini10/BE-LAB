# Function to print the chessboard
def print_board(board):
    for row in board:
        print(" ".join(str(x) for x in row))
    print()

# Function to check if placing a queen is safe
def is_safe(board, row, col, n):
    for i in range(row):
        # Check same column, upper-left diagonal, and upper-right diagonal
        if board[i][col] == 1 or \
           (col - row + i >= 0 and board[i][col - row + i] == 1) or \
           (col + row - i < n and board[i][col + row - i] == 1):
            return False
    return True

# Recursive backtracking function to solve N-Queens
def solve(board, row, n):
    # Base case — all queens are placed
    if row == n:
        print_board(board)
        return
    # Try placing queen in each column
    for col in range(n):
        if is_safe(board, row, col, n):
            board[row][col] = 1     # Place queen
            solve(board, row + 1, n)  # Move to next row
            board[row][col] = 0     # Backtrack (remove queen)

# Main function
def n_queens():
    n = int(input("Enter N: "))  # Input size of board
    board = [[0]*n for _ in range(n)]  # Create N×N board filled with 0

    # Input for initial queen position
    r, c = map(int, input("Enter first queen position (row col): ").split())
    board[r-1][c-1] = 1  # Place the first queen (convert to 0-index)

    print("\nInitial board:")
    print_board(board)  # Display initial setup

    print("Solutions:\n")
    solve(board, 0, n)  # Call recursive solver

# Run program
if __name__ == "__main__":
    n_queens()


# Output:
# Enter N: 4
# Enter first queen position (row col): 1 2
# Enter first queen position (row col):2 3
# Enter N: 8
# Enter first queen position (row col): 1 4
#Enter first queen position (row col): 1 1