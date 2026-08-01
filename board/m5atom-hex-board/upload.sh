#!/bin/bash
echo "##########################################"
echo "# Script to upload web content to SPIFFS #"
echo "##########################################"
echo
read -p "Are you sure? " -n 1 -r
echo  
echo
if [[ $REPLY =~ ^[Yy]$ ]]
then
    cd web
    for f in *; do
        echo "Uploading -> $f"
        curl -F file=@$f http://hex-board.local/upload
    done
fi

