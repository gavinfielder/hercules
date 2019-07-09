#!/bin/sh
# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    namean-lion.sh                                     :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gfielder <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/03/01 12:13:31 by gfielder          #+#    #+#              #
#    Updated: 2019/03/01 12:13:31 by gfielder         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# This script can be run on a freshly installed debian 9 VM and changes
# the default port used by SSH to $PORT

PORT=9361

# Make sure the user is root
EFFECTIVE_USER=`id -u | tr -d ' '`
if [ $EFFECTIVE_USER -ne 0 ]
then
	echo "This script must be run as root."
	exit 1
fi

# Check if we are already in an SSH session. If so, we can skip checking if SSH is installed.
TTY_LEN=`echo $SSH_TTY | wc -c | tr -d ' '`
if [ $TTY_LEN -le 1 ]
then
	# This is not an SSH session.
	# Check if OpenSSH Server is installed.
	INSTALLED=`apt list --installed | grep -c "openssh-server" | tr -d " \n\t"`
	if [ $INSTALLED -eq 0 ]
	then
		echo "openssh-server does not appear to be installed. Installing now."
		# install, using -y to automatically answer yes to any prompt.
		apt-get install openssh-server -y
	fi
fi

# Make a backup copy of /etc/ssh/sshd_config
cp /etc/ssh/sshd_config /etc/ssh/sshd_config.bak

# In order to avoid losing newlines, temporarly change the IFS field delimiter.
IFS_BAK=$IFS
IFS=
NEW_FILE=`grep -v "^Port .*$" /etc/ssh/sshd_config`
echo "Port $PORT" > /etc/ssh/sshd_config
echo "" >> /etc/ssh/sshd_config
echo $NEW_FILE >> /etc/ssh/sshd_config
IFS=$IFS_BAK

# Show the new port number
echo "New SSH Port: $PORT. Restarting SSH now."
/etc/init.d/ssh restart
