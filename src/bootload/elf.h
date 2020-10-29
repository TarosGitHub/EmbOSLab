#ifndef ELF_H_INCLUDED
#define ELF_H_INCLUDED

/**
 * @brief ELFをメモリ上にロードする.
 * 
 * @param buf メモリ上に展開するELFへのポインタ
 * @return 以下の場合は、-1. そうでない場合は、0を返す.
 * - EFLのフォーマット不正
 * - ロード時のエラー
 */
extern int elf_load(char* buf);

#endif
