# philosophers - 42 Project

## Introduction

**philosophers** is a project at 42 that simulates the classic dining philosophers problem to explore synchronization, concurrency, and process management. The goal is to implement a solution where multiple philosophers sit at a table, each with a fork on either side, and attempt to eat without causing deadlock or starvation.

The project involves creating a program that simulates this problem using threads or processes, ensuring that philosophers can eat in a fair manner while avoiding common concurrency issues.

## Project Overview

The problem is defined as follows:

- **Philosophers**: Each philosopher thinks and eats alternately. To eat, a philosopher needs both forks.
- **Forks**: There is one fork between each pair of philosophers. Philosophers must acquire both adjacent forks to eat.
- **Rules**:
  - A philosopher can only use the forks on either side of them.
  - Avoid deadlock: Ensure that no group of philosophers ends up waiting indefinitely for resources.
  - Avoid starvation: Ensure that all philosophers get a chance to eat.

## Requirements

- Implement the solution using threads or processes.
- Ensure proper synchronization to prevent race conditions and deadlock.
- Optionally, implement additional features such as:
  - Setting a maximum time for eating and thinking.
  - Handling different numbers of philosophers and forks.

## Usage

1. Clone the repository and navigate to the project directory:

   ```bash
   git clone https://github.com/fclaus-g/philosophers.git
   cd philosophers
   ```

2. Compile the project using:

   ```bash
   make
   ```

3. Run the simulation with the desired number of philosophers and optional parameters:

   ```bash
   ./philo [number_of_philosophers] [time_to_die] [time_to_eat] [time_to_sleep] [number_of_times_each_philosopher_must_eat]
   ```

   Example:

   ```bash
   ./philo 5 800 200 200 7
   ```

   This command simulates 5 philosophers, where each philosopher has 800 milliseconds to eat, 200 milliseconds to sleep, and the program ensures that each philosopher eats at least 7 times.

## Project Files

- **philo.c**: Contains the main program logic and initialization.
- **philo_utils.c**: Utility functions for handling synchronization and philosopher actions.
- **philo.h**: Header file with function prototypes and necessary includes.
- **Makefile**: Automates the compilation process.

## Example

```bash
./philo 4 400 200 200 5
```

This command runs the simulation with 4 philosophers, each having 400 milliseconds to eat, 200 milliseconds to sleep, and ensures each philosopher eats 5 times.

## License

This project is part of the 42 curriculum and is intended for educational purposes. Feel free to use it for learning, but be mindful of 42’s collaboration policies.
