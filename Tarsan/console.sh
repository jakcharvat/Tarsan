#!/bin/sh

#  console.sh
#  Quizzy
#
#  Created by Jakub Charvát on 05.06.2022.
#  

LOGFILE=console.log

touch $LOGFILE
watch -n0.1 tail $LOGFILE
