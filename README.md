# MultiCOMS

整个软件包含3个主要模块：数据部分、界面显示、相机&显示控制。

### 软件安装

- [Qt环境搭建(Qt Creator)+Visual Studio](http://www.cnblogs.com/ranjiewen/p/5318768.html)
- cn_visual_studio_ultimate_2013_x86_dvd_3009109
- qt-opensource-windows-x86-msvc2013_64_opengl-5.4.1
- qt-vs-addin-1.2.3-opensource

- 按步骤将上面三个文件安装好，既可以在VS下运行Qt工程，首次需要vs配置qt和项目环境，然后运行回报缺少dll文件；然后再将qt的环境变量添加就即可

### 使用方法

- git clone https://github.com/ranjiewwen/QuickLookCameraForCMOS.git

- 使用vs2013打开sln工程设置：
     
     - （1）QT5->Project Setting->Version 选择Qt5.4.1版本
     - （2）QT5->Qt Options->Qt Version->add Qt5.4.1和对应的安装路径
- run即可成功 
        
      
