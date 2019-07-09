# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    hind.rb                                            :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gfielder <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/03/15 13:52:12 by gfielder          #+#    #+#              #
#    Updated: 2019/03/15 16:13:06 by gfielder         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

require "oauth2"
KEYFILE="keys.txt"
FIELD_WIDTH=14

# This function will run for each login in the file
def hind(login, token)
	begin
		response = token.get("/v2/users/#{login}/locations")
		while response.status != 200
			puts "#{login.ljust(FIELD_WIDTH)}: Server response #{response.status}. \
				Trying again..."
			sleep(2)
			response = token.get("/v2/users/#{login}/locations")
		end
		if (response.parsed[0]["end_at"])
			puts "#{login.ljust(FIELD_WIDTH)}: #{login} is not logged in."
		elsif
			location = response.parsed[0]["host"]
			puts "#{login.ljust(FIELD_WIDTH)}: #{login} is located at #{location}"
		end
	rescue
		puts "#{login.ljust(FIELD_WIDTH)}: not a valid login"
	end
end


# Begin main
# First perform some error checks
if not File.file?(KEYFILE)
	puts "key file not found. Run ./get-keys first!"
	exit 0
elsif ARGV.length != 1
	puts "usage: ruby hind.rb filename"
	exit 0
elsif not File.file?(ARGV[0])
	puts "Invalid file specified."
	exit 0
end

# Get the keys from the keyfile
keys = File.readlines(KEYFILE)
uid = keys[0].chomp
secret = keys[1].chomp

# Set up the client credentials
client = OAuth2::Client.new("#{uid}", "#{secret}", site: "https://api.intra.42.fr")
token=0
while token == 0
	begin
		token = client.client_credentials.get_token
	rescue
		puts "Could not connect to the API. Are you connected to the Network? Trying again..."
		sleep(2)
	end
end


# Open the file and read each line
fin = File.open(ARGV[0]).each_line do |line|
	login = line.chomp
	hind(login, token)
end
fin.close
