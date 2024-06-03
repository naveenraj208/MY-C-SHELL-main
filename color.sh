
cd() {
    builtin cd "$@"
    if [ "$PWD" = "/Downloads/MY-C-SHELL-main" ]; then
        printf '\033]11;#0000FF\a' 
    fi
}
