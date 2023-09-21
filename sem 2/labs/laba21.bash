#!/bin/bash

# Указал ли пользователь директорию в качестве аргумента
if [ $# != 1 ]; then
    echo "Use: $0 <directory>"
    exit 1
fi;

# Проверить, существует ли директорий
if [ ! -d "$1" ]; then
    echo "Err: $1 is not a directory"
    exit 1
fi;

# Обход директория и поддиректория
for file in `find $1 -type d`
do
    realpath $file;
done