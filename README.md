# DroneNavigationSystem

This project simulates a drone navigation system between Turkish cities. The system uses Stack and Queue data structures to ensure that the drone determines the optimal route while considering constraints such as weather conditions.

**Project Description**

The drone starts from Ankara and attempts to visit cities within 250 km or less. The goal is to determine the most efficient route and handle possible dead ends by backtracking to move forward in the most effective way.

The data structures used in this project:

Stack: Used for backtracking. If the drone reaches a dead end, it uses the stack to return to its last position.

Queue: Used to determine the nearest cities. Cities to be visited are added to the queue in priority order and processed sequentially.

**🛠 Algorithms Used**

Depth-First Search (DFS): Stack is used for backtracking when encountering dead ends.

Breadth-First Search (BFS): Used to determine the order of visiting the nearest cities.

**📌 Example Usage**

The drone starts from Ankara.

It determines the cities within 250 km and with suitable weather conditions.

The drone follows the optimal path using Stack and Queue.

If a dead end is encountered, it backtracks using the stack.
