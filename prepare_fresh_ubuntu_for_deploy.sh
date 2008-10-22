#!/bin/sh

# As of 2008-09-17 this script gets called by install.sh placed in the same dir

# the command= trick gets screwed up with quotes so be careful


# TODO setup LibertyNet/connectivity

#echo "Becoming root user"
#command="sudo su"
#echo "Running: $command"
#read -p "Press any key to begin" -r A
#$command

echo "Make it so that the OS doesn't record the read time of every file (an optimization and SSD saver)"
read -p "Press any key to begin" -r A
cat /etc/fstab | sed -e 's/relatime,errors=remount-ro/relatime,noatime,errors=remount-ro/' > /tmp/fstab
mv /tmp/fstab /etc/fstab

echo "Reduce swappiness factor so that the swap file is only needed in extreme situations"
read -p "Press any key to begin" -r A
echo "# Set swappiness to zero to save SSD and maximize use of memory
vm.swappiness=0" >> /etc/sysctl.conf

echo "

## Install
## See also (http://codeplot.com/documents/3186/edit)
#I Installed Ubuntu 8.04 Server
#US Keyboard Layout
#Zimbabwe region
#If this machine was using an SSD drive configure the paritions so that it has no swap
#I did a single partition marked as bootable and setup for the root on EXT3+Journaling
#I marked the OpenSSH server as an additional option
#I did not set it as a DNS server or Mail Server
 
## Naming
# For baobab we name our computers after trees so I called this one Sapele
# I added the default user as baobab
  
## Reboot and login
   
## Get the stuff you will need (you may want to combine these steps so you can leave the download running)

   "

command="apt-get update"
echo "Running: $command"
read -p "Press any key to continue" -r A
$command

command="apt-get install mysql-server nginx build-essential sudo git-core libopenssl-ruby lynx openssh-client vim irb ruby1.8-dev ruby1.8 libmysql-ruby rdoc1.8 ri1.8"
echo "Running: $command"
read -p "Press any key to continue" -r A
$command
ln -s /usr/bin/ruby1.8 /usr/bin/ruby
if [ ! -f /usr/bin/gem1.8 ]; then
  echo "Downloading and installing rubygems"
  read -p "Press any key to continue" -r A
  wget http://rubyforge.org/frs/download.php/38646/rubygems-1.2.0.tgz
  tar xvzf rubygems-1.2.0.tgz 
  cd rubygems-1.2.0
  ruby setup.rb
  cd ..
fi

ln -s /usr/bin/gem1.8 /usr/bin/gem


read -p "Press any key to continue" -r A
command="sudo gem install mongrel --no-rdoc --no-ri --verbose"
echo "Running: $command"
read -p "Press any key to continue" -r A
$command

command="sudo gem install mongrel_cluster --no-rdoc --no-ri --verbose"
echo "Running: $command"
read -p "Press any key to continue" -r A
$command

command="sudo gem install rake --verbose"
echo "Running: $command"
read -p "Press any key to continue" -r A
$command

command="sudo gem install json --verbose"
echo "Running: $command"
read -p "Press any key to continue" -r A
$command

   
echo "    
## At the end you will need to input the mysql root password
#    In general we create paswords with a hash of the machine name, a common nonce value and some special characters
      "
    
## Ubuntu 8.0.4.1 and beyond don't need to worry about this 
## Update the ssh for Debian security vulnerability
## If you are running Ubuntu/Debian locally, you should do this on your machine *before*
## You ssh into the server!
      
## Check for vulnerable keys
#      If you are using 8.04 like me (I think that Intrepid will include this fix by default)
#      Then you will get a message saying that it is correcting the blacklisted keys
#      When completed, you should run ssh-vulnkey to make sure your root user is
#      Not blacklisted. You should see two keys listed and both should start with
#      Not blacklisted:
# read -p "Press any key to continue" -r A
#      ssh-vulnkey
       
echo "## Creating deploy and www users on server"
command="adduser --disabled-password deploy"
echo "Running: $command"
read -p "Press any key to continue" -r A
$command

command="adduser --system --no-create-home --group --disabled-password www"
echo "Running: $command"
read -p "Press any key to continue" -r A
$command

