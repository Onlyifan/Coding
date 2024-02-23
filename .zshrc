if [[ $TERM_PROGRAM == "WarpTerminal" ]]; then
    #if [[ -r "${XDG_CACHE_HOME:-$HOME/.cache}/p10k-instant-prompt-${(%):-%n}.zsh" ]]; then
    #  source "${XDG_CACHE_HOME:-$HOME/.cache}/p10k-instant-prompt-${(%):-%n}.zsh"
    #fi
    source /opt/homebrew/share/powerlevel10k/powerlevel10k.zsh-theme
    [[ ! -f ~/.p10k.zsh ]] || source ~/.p10k.zsh
fi

# >>> conda initialize >>>
# !! Contents within this block are managed by 'conda init' !!
__conda_setup="$('/opt/homebrew/Caskroom/miniconda/base/bin/conda' 'shell.zsh' 'hook' 2> /dev/null)"
if [ $? -eq 0 ]; then
    eval "$__conda_setup"
else
    if [ -f "/opt/homebrew/Caskroom/miniconda/base/etc/profile.d/conda.sh" ]; then
        . "/opt/homebrew/Caskroom/miniconda/base/etc/profile.d/conda.sh"
    else
        export PATH="/opt/homebrew/Caskroom/miniconda/base/bin:$PATH"
    fi
fi
unset __conda_setup
# <<< conda initialize <<<

function cd() {
    builtin cd "$@" && lsd -F --group-directories-first
}

alias ..='cd ..'
alias ...='cd ../..'

alias rm='rm -i'

alias l='lsd -F --group-directories-first'
alias la='lsd -AF'
alias ll='lsd -lF --date +%m/%e" "%a" "%T'
alias lla='lsd -lAF --date +%m/%e" "%a" "%T'
alias tree='lsd --tree -lF --date +%m/%e" "%a" "%T'

alias vim='nvim'
alias view='nvim -R'

alias top='htop'

# 添加头文件路径
export C_INCLUDE_PATH=/usr/local/include:$C_INCLUDE_PATH
export CPLUS_INCLUDE_PATH=/usr/local/include/c++:$CPLUS_INCLUDE_PATH
export CPATH=/usr/local/include:$CPATH
export DYLD_LIBRARY_PATH=/usr/local/lib:$DYLD_LIBRARY_PATH
# clang -c -Ofast -ffast-math -flto -o epoll.o epoll.c
# clang -shared -fPIC -Ofast -ffast-math -flto -o libepoll.dylib epoll.o
