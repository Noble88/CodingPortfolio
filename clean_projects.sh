#!/bin/bash

# Define the projects folder
PROJECTS_FOLDER="projects_folder"

# Find all project folders
PROJECTS=$(find "$PROJECTS_FOLDER" -type d)

# Remove executables in each project folder
IFS=$'\n' # Set IFS to newline to properly handle folder names with spaces
for project in $PROJECTS; do
    if [ -f "$project/makefile" ]; then
        make -C "$project" -f makefile clean
    fi
done
