global hash_crc32

section .text

hash_crc32:
    vpxor   xmm0, xmm0, xmm0
    vpcmpeqb        ymm0, ymm0, YWORD [rdi]
    vpmovmskb       ecx, ymm0
    tzcnt   ecx, ecx
    xor eax, eax

loop_32:
    cmp ecx, 4
    jb loop_16

    crc32 eax, dword [rdi]
    add   rdi, 4
    sub   rcx, 4
    jmp   loop_32

loop_16:
    cmp ecx, 2
    jb loop_8

    crc32 eax, word [rdi]
    add   rdi, 2
    sub   rcx, 2
    jmp   loop_16

loop_8:
    cmp ecx, 0
    je end

    crc32 eax, byte [rdi]

end:
    ret

mv_seq:
    db   15
    db   14
    db   13
    db   12
    db   11
    db   10
    db   9
    db   8
    db   7
    db   6
    db   5
    db   4
    db   3
    db   2
    db   1
    db   0
    db   15
    db   14
    db   13
    db   12
    db   11
    db   10
    db   9
    db   8
    db   7
    db   6
    db   5
    db   4
    db   3
    db   2
    db   1
    db   0

