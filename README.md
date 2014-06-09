2DPhys
======

## これは何？
cocos2d-xでBox2DとLiquidFunを使うサンプルです。
View周りの作製にはCocosBuilderも使っています。

## 動作確認環境
 * cocos2d-x3.0alpha0
 * liquidfun-1.0.0
 * CocosBuilder3.0
 * Xcode5.0.2

iOS7.0のシミュレータと実機で動いています。

## ビルドの仕方
1. cocos2d-x3.0alpha0をダウンロードしてくる。
	* ダウンロードリンクはこちらから↓
	* http://www.cocos2d-x.org/download/version#Cocos2d-x

2. cocos2d-x-3.0alpha0/projects/以下にgit cloneする。

3. 以下のコマンドでxcodeを立ち上げて、普通にビルドします。

        open 2DPhys/proj.ios_mac/2DPhys.xcodeproj

## 補足
### Box2Dについて
cocos2d-x標準のBox2Dファイルだともしかしたら動かないかもしれません。
そんな時はliquidfunに入っているBox2Dファイルと同じ物を入れ替えて下さい。
具体的には、以下のディレクトリにあるファイルになります。

    cocos2d-x-3.0alpha0/external/Box2D


### 隠しコマンドについて
流体テストシーンで、長押しするとパラメータが変更されます。

