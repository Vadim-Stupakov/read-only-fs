#!/bin/bash

ARG="${1}"

REDIRFS="redirfs"
FILTER="roflt"
SYSFS_PATH="/sys/fs/${REDIRFS}/filters/${FILTER}"

load(){
    insmod "${REDIRFS}/${REDIRFS}.ko"
    insmod "${FILTER}/${FILTER}.ko"
}

addPaths(){
    local path="${1}"
    echo "a:i:${path}" > "${SYSFS_PATH}/paths"
}

unload(){
    echo "0" > "${SYSFS_PATH}/active"
    echo "c" > "${SYSFS_PATH}/paths"
    echo "1" > "${SYSFS_PATH}/unregister"
    rmmod "${FILTER}"
}

if [ "${ARG}" == "load" ];then
    load
fi

if [ "${ARG}" == "unload" ];then
    unload
fi

# MAIN

if [ "${ARG}" == "" ]; then
    echo "Please, enter a parameter."
fi

if [ "${ARG}" == "add-path" ];then
    path="${2}"
    if [ "${path}" != "" ]; then
        addPaths "${path}"
    else
        echo "Please, enter path as second parameter"
    fi
fi
