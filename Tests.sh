#!/bin/bash

TESTED_PATH="${1}"
TESTED_DIR="${TESTED_PATH}/TEST_DIR}"
MAIN_DIR=$(pwd)

mkdir -p "${TESTED_DIR}"
cd "${TESTED_DIR}"

get_unique_str(){
    cat /proc/sys/kernel/random/uuid
}

# PREPARING VARIABLES AND RESOURCES

CREATE="CREATE.$(get_unique_str)"
CREATE_STATUS="0"

MKDIR="MKDIR.$(get_unique_str)"
MKDIR_STATUS="0"

RMDIR="RMDIR.$(get_unique_str)"
RMDIR_STATUS="0"
mkdir "${RMDIR}"

UNLINK="UNLINK.$(get_unique_str)"
touch ${UNLINK}
UNLINK_STATUS="0"

LINK="LINK.$(get_unique_str)"
LINK_STATUS="0"
FILE_FOR_LINK="FILE_FOR_LINK.$(get_unique_str)"
touch "${FILE_FOR_LINK}"

MKNOD="MKNOD.$(get_unique_str)"
MKNOD_STATUS="0"

RENAME="RENAME.$(get_unique_str)"
RENAME_STATUS="0"
DIR_FOR_RENAME="DIR_FOR_RENAME.$(get_unique_str)"
mkdir "${RENAME}"

SETATTR="SETATTR.$(get_unique_str)"
SETATTR_STATUS="0"
touch "${SETATTR}"
chmod +x "${SETATTR}"

SYMLINK="SYMLINK.$(get_unique_str)"
SYMLINK_STATUS="0"
FILE_FOR_SYMLINK="FILE_FOR_SYMLINK.$(get_unique_str)"
touch "${FILE_FOR_SYMLINK}"

# TESTS IS STARTED
cd "${MAIN_DIR}"
chmod +x ./roflt.sh
./roflt.sh load
./roflt.sh add-path "${TESTED_DIR}"
cd "${TESTED_DIR}"

# CREATE TEST
touch "${CREATE}" > /dev/null 2>&1
CREATE_STATUS="${?}"

# MKDIR TEST
mkdir "${MKDIR}" > /dev/null 2>&1
MKDIR_STATUS="${?}"

# RMDIR TEST
rmdir "${RMDIR}" > /dev/null 2>&1
RMDIR_STATUS="${?}"

# UNLINK TEST
unlink "${UNLINK}" > /dev/null 2>&1
UNLINK_STATUS="${?}"

# LINK TEST
ln "${FILE_FOR_LINK}" "${LINK}" > /dev/null 2>&1
LINK_STATUS="${?}"

# MKNOD TEST
minor=2
major=250
mknod "${MKNOD}" c "${minor}" "${major}" > /dev/null 2>&1
MKNOD_STATUS="${?}"

# RENAME TEST
mv "${RENAME}" "${DIR_FOR_RENAME}" > /dev/null 2>&1
RENAME_STATUS="${?}"

# SYMLINK TEST
ln -s "${FILE_FOR_SYMLINK}" "${SYMLINK}" > /dev/null 2>&1
SYMLINK_STATUS="${?}"

# SETATTR TEST
chmod -x "${SETATTR}" > /dev/null 2>&1
SETATTR_STATUS="${?}"

# MAKING OUTPUT WITH TEST RESULTS
if [ "${CREATE_STATUS}" != "0" ]; then
    printf "%-15s%-10s\n" "CREATE IS " "PASSED"
elif [ "${CREATE_STATUS}" == "0" ]; then
    printf "%-15s%-10s\n" "CREATE IS " "FAILED"
fi

if [ "${MKDIR_STATUS}" != "0" ]; then
    printf "%-15s%-10s\n" "MKDIR IS " "PASSED"
elif [ "${MKDIR_STATUS}" == "0" ]; then
    printf "%-15s%-10s\n" "MKDIR IS " "FAILED"
fi

if [ "${RMDIR_STATUS}" != "0" ]; then
    printf "%-15s%-10s\n" "RMDIR IS " "PASSED"
elif [ "${RMDIR_STATUS}" == "0" ]; then
    printf "%-15s%-10s\n" "RMDIR IS " "FAILED"
fi

if [ "${UNLINK_STATUS}" != "0" ]; then
    printf "%-15s%-10s\n" "UNLINK IS " "PASSED"
elif [ "${UNLINK_STATUS}" == "0" ]; then
    printf "%-15s%-10s\n" "UNLINK IS " "FAILED"
fi

if [ "${LINK_STATUS}" != "0" ]; then
    printf "%-15s%-10s\n" "LINK IS " "PASSED"
elif [ "${LINK_STATUS}" == "0" ]; then
    printf "%-15s%-10s\n" "LINK IS " "FAILED"
fi

if [ "${MKNOD_STATUS}" != "0" ]; then
    printf "%-15s%-10s\n" "MKNOD IS " "PASSED"
elif [ "${MKNOD_STATUS}" == "0" ]; then
    printf "%-15s%-10s\n" "MKNOD IS " "FAILED"
fi

if [ "${RENAME_STATUS}" != "0" ]; then
    printf "%-15s%-10s\n" "RENAME IS " "PASSED"
elif [ "${RENAME_STATUS}" == "0" ]; then
    printf "%-15s%-10s\n" "RENAME IS " "FAILED"
fi

if [ "${SETATTR_STATUS}" != "0" ]; then
    printf "%-15s%-10s\n" "SETATTR IS " "PASSED"
elif [ "${SETATTR_STATUS}" == "0" ]; then
    printf "%-15s%-10s\n" "SETATTR IS " "FAILED"
fi

if [ "${SYMLINK_STATUS}" != "0" ]; then
    printf "%-15s%-10s\n" "SYMLINK IS " "PASSED"
elif [ "${SYMLINK_STATUS}" == "0" ]; then
    printf "%-15s%-10s\n" "SYMLINK IS " "FAILED"
fi

exit 0
