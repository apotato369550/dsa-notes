#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>

// Choose implementation: uncomment one
// #define CLOSED_HASHING_IMPL
#define OPEN_HASHING_IMPL

#ifdef CLOSED_HASHING_IMPL
#include "closed_hashing.h"
#define DICT_TYPE Dictionary
#define INIT_DICT(D) initializeDictionary(D)
#define INSERT(D, elem) insert(D, elem)
#define DELETE(D, elem) deleteElem(D, elem)
#define SEARCH(D, elem) search(D, elem)
#define GET_INDEX(D, elem) getIndex(D, elem)
#define PRINT_DICT(D) printDictionary(D)
#define MAX_SIZE MAX
#define IMPL_NAME "Closed Hashing (Linear Probing)"
#elif defined(OPEN_HASHING_IMPL)
#include "open_hashing.h"
#define DICT_TYPE Dictionary
#define INIT_DICT(D) initializeDictionary(D)
#define INSERT(D, elem) insert(D, elem)
#define DELETE(D, elem) deleteElem(D, elem)
#define SEARCH(D, elem) search(D, elem)
#define GET_INDEX(D, elem) getIndex(D, elem)
#define PRINT_DICT(D) printDictionary(D)
#define MAX_SIZE MAX_ENTRIES
#define IMPL_NAME "Open Hashing (Chaining)"
#endif

// Helper function to count elements in dictionary
int countElements(DICT_TYPE D) {
    int count = 0;

    #ifdef CLOSED_HASHING_IMPL
    // For closed hashing, count non-empty and non-deleted slots
    for (int i = 0; i < MAX_SIZE; i++) {
        if (D[i] != EMPTY && D[i] != DELETED) {
            count++;
        }
    }
    #elif defined(OPEN_HASHING_IMPL)
    // For open hashing, traverse all chains
    for (int i = 0; i < MAX_SIZE; i++) {
        NodePointer curr = D[i];
        while (curr != NULL) {
            count++;
            curr = curr->link;
        }
    }
    #endif

    return count;
}

// Helper function to check if dictionary is full (for closed hashing)
bool isFull(DICT_TYPE D) {
    #ifdef CLOSED_HASHING_IMPL
    return countElements(D) >= MAX_SIZE;
    #else
    return false;  // Open hashing can grow indefinitely
    #endif
}

// Helper function to check if dictionary is empty
bool isEmpty(DICT_TYPE D) {
    return countElements(D) == 0;
}

// Populate dictionary with random characters
void populateRandom(DICT_TYPE D, int numElements) {
    srand((unsigned int)time(NULL));
    printf("\n=== Populating with %d random elements ===\n", numElements);

    int inserted = 0;
    int attempts = 0;
    int maxAttempts = numElements * 10;  // Prevent infinite loop

    while (inserted < numElements && attempts < maxAttempts) {
        // Generate random printable ASCII character (A-Z, a-z, 0-9)
        char elem;
        int randType = rand() % 3;
        if (randType == 0) {
            elem = 'A' + (rand() % 26);  // Uppercase letters
        } else if (randType == 1) {
            elem = 'a' + (rand() % 26);  // Lowercase letters
        } else {
            elem = '0' + (rand() % 10);  // Digits
        }

        // Check if already exists
        if (!SEARCH(D, elem)) {
            INSERT(D, elem);
            printf("  [%d] Inserted '%c' at index %d\n", inserted + 1, elem, GET_INDEX(D, elem));
            inserted++;
        }
        attempts++;

        #ifdef CLOSED_HASHING_IMPL
        if (isFull(D)) {
            printf("Dictionary is FULL! Cannot insert more elements.\n");
            break;
        }
        #endif
    }

    if (inserted < numElements && attempts >= maxAttempts) {
        printf("Reached maximum attempts. Only inserted %d elements.\n", inserted);
    }
    printf("Population complete! Total elements: %d\n", countElements(D));
}

