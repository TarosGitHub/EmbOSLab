#ifndef ELF_H_INCLUDED
#define ELF_H_INCLUDED

/**
 * @brief エントリーポイント関数型
 */
typedef void (*EntryPoint)(void);

/**
 * @brief ELFをメモリ上にロードする.
 * 
 * @param buf メモリ上に展開するELFへのポインタ
 * @return 以下の場合は、NULL. そうでない場合は、展開されたELFのエントリーポイントを返す.
 * - EFLのフォーマット不正
 * - ロード時のエラー
 */
extern EntryPoint elf_load(char* buf);

#endif
