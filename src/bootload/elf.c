#include "defines.h"
#include "elf.h"
#include "lib.h"

/* ELFヘッダ */
struct elf_header {
    struct {
        unsigned char magic[4]; /* マジックナンバ */
        unsigned char class; /* 32/64ビット */
        unsigned char format; /* エンディアン */
        unsigned char version; /* ELFフォーマットバージョン */
        unsigned char abi; /* OS種別 */
        unsigned char abi_version; /* OSバージョン */
        unsigned char reserve[7];
    } id; /* 識別情報(16bit) */
    short type; /* ファイル種別 */
    short arch; /* CPU種類 */
    long version; /* ファイルバージョン */
    long entry_point; /* 実行開始アドレス */
    long program_header_offset; /* プログラム・ヘッダ・テーブルの位置 */
    long section_header_offset; /* セクション・ヘッダ・テーブルの位置 */
    long flags; /* 各種フラグ */
    short header_size; /* ELFヘッダサイズ */
    short program_header_size; /* プログラム・ヘッダのサイズ */
    short program_header_num; /* プログラム・ヘッダの個数 */
    short section_header_size; /* セクション・ヘッダのサイズ */
    short section_header_num; /* セクション・ヘッダの個数 */
    short section_name_index; /* セクション名を格納するセクション */
};

/* プログラム・ヘッダ */
struct elf_program_header {
    long type; /* セグメント種別 */
    long offset; /* ファイル中の位置 */
    long virtual_addr; /* 論理アドレス(VA) */
    long physical_addr; /* 物理アドレス(PA) */
    long file_size; /* ファイル中のサイズ */
    long memory_size; /* メモリ上でのサイズ */
    long flags; /* 各種フラグ */
    long align; /* アラインメント */
};

/**
 * @brief プログラムヘッダ取得.
 * 
 * @param elf_header ELFヘッダへのポインタ
 * @param index プログラムヘッダのインデックス
 * @return プログラムヘッダへのポインタ.
 */
#define get_program_header(elf_header, index) ((struct elf_program_header*)((char*)(elf_header) + (elf_header)->program_header_offset + (elf_header)->program_header_size * (index)))

/**
 * @brief セグメントがロード可能かどうか判定する.
 * 
 * @param program_header プログラムヘッダへのポインタ
 * @return ロード可能の場合、真(0以外). そうでない場合、偽(0)を返す.
 */
#define can_load(program_header) ((program_header)->type == 1)

/**
 * @brief ELFヘッダのチェック.
 * 
 * @param header ELFヘッダへのポインタ
 * @return 以下の場合、-1. そうでない場合、0.
 * - ELFファイルでない
 * - 32bitでない
 * - ビッグエンディアンでない
 * - ELFフォーマットバージョン1でない
 * - 実行可能ファイルで
 * - ファイルバージョン1でない
 * - アーキテクチャが Hitachi H8/300 か H8/300h でない
 */
static int elf_check(struct elf_header* header)
{
    /* ELFであること */
    if (memcmp(header->id.magic, "\x7f" "ELF", 4)) {
        return -1;
    }

    /* 32bitであること */
    if (header->id.class != 1) {
        return -1;
    }

    /* ビッグエンディアンであること */
    if (header->id.format != 2) {
        return -1;
    }

    /* ELFフォーマットバージョン1であること */
    if (header->id.version != 1) {
        return -1;
    }

    /* 実行可能ファイルであること */
    if (header->type != 2) {
        return -1;
    }

    /* ファイルバージョン1であること */
    if (header->version != 1) {
        return -1;
    }

    /* アーキテクチャが Hitachi H8/300 か H8/300h であること */
    if ((header->arch != 46) && (header->arch != 47)) {
        return -1;
    }

    return 0;
}

/**
 * @brief セグメント単位でのロード.
 * 
 * @param header ELFヘッダへのポインタ
 * @return 常に0を返す.
 */
static int elf_load_program(struct elf_header* header)
{
    struct elf_program_header* phdr;

    int phdr_index;
    for (phdr_index = 0; phdr_index < header->program_header_num; phdr_index++) {
        phdr = get_program_header(header, phdr_index);

        if (!can_load(phdr)) {
            continue;
        }

        /* セグメントをメモリ上に展開 */
        memcpy((char*)phdr->physical_addr, (char*)header + phdr->offset, phdr->file_size);
        memset((char*)phdr->physical_addr + phdr->file_size, 0, phdr->memory_size - phdr->file_size);
    }

    return 0;
}

EntryPoint elf_load(char* buf)
{
    struct elf_header* header = (struct elf_header*)buf;

    if (elf_check(header) < 0) {
        return (EntryPoint)NULL;
    }

    if (elf_load_program(header) < 0) {
        return (EntryPoint)NULL;
    }

    return (EntryPoint)header->entry_point;
}