// Populate with predefined set of characters
void populatePredefined(DICT_TYPE D, const char *chars) {
    printf("\n=== Populating with predefined characters: \"%s\" ===\n", chars);

    int len = strlen(chars);
    int inserted = 0;

    for (int i = 0; i < len; i++) {
        char elem = chars[i];

        #ifdef CLOSED_HASHING_IMPL
        if (isFull(D)) {
            printf("Dictionary is FULL! Cannot insert more elements.\n");
            break;
        }
        #endif

        if (!SEARCH(D, elem)) {
            INSERT(D, elem);
            printf("  [%d] Inserted '%c' at index %d\n", inserted + 1, elem, GET_INDEX(D, elem));
            inserted++;
        } else {
            printf("  [skip] '%c' already exists\n", elem);
        }
    }

    printf("Predefined population complete! Total elements: %d\n", countElements(D));
}

// Delete random elements from dictionary
void deleteRandom(DICT_TYPE D, int numToDelete) {
    if (isEmpty(D)) {
        printf("Dictionary is empty! Nothing to delete.\n");
        return;
    }

    int currentCount = countElements(D);
    if (numToDelete > currentCount) {
        numToDelete = currentCount;
    }

    printf("\n=== Deleting %d random elements ===\n", numToDelete);

    srand((unsigned int)time(NULL));
    int deleted = 0;
    int attempts = 0;
    int maxAttempts = numToDelete * 20;

    while (deleted < numToDelete && attempts < maxAttempts) {
        // Generate random character to try deleting
        char elem;
        int randType = rand() % 3;
        if (randType == 0) {
            elem = 'A' + (rand() % 26);
        } else if (randType == 1) {
            elem = 'a' + (rand() % 26);
        } else {
            elem = '0' + (rand() % 10);
        }

        if (SEARCH(D, elem)) {
            DELETE(D, elem);
            printf("  [%d] Deleted '%c'\n", deleted + 1, elem);
            deleted++;
        }
        attempts++;

        if (isEmpty(D)) {
            printf("Dictionary is now EMPTY!\n");
            break;
        }
    }

    printf("Random deletion complete! Remaining elements: %d\n", countElements(D));
}

// Test all hash indices
void testHashFunction(DICT_TYPE D) {
    printf("\n=== Testing Hash Function ===\n");
    printf("Character ranges and their hash indices:\n");

    printf("\nDigits (0-9):\n");
    for (char c = '0'; c <= '9'; c++) {
        printf("  '%c' -> hash index %d\n", c, hash(c));
    }

    printf("\nUppercase Letters (A-Z, showing first 10):\n");
    for (char c = 'A'; c <= 'J'; c++) {
        printf("  '%c' -> hash index %d\n", c, hash(c));
    }

    printf("\nLowercase Letters (a-z, showing first 10):\n");
    for (char c = 'a'; c <= 'j'; c++) {
        printf("  '%c' -> hash index %d\n", c, hash(c));
    }

    printf("\nNote: All indices are modulo %d\n", MAX_SIZE);
}

// Stress test - insert many elements and observe collisions
void stressTest(DICT_TYPE D) {
    printf("\n=== Stress Test ===\n");
    printf("Attempting to insert entire alphabet (uppercase)...\n");

    int inserted = 0;
    int collisions = 0;

    for (char c = 'A'; c <= 'Z'; c++) {
        #ifdef CLOSED_HASHING_IMPL
        if (isFull(D)) {
            printf("Dictionary FULL after %d insertions!\n", inserted);
            break;
        }
        #endif

        int expected_index = hash(c);
        INSERT(D, c);
        int actual_index = GET_INDEX(D, c);

        if (expected_index != actual_index) {
            printf("  '%c': Collision! Expected index %d, placed at %d\n",
                   c, expected_index, actual_index);
            collisions++;
        } else {
            printf("  '%c': Placed at expected index %d\n", c, expected_index);
        }
        inserted++;
    }

    printf("\nStress test complete!\n");
    printf("  Inserted: %d characters\n", inserted);
    printf("  Collisions handled: %d\n", collisions);
    printf("  Total elements in dictionary: %d\n", countElements(D));
}

