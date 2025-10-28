#!/bin/bash

cp -rf notebook/topics/ tmp/

get_new_path() {
    local dir="$1"
    local basename=$(basename "$dir")
    local dirname=$(dirname "$dir")
    local new_basename="${basename//_/ }"
    local new_basename=$(echo "$new_basename" | awk '{for(i=1;i<=NF;i++){$i=toupper(substr($i,1,1)) substr($i,2)}}1')
    local new_path="$dirname/$new_basename"
    echo "$new_path"
}

process_dir() {
    local dir=$1

    new_dir=$(get_new_path "$dir")
    if [ "$dir" != "$new_dir" ]; then
        mv "$dir" "$new_dir"
    fi
    for file in "$new_dir"/*; do
        if [ -f "$file" ]; then
            new_file=$(get_new_path "$file")
            mv "$file" "$new_file"
        elif [ -d "$file" ]; then
            process_dir "$file"
        fi
    done
}

process_dir ./tmp

cd Tmp
codes2pdf ./ notebook.pdf --author "$1" --initials "$2"
cp notebook.pdf ../notebook.pdf
cd ..

rm -rf Tmp
