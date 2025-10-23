#!/usr/bin/bash

## Nouns : 
    # user 
    # todo-list
    # task
    # todo-file
    
## Verbs :
    # add
    # list
    # mark
    # del
    
## main    
function main () {
    # business logic here.
    echo "main: begin"
    
    # define printf colors
    RED="\e[31m"
    GREEN="\e[32m"
    RESET="\e[0m"

    # if no arguments at all
    if [[ $# -eq 0 ]]; then
        printf "Usage: ./todo ${RED}(not enough argumants !!)${RESET}\n"
        return 1
    # if only one argument
    elif [[ $# -eq 1 ]]; then
        # make sure it only list command
        if [[ "${1}" == "list" ]]; then
            list "./todo.txt"
            return 0
        else
            printf "Command not found ${RED}(Wrong command !!)${RESET}\n"
            return 1
        fi
    fi

    local COMMAND="$1"
    local TASK="$2"
    local TASK_NUMBER="$2"
    local -i TASKS_COUNTS 

    # create todo list if not exist
    if [ ! -f "./todo.txt" ]; then
        echo "Create: todo.txt"
        touch "./todo.txt"
        echo "Tasks N#:" >> ./todo.txt
        echo "0" >> ./todo.txt
        echo "Tasks:" >> ./todo.txt
        # no tasks exists in todo list
        TASKS_COUNTS=0
    else
        # get N# tasks exist in todo list
        TASKS_COUNTS="$(head -n 2 ./todo.txt | tail -1)"
    fi
    
    local LIST_PATH="./todo.txt"
    
    case "${COMMAND}" in
        "add")
            add "$LIST_PATH" "$TASK" "$TASKS_COUNTS"
        ;;
        "mark")
            mark "$LIST_PATH" "$TASK_NUMBER"
            if [[ "$?" == "1" ]];then
                return 0
            fi
        ;;    
        "del")
            echo "Delete task: [${TASKS_NUMBER}] ${TASK}"
            del "$LIST_PATH" "$TASK_NUMBER"
        ;;
        *)
            printf "Command not found ${RED}(Wrong command !!)${RESET}\n"
            return 1
        ;;
    esac

    return 0
}

## functions
function add () 
{
    local LIST_PATH="$1"
    local TASK="$2"
    local -i TASK_NUMBER=$(("$3"+1))
    local -i LINE_2=2
    echo "Add task: [${TASK_NUMBER}] ${TASK}"
    echo "[${TASK_NUMBER}] ${TASK}" >> "$LIST_PATH"
    sed -i "${LINE_2}c${TASK_NUMBER}" "$LIST_PATH"
}

function list () 
{
    local LIST_PATH="$1"
    echo "List todo tasks:"
    echo ""
    local LIST_PATH="$1"
    cat "$LIST_PATH"
    echo ""
}


function mark () 
{
    local LIST_PATH="$1"
    local TASK_NUMBER="$2"

    echo "$TASK_NUMBER"
    if [[ "${TASK_NUMBER}" == *[^0-9]* ]]; then
        printf "Argument isn't a number ${RED}(Wrong argument !!)${RESET}\n"
        return 1
    fi
    printf "Mark: task [${TASK_NUMBER}] ${GREEN}done${RESET}\n"
    
}

function del () 
{
    local LIST_PATH="$1"
    local TASK="$2"
}

# call main function ---> entry point.
main "$@"