// Display collision statistics
void showStatistics(DICT_TYPE D) {
    printf("\n=== Dictionary Statistics ===\n");
    printf("Implementation: %s\n", IMPL_NAME);
    printf("Maximum capacity: ");
    #ifdef CLOSED_HASHING_IMPL
    printf("%d\n", MAX_SIZE);
    #else
    printf("Unlimited (dynamic chaining)\n");
    #endif

    int totalElements = countElements(D);
    printf("Current elements: %d\n", totalElements);

    #ifdef CLOSED_HASHING_IMPL
    printf("Load factor: %.2f%%\n", (totalElements * 100.0) / MAX_SIZE);

    // Count empty and deleted slots
    int emptySlots = 0, deletedSlots = 0;
    for (int i = 0; i < MAX_SIZE; i++) {
        if (D[i] == EMPTY) emptySlots++;
        else if (D[i] == DELETED) deletedSlots++;
    }
    printf("Empty slots: %d\n", emptySlots);
    printf("Deleted slots: %d\n", deletedSlots);

    #elif defined(OPEN_HASHING_IMPL)
    // Show chain lengths
    printf("Chain length distribution:\n");
    int maxChainLen = 0;
    int nonEmptyChains = 0;

    for (int i = 0; i < MAX_SIZE; i++) {
        int chainLen = 0;
        NodePointer curr = D[i];
        while (curr != NULL) {
            chainLen++;
            curr = curr->link;
        }

        if (chainLen > 0) {
            printf("  Index %d: %d elements\n", i, chainLen);
            nonEmptyChains++;
            if (chainLen > maxChainLen) {
                maxChainLen = chainLen;
            }
        }
    }

    printf("Non-empty chains: %d / %d\n", nonEmptyChains, MAX_SIZE);
    printf("Longest chain: %d elements\n", maxChainLen);
    if (totalElements > 0) {
        printf("Average chain length: %.2f\n", (float)totalElements / nonEmptyChains);
    }
    #endif
}

void showMenu() {
    printf("\n=== Hash Table Operations Menu ===\n");
    printf("Implementation: %s\n", IMPL_NAME);
    printf("----------------------------------\n");
    printf("1.  Initialize Dictionary\n");
    printf("2.  Insert Element\n");
    printf("3.  Delete Element\n");
    printf("4.  Search Element\n");
    printf("5.  Display Dictionary\n");
    printf("6.  Get Element Index\n");
    printf("7.  Populate with Random Characters\n");
    printf("8.  Populate with Predefined String\n");
    printf("9.  Delete Random Elements\n");
    printf("10. Test Hash Function\n");
    printf("11. Stress Test (Insert A-Z)\n");
    printf("12. Show Statistics\n");
    printf("0.  Exit\n");
    printf("----------------------------------\n");
    printf("Choice: ");
}

