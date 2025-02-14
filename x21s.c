#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "sph/extra.h"
#include "sph/sph_blake.h"
#include "sph/sph_bmw.h"
#include "sph/sph_groestl.h"
#include "sph/sph_jh.h"
#include "sph/sph_keccak.h"
#include "sph/sph_skein.h"
#include "sph/sph_luffa.h"
#include "sph/sph_cubehash.h"
#include "sph/sph_shavite.h"
#include "sph/sph_simd.h"
#include "sph/sph_echo.h"
#include "sph/sph_hamsi.h"
#include "sph/sph_fugue.h"
#include "sph/sph_shabal.h"
#include "sph/sph_whirlpool.h"
#include "sph/sph_sha2.h"
#include "sph/sph_haval.h"
#include "sph/sph_tiger.h"
#include "sph/lyra2.h"
#include "sph/gost_streebog.h"

enum Algo {
        BLAKE = 0,
        BMW,
        GROESTL,
        JH,
        KECCAK,
        SKEIN,
        LUFFA,
        CUBEHASH,
        SHAVITE,
        SIMD,
        ECHO,
        HAMSI,
        FUGUE,
        SHABAL,
        WHIRLPOOL,
        SHA512,
        HASH_FUNC_COUNT
};
static void getAlgoString(const uint8_t* prevblock, char *output)
{
    strcpy(output, "0123456789ABCDEF");

    int i;

    for (i = 0; i < 16; i++){
            uint8_t b = (15 - i) >> 1; // 16 ascii hex chars, reversed
            uint8_t algoDigit = (i & 1) ? prevblock[b] & 0xF : prevblock[b] >> 4;

            int offset = algoDigit;
            // insert the nth character at the front
            char oldVal = output[offset];
            int j;
            for (j = offset; j-->0;) {
                    output[j+1] = output[j];
            }
            output[0] = oldVal;
    }
}

void x21s_hash(const char* input, char* output, uint32_t len) {
        uint32_t hash[64/4];
        char hashOrder[HASH_FUNC_COUNT + 1] = { 0 };

        sph_blake512_context ctx_blake;
        sph_bmw512_context ctx_bmw;
        sph_groestl512_context ctx_groestl;
        sph_jh512_context ctx_jh;
        sph_keccak512_context ctx_keccak;
        sph_skein512_context ctx_skein;
        sph_luffa512_context ctx_luffa;
        sph_cubehash512_context ctx_cubehash;
        sph_shavite512_context ctx_shavite;
        sph_simd512_context ctx_simd;
        sph_echo512_context ctx_echo;
        sph_hamsi512_context ctx_hamsi;
        sph_fugue512_context ctx_fugue;
        sph_shabal512_context ctx_shabal;
        sph_whirlpool_context ctx_whirlpool;
        sph_sha512_context ctx_sha512;
        sph_haval256_5_context ctx_haval;
        sph_tiger_context ctx_tiger;
        sph_gost512_context ctx_gost;
        sph_sha256_context ctx_sha;

        void *in = (void*) input;
        int size = len;

        getAlgoString(&input[4], hashOrder);

        int i;

        for (i = 0; i < 16; i++)
        {
                const char elem = hashOrder[i];
                const uint8_t algo = elem >= 'A' ? elem - 'A' + 10 : elem - '0';

                switch (algo) {
                case BLAKE:
                        sph_blake512_init(&ctx_blake);
                        sph_blake512(&ctx_blake, in, size);
                        sph_blake512_close(&ctx_blake, hash);
                        break;
                case BMW:
                        sph_bmw512_init(&ctx_bmw);
                        sph_bmw512(&ctx_bmw, in, size);
                        sph_bmw512_close(&ctx_bmw, hash);
                        break;
                case GROESTL:
                        sph_groestl512_init(&ctx_groestl);
                        sph_groestl512(&ctx_groestl, in, size);
                        sph_groestl512_close(&ctx_groestl, hash);
                        break;
                case SKEIN:
                        sph_skein512_init(&ctx_skein);
                        sph_skein512(&ctx_skein, in, size);
                        sph_skein512_close(&ctx_skein, hash);
                        break;
                case JH:
                        sph_jh512_init(&ctx_jh);
                        sph_jh512(&ctx_jh, in, size);
                        sph_jh512_close(&ctx_jh, hash);
                        break;
                case KECCAK:
                        sph_keccak512_init(&ctx_keccak);
                        sph_keccak512(&ctx_keccak, in, size);
                        sph_keccak512_close(&ctx_keccak, hash);
                        break;
                case LUFFA:
                        sph_luffa512_init(&ctx_luffa);
                        sph_luffa512(&ctx_luffa, in, size);
                        sph_luffa512_close(&ctx_luffa, hash);
                        break;
                case CUBEHASH:
                        sph_cubehash512_init(&ctx_cubehash);
                        sph_cubehash512(&ctx_cubehash, in, size);
                        sph_cubehash512_close(&ctx_cubehash, hash);
                        break;
                case SHAVITE:
                        sph_shavite512_init(&ctx_shavite);
                        sph_shavite512(&ctx_shavite, in, size);
                        sph_shavite512_close(&ctx_shavite, hash);
                        break;
                case SIMD:
                        sph_simd512_init(&ctx_simd);
                        sph_simd512(&ctx_simd, in, size);
                        sph_simd512_close(&ctx_simd, hash);
                        break;
                case ECHO:
                        sph_echo512_init(&ctx_echo);
                        sph_echo512(&ctx_echo, in, size);
                        sph_echo512_close(&ctx_echo, hash);
                        break;
                case HAMSI:
                        sph_hamsi512_init(&ctx_hamsi);
                        sph_hamsi512(&ctx_hamsi, in, size);
                        sph_hamsi512_close(&ctx_hamsi, hash);
                        break;
                case FUGUE:
                        sph_fugue512_init(&ctx_fugue);
                        sph_fugue512(&ctx_fugue, in, size);
                        sph_fugue512_close(&ctx_fugue, hash);
                        break;
                case SHABAL:
                        sph_shabal512_init(&ctx_shabal);
                        sph_shabal512(&ctx_shabal, in, size);
                        sph_shabal512_close(&ctx_shabal, hash);
                        break;
                case WHIRLPOOL:
                        sph_whirlpool_init(&ctx_whirlpool);
                        sph_whirlpool(&ctx_whirlpool, in, size);
                        sph_whirlpool_close(&ctx_whirlpool, hash);
                        break;
                case SHA512:
                        sph_sha512_init(&ctx_sha512);
                        sph_sha512(&ctx_sha512,(const void*) in, size);
                        sph_sha512_close(&ctx_sha512,(void*) hash);
                        break;
                }
                in = (void*) hash;
                size = 64;
        }

        sph_haval256_5_init(&ctx_haval);
        sph_haval256_5(&ctx_haval,(const void*) hash, 64);
        sph_haval256_5_close(&ctx_haval,hash);

        sph_tiger_init(&ctx_tiger);
        sph_tiger (&ctx_tiger, (const void*) hash, 64);
        sph_tiger_close(&ctx_tiger, (void*) hash);

        LYRA2((void*) hash, 32, (const void*) hash, 32, (const void*) hash, 32, 1, 4, 4);

        sph_gost512_init(&ctx_gost);
        sph_gost512 (&ctx_gost, (const void*) hash, 64);
        sph_gost512_close(&ctx_gost, (void*) hash);

        sph_sha256_init(&ctx_sha);
        sph_sha256 (&ctx_sha, (const void*) hash, 64);
        sph_sha256_close(&ctx_sha, (void*) hash);

        memcpy(output, hash, 32);
}
