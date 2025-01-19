# Miner Game

闲得无聊就用 C++ 复刻了初中时自创的游戏，~~会时不时改改 bug/增加新模式~~。

~~本来想做图形化界面的，但是作者目前有点菜搞不来qwq，说不定以后会上线。~~

（这个游戏之前还有一个 <a href="https://www.bilibili.com/video/BV1xb4y11763">VB 版本</a>，只剩下一个视频证明它存在过...）

### 经典模式游戏规则简介：

这是一个 **完全随机** 的自走棋，只需要输入玩家人数和所有玩家的昵称后，游戏就会自动运行。

游戏的棋盘是一个 $16\times 16$ 的网格，每个网格上有一些方块，具体是：

- 木：木头，分值为 $1$。可被岩浆烧毁。
- 石：石头，无特殊效果。
- 煤：煤矿，分值为 $3$。
- 铁：铁矿，分值为 $8$。
- 金：金矿，分值为 $24$。
- 钻：钻石，分值为 $64$。
- 红：红宝石，随机增加至多 $5$ 点生命值。
- 绿：绿宝石，随机增加至多 $1.0$ 倍得分倍率。
- 蓝：蓝宝石，随机增加至多 $30\%$ 物理闪避，闪避率上限为 $90\%$。
- 炸：炸弹，可由玩家、岩浆或另一个炸弹触发，炸毁曼哈顿距离不超过 $2$ 的所有方块。若由玩家触发则降低 $2$ 点生命值。 
- 浆：岩浆，随着游戏的进行会不断通过空气方块、木头进行扩散，玩家接触到会降低 $1$ 点生命值。

玩家轮流在地图上进行采矿，游戏会计算该玩家的随机采矿点，并获得该矿石对应的分数或者 buff。若玩家的生命值为 $0$ 则阵亡，所有玩家阵亡时游戏结束。游戏结束后得分高者获胜。

游戏会不断更新新模式，每个模式对应一个文件夹，运行文件夹目录下的 C++ 可执行文件即可。（不同的模式基本就是经典模式改一下矿石生成规则，若有特别的规则变化则会在控制台说明）

~~如果想到比较有趣的模式也可以提 issue，会根据实际情况做的。~~

**Tips:若感觉程序的运行速度较慢，可以修改宏定义里的sleep参数大小。**