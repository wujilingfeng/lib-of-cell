<<<<<<< HEAD
#### dependencies(optional)

* Eigen（不再维护相关代码）
* Algebras
* cstructures

基于Eigen库的算法头文件依赖Eigen库，Eigen放到thirdpart文件夹.

我已经不再维护EIgen库的算法，目前我重写了基于Algebras库的算法。

Algebras的张量库可以代替EIgen.

基于Algebras库的算法头文件依赖Algebras库，Algebras放到thirdpart文件夹。

#### install
新建build文件夹，并进入.
cmake ..
make 
make install

#### 可视化

推荐使用Mesh_viewer库，代码紧凑，功能齐全,仅仅依赖opengl，跨平台，只需添加必要数据即可显示.

libcell_tools_view.h文件添加了libcell支持Mesh_viewer的j小函数，方便你的使用.

#### 遗留的工作

* 各种算法的完善

#### 支持的网格结构

* cell网格结构。市面上没有针对高维网格的数据结构，cell格式文件为仿照off自定义文件格式，非常简单（意味这极低的学习成本）
* tools_formats.h提供了off,obj,mesh文件格式的转换
=======
# libcell1.0
>>>>>>> c7898cad0d5d522b972b6384cefdd0360de41efd

