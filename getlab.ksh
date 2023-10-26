#!/bin/ksh

#set -o xtrace

CLASS="4301"
BASEDIR="/usr/local/${CLASS}"
DATADIR="${BASEDIR}/data"
SRCDIR="${BASEDIR}/src"
LIBDIR="${BASEDIR}/lib"
INCLUDEDIR="${BASEDIR}/include"

if [[ $# != 1 ]]; then
  print "Usage:" $0 "lab#"
  print "  where   lab# = a two-digit, zero-filled decimal number"
  print "                 representing the lab #"
  exit 1
fi

labNum=$1
while [[ ${#labNum} != 2 ]]; do
  read labNum?"Enter the # of the lab as a 2-digit # "
done

# create a folder for the new assignment
print -n "  * Checking to see if a folder exists for Lab ${labNum}. . ."
if [[ ! -d ./${labNum} ]]; then
  print "No"
  print "  * Creating a folder for Lab ${labNum}"
  mkdir ./${labNum}
else
  print "Yes"
  print "  * Folder for lab ${labNum} already exists; exiting"
  exit 2
fi

# copy all files from data folder
print -n "  * Checking to see if Lab ${labNum} has sample input and output files. . ."
if [[ -d ${DATADIR}/${labNum} ]]; then
  if [[ -z "$(ls -A ${DATADIR}/${labNum})" ]]; then
    print "No"
  else
    print "Yes"
    print "  * Copying input and output files for Lab ${labNum}"
    print "    from folder ${DATADIR}/${labNum} to folder ./${labNum}"
    cp ${DATADIR}/${labNum}/* ./${labNum}
  fi
else
  print "No"
fi

# if ${labNum}main.C exists, copy it
print -n "  * Checking to see if ${SRCDIR}/lab${labNum}main.C exists. . ."
if [[ -a ${SRCDIR}/lab${labNum}main.C ]]; then
  print "Yes"
  print "  * Copying file ${SRCDIR}/lab${labNum}main.C to folder ./${labNum}"
  cp ${SRCDIR}/lab${labNum}main* ./${labNum}
else
  print "No"
fi

# if an include file exists, copy it
print -n "  * Checking to see if ${INCLUDEDIR}/lab${labNum}.h exists. . ."
if [[ -a ${INCLUDEDIR}/lab${labNum}.h ]]; then
  print "Yes"
  print "  * Copying file ${INCLUDEDIR}/lab${labNum}.h to folder ./${labNum}"
  cp ${INCLUDEDIR}/lab${labNum}.h ./${labNum}
else
  print "No"
fi

# copy the Makefile to the new folder
if [[ -a ${SRCDIR}/Makefile ]]; then
  print "  * Copying file ${SRCDIR}/Makefile to folder ./${labNum}"
  cp ${SRCDIR}/Makefile ./${labNum}
  pattern='^#include[[:space:]]*((<lab'${labNum}'\.cpp>)|("lab'${labNum}'\.cpp"))'
  if [[ -a ${LIBDIR}/liblab${labNum}.a ]]; then
    print "  * Adding a target of lab${labNum} to targets2srcfileswithlibrary"
    sed -e "s/^\(targets2srcfileswithlibrary = .*\)/\1 lab${labNum}/g" \
      ./${labNum}/Makefile > ./${labNum}/TmpFile
    # create an empty file for the implementation code
    print "  * Touching file ./${labNum}/lab${labNum}.cpp"
    touch ./${labNum}/lab${labNum}.cpp
  elif [[ -a ${SRCDIR}/lab${labNum}main.C ]] && \
       egrep ${pattern} ${SRCDIR}/lab${labNum}main.C >/dev/null
  then
    print "  * Adding a target of lab${labNum}main to targets1srcfile"
    sed -e "s/^\(targets1srcfile = .*\)/\1 lab${labNum}main/g" \
      ./${labNum}/Makefile > ./${labNum}/TmpFile
    # create an empty file for the implementation code
    print "  * Touching file ./${labNum}/lab${labNum}.cpp"
    touch ./${labNum}/lab${labNum}.cpp
  elif [[ -a ${INCLUDEDIR}/lab${labNum}.h ]] && \
       egrep ${pattern} ${INCLUDEDIR}/lab${labNum}.h >/dev/null
  then
    print "  * Adding a target of lab${labNum}main to targets1srcfile"
    sed -e "s/^\(targets1srcfile = .*\)/\1 lab${labNum}main/g" \
      ./${labNum}/Makefile > ./${labNum}/TmpFile
    # create an empty file for the implementation code
    print "  * Touching file ./${labNum}/lab${labNum}.cpp"
    touch ./${labNum}/lab${labNum}.cpp
  elif [[ -a ${SRCDIR}/lab${labNum}main.C ]]; then
    print "  * Adding a target of lab${labNum} to targets2srcfiles"
    sed -e "s/^\(targets2srcfiles = .*\)/\1 lab${labNum}/g" \
      ./${labNum}/Makefile > ./${labNum}/TmpFile
    # create an empty file for the implementation code
    print "  * Touching file ./${labNum}/lab${labNum}.cpp"
    touch ./${labNum}/lab${labNum}.cpp
  else
    print "  * Adding a target of lab${labNum} to targets1srcfile"
    sed -e "s/^\(targets1srcfile = .*\)/\1 lab${labNum}/g" \
      ./${labNum}/Makefile > ./${labNum}/TmpFile
    # create an empty file for the implementation code
    print "  * Touching file ./${labNum}/lab${labNum}.cpp"
    touch ./${labNum}/lab${labNum}.cpp
  fi
  mv ./${labNum}/TmpFile ./${labNum}/Makefile
fi

print "  * Edit file ./${labNum}/lab${labNum}.cpp in Notepad++"

exit 0
