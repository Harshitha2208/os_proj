#include <stdio.h>
#include <stdint.h>
#include <string.h>

#define SHA256_BLOCK_SIZE 64

// SHA-256 context structure
struct sha256_ctx {
    uint32_t state[8];
    uint64_t count;
    uint8_t buffer[SHA256_BLOCK_SIZE];
};

// Function prototypes
void sha256_init(struct sha256_ctx *ctx);
void sha256_update(struct sha256_ctx *ctx, const uint8_t *data, size_t len);
void sha256_final(struct sha256_ctx *ctx, uint8_t *hash);

// SHA-256 constants
static const uint32_t k[64] = {
    0x428a2f98, 0x71374491, 0xb5c0fbcf, 0xe9b5dba5,
    0x3956c25b, 0x59f111f1, 0x923f82a4, 0xab1c5ed5,
    0xd807aa98, 0x12835b01, 0x243185be, 0x550c7dc3,
    0x72be5d74, 0x80deb1fe, 0x9bdc06a7, 0xc19bf174,
    0xe49b69c1, 0xefbe4786, 0x0fc19dc6, 0x240ca1cc,
    0x2de92c6f, 0x4a7484aa, 0x5cb0a9dc, 0x76f988da,
    0x983e5152, 0xa831c66d, 0xb00327c8, 0xbf597fc7,
    0xc6e00bf3, 0xd5a79147, 0x06ca6351, 0x14292967,
    0x27b70a85, 0x2e1b2138, 0x4d2c6dfc, 0x53380d13,
    0x650a7354, 0x766a0abb, 0x81c2c92e, 0x92722c85,
    0xa2bfe8a1, 0xa81a664b, 0xc24b8b70, 0xc76c51a3,
    0xd192e819, 0xd6990624, 0xf40e3585, 0x106aa070,
    0x19a4c116, 0x1e376c08, 0x2748774c, 0x34b0bcb5,
    0x391c0cb3, 0x4ed8aa4a, 0x5b9cca4f, 0x682e6ff3,
    0x748f82ee, 0x78a5636f, 0x84c87814, 0x8cc70208,
    0x90befffa, 0xa4506ceb, 0xbef9a3f7, 0xc67178f2
};


// SHA-256 functions
#define Ch(x, y, z) (((x) & (y)) ^ ((~(x)) & (z)))
#define Maj(x, y, z) (((x) & (y)) ^ ((x) & (z)) ^ ((y) & (z)))
#define S(x, n) (((x) >> (n)) | ((x) << (32 - (n))))
#define R(x, n) ((x) >> (n))
#define Sigma0(x) (S(x, 2) ^ S(x, 13) ^ S(x, 22))
#define Sigma1(x) (S(x, 6) ^ S(x, 11) ^ S(x, 25))
#define sigma0(x) (S(x, 7) ^ S(x, 18) ^ R(x, 3))
#define sigma1(x) (S(x, 17) ^ S(x, 19) ^ R(x, 10))

// SHA-256 initialization
void sha256_init(struct sha256_ctx *ctx) {
    ctx->state[0] = 0x6a09e667;
    ctx->state[1] = 0xbb67ae85;
    ctx->state[2] = 0x3c6ef372;
    ctx->state[3] = 0xa54ff53a;
    ctx->state[4] = 0x510e527f;
    ctx->state[5] = 0x9b05688c;
    ctx->state[6] = 0x1f83d9ab;
    ctx->state[7] = 0x5be0cd19;
    ctx->count = 0;
}

// SHA-256 update
void sha256_update(struct sha256_ctx *ctx, const uint8_t *data, size_t len) {
    size_t i;

    for (i = 0; i < len; ++i) {
        ctx->buffer[(ctx->count % SHA256_BLOCK_SIZE)] = data[i];
        ++ctx->count;
        if ((ctx->count % SHA256_BLOCK_SIZE) == 0) {
            // Block complete, process it
            // (Note: This part is simplified for clarity. It doesn't handle message length extension attacks.)
            // TODO: Implement the actual SHA-256 block processing
            // ...

            // Reset buffer
            memset(ctx->buffer, 0, SHA256_BLOCK_SIZE);
        }
    }
}

// SHA-256 finalization
void sha256_final(struct sha256_ctx *ctx, uint8_t *hash) {
    // TODO: Implement the finalization steps
    // (Note: This part is simplified for clarity. It doesn't handle message length extension attacks.)
    // ...

    // Placeholder: Copy the state as the hash
    memcpy(hash, ctx->state, sizeof(ctx->state));
}

// Convert hash to hexadecimal string
void hash_to_string(const uint8_t *hash, char *output) {
    for (int i = 0; i < 32; i++) {
        sprintf(output + 2 * i, "%02x", hash[i]);
    }
}

void hash() {
    char password[20];
    char confirm_password[20];
    char username[20];
    printf("enter username : ");
    scanf("%s",username);
    printf("enter password : ");
    scanf("%s",password);
    printf("confirm password : ");
    scanf("%s",confirm_password);
    if(strcmp(password,confirm_password)!=0){
        printf("registration successful\n\n");
    }
    struct sha256_ctx ctx;
    uint8_t hash[32];  // SHA-256 produces a 256-bit hash (32 bytes)
    char hash_string[65];  // 2 characters per byte plus null terminator

    // Initialize SHA-256 context
    sha256_init(&ctx);

    // Update context with input string
    sha256_update(&ctx, (const uint8_t *)password, strlen(password));

    // Finalize and obtain hash
    sha256_final(&ctx, hash);

    // Convert hash to hexadecimal string
    hash_to_string(hash, hash_string);
    char hashed[66];
    strcpy(hashed, hash_string);
    strcat(hashed, "\n");
    printf("%s",hashed);
    printf("test");
   // hash_string
    FILE *file;

    // Open the file in append mode
    file = fopen("pass.txt", "a");

    // Check if the file is successfully opened
    if (file == NULL) {
        printf("Unable to open the file for appending.\n");

    }
    fprintf(file,hashed);

    // Close the file
    fclose(file);

    printf("Content appended successfully.\n");

}
