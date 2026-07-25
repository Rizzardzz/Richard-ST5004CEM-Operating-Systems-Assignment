/*
====================================================
ST5004CEM Operating Systems and Security
Task 2: Memory Management Simulation

Features:
- Configurable page size
- Configurable number of frames
- Logical-address to page-number conversion
- FIFO and LRU page replacement
- Correct empty-frame allocation
- Page fault, hit and ratio calculations
- Detailed memory-allocation logging
====================================================
*/

#include <stdio.h>

#define MAX_FRAMES 10

/* Logical addresses used for testing.
   With a page size of 1024 bytes, these produce:
   7, 0, 1, 2, 0, 3, 0, 4, 2, 3
*/
int logicalAddresses[] = {
    7168, 0, 1024, 2048, 0,
    3072, 0, 4096, 2048, 3072
};

int pages[10];
int pageCount = 10;

/* Stores the final results of an algorithm. */
typedef struct
{
    int hits;
    int faults;
} Result;

/* Displays the current contents of all frames. */
void displayFrames(int frames[], int frameCount)
{
    printf("[ ");

    for (int i = 0; i < frameCount; i++)
    {
        if (frames[i] == -1)
            printf("- ");
        else
            printf("%d ", frames[i]);
    }

    printf("]");
}

/* Prints the performance statistics. */
void displayResults(Result result)
{
    printf("\nTotal Page Faults: %d\n", result.faults);
    printf("Total Hits: %d\n", result.hits);
    printf("Hit Ratio: %.2f\n",
           (float)result.hits / pageCount);
    printf("Miss Ratio: %.2f\n",
           (float)result.faults / pageCount);
}

/*
Simulates FIFO page replacement.
The oldest loaded page is replaced first.
*/
Result fifo(int frameCount)
{
    int frames[MAX_FRAMES];
    int nextFrame = 0;
    Result result = {0, 0};

    for (int i = 0; i < frameCount; i++)
        frames[i] = -1;

    printf("\n===== FIFO Page Replacement =====\n");

    for (int i = 0; i < pageCount; i++)
    {
        int page = pages[i];
        int found = 0;
        int replacedPage = -1;

        /* Check whether the page is already loaded. */
        for (int j = 0; j < frameCount; j++)
        {
            if (frames[j] == page)
            {
                found = 1;
                break;
            }
        }

        if (found)
        {
            result.hits++;
            printf("Page %d -> Hit        ", page);
        }
        else
        {
            result.faults++;
            replacedPage = frames[nextFrame];
            frames[nextFrame] = page;
            nextFrame = (nextFrame + 1) % frameCount;

            printf("Page %d -> Page Fault ", page);
        }

        displayFrames(frames, frameCount);

        if (!found && replacedPage != -1)
            printf(" Replaced: %d", replacedPage);

        printf("\n");
    }

    displayResults(result);
    return result;
}

/*
Simulates LRU page replacement.
Empty frames are used before any loaded page is replaced.
When frames are full, the least recently used page is removed.
*/
Result lru(int frameCount)
{
    int frames[MAX_FRAMES];
    int lastUsed[MAX_FRAMES];
    Result result = {0, 0};

    for (int i = 0; i < frameCount; i++)
    {
        frames[i] = -1;
        lastUsed[i] = -1;
    }

    printf("\n===== LRU Page Replacement =====\n");

    for (int i = 0; i < pageCount; i++)
    {
        int page = pages[i];
        int foundIndex = -1;
        int replaceIndex = -1;
        int replacedPage = -1;

        /* Search for the requested page. */
        for (int j = 0; j < frameCount; j++)
        {
            if (frames[j] == page)
            {
                foundIndex = j;
                break;
            }
        }

        if (foundIndex != -1)
        {
            result.hits++;
            lastUsed[foundIndex] = i;
            printf("Page %d -> Hit        ", page);
        }
        else
        {
            result.faults++;

            /* Use an empty frame before replacing a page. */
            for (int j = 0; j < frameCount; j++)
            {
                if (frames[j] == -1)
                {
                    replaceIndex = j;
                    break;
                }
            }

            /* If no empty frame exists, find the LRU page. */
            if (replaceIndex == -1)
            {
                replaceIndex = 0;

                for (int j = 1; j < frameCount; j++)
                {
                    if (lastUsed[j] < lastUsed[replaceIndex])
                        replaceIndex = j;
                }
            }

            replacedPage = frames[replaceIndex];
            frames[replaceIndex] = page;
            lastUsed[replaceIndex] = i;

            printf("Page %d -> Page Fault ", page);
        }

        displayFrames(frames, frameCount);

        if (foundIndex == -1 && replacedPage != -1)
            printf(" Replaced: %d", replacedPage);

        printf("\n");
    }

    displayResults(result);
    return result;
}

int main(void)
{
    int pageSize;
    int frameCount;

    printf("====================================\n");
    printf(" Memory Management Simulation\n");
    printf("====================================\n");

    printf("Enter page size in bytes: ");

    if (scanf("%d", &pageSize) != 1 || pageSize <= 0)
    {
        printf("Invalid page size.\n");
        return 1;
    }

    printf("Enter number of frames (1-%d): ", MAX_FRAMES);

    if (scanf("%d", &frameCount) != 1 ||
        frameCount < 1 || frameCount > MAX_FRAMES)
    {
        printf("Invalid number of frames.\n");
        return 1;
    }

    /* Convert every logical address into a page number. */
    for (int i = 0; i < pageCount; i++)
        pages[i] = logicalAddresses[i] / pageSize;

    printf("\nPage Size: %d bytes\n", pageSize);
    printf("Number of Frames: %d\n", frameCount);

    printf("Logical Addresses: ");

    for (int i = 0; i < pageCount; i++)
        printf("%d ", logicalAddresses[i]);

    printf("\nPage Reference String: ");

    for (int i = 0; i < pageCount; i++)
        printf("%d ", pages[i]);

    printf("\n");

    Result fifoResult = fifo(frameCount);
    Result lruResult = lru(frameCount);

    printf("\n===== Algorithm Comparison =====\n");
    printf("FIFO Faults: %d | Hits: %d\n",
           fifoResult.faults, fifoResult.hits);
    printf("LRU Faults:  %d | Hits: %d\n",
           lruResult.faults, lruResult.hits);

    if (lruResult.faults < fifoResult.faults)
        printf("LRU performed better for this test.\n");
    else if (fifoResult.faults < lruResult.faults)
        printf("FIFO performed better for this test.\n");
    else
        printf("Both algorithms performed equally.\n");

    printf("\nSimulation Completed Successfully\n");
    return 0;
}
