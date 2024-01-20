# Sokoban
cocos2x+vs2019：

安装方法：https://www.bilibili.com/video/BV1ho4y1S7s3

参考样例：https://gitee.com/at_He/moon-warriors

讲解：https://www.bilibili.com/video/BV1bs4y1H7dD

设计思路：

初始化一个10*10的初始区域

初始化每个棋盘大小

将每个棋盘上的东西放上去

棋盘-》BoxCollection

每个棋盘中-1为空白，-2为栅栏，-3为棋子，n为内置的其他棋盘

### Well Come to Recurse Box!

| Event       | Action                     |
| ----------- | -------------------------- |
| W A S D     | move up, down, left, right |
| Mouse wheel | zoom in / out              |

Box Example:

<img src="Resources/MainMenu/boxes/player.png" alt="player" style="zoom:25%;" /> Player
<img src="Resources/MainMenu/boxes/traget_player.png" alt="traget_player" style="zoom:25%;" />Player Target
<img src="Resources/MainMenu/boxes/default_box.png" alt="default_box" style="zoom:25%;" />Box
<img src="Resources/MainMenu/boxes/target_box.png" alt="target_box" style="zoom:25%;" /> Box Target
<img src="Resources/MainMenu/boxes/boundary.png" alt="boundary" style="zoom:25%;" />Boundary
<img src="Resources/MainMenu/boxes/panel.png" alt="panel" style="zoom:25%;" />Floor

