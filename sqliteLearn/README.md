## 挂载

```shell
#1. 创建一个容器
docker run --name wwq -p 8080:8080 --mount type=bind,source=/home/kingwq/catkin_ws,target=/home/ros_ws -itd ros-agent
 
docker run --name wwq -p 8080:8080 -v /home/kingwq/catkin_ws:/home/docker_ws -itd ros-agent
#-d参数实现后台运行

# 进入一个容器
docker exec -it bae /bin/bash

#导出一个容器
```

## 保存容器为镜像

```shell
docker commit 3bd0eef03413  demo：v1.3  #提交你刚才修改的镜像，新的镜像名称为demo，版本为v1.1
```

## 镜像的导出和导入

```shell
#导出
docker save -o <保存路径> <镜像名称：标签>
docker save -o ./ubuntu.tar ubuntu:18.04
#导入
docker load --input ./ubuntu18.tar
```

## 容器的导出和导入

```shell
docker ps 

docker stop <容器名>
docker stop ubuntu18

#导出容器
docker export <容器名>  > <保存路径>
docker export ubuntu18 > ./ubuntu18.tar
#导入容器的命令
docker import <文件路径> <容器名>

```

## 镜像容器的操作

> doker save -o 保存到本地镜像的名字 镜像名称
>
> docker load –input 本地镜像名字
> （导入镜像）
>
> docker load < 本地镜像名字
>
> 删除镜像：docker rmi 镜像ID  （删除镜像)-f 参数；强制性删除
>
> 删除容器：docker rm 容器id
>
> 查看正在运行的容器：docker ps

## docker中apt-get update 报错解决

```shell
#发现有人通过--net=host参数改变容器网络模式解决，实验后果然解决问题。
docker run -it --name test --net=host ubuntu
```

## docker中安装软件失败问题

> 1.启动容器时,挂载本地Linux系统的etc/apt文件  docker run -ti -v /etc/apt/:/home/etc ubuntu
>
> 2.删除容器下的sources.lis  rm /etc/apt/sources.list
>
> 3.将本地sources.list 复制过来 cp /home/etc/sources.list /etc/apt/

## Sqlite3安装

```
sudo apt-get install sqlite3
```

