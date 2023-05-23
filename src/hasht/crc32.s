global hash_crc32

section .text

hash_crc32:
    vpxor       xmm0, xmm0, xmm0
    vpcmpeqb    ymm0, ymm0, yword [rdi]
    vpmovmskb   ecx,  ymm0
    tzcnt       ecx,  ecx

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

