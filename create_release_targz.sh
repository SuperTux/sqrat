#!/bin/sh -ex
export DIR=sqrat-0.8.92
tar cvfz ${DIR}.tar.gz --exclude-vcs --exclude-backups --exclude="*~" --exclude="*.orig" ${DIR}/{docs,g*,i*,R*,r*,sq*}  
