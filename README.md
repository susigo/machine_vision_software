# machine_vision_software
请看说明文档
	这是用于计算机视觉课程作业的演示软件无任何版权保护您可随意修改使用、
  本软件基于ubuntu2019、 qt5.13 、opencv3.4.7、c++环境，有两个简单功能。
一将按钮映射到编译目录下的 ./imgs/文件夹中;
二、在新窗口中显示选中算子对当前图片进行卷集处理后的效果图。
因时间有限我只实现了canny、sobel、laplacian、susan这四个算子，图片的保存与清除功能也没有添加。

软件使用方法：
	桌面右键新建命令窗口，敲入：qtcreator
	qtcreator打开后，在项目中打开MV_1_2项目，项目打开后点击编译按钮、
  编译完成后会弹出软件窗口，首先选择图片按钮（只需点击一次），再选	择算子按钮（请务必注意顺序）。
软件注意事项：
	1、亮度调整、对比度调整、以及部分算子功能未加入；
	2、底部阈值上下限未暂时无用；
	3、还原、保存功能暂未加入；
