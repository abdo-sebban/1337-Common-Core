#!/bin/bash

if [ ! -f "/var/www/html/wp-login.php" ]; then
    wp core download --path=/var/www/html --allow-root
fi

if [ ! -f "/var/www/html/wp-config.php" ]; then
    wp config create \
        --dbname=${MYSQL_DATABASE} \
        --dbuser=${MYSQL_USER} \
        --dbpass=${MYSQL_PASSWORD} \
        --dbhost=mariadb \
        --path=/var/www/html \
        --allow-root
fi

until wp db check --path=/var/www/html --allow-root 2>/dev/null; do
    echo "Waiting for MariaDB..."
    sleep 2
done

if ! wp core is-installed --path=/var/www/html --allow-root 2>/dev/null; then
    wp core install \
        --url=${DOMAIN_NAME} \
        --title=${WP_TITLE} \
        --admin_user=${WP_ADMIN_USER} \
        --admin_password=${WP_ADMIN_PASSWORD} \
        --admin_email=${WP_ADMIN_EMAIL} \
        --path=/var/www/html \
        --allow-root

    wp user create ${WP_USER} ${WP_USER_EMAIL} \
        --role=author \
        --user_pass=${WP_USER_PASSWORD} \
        --path=/var/www/html \
        --allow-root
fi

exec "$@"
