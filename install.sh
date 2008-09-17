#!/bin/sh
#
# sudo ./install.sh
# currently requires prepare_fresh_ubuntu_for_deploy.sh on in the same dir as this script


# setup hostname
echo "Hostname is currently `hostname`"
read -p "Enter new hostname
" -r NEWNAME 
echo "$NEWNAME" > /etc/hostname

# Requisites

# Bind9 conflicts with dnsmasq
command="apt-get remove bind9"
echo "Running: $command"
read -p "Press any key to begin" -r A
$command

command="apt-get install dnsmasq firefox-2 build-essential git-core"
echo "Running: $command"
read -p "Press any key to begin" -r A
$command

# Why do we need this?
echo "Becoming root user"
command="apt-get install xinit xauth"
echo "Running: $command"
read -p "Press any key to begin" -r A
$command


# In order to set this up on the server you will need to do a couple of things, such as:
command="adduser firefox"
echo "Running: $command"
read -p "Press any key to begin" -r A
$command

#command="su firefox"
#echo "Running: $command"
#read -p "Press any key to begin"
#$command
     
command="cd /home/firefox"
echo "Running: $command"
read -p "Press any key to begin" -r A
$command

# install git, make, gcc
#echo "
#deb http://us.archive.ubuntu.com/ubuntu/ hardy-updates main multiverse universe
#deb-src http://us.archive.ubuntu.com/ubuntu/ hardy-updates main multiverse universe" >> /etc/apt/sources.list
#command="apt-get install git-core build-essential"
#echo "Running: $command"
#read -p "Press any key to begin"
#$command

command="git init"
echo "Running: $command"
read -p "Press any key to begin" -r A
$command

#echo "Enter the git url for firefox (git://github.com/baobab/firefox-daemon.git)"
#read -e GIT_URL
GIT_URL="git://github.com/baobab/firefox-daemon.git"

command="git remote add origin $GIT_URL"
echo "Running: $command"
read -p "Press any key to begin" -r A
$command


command="git pull origin master"
echo "Running: $command"
read -p "Press any key to begin" -r A
$command

command="cd src"
echo "Running: $command"
read -p "Press any key to begin" -r A
$command

command="make"
echo "Running: $command"
read -p "Press any key to begin" -r A
$command

command="cp apps/baobab.firefox/baobab.firefox* .."
echo "Running: $command"
read -p "Press any key to begin" -r A
$command

command="cd .."
echo "Running: $command"
read -p "Press any key to begin" -r A
$command


#command="exit"
#echo "Running: $command"
#read -p "Press any key to begin"
#$command

command="cp firefox-daemon /etc/init.d/"
echo "Running: $command"
read -p "Press any key to begin" -r A
$command

command="sudo /usr/sbin/update-rc.d -f firefox-daemon defaults"
echo "Running: $command"
read -p "Press any key to begin" -r A
$command

command="sudo /etc/init.d/firefox-daemon"
echo "Running: $command"
read -p "Press any key to begin" -r A
$command

echo "make sure you have a /usr/bin/firefox, you may have /usr/bin/firefox-2"
command="sudo ln /usr/bin/firefox-2 /usr/bin/firefox"
echo "Running: $command"
read -p "Press any key to begin" -r A
$command

# make your /etc/dnsmasq.conf file look like this (replace x with your subnet)
echo "dhcp-range=192.168.5.100,192.168.5.150,12h" >  /etc/dnsmasq.conf

# we need to remove everything from your /etc/resolv.conf but we need to resolve some domains for downlads for now`
echo "nameserver 196.216.8.4" > /etc/resolv.conf

# make your /etc/network/interfaces look like this:

echo "
auto lo
iface lo inet loopback

auto eth0
iface eth0 inet static
address 192.168.5.200
netmask 255.255.255.0
gateway 192.168.5.1" > /etc/network/interfaces

#setup hosts file
echo "
192.168.5.200 bart localhost $NEWNAME" >> /etc/hosts

# TODO: merge these scripts
#echo "get second install script"
#cd /home/firefox
#command="git clone git://gist.github.com/10601.git"
#read -p "Press any key to begin" -r A
#$command


#cd 10601
cd ~
chmod ugo+x prepare_fresh_ubuntu_for_deploy.sh
command="sh prepare_fresh_ubuntu_for_deploy.sh"
$command


# remove everything from your /etc/resolv.conf
echo "" > /etc/resolv.conf

# restart dnsmasq
command="sudo /etc/init.d/dnsmasq restart"
echo "Running: $command"
read -p "Press any key to begin" -r A
$command

echo "
# You may want to debug
#ps aux | grep firefox
#sudo kill XXXX
#sudo su firefox
#cd ~
#./baobab.firefox
#<connect>"

echo "Finito!"

