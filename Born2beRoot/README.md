# Linux Basics and System Administration

<p align="center">
  <i>Your guide to mastering essential Linux concepts and tools, designed for efficient system administration.</i><br>
</p>

<p align="center">
  <img alt="Code Size" src="https://img.shields.io/github/languages/code-size/abdo-sebban/Born2beRoot?color=blueviolet" />
  <img alt="Top Language" src="https://img.shields.io/github/languages/top/abdo-sebban/Born2beRoot?color=blue" />
  <img alt="Last Commit" src="https://img.shields.io/github/last-commit/abdo-sebban/Born2beRoot?color=brightgreen" />
</p>

---

<h3 align="center">
  <a href="#virtualization">Virtualization</a> ·
  <a href="#partitions">Partitions</a> ·
  <a href="#apparmor">AppArmor</a> ·
  <a href="#lvm">LVM</a> ·
  <a href="#sudo-vs-su">sudo vs su</a> ·
  <a href="#ssh">SSH</a> ·
  <a href="#user-management">User Management</a> ·
  <a href="#password-policies">Password Policies</a> ·
  <a href="#ufw">UFW</a> ·
  <a href="#crontab">Crontab</a> ·
  <a href="#why-debian">Why Debian?</a> ·
  <a href="#debian-vs-rocky">Debian vs Rocky</a> ·
  <a href="#hostname-and-networking">Hostname and Networking</a> ·
  <a href="#basic-bash-commands">Basic Bash Commands</a> ·
</h3>

---

## 1. Virtualization

**Virtualization** allows running multiple operating systems on a single physical machine. Tools like VirtualBox, VMware, and KVM enable efficient resource utilization and testing environments.

---

## 2. Partitions

**Partitions** divide a disk into separate sections for better organization and isolation. Common types include primary, extended, and logical partitions. Efficient partitioning ensures optimized performance and data safety.

---

## 3. AppArmor

**AppArmor** is a Linux security module that restricts applications' capabilities through profiles, enhancing the system's security. It is particularly useful for isolating vulnerable or high-risk applications.

---

## 4. LVM (Logical Volume Manager)

**LVM** provides flexible disk management by allowing resizing and creating logical volumes without unmounting partitions. This makes it easier to adapt to changing storage needs.

---

## 5. sudo vs su

- **sudo:** Executes commands with elevated privileges temporarily, ensuring security by not sharing the root password.
- **su:** Switches to another user account, often root, requiring its password. It provides full root access but can pose security risks if misused.

---

## 6. SSH (Secure Shell)

**SSH** allows secure remote access and management of servers. Use public/private key pairs for enhanced security, and disable password-based authentication where possible.

---

## 7. User Management

Tools like `adduser`, `deluser`, and `usermod` manage system users and groups effectively. Proper user management ensures controlled access and system integrity.

---

## 8. Password Policies

Implement strong password policies using `passwd` and configure password expiration and complexity requirements in `/etc/login.defs`. Use tools like `faillog` to monitor failed login attempts.

---

## 9. UFW (Uncomplicated Firewall)

**UFW** simplifies managing iptables, enabling you to allow, deny, or limit network traffic with commands like `ufw allow 22`. Always ensure unnecessary ports are closed to minimize vulnerabilities.

---

## 10. Crontab

**Crontab** schedules recurring tasks. Example: `0 2 * * * /path/to/script.sh` runs a script daily at 2 AM. Use `crontab -e` to edit jobs and `crontab -l` to list current jobs.

---

## 11. Why Debian?

**Debian** is known for stability, extensive package repositories, and community support. It is an excellent choice for servers and desktops due to its robust performance and free software philosophy.

---

## 12. Debian vs Rocky

- **Debian:** Focuses on stability and freedom, making it ideal for general-purpose use and development.
- **Rocky:** An enterprise Linux distribution compatible with Red Hat, designed for business environments requiring long-term support.

---

## 13. Hostname and Networking

Use `hostnamectl` to set or view the hostname. Configure network settings in `/etc/network/interfaces` or use tools like `nmcli`. Regularly monitor network configurations to ensure stability.

---

## 14. Basic Bash Commands

- `ls`: List files and directories
- `cd`: Change directory
- `grep`: Search text in files
- `find`: Locate files
- `top`: Monitor system processes
- `df -h`: Display disk space usage
- `free -m`: Check memory usage
