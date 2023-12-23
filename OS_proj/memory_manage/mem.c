#include <stdio.h>
#include <stdlib.h>

#define MAX_MEMORY_SIZE 3
#define PAGE_SIZE 3

// Structure to represent a page
struct Page {
    int page_id;
    int process_id;
};

// Function to simulate demand paging with a basic page replacement policy
void demandPaging(struct Page pageQueue[], int n) {
    printf("Demand Paging Simulation:\n");

    // Memory array to simulate main memory
    struct Page *memory = (struct Page *)malloc(MAX_MEMORY_SIZE * sizeof(struct Page));

    // Initialize memory
    for (int i = 0; i < MAX_MEMORY_SIZE; i++) {
        memory[i].page_id = -1; // -1 indicates an empty slot in memory
        memory[i].process_id = -1;
    }

    printf("Loading pages into memory:\n");

    for (int i = 0; i < n; i++) {
        float requiredPages = (pageQueue[i].process_id + PAGE_SIZE - 1) / PAGE_SIZE; // Calculate the number of pages needed

        // Check if the pages are already in memory
        int pagesInMemory = 0;
        for (int j = 0; j < MAX_MEMORY_SIZE; j++) {
            if (memory[j].process_id == pageQueue[i].process_id) {
                pagesInMemory++;
            }
        }

        if (pagesInMemory < requiredPages) {
            // Page fault: Not all required pages are in memory

            // Evict pages using a simple FIFO replacement policy
            for (int j = 0; j < MAX_MEMORY_SIZE; j++) {
                if (memory[j].page_id == -1 || memory[j].process_id != pageQueue[i].process_id) {
                    // Empty slot or page from a different process
                    continue;
                }

                // Evict the page
                printf("Evicting page %d of process %d from memory\n", memory[j].page_id, memory[j].process_id);
                memory[j].page_id = -1;
                memory[j].process_id = -1;

                pagesInMemory--;
                if (pagesInMemory == requiredPages) {
                    break; // Enough pages evicted
                }
            }
        }

        // Load pages into memory
        for (int j = 0; j < requiredPages; j++) {
            int emptySlotIndex = -1;
            for (int k = 0; k < MAX_MEMORY_SIZE; k++) {
                if (memory[k].page_id == -1) {
                    emptySlotIndex = k;
                    break;
                }
            }

            if (emptySlotIndex != -1) {
                // Load the page
                memory[emptySlotIndex].page_id = j;
                memory[emptySlotIndex].process_id = pageQueue[i].process_id;
                printf("Loaded page %d of process %d into memory\n", j, pageQueue[i].process_id);
            }
        }
    }

    // Free allocated memory
    free(memory);

    printf("Demand Paging Simulation complete.\n");
}

int main() {
    // Example pages
    struct Page pageQueue[] = {
        {0, 1},
        {5, 2},
        {10, 1},
        {2, 3},
        // Add more pages as needed
    };

    int n = sizeof(pageQueue) / sizeof(pageQueue[0]);

    // Perform demand paging simulation
    demandPaging(pageQueue, n);

    return 0;
}
