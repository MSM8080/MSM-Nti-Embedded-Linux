#!/usr/bin/bash

## Nouns
    # path ----> string
    # backups-directory ----> string
    # time-stamp ---> string
    # version-number ----> int
    
## Verbs
    # include 
        # 1. include word{-backup} in new extension: ~/dir-backup
        # 2. include {-time-stamp} in new extension: ~/dir-backup-2025-09-01-13-00
    
    # create
        # 1. create ~/backaps dir
        # 2. copy dir to new path with new name
        # 3. create ~/backups/new_dir_name.tar.gz

    # delete
        # 1. count number of dir backup versions
        # 2. delete dir.tar.gz old version if number exceed 5


function main()   
{
    echo "main: begin"

    # check if passed an argument
    if [[ $# -ne 1 ]]; then
        echo "Usage: main <path>"
        return 1
    fi

    # check if path to exist directory
    local DIR_PATH="$1"
    if [ ! -d "${DIR_PATH}" ]; then
        echo "Not a directory !!"
        return 1
    else 
        local DIR_NAME=$(basename "$DIR_PATH")
        
        # {include} "DIR_NAME-backups-timestamp"
        local NEW_DIR_NAME
        include "$DIR_NAME"
        
        # {create} ~/backups directory with create new backup dir in it
        local NEW_DIR_PATH
        local BACKUP_PATH
        create "$DIR_PATH" "$NEW_DIR_NAME"

        # {delete} oldest backup version if more than 5 backups versions
        delete "$BACKUP_PATH" "$DIR_NAME"
    fi
    
    
}

function include () 
{
    #echo "Usage: include <DIR>"
    local DIR_NAME="$1"
    # 1. include word{-backup} in new extension: ~/dir-backup
    NEW_DIR_NAME="$DIR_NAME-backup"
        # 2. include {-time-stamp} in new extension: ~/dir-backup-2025-09-01-13-00
    NEW_DIR_NAME="$NEW_DIR_NAME-$(date +%F)-$(date +%T)"

    echo "New directroy name: $NEW_DIR_NAME"
}


function create () 
{
    #echo "Usage: create <DIR_PATH> <NEW_DIR_NAME>"
    local DIR_PATH="$1"
    local NEW_DIR_NAME="$2"
    local PARENT_PATH="$(dirname "$DIR_PATH")"
    BACKUP_PATH="$PARENT_PATH/backups"

    # check if /PARENT_PATH/backups directory is not exist
    if [ ! -d "$BACKUP_PATH" ]; then
        # create it
        mkdir "$BACKUP_PATH"
        echo "New backup directroy path: $NEW_DIR_NAME"
    fi

    NEW_DIR_PATH=$"$BACKUP_PATH/$NEW_DIR_NAME"
    
    # copy dir to new path with new name
    cp -r "$DIR_PATH" "$NEW_DIR_PATH"

    # create new backup dir with new name into ~/backups directory
    tar czf "$NEW_DIR_PATH.tar.gz" "$NEW_DIR_PATH" 

    # delete new dir and keep only .tar.gz file
    rm -r "$NEW_DIR_PATH"

    echo "New backup file name: $NEW_DIR_PATH.tar.gz"
}


function delete () 
{
    #echo "Usage: delete <BACKUP_PATH> <DIR_NAME>"
    local BACKUP_PATH="$1"
    local DIR_NAME="$2"
    local -i FILE_NUMBERS=0
    
    # count thier numbers
    for FILE in "$BACKUP_PATH/"*; do
        FILE_NUMBERS=$((FILE_NUMBERS+1))
    done

    echo "Number of backup versions: $FILE_NUMBERS"
    # if more than 5 delete first one
    if (( FILE_NUMBERS > 5 )); then
        for FILE in "$BACKUP_PATH/"*; do
            echo "Delete oldest version: $FILE"
            rm "$FILE"
            return 0
        done
    fi
}



main "$@"