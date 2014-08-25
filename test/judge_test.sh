#!/bin/sh
test_data()
{
    echo "test"
    return 0
}

generate_quiz()
{
    args=($@)
    unset args[0]
    args=(${args[@]})
    for arg in ${args[@]}
    do
        mkdir ${arg}
        cd ${arg}
        touch ${arg}.c
        touch ${arg}.md
        touch ${arg}_test.c
        mkdir input
        mkdir output
        cd ..
    done
}


case $1 in
    "generate") generate_quiz $@;;
    *) echo "Error - Unknown command";;
esac
