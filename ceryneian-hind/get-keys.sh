#!/bin/sh
/Applications/Google\ Chrome.app/Contents/MacOS/Google\ Chrome https://profile.intra.42.fr/oauth/applications/2812

read -p "Enter UID: " HIND_UID
read -p "Enter SECRET: " HIND_SECRET

echo $HIND_UID > keys.txt
echo $HIND_SECRET >> keys.txt
