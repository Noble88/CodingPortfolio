#!/bin/bash

# Define the projects folder
PROJECTS_FOLDER="projects_folder"

# Find all project folders
PROJECTS=$(find "$PROJECTS_FOLDER" -type d)

# Iterate over each project folder to build the projects
IFS=$'\n' # Set IFS to newline to properly handle folder names with spaces
for project in $PROJECTS; do
    if [ -f "$project/makefile" ]; then
        project_name=$(basename "$project")

        # Define the character limit for the project name
        CHARACTER_LIMIT=25  # Adjust this value as needed

        # Trim project name if it exceeds character limit
        if [ ${#project_name} -gt $CHARACTER_LIMIT ]; then
            project_name="${project_name:0:$((CHARACTER_LIMIT-3))}..."
        fi

        # Add spaces up to the character limit if the project name is shorter
        while [ ${#project_name} -lt $CHARACTER_LIMIT ]; do
            project_name+=" "
        done

        echo -n "Building: $project_name"

        # Check if make changed anything
        make_output=$(make -C "$project" -f makefile 2>&1)

        # Check for errors in make output
        if [[ $make_output == *Error* ]]; then
            echo "$make_output"
            break
        fi

        # Check for modified source files
        modified_sources=$(echo "$make_output" | grep -oE 'g\+\+.*-o.*' | sed 's/g\+\+//g' | sed 's/-c//g' | sed 's/-o//g')

        if [ -n "$modified_sources" ]; then
            echo " | Files need to be built."
            echo "$modified_sources" | awk -F'/' '{
                for (i = 1; i < NF - 1; i++) {
                    printf "   - %s\n", $i
                    printf "%*s", (i + 1) * 3, ""
                }
                split($NF, file_parts, ".")
                print "   - " file_parts[1]
            }' | sed 's/++//g'
        else
            echo " | Nothing to be done for 'all'."
        fi
    fi
done
