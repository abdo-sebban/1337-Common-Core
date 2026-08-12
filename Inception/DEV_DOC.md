# Developer Documentation

This document explains how a developer can set up, build, run and maintain the Inception infrastructure. It assumes basic familiarity with Docker, Docker Compose and the command line.

## 1. Project overview

The project sets up a small infrastructure with Docker Compose, composed of three custom-built services:

- `mariadb` — MariaDB database server
- `wordpress` — WordPress + php-fpm
- `nginx` — NGINX reverse proxy with TLS

Each service has its own Dockerfile, built from `debian:bookworm` (the penultimate stable Debian release), with no pre-built images pulled from Docker Hub other than the base Debian image.

## 2. Project structure

```
.
├── Makefile
└── srcs/
    ├── .env
    ├── docker-compose.yml
    └── requirements/
        ├── mariadb/
        │   ├── Dockerfile
        │   ├── conf/
        │   │   └── 50-server.cnf
        │   └── tools/
        │       └── start.sh
        ├── wordpress/
        │   ├── Dockerfile
        │   ├── conf/
        │   │   └── www.conf
        │   └── tools/
        │       └── start.sh
        └── nginx/
            ├── Dockerfile
            ├── conf/
            │   └── nginx.conf
            └── tools/
                └── start.sh
```

## 3. Setting up the environment from scratch

### Prerequisites

- A Linux virtual machine with Docker and Docker Compose v2 installed.
- `make` installed.
- The domain `<login>.42.fr` (here `asebban.42.fr`) resolving to `127.0.0.1`. If it is not already configured, add it to `/etc/hosts`:

```bash
echo "127.0.0.1 asebban.42.fr" | sudo tee -a /etc/hosts
```

### Configuration files

All configuration files live under `srcs/requirements/<service>/`:

- **`mariadb/conf/50-server.cnf`** — MariaDB server configuration. The key change from the default is `bind-address = 0.0.0.0`, so MariaDB accepts connections from other containers on the Docker network (by default it only listens on `127.0.0.1`).
- **`wordpress/conf/www.conf`** — php-fpm pool configuration. The key change is `listen = 0.0.0.0:9000`, so NGINX (in another container) can reach php-fpm over TCP instead of a local Unix socket.
- **`nginx/conf/nginx.conf`** — NGINX server block: listens on port 443 with TLSv1.2/TLSv1.3, serves WordPress files from `/var/www/html`, and forwards `.php` requests to `wordpress:9000` via FastCGI.

### Environment variables and secrets

All credentials and environment-specific values are stored in `srcs/.env`, which is **not** committed to Git (it should be listed in `.gitignore`). It must contain at least:

```bash
# Domain
DOMAIN_NAME=domainname

# MariaDB
MYSQL_DATABASE=database
MYSQL_USER=regular user
MYSQL_PASSWORD= password
MYSQL_ROOT_PASSWORD= admin password

# WordPress
WP_TITLE=MyWebsite
WP_ADMIN_USER=admin user
WP_ADMIN_PASSWORD=admin password
WP_ADMIN_EMAIL=asebban@42.fr
WP_USER=regular user
WP_USER_PASSWORD=userpass
WP_USER_EMAIL=user@42.fr
```

Notes:
- `WP_ADMIN_USER` must **not** contain `admin`, `Admin`, `administrator` or `Administrator`.
- No credentials are hardcoded in any Dockerfile, configuration file, or script — everything is read from these environment variables at container startup.

## 4. Building and launching the project

All commands are run from the project root (where the `Makefile` is located).

### Build and start everything

```bash
make
```

This target:
1. Creates the host data directories `~/data/mariadb` and `~/data/wordpress` (required because named volumes are bound to these paths).
2. Runs `docker compose -f srcs/docker-compose.yml up -d --build`, which builds the three images and starts the containers in detached mode.

### Stop the containers

```bash
make down
```

Runs `docker compose -f srcs/docker-compose.yml down`. Containers and the network are removed, but images, volumes and host data are preserved.

### Rebuild from scratch

```bash
make re
```

Equivalent to `make down` followed by `make`.

### Full cleanup

```bash
make clean
```

Stops the containers, then runs `docker system prune -af` (removes unused containers, images, networks and build cache — system-wide) and deletes `~/data`. This does **not** remove the named volumes themselves.

```bash
make fclean
```

Same as `clean`, plus removes all unused Docker volumes on the system (`docker volume prune -f`), including the `mariadb` and `wordpress` volumes created by this project.

## 5. Managing containers and volumes

### Useful container commands

```bash
# List running containers
docker ps

# View logs of a service
docker logs -f mariadb
docker logs -f wordpress
docker logs -f nginx

# Open a shell inside a container
docker exec -it mariadb bash
docker exec -it wordpress bash
docker exec -it nginx bash
```

### Checking MariaDB

```bash
docker exec -it mariadb mysql -u root -p"$MYSQL_ROOT_PASSWORD" -e "SHOW DATABASES;"
docker exec -it mariadb mysql -u root -p"$MYSQL_ROOT_PASSWORD" -e "SELECT User, Host FROM mysql.user;"
```

### Checking WordPress

```bash
docker exec -it wordpress wp user list --path=/var/www/html --allow-root
docker exec -it wordpress wp core is-installed --path=/var/www/html --allow-root
```

### Managing volumes and the network

```bash
# List volumes (look for srcs_mariadb and srcs_wordpress)
docker volume ls

# List networks (look for srcs_inception)
docker network ls

# Inspect the custom network
docker network inspect srcs_inception
```

## 6. How the services start up

Each service has a `start.sh` script set as its `ENTRYPOINT`, and its main process set as `CMD`. The script always finishes with `exec "$@"`, which replaces the shell process with the main service process (PID 1).

- **mariadb/start.sh**: initializes the data directory on first run (`mysql_install_db`), starts MariaDB temporarily, creates the WordPress database and the two MySQL users (`MYSQL_USER` and `root`), then shuts down the temporary instance and finally `exec`s `mysqld` as PID 1.
- **wordpress/start.sh**: downloads WordPress files if missing, generates `wp-config.php` from the environment variables, waits until the database is reachable (`wp db check`), installs WordPress and creates the two WordPress users if not already installed (`wp core is-installed`), then `exec`s `php-fpm8.2 -F` as PID 1.
- **nginx/start.sh**: generates a self-signed TLS certificate (valid for the domain in `DOMAIN_NAME`) if needed, then `exec`s `nginx -g "daemon off;"` as PID 1.

## 7. Where data is stored and how it persists

The project uses two **named Docker volumes**, both backed by bind mounts to the host filesystem (not raw bind-mount volumes, as required by the subject):

| Volume name | Container path | Host path |
|---|---|---|
| `mariadb` | `/var/lib/mysql` | `/home/<login>/data/mariadb` |
| `wordpress` | `/var/www/html` | `/home/<login>/data/wordpress` |

This is configured in `docker-compose.yml` using `driver: local` with `driver_opts` (`type: none`, `o: bind`, `device: /home/${USER}/data/...`).

Because of this setup:
- Database files (tables, users, WordPress data) survive container restarts and rebuilds.
- WordPress core files, themes, plugins and uploads also persist across restarts and rebuilds.
- Running `make down` / `make re` does **not** delete this data.
- Running `make clean` / `make fclean` **does** delete this data (it removes `~/data`).

All three containers are attached to a single custom bridge network, `inception`, defined in `docker-compose.yml`. This network provides automatic DNS resolution between containers (e.g. `wordpress` can reach the database simply by using `mariadb` as the hostname, and NGINX reaches php-fpm via `wordpress:9000`)