visudo_commands="deploy ALL=(ALL) NOPASSWD:ALL
Defaults env_reset, insults"
echo "Adding: 
-----
$visudo_commands 
-----
to /etc/sudoers"
read -p "Press any key to continue" -r A

echo "$visudo_commands" >> /etc/sudoers
           
echo "
           Enter file in which to save the key (/home/YOURLOCALUSER/.ssh/id_rsa): <Enter>
           Enter passphrase (empty for no passphrase): <Enter>
           Enter same passphrase again: <Enter>

            
## On your local scp your public key up (note that I use the baobab user I created when installing Ubuntu on the server)
## Make sure you copy the id_rsa.pub and not the id_rsa, the id_rsa file is your private key and you want to keep it safe!
## If you don't know your server's ip address, type ifconfig on the server
            scp ~/.ssh/id_rsa.pub baobab@YOURSERVERIP:/tmp
            password: <Enter your server's baobab user password>

Generating keys for the deploy user now...

Press enter twice when asked for a passphrase (we want an empty passphrase)

"            
read -p "Press any key to continue" -r A
echo "Running: su deploy -c \"ssh-keygen -t rsa\""
read -p "Press any key to continue" -r A
su deploy -c "ssh-keygen -t rsa"
             
echo "## Adding public keys for all Baobab programmers
This should be safe to do - public keys are only have of the authentication puzzle - 
hence private and public keys.
"
read -p "Press any key to continue" -r A

echo "ssh-rsa AAAAB3NzaC1yc2EAAAABIwAAAQEAyUvMIvhJUYs7nIaiLBnUcs03XuOeHiw1JGh1M/ovbKc9YO4SJsl9CYxpyDeh9jSyvdNhNdeUSg7PBSSyAYpVXeK6WXN9LnqKOWRu8n5rXGNSycM2tenaADiS/xtMkHmIFYOE/QFQF+Amg5lKR1DjsfZXzscdtYsmAT09j6GFYfgY/KIP/gxSsEDzOGSIxYqJwpCzV+/nwub72ElzVcW9EJu2HpSD8jhKF6XrZ3VExsCk9v86qrTGWeVOyFubRb7+V6Db4xc+x2HirdyMW7hZceDfTpB0xX1GXd4PYZ023gfvNkGbIj/aOSDeJtDIJyQhzCbIXY+CiLkU556e0rg2Nw== njero@alexandria.local
ssh-rsa AAAAB3NzaC1yc2EAAAABIwAAAQEAzFtSLwtu0GoHLWG8X5ScMBX0xYtxjlWiEhEJRPWoIq+e4MQg34mtSEUtVt9lyeiAx9PfrmFhcbFeL72Y1bRi7bxEy+9Nu72bEPicVibukTuiFz1M0snoHVCtr6FnHd8q29+hcfeaqFwn2lIyE11DiH5aHOd2hAPNAVQ/p1CPY5HCmIerIuuE+QgEQTE6Zm3Lp8L4LvyFhZl4kZ5CLx8mOQWIj8ZVh3HUvCCh2b3AZdZzOE4E2Jk0ST4QJ7IlenRQ+9E6RKQ6pVOYgYunfhD0IIaXrd9UiGTGm+G/3YfKHhIznF3QyBv5lW06A5BKz37v8rXil7zu0jKLh5Kf41BiAQ== ace@lalanje
ssh-rsa AAAAB3NzaC1yc2EAAAABIwAAAIEAzb5cQe46LoJB5PQou+Rc+BNyRLC5iMILS8/KddZUJGdQobzzx6pxyvS6Wq9i6EGj6X8WzGTa9FLgFUNI1EGg0wLMANTpDwiMYyBLZQ8oLwbUkTrQaDKw8Bf/FwLQiaUjx0DB7U7YNJlGMZBtUgshD/4Z7KjThsB5ZA7dhtGiWws= crazy@sequoyah
ssh-rsa AAAAB3NzaC1yc2EAAAABIwAAAQEAyEB1sXJNJxzoUd4XZlwPBjmcnpyM1L6DWOHXgN/i/duVsqJrotxwtg9Qs0n5N9i8NxydzuwcMAb18RbtbSsGNxEcufOrNWyCHnBCDYfnt13eXjY+hpB4mMREg8xe5hzWdrQyCwdOHwqxDWOLmIsWrvfCrKtXH29+v3DvaFiJ1ndPx0wxrZ4hptRsnwuMyiNLRhuD616YzbSEASus+CKIKiVTtm/AvGr+YMS5vDt3bQsiRfvbp5dktUOZH+4Wsi4W93BQ2+bGFfNgu3BrtqKCsCb9K7UPFORyADVmgqD3vvcB8QCO3NRjOgq+9quVoynr9PAwxEONfVTFCg0gOgLXDQ== soyapi@masau
ssh-rsa AAAAB3NzaC1yc2EAAAABIwAAAQEAq7R5LvOBW5U1Vgn8ce/WDYr6A2/stqDvMwCAlZFqpBZExjWcFDC30aNX7bjdESwJ+BJTSZ6P7pCe4N+uia8nFLvxfUCMSXTvQ+cmOKnpmRbMDvctAafuk5fSLuPS9bReY/sh76ax135jrQejbGW4q+pLpUV3D0Ff9vgo905OCVjpCx+QrYMr4bqQ38h/a/GvdLx8Ow6c7fHJPDzJx+lxXQ6YUhm1AIzJFAgtVg1JXs0tkC4/9TxreRUnHyIWH7h4c+lzdPoJT8a2QV4IkHf3xMhki/mCYRFx7GBk3N8pnTO9b2PWlTN6dZtDYixrnVpkGxp4zKAmAa3i6G3IQ9QBkQ== bond@nkungudza
" >> /home/deploy/.ssh/authorized_keys

