# TLPI

记录学习TLPI的仓库，书籍全名为Linux_UNIX系统编程手册，作者: [Michael Kerrisk](https://book.douban.com/search/Michael%20Kerrisk) 。

### 使用方法

每个章节对应每个文件夹，使用之前需要打包书籍所给的源码文件，然后使用别名来默认链接静态库。

以Debian/Ubuntu为例，具体操作如下：

第一步：下载本书所给的源码文件

```bash
wget "http://man7.org/tlpi/code/download/tlpi-161214-dist.tar.gz"
```

或者[点此下载](https://files.cnblogs.com/files/pluse/tlpi-161214-dist.tar.gz)

第二步：解压后，make编译

```bash
tar -zxvf tlpi-161214-dist.tar.gz
cd tlpi-dist/
make -j
```

第三步：拷贝头文件至系统目录

```bash
cd lib/
sudo cp tlpi_hdr.h /usr/local/include/
sudo cp get_num.h /usr/local/include/
sudo cp error_functions.h /usr/local/include/
sudo cp ename.c.inc /usr/local/include/
```

第四步：制作静态库文件

```bash
gcc -c get_num.c error_functions.c
ar -crv libtlpi.a get_num.o error_functions.o
sudo cp libtlpi.a /usr/local/lib
```

完成：以后每次编译包含上述四个头文件的代码时需手动链接静态库。以编译example.c为例：

```bash
gcc example.c -o example -ltlpi
```

