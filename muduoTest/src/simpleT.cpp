#include <stdio.h>
#include <iostream>
#include <unistd.h>      //getpid()
#include <sys/syscall.h> //systemcall

int main(int argc, char **argv)
{
    std::cout << "pid=" << getpid() << std::endl;
    auto a = static_cast<pid_t>(::syscall(SYS_gettid));
    std::cout << a << std::endl;
    std::cout << static_cast<pid_t>(::syscall(SYS_gettid)) << std::endl;
    char strings[30];
    snprintf(strings,sizeof strings, "%s","hello world!");
    printf("%s\n",strings);
    
    return 0;
}