# 1337-Common-Core

A collection of my 1337 Common Core projects, covering C/C++ programming, algorithms, Unix, system programming, and software engineering fundamentals.

## 📚 Table of Contents

- [About](#about)
- [Disclaimer](#disclaimer)
- [Projects](#projects)
- [Tech Stack](#tech-stack)
- [Getting Started](#getting-started)

## Disclaimer

> **For 42 Students:** Please do not copy-paste code from this repository. The 42 pedagogy is based on doing the work yourself. Using this code for your own evaluation will likely result in a `-42` (Cheat) from the Moulinette or during a defense. Use this only for reference or understanding the logic.

## About

This repository gathers all the projects completed during the **Common Core** curriculum at **1337** (42 Network).
Each project lives in its own folder with its own `Makefile` and source files, and explores a specific area of low-level programming, system administration, or software design - from reimplementing standard C library functions to building a full IRC server and a raycasting game engine.

## Projects

| Project | Description |
|---|---|
| **[Libft](./Libft)** | A custom C library reimplementing standard libc functions (string, memory, list utilities) plus bonus linked-list functions. Used as a foundation library across later projects. |
| **[get_next_line](./get_next_line)** | A function that reads a file line by line, independent of file descriptor state, with a bonus version handling multiple file descriptors simultaneously. |
| **[ft_printf](./ft_printf)** | A custom reimplementation of the `printf` function supporting the main format conversions (`%d`, `%s`, `%x`, `%p`, `%u`, etc.). |
| **[Born2beRoot](./Born2beRoot)** | A system administration project: setting up a virtual machine (Debian/Rocky) with strict security policies, LVM partitioning, and a custom monitoring script (`monitoring.sh`). |
| **[pipex](./pipex)** | Reimplementation of shell piping (`|`) between two commands using `fork`, `pipe`, `dup2`, and `execve`, with a bonus supporting multiple pipes and here-docs. |
| **[so_long](./so_long)** | A small 2D game built with the MinilibX graphics library: move a player through a map, collect items, and reach the exit. |
| **[push_swap](./push_swap)** | A sorting algorithm project: sort a stack of integers using a limited instruction set and two stacks, optimizing for the fewest number of moves. Includes a bonus `checker`. |
| **[NetPractice](./NetPractice)** | A series of networking exercises (subnetting, routing, IP configuration) solved through JSON-based network topology levels. |
| **[Philosophers](./Philosophers)** | An implementation of the Dining Philosophers problem using threads and mutexes to explore concurrency, deadlocks, and resource-sharing. |
| **[minishell](./minishell)** | A simplified Unix shell supporting pipes, redirections, environment variables, built-in commands, and signal handling. |
| **[CPP Modules 00–09](./CPP)** | A progression through C++ fundamentals: OOP basics, inheritance, polymorphism, abstract classes, interfaces, templates, STL containers, and algorithm implementation (e.g. `PmergeMe`, `RPN`). |
| **[cub3d](./cub3d)** | A raycasting engine inspired by Wolfenstein 3D, rendering a first-person 3D maze from a 2D map, with textures, sprites, and a bonus version featuring doors, animated weapons, and a minimap. |
| **[FT-IRC](./FT-IRC)** | A custom IRC server implemented in C++ following the IRC protocol (RFC), supporting multiple clients, channels, and standard commands (`JOIN`, `KICK`, `MODE`, `TOPIC`, etc.), plus an IRC bot. |
| **[Inception](./Inception)** | A system administration project using Docker to set up a small infrastructure: NGINX, WordPress, and MariaDB, each running in its own containerized service via `docker-compose`. |

## Tech Stack

- **Languages:** C, C++, Bash
- **Tools:** Docker & Docker Compose, MiniLibX, Make
- **Concepts:** Memory management, multithreading & synchronization, networking & sockets, system administration, algorithmic optimization, object-oriented design

## Getting Started

Pick a project, `cd` in, `make`. That's the whole ritual.

```bash
cd push_swap && make
./push_swap 3 1 2
```

Threaded and networked projects run just as easily:

```bash
cd Philosophers/philo && make
./philo 4 410 200 200

cd minishell && make
./minishell
```

Docker-based projects spin up their own stack instead of a binary:

```bash
cd Inception && make
```

---

<p align="center">
  <sub>1337 / 42 Network - Common Core</sub>
</p>