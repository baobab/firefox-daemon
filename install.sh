#!/bin/sh
#


# Requisites

# Bind9 conflicts with dnsmasq
command="apt-get remove bind9"
echo "Running: $command"
read -p "Press any key to begin"
$command

command="apt-get install dnsmasq firefox2 build-essential"
echo "Running: $command"
read -p "Press any key to begin"
$command

# Why do we need this?
echo "Becoming root user"
command="apt-get install xinit xauth"
echo "Running: $command"
read -p "Press any key to begin"
$command


# In order to set this up on the server you will need to do a couple of things, such as:
command="adduser firefox"
echo "Running: $command"
read -p "Press any key to begin"
$command

command="sudo su firefox"
echo "Running: $command"
read -p "Press any key to begin"
$command

command="cd ~"
echo "Running: $command"
read -p "Press any key to begin"
$command

command="git init"
echo "Running: $command"
read -p "Press any key to begin"
$command

echo "Enter the git url for firefox (git://github.com/baobab/firefox-daemon.git)"
read -e GIT_URL

command="git remote add origin $GIT_URL"
echo "Running: $command"
read -p "Press any key to begin"
$command


command="git pull origin master"
echo "Running: $command"
read -p "Press any key to begin"
$command

command="cd src"
echo "Running: $command"
read -p "Press any key to begin"
$command

command="make"
echo "Running: $command"
read -p "Press any key to begin"
$command

command="cp apps/baobab.firefox/baobab.firefox* .."
echo "Running: $command"
read -p "Press any key to begin"
$command

command="cd .."
echo "Running: $command"
read -p "Press any key to begin"
$command

command="exit"
echo "Running: $command"
read -p "Press any key to begin"
$command

command="cp firefox-daemon /etc/init.d/"
echo "Running: $command"
read -p "Press any key to begin"
$command

command="sudo /usr/sbin/update-rc.d -f firefox-daemon defaults"
echo "Running: $command"
read -p "Press any key to begin"
$command

command="sudo /etc/init.d/firefox-daemon"
echo "Running: $command"
read -p "Press any key to begin"
$command

echo "make sure you have a /usr/bin/firefox, you may have /usr/bin/firefox-2"
command="sudo ln /usr/bin/firefox-2 /usr/bin/firefox"
echo "Running: $command"
read -p "Press any key to begin"
$command

# make your /etc/dnsmasq.conf file look like this (replace x with your subnet)
echo "dhcp-range=192.168.5.100,192.168.5.150,12h" >  /etc/dnsmasq.conf

# remove everything from your /etc/resolv.conf
echo "" > /etc/resolv.conf

# make your /etc/network/interfaces look like this:

echo "
auto lo
iface lo inet loopback

auto eth0
iface eth0 inet static
address 192.168.5.200
netmask 255.255.255.0
gateway 192.168.5.1" > /etc/network.interfaces

#setup hosts file
echo "
bart localhost 192.168.5.200" >> /etc/hosts

# restart dnsmasq
command="sudo /etc/init.d/dnsmasq restart"
echo "Running: $command"
read -p "Press any key to begin"
$command

# You may want to debug
#ps aux | grep firefox
#sudo kill XXXX
#sudo su firefox
#cd ~
#./baobab.firefox
#<connect>