chmod 600 /home/deploy/.ssh/authorized_keys
chown deploy /home/deploy/.ssh/authorized_keys
              
echo "## On the server, create the root project folder (our project is called 'bart')"
command="mkdir /var/www/bart"
echo "Running: $command"
read -p "Press any key to continue" -r A
$command

command="chown deploy:deploy /var/www/bart"
echo "Running: $command"
read -p "Press any key to continue" -r A
$command


command="mkdir /etc/mongrel_cluster"
echo "Running: $command"
read -p "Press any key to continue" -r A
$command

echo "Creating mongrel user"
command="sudo adduser --system --no-create-home --group --disabled-password mongrel"
echo "Running: $command"
read -p "Press any key to continue" -r A
$command

echo "               
## On the server, setup the database
## We should be calling the database openmrs, with the user openmrs
## The password should be common probably

Enter the password you want to use for the openmrs database"
read -r PASSWORD

echo "Creating the openmrs database and the openmrs user. Enter root db password when prompted"
read -p "Press any key to continue" -r A

echo "CREATE DATABASE openmrs; GRANT ALL on openmrs.* to 'openmrs'@'localhost' IDENTIFIED BY '$PASSWORD';" | mysql -u root -p
                
echo "                 
## On your LOCAL MACHINE (NOT THE SERVER), cross your fingers and deploy (cap -T if you want to see all tasks)
## I have noticed that the deploy and deploy:setup tasks rely on each other
## So you have to run cap deploy first and let it fail...
## then run setup, then run deploy again
                 cap deploy
                 cap deploy:setup
                 cap deploy
                  
                 cap nginx:setup
                 cap nginx:start
 
                 * On the SERVER, run these db/migrate and bootstrap scripts while in /var/www/bart/current
echo 'DELETE FROM schema_migrations; DROP TABLE sessions; DROP TABLE weight_for_heights;' | mysql -u {dbusername} -p {database}
 
RAILS_ENV=production rake db:migrate
RAILS_ENV=production rake openmrs:bootstrap:load:defaults
 
RAILS_ENV=production script/runner 'PatientAdherenceDate.reset;PatientPrescriptionTotal.reset;PatientWholeTabletsRemainingAndBrought.reset;PatientHistoricalOutcome.reset'
           
                  * On your LOCAL MACHINE
                  cap deploy:restart
                     
# ------------- Firefox
# READ the firefox README
# If you don't have the firefox daemon it is here http://github.com/baobab/firefox-daemon 
                     "
