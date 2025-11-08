class Job:
    def __init__(self, job_id, deadline, profit): 
        # Initialize each job with its ID, deadline, and profit
        self.job_id = job_id
        self.deadline = deadline 
        self.profit = profit


def job_sequencing(jobs):
    # 1️⃣ Sort all jobs in descending order of profit (most profitable first)
    jobs.sort(key=lambda x: x.profit, reverse=True)

    # 2️⃣ Find the maximum deadline to know how many time slots we need
    max_deadline = max(job.deadline for job in jobs)

    # 3️⃣ Create a result list to store job IDs (-1 = empty slot)
    result = [-1] * (max_deadline + 1)
    total_profit = 0
    job_sequence = []

    # 4️⃣ Schedule jobs one by one
    for job in jobs:
        # Try to schedule the job in the latest available slot before its deadline
        for t in range(job.deadline, 0, -1):
            if result[t] == -1:  # Slot is free
                result[t] = job.job_id  # Place the job
                total_profit += job.profit  # Add profit
                job_sequence.append(job.job_id)  # Record the job
                break  # Move to next job once scheduled

    # 5️⃣ Return final job sequence and total profit
    return job_sequence, total_profit


if __name__ == "__main__":
    # 🟩 Input number of jobs
    n = int(input("Enter number of jobs: "))
    jobs = []

    # 🟩 Take job details from user
    for i in range(n):
        job_id = input(f"\nEnter Job ID for Job {i+1}: ")
        deadline = int(input(f"Enter deadline for Job {job_id}: "))
        profit = int(input(f"Enter profit for Job {job_id}: "))
        jobs.append(Job(job_id, deadline, profit))

    # 🟩 Get job sequence and total profit
    sequence, profit = job_sequencing(jobs)

    # 🟩 Display results
    print("\n--- Job Sequencing Result ---")
    print("Job Sequence:", sequence)
    print("Total Profit:", profit)
