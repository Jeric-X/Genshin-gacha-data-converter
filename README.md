# Genshin gacha data converter
将[统一可交换祈愿记录标准](https://github.com/DGP-Studio/Snap.Genshin/wiki/StandardFormat)导出的json格式祈愿历史记录转换为用于导入[paimon.moe](https://paimon.moe/)的xlsx文件

# 使用方法
- 使用支持导出`统一可交换祈愿记录标准`工具导出`data.json`
- 下载最新的对应`data.json`语言的本地化对照表`zh.json`，[地址](https://github.com/MadeBaruna/paimon-moe/tree/main/src/locales/items)
- 使用`paimon.moe`的`导出到Excel`功能导出一份空记录`export.xlsx`
- 把前面获得文件放到程序同目录，打开命令行，执行`GenshinConverter data.json zh.json export.xlsx`，报错的话下载安装[vc++运行时](https://docs.microsoft.com/en-us/cpp/windows/latest-supported-vc-redist?view=msvc-170)

# Powered By
- [Qt](https://www.qt.io/) under LGPL v3 license or Commercial license
- [QXlsx](https://github.com/QtExcel/QXlsx) under MIT license