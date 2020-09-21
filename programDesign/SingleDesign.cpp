#include <stdio.h>

//饿汉模式

/*
不管程序是否需要这个对象的实例，总是在加载的时候就先创建好实例。
理解起来就像一个人想不想吃东西都把吃的先买好，如同怕饿了一样。
*/

class singleton

{

protected:

    singleton()
    {}

private:

    static singleton* p;

public:

    static singleton* initance();
	void hello(){printf("hello singleton\n");};
};

singleton* singleton::p = new singleton;

singleton* singleton::initance()
{
    return p;
}

//懒汉模式
#if 0
class singleton
{
protected:
    singleton()
    {
        pthread_mutex_init(&mutex);
    }
private:
    static singleton* p;
public:
    static pthread_mutex_t mutex;
    static singleton* initance();
};
 
pthread_mutex_t singleton::mutex;
singleton* singleton::p = NULL;
singleton* singleton::initance()
{
    if (p == NULL)
    {
        pthread_mutex_lock(&mutex);
        if (p == NULL)
            p = new singleton();
        pthread_mutex_unlock(&mutex);
    }
    return p;
}

#endif
#if 0
class singleton
{
protected:
    singleton()
    {
        pthread_mutex_init(&mutex);
    }
public:
    static pthread_mutex_t mutex;
    static singleton* initance();
    int a;
};
 
pthread_mutex_t singleton::mutex;
singleton* singleton::initance()
{
    pthread_mutex_lock(&mutex);
    static singleton obj;
    pthread_mutex_unlock(&mutex);
    return &obj;
}
#endif
/*
如何对象使用频率不高，占用内存还特别大，明显不适用饿汉模式了，这时需要一种懒加载
的思想，当程序需要这个实例的时候采取创建对象，就如同一个懒的饿到不行才去吃东西。
*/

int main(int argc, char* argv[] )
{
	singleton::initance()->hello();
	return 0;
}