int main() {
    DICT_TYPE dict;
    int choice = -1;

    printf("========================================\n");
    printf("  HASH TABLE TESTING FRAMEWORK\n");
    printf("========================================\n");
    printf("Current implementation: %s\n", IMPL_NAME);
    printf("Dictionary capacity: %d entries\n", MAX_SIZE);
    printf("========================================\n");

    // Initialize dictionary by default
    INIT_DICT(dict);
    printf("Dictionary initialized successfully!\n");

    while (choice != 0) {
        showMenu();

        if (scanf("%d", &choice) != 1) {
            // Clear invalid input
            while (getchar() != '\n');
            printf("\nInvalid input! Please enter a number.\n");
            continue;
        }

        switch (choice) {
            case 1: {
                printf("\n--- Initialize Dictionary ---\n");
                INIT_DICT(dict);
                printf("Dictionary re-initialized successfully!\n");
                break;
            }

            case 2: {
                printf("\n--- Insert Element ---\n");

                #ifdef CLOSED_HASHING_IMPL
                if (isFull(dict)) {
                    printf("Dictionary is FULL! Cannot insert.\n");
                    break;
                }
                #endif

                char elem;
                printf("Enter character to insert: ");
                scanf(" %c", &elem);

                if (SEARCH(dict, elem)) {
                    printf("Element '%c' already exists in dictionary!\n", elem);
                } else {
                    INSERT(dict, elem);
                    printf("Successfully inserted '%c' at index %d\n", elem, GET_INDEX(dict, elem));
                }
                break;
            }

            case 3: {
                printf("\n--- Delete Element ---\n");

                if (isEmpty(dict)) {
                    printf("Dictionary is EMPTY! Nothing to delete.\n");
                    break;
                }

                char elem;
                printf("Enter character to delete: ");
                scanf(" %c", &elem);

                if (SEARCH(dict, elem)) {
                    DELETE(dict, elem);
                    printf("Successfully deleted '%c' from dictionary.\n", elem);
                } else {
                    printf("Element '%c' not found in dictionary!\n", elem);
                }
                break;
            }

            case 4: {
                printf("\n--- Search Element ---\n");
                char elem;
                printf("Enter character to search: ");
                scanf(" %c", &elem);

                if (SEARCH(dict, elem)) {
                    printf("Element '%c' FOUND at index %d!\n", elem, GET_INDEX(dict, elem));
                } else {
                    printf("Element '%c' NOT FOUND in dictionary.\n", elem);
                }
                break;
            }

            case 5: {
                printf("\n--- Display Dictionary ---\n");
                PRINT_DICT(dict);
                printf("Total elements: %d\n", countElements(dict));
                break;
            }

            case 6: {
                printf("\n--- Get Element Index ---\n");
                char elem;
                printf("Enter character to find index: ");
                scanf(" %c", &elem);

                if (SEARCH(dict, elem)) {
                    printf("Element '%c' is at index %d\n", elem, GET_INDEX(dict, elem));
                } else {
                    printf("Element '%c' not found in dictionary!\n", elem);
                }
                break;
            }

            case 7: {
                printf("\n--- Populate with Random Characters ---\n");
                int num;
                printf("Current elements: %d\n", countElements(dict));
                printf("Enter number of elements to add: ");
                scanf("%d", &num);

                if (num <= 0) {
                    printf("Invalid number! Must be greater than 0.\n");
                } else {
                    #ifdef CLOSED_HASHING_IMPL
                    int remaining = MAX_SIZE - countElements(dict);
                    if (num > remaining) {
                        printf("Warning: Only %d slots available. Will attempt to insert %d elements.\n",
                               remaining, num);
                    }
                    #endif
                    populateRandom(dict, num);
                }
                break;
            }

            case 8: {
                printf("\n--- Populate with Predefined String ---\n");
                char str[256];
                printf("Current elements: %d\n", countElements(dict));
                printf("Enter string of characters to insert: ");
                scanf(" %255s", str);

                populatePredefined(dict, str);
                break;
            }

            case 9: {
                printf("\n--- Delete Random Elements ---\n");

                if (isEmpty(dict)) {
                    printf("Dictionary is EMPTY! Nothing to delete.\n");
                    break;
                }

                int num;
                int currentCount = countElements(dict);
                printf("Current elements: %d\n", currentCount);
                printf("Enter number of elements to delete: ");
                scanf("%d", &num);

                if (num <= 0) {
                    printf("Invalid number! Must be greater than 0.\n");
                } else {
                    deleteRandom(dict, num);
                }
                break;
            }

            case 10: {
                testHashFunction(dict);
                break;
            }

            case 11: {
                printf("\n--- Stress Test ---\n");
                printf("This will INSERT the entire uppercase alphabet (A-Z).\n");
                printf("Current elements will be preserved.\n");
                printf("Continue? (1=Yes, 0=No): ");
                int confirm;
                scanf("%d", &confirm);

                if (confirm == 1) {
                    stressTest(dict);
                } else {
                    printf("Stress test cancelled.\n");
                }
                break;
            }

            case 12: {
                showStatistics(dict);
                break;
            }

            case 0: {
                printf("\n========================================\n");
                printf("  Exiting Hash Table Testing Framework\n");
                printf("========================================\n");
                printf("Final statistics:\n");
                printf("  Total elements: %d\n", countElements(dict));
                printf("\nGoodbye!\n");
                break;
            }

            default: {
                printf("\nInvalid choice! Please select a valid option (0-12).\n");
                break;
            }
        }

        if (choice != 0) {
            printf("\nPress Enter to continue...");
            while (getchar() != '\n');  // Clear input buffer
            getchar();  // Wait for Enter
        }
    }

    return 0;
}
