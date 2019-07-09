#!/usr/bin/php
<?php
# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    girdle.php                                         :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gfielder <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/04/26 14:11:24 by gfielder          #+#    #+#              #
#    Updated: 2019/04/26 14:11:24 by gfielder         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

define("ERR", "\x1B[1;31m");
define("RST", "\x1B[0;0;0m");
define("GRN", "\x1B[0;36m");
define("PMT", "\x1B[4;36m");

function get_email_address()
{
	while (1)
	{
		$input = str_replace(array('\'', '"', ',', ';', '<', '>'), "",
			trim(readline(), "\t\n\r\0\x0B '\"?"));
		if (filter_var($input, FILTER_VALIDATE_EMAIL))
			return $input;
		else
			echo ERR."That does not appear to be a valid email address. Enter a valid email address.\n".RST;
	}
}

function get_yes_no()
{
	while (1)
	{
		$input = trim(readline());
		if (strtolower($input) == 'y' || strtolower($input) == 'yes')
			return true;
		elseif (strtolower($input) == 'n' || strtolower($input) == 'no')
			return false;
		echo ERR."Invalid response. Please type y/Y/yes or n/N/no\n".RST;
	}
}

echo PMT."Enter your email address:\n".RST;
$from = get_email_address();
$headers = "From: ".$from;
echo PMT."Enter recipient email address:\n".RST;
$to = get_email_address();
echo PMT."Enter the subject:\n".RST;
$subject = trim(readline());
echo PMT."Enter the message:\n".RST;
$msg = trim(readline());

echo PMT."Confirm sending? y/n".RST;
if (!get_yes_no())
{
	echo GRN."Message cancelled. Exiting now.\n".RST;
	exit(0);
}

if (mail($to, $subject, $msg, $headers))
{
	echo GRN."Sent: Message sent to $to\n".RST;
}
else
{
	echo ERR."There was an error sending the message.\n".RST;
}

?>
