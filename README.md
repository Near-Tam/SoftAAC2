# SoftAAC2
通过修改SoftAAC2.cpp学习解码器的解码的过程，以及OMX框架。从而认识解码器的移植操作。
## SoftAAC2.cpp
在该文件中添加一些log，观察流程

ALOGE("zhiyuanLOG: I am out internalGetParameter case3 if3");

## Softlame.cpp
模仿SoftAAC2.cpp编写出来。目的：lame解码器移植

# 开发步骤
## 修改源码
对SoftAAC2.cpp进行修改

## 编译

	在andrrid_source7.1/aosp目录下
	$source build/envsetup.sh
	$lunch [2] #aosp_arm64-eng
	$mmm framework/av/media/libstagefright/codecs/aacdec/

## 生成libstagefright_soft_aacdec.so，覆盖到手机上
	$adb root
	$adb remount
	$adb push out/target/product/generic_arm64/system/lib/libstagefright_soft_aacdec.so /system/lib
	$adb push out/target/product/generic_arm64/system/lib64/libstagefright_soft_aacdec.so /system/lib64

## 让新编译的程序生效
### 方法1：重启
$adb reboot
### 方法2：杀进程(kill pid)
$adb shell ps |grep mediaserver
$adb shell kill pid号(如：1046)

## 观察并保存log.txt
### 1.不打印log，但保存
$adb logcat -v threadtime > log.txt

### 2.同时打印和保存
$adb logcat -v threadtime | tee log.txt
