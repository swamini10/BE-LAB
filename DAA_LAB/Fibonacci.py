# ------------------------------------------------------------
# Program: Fibonacci Numbers (Recursive vs Non-Recursive)
# Purpose: To calculate Fibonacci numbers using both methods,
#          measure execution time, and count the number of steps.
# ------------------------------------------------------------

import time   # Used to measure execution time

# ---------- Recursive Fibonacci Function ----------
def fib_recursive(n, steps):
    # Count each function call as one step
    steps[0] += 1
    #print(f"Recursive Step {steps[0]}: fib_recursive({n}) ")  #  show each recursive call

    # Base case: if n is 0 or 1, return n
    if n <= 1:
        return n

    # Recursive calls (each adds to step count)
    return fib_recursive(n - 1, steps) + fib_recursive(n - 2, steps)


# ---------- Non-Recursive (Iterative) Fibonacci Function ----------
def fib_non_recursive(n, steps):
    n1, n2 = 0, 1  # First two Fibonacci numbers

    # Handle invalid or small inputs
    if n <= 0:
        print("Invalid input! n should be greater than 0.")
        return
    elif n == 1:
        print(n1)
        return
    elif n == 2:
        print(n1, n2)
        return
    else:
        # Print first two numbers
        print(n1, n2, end=" ")

        # Loop to calculate next Fibonacci numbers
        for i in range(2, n):
            steps[0] += 1         # Count each loop iteration as one step
            n3 = n1 + n2          # Calculate next Fibonacci number
            #print(f"\nNon-Recursive Step {steps[0]}: {n1} + {n2} = {n3}")  #  show each calculation step

            print(n3, end=" ")    # Print it
            n1, n2 = n2, n3       # Update variables for next iteration
        print()  # Newline after sequence


# ---------- Main Function ----------
def main():
    # Take user input
    n = int(input("Enter the number of elements: "))

    # ---------- Recursive Fibonacci ----------
    print("\nFibonacci Sequence (Recursive): ", end="")
    steps_recursive = [0]   # Use list so step count can be updated inside function
    start1 = time.time()    # Record start time
    for i in range(n):
        print(fib_recursive(i, steps_recursive), end=" ")
    end1 = time.time()      # Record end time
    time_recursive = (end1 - start1) * 1_000_000  # Convert to microseconds

    # ---------- Non-Recursive Fibonacci ----------
    print("\n\nFibonacci Sequence (Non-Recursive): ", end="")
    steps_nonrecursive = [0]   # Step counter for loop version
    start2 = time.time()       # Record start time
    fib_non_recursive(n, steps_nonrecursive)
    end2 = time.time()         # Record end time
    time_nonrecursive = (end2 - start2) * 1_000_000  # Convert to microseconds

    # ---------- Time, Step Count & Space Complexity ----------
    print("\n=== Time, Step Count, and Space Complexity Analysis ===")
    print(f"Recursive Time Taken: {time_recursive:.2f} microseconds")
    print(f"Recursive Steps Taken: {steps_recursive[0]}")
    print("Recursive Time Complexity: O(2^n)")
    print("Recursive Space Complexity: O(n)\n")

    print(f"Non-Recursive Time Taken: {time_nonrecursive:.2f} microseconds")
    print(f"Non-Recursive Steps Taken: {steps_nonrecursive[0]}")
    print("Non-Recursive Time Complexity: O(n)")
    print("Non-Recursive Space Complexity: O(1)")


# ---------- Run the Program ----------
if __name__ == "__main__":
    main()


# recursive method
# If n <= 1, return n.
# Otherwise, call the function again for (n-1) and (n-2).
# Add their results to get the Fibonacci number.
# This continues until all smaller calls reach the base case.

# Non-Recursive
# Start from the first two numbers (0 and 1).
# Use a loop to compute the next numbers up to n.
# Each iteration updates the two previous numbers.
# Print the sequence.
