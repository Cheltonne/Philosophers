# Philosophers

This project, completed as part of the curriculum at [42 Paris](https://42.fr/en/homepage/), involved implementing a simulation of the classic dining philosophers problem using threads and mutexes. The project demonstrates concurrent programming concepts and was designed to handle synchronization and prevent data races.

## Overview
In this simulation:
- Philosophers sit at a round table with a bowl of spaghetti in the center.
- Each philosopher alternates between eating, thinking, and sleeping.
- To eat, a philosopher must pick up two forks (one on their left and one on their right).
- Philosophers put down their forks after eating and proceed to sleep before thinking again.
- The simulation ends if a philosopher dies from starvation.

### Key Features
- **Threaded Simulation**: Each philosopher is represented as a thread.
- **Mutex Protection**: Forks are protected with mutexes to prevent duplication and ensure safe access.
- **Dynamic Input**: The program accepts the following arguments:
  1. `number_of_philosophers`: Number of philosophers (and forks).
  2. `time_to_die`: Maximum time (in ms) a philosopher can go without eating before dying.
  3. `time_to_eat`: Time (in ms) it takes for a philosopher to eat.
  4. `time_to_sleep`: Time (in ms) a philosopher spends sleeping.
  5. (Optional) `number_of_times_each_philosopher_must_eat`: Simulation ends if all philosophers eat this many times.

### Program Requirements
- Logs each philosopher’s state changes:
  - `timestamp_in_ms X has taken a fork`
  - `timestamp_in_ms X is eating`
  - `timestamp_in_ms X is sleeping`
  - `timestamp_in_ms X is thinking`
  - `timestamp_in_ms X died`
- Ensures no data races and prevents philosophers from dying unnecessarily.
- State changes are formatted and displayed in real-time.

### Implementation Notes
- Uses `pthread` library functions for thread creation and synchronization.
- Employs mutexes to manage fork states and avoid race conditions.
- Handles scenarios with varying numbers of philosophers, including edge cases like a single philosopher.

This project serves as an introduction to concurrent programming, demonstrating how to manage threads and shared resources efficiently while adhering to strict rules of synchronization.

