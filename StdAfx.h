// stdafx.h : 標準のシステム インクルード ファイルのインクルード ファイル、または
// 参照回数が多く、かつあまり変更されない、プロジェクト専用のインクルード ファイル
// を記述します。
// 
// 最終更新日：2023/10/07

#pragma once

#define WIN32_LEAN_AND_MEAN             // Windows ヘッダーから使用されていない部分を除外します。
// Windows ヘッダー ファイル:
#include <windows.h>

// C ランタイム ヘッダー ファイル
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>

// TODO: プログラムに必要な追加ヘッダーをここで参照してください。
#define _CRT_SECURE_NO_WARNINGS
#define _WINSOCK_DEPRECATED_NO_WARNINGS // 古い関数をいくつか使っているので。古いのを置き換えできるなら不要。

#include <memory.h>
#include <conio.h>    // getch
#include <objbase.h>  // CoCreateGuid
#include <iostream>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <vector>
#include <iterator>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
using namespace std;

// ファイルの存在確認
#include <shlwapi.h>
#pragma comment( lib, "shlwapi.lib" )
