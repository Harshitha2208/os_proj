#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_USERNAME_LENGTH 50
#define MAX_PASSWORD_LENGTH 50
#define ROTRIGHT(word, bits) (((word) >> (bits)) | ((word) << (32 - (bits))))
#define CH(x, y, z) (((x) & (y)) ^ (~(x) & (z)))
#define MAJ(x, y, z) (((x) & (y)) ^ ((x) & (z)) ^ ((y) & (z)))
#define EP0(x) (ROTRIGHT(x, 2) ^ ROTRIGHT(x, 13) ^ ROTRIGHT(x, 22))
#define EP1(x) (ROTRIGHT(x, 6) ^ ROTRIGHT(x, 11) ^ ROTRIGHT(x, 25))
#define SIG0(x) (ROTRIGHT(x, 7) ^ ROTRIGHT(x, 18) ^ ((x) >> 3))
#define SIG1(x) (ROTRIGHT(x, 17) ^ ROTRIGHT(x, 19) ^ ((x) >> 10))
const uint32_t k[64] = {
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
void sha256(const char *message, uint32_t hash[8]) {
    uint32_t w[64];
    uint32_t a, b, c, d, e, f, g, h;
    uint32_t temp1, temp2;
    int t;

    // Initialize hash values
    hash[0] = 0x6a09e667;
    hash[1] = 0xbb67ae85;
    hash[2] = 0x3c6ef372;
    hash[3] = 0xa54ff53a;
    hash[4] = 0x510e527f;
    hash[5] = 0x9b05688c;
    hash[6] = 0x1f83d9ab;
    hash[7] = 0x5be0cd19;

    // Pre-processing
    size_t initial_len = strlen(message);
    size_t new_len = ((initial_len + 8) / 64 + 1) * 64;
    uint8_t *msg = malloc(new_len);
    memcpy(msg, message, initial_len);
    msg[initial_len] = 0x80;  // Padding: Add a single '1' bit
    for (size_t i = initial_len + 1; i < new_len - 8; i++)
        msg[i] = 0;  // Padding: Add zeros
    uint64_t bit_len = initial_len * 8;
    memcpy(msg + new_len - 8, &bit_len, 8);  // Append the original length in bits

    // Process each 512-bit block
    for (size_t i = 0; i < new_len; i += 64) {
        // Prepare the message schedule
        for (t = 0; t < 16; t++)
            w[t] = (msg[i + t * 4] << 24) | (msg[i + t * 4 + 1] << 16) | (msg[i + t * 4 + 2] << 8) | (msg[i + t * 4 + 3]);

        for (t = 16; t < 64; t++)
            w[t] = SIG1(w[t - 2]) + w[t - 7] + SIG0(w[t - 15]) + w[t - 16];

        // Initialize working variables to the current hash value
        a = hash[0];
        b = hash[1];
        c = hash[2];
        d = hash[3];
        e = hash[4];
        f = hash[5];
        g = hash[6];
        h = hash[7];

        // Main loop
        for (t = 0; t < 64; t++) {
            temp1 = h + EP1(e) + CH(e, f, g) + w[t] + k[t]; // Fix: Removed k[t] from this line
            temp2 = EP0(a) + MAJ(a, b, c);
            h = g;
            g = f;
            f = e;
            e = d + temp1;
            d = c;
            c = b;
            b = a;
            a = temp1 + temp2;
        }

        // Update hash value
        hash[0] += a;
        hash[1] += b;
        hash[2] += c;
        hash[3] += d;
        hash[4] += e;
        hash[5] += f;
        hash[6] += g;
        hash[7] += h;
    }

    // Free dynamically allocated memory
    free(msg);
}

int hash() {
    char username[50];
    printf("Enter your username: ");
    scanf("%s", username);

    FILE *userFile = fopen("user.txt", "a");
    if (userFile == NULL) {
        printf("Error opening user file. Exiting.\n");
        return 1; // Exit with an error code
    }

    // Print the username to the user file
    fprintf(userFile, "%s\n", username);

    // Close the user file
    fclose(userFile);
    char password[50];
    char confirm_password[50];

    // Input password
    printf("Enter your password: ");
    scanf("%s", password);

    // Input confirmation
    printf("Confirm your password: ");
    scanf("%s", confirm_password);

    // Check if passwords match
    if (strcmp(password, confirm_password) != 0) {
        printf("Passwords do not match. Exiting.\n");
        return 1; // Exit with an error code
    }

    // Hash the password
    uint32_t hash[8];
    sha256(password, hash);

    // Open the file in append mode
    FILE *file = fopen("pass.txt", "a");
    if (file == NULL) {
        printf("Error opening file. Exiting.\n");
        return 1; // Exit with an error code
    }

    // Print the hashed password to the file
    for (int i = 0; i < 8; i++) {
        fprintf(file, "%08x", hash[i]);
    }
    fprintf(file, "\n");

    // Close the file
    fclose(file);

    printf("Password hashed and saved to pass.txt.\n");

    return 0;
}
bool authenticate_user() {
    char entered_username[MAX_USERNAME_LENGTH];
    char entered_password[MAX_PASSWORD_LENGTH];

    // Input username and password for authentication
    printf("Enter your username: ");
    scanf("%s", entered_username);
    printf("Enter your password: ");
    scanf("%s", entered_password);
    
    // Open user file for reading
    FILE *userFile = fopen("user.txt", "r");
    if (userFile == NULL) {
        perror("Error opening user file");
        exit(EXIT_FAILURE);
    }

    // Open password file for reading
    FILE *passFile = fopen("pass.txt", "r");
    if (passFile == NULL) {
        perror("Error opening password file");
        fclose(userFile);
        exit(EXIT_FAILURE);
    }

    char username[MAX_USERNAME_LENGTH];
    char hashed_password[MAX_PASSWORD_LENGTH];

    bool user_found = false;

    // Read each line from user file
    while (fscanf(userFile, "%s", username) == 1) {
        // Check if the entered username matches
        if (strcmp(username, entered_username) == 0) {
            user_found = true;
            
            // Read the hashed password from the same line in the password file
            fscanf(passFile, "%s", hashed_password);

            // Hash the entered password
            uint32_t entered_password_hash[8];
            sha256(entered_password, entered_password_hash);

            // Compare the hashed passwords
            char entered_password_hex[65];
            for (int i = 0; i < 8; i++) {
                sprintf(entered_password_hex + i * 8, "%08x", entered_password_hash[i]);
            }

            if (strcmp(hashed_password, entered_password_hex) == 0) {
                printf("Authentication successful!\n");
                fclose(userFile);
                fclose(passFile);
                return true;
            } else {
                printf("Authentication failed. Incorrect password.\n");
                fclose(userFile);
                fclose(passFile);
                return false;
            }
        }

        // Move to the next line in the password file
        fscanf(passFile, "%*[^\n]"); // Skip the rest of the line
    }

    fclose(userFile);
    fclose(passFile);

    if (!user_found) {
        printf("User not found.\n");
    }

    return false;
}
