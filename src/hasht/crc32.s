global hash_crc32

section .text

hash_crc32:
    vpxor       xmm0, xmm0, xmm0
    vpcmpeqb    ymm0, ymm0, yword [rdi]
    vpmovmskb   ecx,  ymm0
    lzcnt       ecx,  ecx

    xor     edx, edx
    xor     eax, eax

loop_64:
    cmp ecx, 8
    jb loop_32

    crc32 rax, qword [rdi+rdx]
    add   rdx, 8
    sub   rcx, 8
    jmp   loop_64 

loop_32:
    cmp ecx, 4
    jb loop_16

    crc32 eax, dword [rdi+rdx]
    add   rdx, 4
    sub   rcx, 4
    jmp   loop_32

loop_16:
    cmp ecx, 2
    jb loop_8

    crc32 eax, word [rdi+rdx]
    add   rdx, 2
    sub   rcx, 2
    jmp   loop_16

loop_8:
    cmp ecx, 0
    je end

    crc32 eax, byte [rdi+rdx]

end:
    ret

