# Welcome to my Coding Portfolio

## Description
  Personally, This project is a way to run all my different C++ coding projects or school assignments I have accumlated over time. The point of this project was to create a single area where anyone can simply see my C++ knowledge without dumping scattered files to some employer who will most likely won't bother (or thats the hope). 
  In General terms, this project is allows someone to run all kinds of different projects after running the code once. Comes with a built in sorting and viewing feature to help find the one project out of the many (not yet implemented). Adding, and building is quite easy and can be done with either terminal commands or inside the project itself, running projects is just "./main" in the termianl.

## Table of Contents
- [Description](#description)
- [Table of Contents](#table-of-contents)
- [Installation Process](#installation-process)
  - [How to Build](#how-to-build)
  - [How to Run](#how-to-run)
  - [Terminal Input To Build & Run (CopyPasta)](#terminal-input-to-build--run-copypasta)
- [Usage](#usage)
  - [Getting Started](#getting-started)
- [Configuration (WIP) \[Progress Status: Not Worked On Yet\]](#configuration-wip-progress-status-not-worked-on-yet)
  - [Environment Variables](#environment-variables)
  - [Configuration Files](#configuration-files)
  - [Command-Line Options](#command-line-options)
  - [Dependencies](#dependencies)
  - [Installation Instructions](#installation-instructions)
- [Features](#features)
  - [Running All Creating C++ Projects](#running-all-creating-c-projects)
  - [Building Projects While Running](#building-projects-while-running)
  - [Input Cleaner](#input-cleaner)
  - [Sorting Projects & Project View](#sorting-projects--project-view)
- [Contributing](#contributing)
  - [General Contribution](#general-contribution)
  - [Pushing to Github Copypaste](#pushing-to-github-copypaste)
- [Credits/Acknowledgments](#creditsacknowledgments)
  - [Coding](#coding)
  - [Knowledge Help](#knowledge-help)
- [Troubleshooting](#troubleshooting)
- [Contact](#contact)
- [Roadmap](#roadmap)
- [List of what to do for read me](#list-of-what-to-do-for-read-me)

## Installation Process
  ### How to Build
  ```Bash
    chmod +x build_projects.sh
    ./build_projects.sh
    make
  ```

  ### How to Run
  ```Bash
    ./main
  ```
  
  ### Terminal Input To Build & Run (CopyPasta)
  ```Bash
    chmod +x build_projects.sh
    ./build_projects.sh
    make
    ./main
  ```
  
## Usage 
  ### Getting Started 
  1) make a folder inside of **projects_folder** (*can be any name u want*)
  2) Add metadata (with proper format), main.cpp, and copy of makefile
     - *see "projects_folder/exampleProject" for reference*
  3) Make sure any added projects do not leave the scope of its own folder!
  
  Other Notes...
  - metadata.txt: The Prefixes of each line "Project Name:", "Project Type:", is taken out when  In the metadata putting Description: delcare that line as a description and will not be shown in the meta data that appears when viewing projects

## Configuration (WIP) \[Progress Status: Not Worked On Yet\]
  ### Environment Variables:
  If your project relies on environment variables for configuration (such as database connection strings, API keys, or other sensitive information), you should document which variables need to be set and what their values should be.
    
  ### Configuration Files
  If your project uses configuration files (such as .env files, JSON files, YAML files, etc.), you can explain what settings are available in these files and how users should configure them.

  ### Command-Line Options
  If your project is a command-line tool, you might allow users to pass configuration options via command-line arguments. In this case, you can document what options are available and how to use them.
    
  ### Dependencies
  If your project depends on other services or libraries, you can mention any specific configuration requirements for those dependencies.

  ### Installation Instructions
  Sometimes, configuration steps are integrated into the installation process. If there are any configuration steps that need to be performed during installation, you should document them here.

## Features
  ### Running All Creating C++ Projects
  - By following the [Getting Started](#getting-started) you can create as many projects as you want (inside the folder called "projects_folder") and be able to run them all in one place
  ### Building Projects While Running
  - You will be able to type "build" or "build executables"

  ### Input Cleaner
  Your input will be cleaned by...
  - Capatlization doesn't matter
  - Trims leading and trailing white space
  - Filters Non-Alphanumeric Characters (Only reads numbers & letters)

  ### Sorting Projects & Project View
  Sorting: (THIS IS CURRENTLY UNDER DEVELOPMENT) Typeing "sort" will bring you to the sorting sections, and you sort by Date Completed, Name, Assignment Type
  Viewing: Typing "view" or "view options" you can select what type of viewing you would like...
  - "Minimal View": displays the coding project's name, project type, & data completed
  - "Show All Info": displays all the info stored for each project in chunks


## Contributing
  ### General Contribution
  Feel free to leave a comment suggesting and cool implementation, but other than that this is a personal project so I don't want anyone modifing the repository. Also by 2026 I will have graduated and most likely stop updating this project

  ### Pushing to Github Copypaste
  ```bash
  git config --global user.name "Henry Burton" && git config --global user.email "henrydburton@gmail.com" && git add . && git commit -m "INSERT COMMENT HERE" && git push -u origin main
  ```

## Credits/Acknowledgments
  ### Coding 
  - Henry Burton: Thats me, the author
  - Chat GPT: provided code implementations that were: unknown to me, to lazy for me to type, or more efficent then my current code
  
  ### Knowledge Help
  - Data Structures and Algorithms Teacher, Rene German
    - Taught about data structures and algorithms
    - Gave me feedback on the project and what implementation I should use over others
    - Said if I ever make it big, take him out to a stake and lobster dinner
  - Chat GPT
    - Gave suggestions on tackling asertain aspects of the project
    - Explained methtodology of implementions that were unknown to me

## Troubleshooting
  I plan on adding a debugger but for now `¯\_(ツ)_/¯`

## Contact
  Email me at henrydburton@gmail.com or leave a comemnt on the Github

## Roadmap
  These are ussally done in no particular order
  - Add a Debugger: This debugger shouldn't conflict 
    - Implement Debugger for Terminal Manager
    - Make Debugger for building files should specify: what files it is using to make the executable, name if executable, whether there is a executable already there, ASK GPT FOR MORE INFO on what to put
  - Add Sorting by Name, Assignment, Data Completed

## List of what todo for read me
  ### Catagories to Add
  1) Project Title: Clearly state the name of your project.
  2) Description: Provide a brief overview of what your project does and its purpose.
  3) Table of Contents: Include a table of contents with links to different sections for easy navigation.
  4) Installation: Instructions on how to install and set up your project, including any dependencies.
  5) Usage: Explain how to use your project, including examples or code snippets if applicable.  
    - Add a list of commands the user can use and how to input correct stuff
  6) Configuration (WIP): Provide information on any configuration settings or environment variables that need to be set.
  7) Features: List the key features of your project to give users an overview of its capabilities.
    - when creating the debugger add in features 
  8) Contributing: Guidelines for how others can contribute to your project, including information on coding standards, pull request guidelines, etc.
  9) License (NOT IMPLEMENTED): Clearly state the license under which your project is distributed.
  10) Credits/Acknowledgments: Thank any contributors, libraries, or resources that helped you build your project.
  11) Troubleshooting: Provide solutions to common issues or error messages that users might encounter.
    - Once created the debugger change this
  12) FAQs (NOT IMPLEMENTED): Address frequently asked questions about your project.
  13) Contact Information: Provide a way for users to get in touch with you if they have questions or feedback.
  14) Changelog (NOT IMPLEMENTED): Document changes and updates to your project over time.
  15) Roadmap (NOT IMPLEMENTED): Outline future plans and features that you intend to implement in your project.
  16) Testing (NOT IMPLEMENTED): Information on how to run tests and verify the correctness of your project.
  17) Security (NOT IMPLEMENTED): Any security considerations or best practices that users should be aware of.
  18) Dependencies (NOT IMPLEMENTED): List any external libraries or dependencies that your project relies on.
  19) Deployment (NOT IMPLEMENTED): Instructions on how to deploy your project to a production environment, if applicable.
  20) Resources (NOT IMPLEMENTED): Links to additional documentation, tutorials, or other helpful resources related to your project.

  ### GPT Suggestions
  - Clearer Installation Instructions: While you have provided installation instructions under the "Installation Process" section, it might be helpful to provide more context or explanations for each step. This can help users who are less familiar with the project or its dependencies.
  - Consolidate Similar Sections: Some sections, such as "Usage" and "Features," contain related information. Consider consolidating similar sections to avoid redundancy and improve readability.
  - Interactive Examples: If possible, consider including interactive examples or live demos to showcase your project's functionality. This can provide a more engaging experience for users and help them understand how to use your project effectively.
  
  ### Other Todo

