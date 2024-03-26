このプログラムは [https://github.com/kaz-mac/m5ime_light](https://github.com/kaz-mac/m5ime_light) に移動しました！

<br><br><br><br><br><br><br><br>



# M5Stack ATOM MatrixでPCのIMEの状態をLEDで表示するやつ

IMEの日本語入力の状態がオンなのかオフなのかわからなくて、日本語入力したいのに英字になったり、英字入力したいのに日本語になったりして困ってたら、シャポコさんがIMEの状態をシリアルポートに出力するやつを作ってたのを知ったので、ATOM Matrixと組み合わせてLEDをゲーミングPCのように光らせるやつを作ってみました。

## 必要なもの
* ハードウェア M5Stack [ATOM Matrix](https://www.switch-science.com/products/6260)
* FastLEDライブラリ
* PC側ソフトウェア [ImeTo232C](https://github.com/shapoco/ImeTo232C)、[参考ページ](https://blog.shapoco.net/2018/02/ime-status-to-led.html)

## しくみ
ATOM Matrixにプログラムを書き込むときに使うRTS/DTS信号のうち、G0に繋がっているRTSをIMEの状態の取得用に使います。PC側のソフトウェアはシャポコさんのImeTo232Cで、IMEがオンになったらRSTを出力するように設定します。この信号を使ってLEDのオン/オフを切り替えてます。
ATOM Matrixの本来の用途での使い方ではないので、フリーズしたりモードが切り替わってしまうことがあるかもしれません。

## 使い方
ImeTo232C側の設定はソースプログラムを見てください。
