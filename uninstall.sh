#!/bin/bash

installPath="install_manifest.txt"

if [ -f "$installPath" ]; then
    while read p; do
        rm $p
    done < $installPath
    mv "$installPath" "$installPath""_OLD"
else
    echo "Cannot uninstall: $installPath does not exist."
fi
