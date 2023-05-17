* [Zadani](https://cw.fel.cvut.cz/wiki/courses/b2b99ppc/hw/hw05)

Testovani na Linuxu

```shell
#!/bin/bash

unzip $1
dir=`basename $1 .zip` 
cd dir
qmake
make
debug/hw05
```