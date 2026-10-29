# Monopoly Multiplayer

Multiplayer Monopoly game developed from scratch with a modular architecture and a player-hosted server model (Listen Server / P2P Host). The architecture enforces strict separation between the application interface, graphical game client, network layer, and authoritative rule engine.

## General Architecture

The project follows a decoupled modular design. The application is organized into the following main components:

```
monopoly-multiplayer/
├── CMakeLists.txt                # Global C/C++ build configuration
├── README.md                     # Project documentation
├── bin/                          # Output binaries and compiled libraries
│
├── src/                          # Native C/C++ source code
│   ├── app.c                     # Entry point (main) and state machine
│   │
│   ├── menu/                     # Menu and lobby logic and graphics
│   │   ├── menu.c
│   │   ├── menu.h
│   │   ├── menu_graphics.c
│   │   └── menu_graphics.h
│   │
│   ├── game_client/              # Visual game client (Board / Tokens)
│   │   ├── game_client.c
│   │   ├── game_client.h
│   │   ├── game_client_graphics.c
│   │   └── game_client_graphics.h
│   │
│   └── game_host/                # Authoritative rule engine (C core)
│       ├── game_host.c
│       └── game_host.h
│
├── python_server/                # Networking layer (Python)
│   ├── red_host.py               # Host TCP network server
│   ├── red_cliente.py            # Client TCP network handler
│   └── main_server.py            # Dedicated server launcher script
│
└── assets/                       # Static game resources
    ├── fonts/                    # Interface typography
    ├── textures/                 # Board, tokens, cards, houses/hotels
    └── audio/                    # Sound effects and music
```

## Module Descriptions and Responsibilities

### 1. Main Core

* **`app.c`**: Contains the `main()` entry point and manages the application state machine (`STATE_MENU`, `STATE_LOBBY`, `STATE_IN_GAME`, `STATE_EXIT`). Controls the main event loop and coordinates the lifecycle of all subsystems.

### 2. Menu Module (`src/menu/`)

* **`menu.c` / `menu.h`**: Handles user input and navigation flow for menus (create room, join by IP, select name, choose avatar).

* **`menu_graphics.c` / `menu_graphics.h`**: Renders visual interface elements (buttons, form inputs, images) using the graphics library.

### 3. Game Client Module (`src/game_client/`)

* **`game_client.c` / `game_client.h`**: Maintains the local visual game state received from the server and handles player actions (roll dice, buy property, end turn).

* **`game_client_graphics.c` / `game_client_graphics.h`**: Renders the 2D game board, token movement animations, balance panels, cards, and property structures.

### 4. Rule Engine (`src/game_host/`)

* **`game_host.c` / `game_host.h`**: The **single authoritative source of truth** for the game, written in pure C. Independent of networking and graphics.

  * Tracks official game state (cash, positions, property ownership, turn order, jail status, bankruptcy).

  * Exposes a native C API that validates rules and executes actions.

### 5. Network Layer (`python_server/`)

* **`red_host.py`**: TCP socket server in Python. Listens to connected clients, invokes the C rule engine (`game_host`) via FFI (`ctypes`/`cffi`), and broadcasts state updates to all players.

* **`red_cliente.py`**: Manages the client's TCP socket connection with the host server, serializing messages and transmitting player actions.

* **`main_server.py`**: Allows running the server as a headless standalone process without launching the GUI.

## Data and Communication Model

1. **Protocol:** Communication uses **TCP** to ensure ordered, reliable delivery of game actions and state events.

2. **Intention vs. Authority:**

   * The client **never** updates game state directly. It sends action requests (e.g., `BUY_PROPERTY(id)`).

   * The host server (`red_host.py` + `game_host.c`) validates action prerequisites (funds, ownership status, turn validity).

   * Upon validation, the server updates the official state and broadcasts synchronization messages to all clients.

3. **C / Python Integration:**

   * `game_host.c` is compiled into a shared library (`.so` / `.dll`).

   * `red_host.py` loads the library using `ctypes` or `cffi` to execute core rules.

   * Communication between C client modules and local Python scripts occurs over sockets or local IPC pipes.

## Development Roadmap

1. **Phase 1: Rule Engine Core (C)**

   * Define core data structures (`GameState`, `Player`, `Property`).

   * Implement game loop functions in `game_host.c` and verify via CLI unit tests.

2. **Phase 2: Networking and FFI Bindings**

   * Bind `game_host` to `red_host.py`.

   * Validate TCP message flow using test CLI clients.

3. **Phase 3: Application Menus**

   * Build lobby and configuration screens in `menu.c` and `menu_graphics.c`.

4. **Phase 4: Graphical Board and Integration**

   * Implement 2D board rendering in `game_client_graphics.c`.

   * Connect all components inside `app.c` main loop.