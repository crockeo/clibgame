#!/bin/bash

installPath="install_manifest.txt"

if [ -f "$installPath" ]; then
    while read p; do
        rm $p
    done < $installPath
    rm "$installPath"
else
    echo "Cannot uninstall: $installPath does not exist."
fi
