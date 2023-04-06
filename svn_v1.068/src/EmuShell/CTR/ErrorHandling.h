/*---------------------------------------------------------------------------*
  Project:  Pia
  File:     main.cpp

  Copyright (C)2011-2012 Nintendo Co., Ltd.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.
 *---------------------------------------------------------------------------*/


#ifndef ERRORHANDLING_H_
#define ERRORHANDLING_H_

#include <nn/types.h>

namespace nn{
    class Result;
}


///< これはエラー処理のために用意されたクラスです。
class ErrorHandling{
public:
    // 初期化処理。
    static void Initialize(void);

    // 終了処理。
    static void Finalize(void);

    // エラーが検出されたか？
    static bool IsErrorDetected(void);

    // エラーが検出されたことが明らかになってから呼んでもらうことを想定。
    // 発生したエラーに関する情報を得る。
    static nn::Result GetResultCode(void);
    static const char* GetFilename(void);
    static u32 GetLineNo(void);

    static void PrintResult(nn::Result result);

    // デバッグ出力に本クラスで保持しているリザルトコードの文字列表現をプリント。
    static void Print(void);

    // 本クラスで保持しているnn::Result型の値をクリアする。
    static void Clear(void);

    // {secret}
    // n1769
    // リザルトコードを強引にセットする。わざとエラーを発生させ、
    // エラー処理シーケンスが正常に機能するかどうかをチェックするために用意した。
    static void SetResultCode(nn::Result result);

    static const size_t FILENAME_MAX_LEN = 256;

    // nn::Result型のエラーコード関連。
    static nn::Result  s_result;
    static char8       s_filename[FILENAME_MAX_LEN];
    static u32         s_lineNo;

private:
    ///< コピーコンストラクタ、代入演算子は封印します。
    ErrorHandling(void){}
   ~ErrorHandling(void){}
    ErrorHandling           (const ErrorHandling&);
    ErrorHandling& operator=(const ErrorHandling&);

    static bool s_bInitialized;
};


#endif  // end of ERRORHANDLING_H_
