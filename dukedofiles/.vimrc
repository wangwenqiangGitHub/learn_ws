set number
set ts=4
set softtabstop=4
"禁止生成临时文件
set noswapfile
set nobackup

"set mouse=a

"搜索忽略大小写
" set ignorecase

"编码设置
  set enc=utf-8
"  set fencs=utf-8,ucs-bom,shift-jis,gb18030,gbk,gb2312,cp936

 "共享剪贴板  
  set clipboard=unnamed

 "代码补全
"  set completeopt=preview,menu

"Tab键的宽度
  set tabstop=4
  "统一缩进为4
  set softtabstop=4
  set shiftwidth=4

"设置文件编码
set fenc=utf-8

set encoding=UTF-8
" 设置编码
map <F2> :call TitleDet()<cr>
 function AddTitle()
    " call append(0,"\#!/bin/sh")
     call append(1,"# *****************************************************")
     call append(2,"# Author       : wwq ")
     call append(3,"# Last modified: ".strftime("%Y-%m-%d %H:%M"))
     call append(4,"# Email        : 1103169969@qq.com")
     call append(5,"# Filename     : ".expand("%:t"))
     call append(6,"# Description  : ")
     call append(7,"# ******************************************************")
     echohl WarningMsg | echo "Successful in adding copyright." | echohl None
 endf
 
 function UpdateTitle()
      normal m'
      execute '/# Last modified/s@:.*$@\=strftime(":\t%Y-%m-%d %H:%M")@'
      normal ''
      normal mk
      execute '/# Filename/s@:.*$@\=":\t".expand("%:t")@'
      execute 'noh'
      normal 'k
      echohl WarningMsg | echo \"Successful in updating the copyright.\" | echohl None
 endfunction
 
 function TitleDet()
     let n=1
     while n < 10
         let line = getline(n)
         if line =~ '^\#\s*\S*Last\smodified\S*.*$'
             call UpdateTitle()
             return
         endif
         let n = n + 1
     endwhile
     call AddTitle()
 endfunction

call plug#begin('~/.vim/plugged')
"Plug 'neoclide/coc.nvim', {'branch': 'release'}
"coc.nvim让vim能够使用vscode的功能"
"Plug 'preservim/nerdtree'
"左侧文件管理器
"Plug 'Xuyuanp/nerdtree-git-plugin'
"文件管理器的git插件"
"Plug 'vim-airline/vim-airline'
"底部状态栏"
"Plug 'vim-airline/vim-airline-themes'
"状态栏主题插件"
"Plug 'jiangmiao/auto-pairs'
"括号自动补齐"
"Plug 'kien/ctrlp.vim'
"模糊查找类似ctrlp"
"Plug 'mhinz/vim-startify'
"打开界面
"Plug 'ryanoasis/vim-devicons'
" 图标
"Plug 'fatih/vim-go', { 'do': ':GoUpdateBinaries' }
"vim的golang插件
"Plug 'Yggdroot/indentLine'
" 垂直对齐线
call plug#end()
