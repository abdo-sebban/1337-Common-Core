# User Documentation

This document explains, in simple terms, how to use the Inception infrastructure once it is up and running. It is written for end users and administrators who do not need to know how the project was built, only how to operate it day to day.

## 1. What services does this stack provide?

The project runs a small website infrastructure made of three containers that work together:

- **NGINX**: the only entry point to the infrastructure. It receives all incoming traffic on port 443 (HTTPS) and forwards PHP requests to the WordPress container. It only accepts TLSv1.2 or TLSv1.3 connections.
- **WordPress + php-fpm**: runs the WordPress website. This is the actual content management system (CMS) that powers the site and its admin panel.
- **MariaDB**: the database that stores all WordPress data (posts, pages, settings, users).

All three containers are connected through a private Docker network called `inception`, and the WordPress files and database are stored in two persistent volumes so that data is not lost when containers restart.

## 2. Starting and stopping the project

All commands below must be run from the root of the project (the folder that contains the `Makefile`).

### Start the project

```bash
make
```

This command will:
- create the data folders on the host machine (`~/data/mariadb` and `~/data/wordpress`)
- build the three Docker images (mariadb, wordpress, nginx)
- start all containers in the background

### Stop the project

```bash
make down
```

This stops and removes the containers, but keeps the images, volumes and data, so nothing is lost.

### Restart the project (rebuild)

```bash
make re
```

This stops everything and starts it again, rebuilding the images if needed.

### Completely remove the project

```bash
make clean
```

This stops the containers, removes unused Docker images, containers, networks and build cache, and deletes the local data folder (`~/data`). Note that this does **not** remove the named volumes themselves.

```bash
make fclean
```

Same as `clean`, but additionally removes all unused Docker volumes on the system (including the ones created by this project). Use this when you want a totally fresh start.

## 3. Accessing the website and the administration panel

Before accessing the site, make sure your domain name is configured to point to your local machine. The domain used for this project is:

```
asebban.42.fr
```

If it is not already configured, add this line to `/etc/hosts`:

```bash
echo "127.0.0.1 asebban.42.fr" | sudo tee -a /etc/hosts
```

### Website (front office)

Open a browser and go to:

```
https://asebban.42.fr
```

Since the SSL certificate is self-signed (generated for this project, not issued by a public authority), the browser will show a security warning. This is expected. Click **Advanced** and then **Proceed/Continue** to access the site anyway.

### Administration panel (back office)

Go to:

```
https://asebban.42.fr/wp-admin
```

Log in using the administrator account described below.

## 4. Locating and managing credentials

All sensitive information (passwords, database credentials, WordPress account details) is stored in the `.env` file located in the `srcs/` folder. This file is **not** committed to Git, as it contains confidential information.

The `.env` file contains, among others:

| Variable | Purpose |
|---|---|
| `DOMAIN_NAME` | The domain name used to access the site (`asebban.42.fr`) |
| `MYSQL_DATABASE` | Name of the WordPress database |
| `MYSQL_USER` / `MYSQL_PASSWORD` | Credentials of the regular database user used by WordPress |
| `MYSQL_ROOT_PASSWORD` | Password of the MariaDB root user |
| `WP_ADMIN_USER` / `WP_ADMIN_PASSWORD` / `WP_ADMIN_EMAIL` | Credentials of the WordPress administrator account |
| `WP_USER` / `WP_USER_PASSWORD` / `WP_USER_EMAIL` | Credentials of the second WordPress account (author role) |

To find the admin login details:

```bash
cat srcs/.env
```

There are **two WordPress user accounts**:
- An **administrator** account (`WP_ADMIN_USER`), which can manage the whole site (plugins, themes, users, settings).
- A **regular author** account (`WP_USER`), which can write and manage its own posts but has no administrative rights.

For security reasons, the administrator's username never contains the word "admin" or "administrator", as required by the project rules.

## 5. Checking that the services are running correctly

### Check that all containers are up

```bash
docker ps
```

You should see three containers, all with status `Up`:

```
nginx       Up   0.0.0.0:443->443/tcp
wordpress   Up
mariadb     Up
```

If a container is missing or shows `Restarting`, something is wrong and you should check its logs (see below).

### Check the logs of a service

```bash
docker logs nginx
docker logs wordpress
docker logs mariadb
```

These commands show what happened when the container started and can help identify problems (for example, MariaDB not ready, WordPress installation errors, etc.).

### Check the website is reachable

```bash
curl -k -I https://asebban.42.fr
```

A response starting with `HTTP/1.1 200 OK` (or a redirect) means the website is responding correctly. The `-k` flag is needed because the certificate is self-signed.

### Check WordPress users

```bash
docker exec -it wordpress wp user list --path=/var/www/html --allow-root
```

This should list the two configured users (administrator and regular author) with their roles.

### What to do if something is not working

1. Run `docker ps` to confirm all three containers are running.
2. Run `docker logs <container_name>` to read the error messages.
3. If needed, restart everything with `make re`.
4. If the data seems corrupted, perform a full reset with `make clean`.
