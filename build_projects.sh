#!/bin/bash

# Define the projects folder
PROJECTS_FOLDER="projects_folder"

# Find all project folders
PROJECTS=$(find "$PROJECTS_FOLDER" -type d)

# Build executables in each project folder using their respective makefiles
for project in $PROJECTS; do
    if [ -f "$project/makefile" ]; then
        make -C "$project" -f makefile
    fi
done
