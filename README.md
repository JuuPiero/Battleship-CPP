# Battleship
## Task

Design and implement a console application for the **Battleship** game with an interface for interaction via standard input/output streams.

### Rules

The rules are identical to the classic [Battleship game](https://en.wikipedia.org/wiki/Battleship_(game)), except the field size and the number of ships can be arbitrary (ship sizes correspond to those in the classic game).

The game requires two players: **master** and **slave**. The master sets the game parameters: field size and the number of ships, and communicates them to the slave. Then, both players arrange their ships according to these parameters. After starting the game, players take turns firing at each other's ships following the classic Battleship rules.

### Commands

The table below lists the commands, their parameters, and possible responses.  
Responses always end with a newline character. All commands and responses are in lowercase.

| Command                      | Response        | Description                                                                        |
|------------------------------|-----------------|------------------------------------------------------------------------------------|
| `ping`                       | `pong`          | Test command                                                                       |
| `exit`                       | `ok`            | Terminates the program                                                            |
| `create [master,slave]`      | `ok`            | Creates a game in either master or slave mode                                     |
| `start`                      | `ok`            | Starts the game                                                                   |
| `stop`                       | `ok`            | Stops the current game                                                            |
| `set width N`                | `ok/failed`     | Sets the field width (N is a positive integer within `uint64_t`)                  |
| `get width`                  | `N`             | Retrieves the field width (N is a positive integer within `uint64_t`)            |
| `set height N`               | `ok/failed`     | Sets the field height (N is a positive integer within `uint64_t`)                |
| `get height`                 | `N`             | Retrieves the field height (N is a positive integer within `uint64_t`)           |
| `set count [1,2,3,4] N`      | `ok/failed`     | Sets the number of ships of a specific type (N is a positive integer within `uint64_t`) |
| `get count [1,2,3,4]`        | `N`             | Retrieves the number of ships of a specific type (N is a positive integer within `uint64_t`) |
| `set strategy [ordered,custom]` | `ok`         | Selects the strategy for the game                                                 |
| `shot X Y`                   | `miss/hit/kill` | Shoots at the opponent's ships at coordinates `(X,Y)` (X and Y are positive integers within `uint64_t`) |
| `shot`                       | `X Y`           | Returns the coordinates of your next shot as two numbers separated by a space `(X Y)` |
| `finished`                   | `yes/no`        | Checks if the current game is finished                                            |
| `win`                        | `yes/no`        | Checks if you are the winner                                                      |
| `lose`                       | `yes/no`        | Checks if you are the loser                                                       |
| `dump PATH`                  | `ok`            | Saves the field size and your current ship arrangement to a file                  |
| `load PATH`                  | `ok`            | Loads the field size and ship arrangement from a file                             |

### File Format for `dump`/`load`

The file is in text format.  
- The first line specifies the field size: width and height separated by a space.  
- Each subsequent line describes a ship: size and coordinates (width, height) separated by a space.

### Strategies

You need to implement at least two strategies for the game:

1. **Ordered**: A testing algorithm that fires sequentially row by row starting from point `(0,0)`.  
2. **Custom**: Your custom algorithm (used by default).  

### Requirements

- When generating a game, the field size and the number of ships must be consistent (the field size cannot be zero, and all ships must fit on the field).  
- Coordinates `(0,0)` represent the top-left corner of the field.  
- There is always one master and one slave in the game.  
- The game cannot start until the field size and the number of ships are set (at least one ship of any type must be placed).  
- After the game starts, the field size and the number of ships cannot be changed.  
- The strategy type can be changed during the game.  
- Responses to commands like `win`, `finished`, and `lose` must be consistent (e.g., you cannot win or lose if the game is not finished).  
- The `load` command can be executed before starting the game, overriding the rules set by `create`. This can be used for testing.

### Implementation

Your application must implement both roles: master and slave.  
Command input and output must be handled via standard input/output streams.

The evaluation will consider the architecture of your solution and the organization of your codebase. Focus on identifying abstractions, separating input/output handling from business logic. Writing tests is encouraged.

### Notes

At each game run, your application plays the strategy for one player only (either master or slave). To have a complete game, you need either a second application or a human player.

After the third deadline, algorithm competitions will be held within each group.  
- **First place** receives an additional 5 points.  
- **Fifth place** receives 1 point.  
- Memory usage is limited to **64MB**.