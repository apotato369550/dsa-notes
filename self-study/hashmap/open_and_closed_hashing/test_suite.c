#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <string.h>

// Choose implementation to test - uncomment one
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

// Test statistics
typedef struct {
    int totalTests;
    int passedTests;
    int failedTests;
} TestStats;

TestStats testStats = {0, 0, 0};

// Color codes for output
#define COLOR_GREEN "\033[0;32m"
#define COLOR_RED "\033[0;31m"
#define COLOR_YELLOW "\033[0;33m"
#define COLOR_BLUE "\033[0;34m"
#define COLOR_CYAN "\033[0;36m"
#define COLOR_MAGENTA "\033[0;35m"
#define COLOR_RESET "\033[0m"

// Helper function to count elements
int countElements(DICT_TYPE D) {
    int count = 0;

    #ifdef CLOSED_HASHING_IMPL
    for (int i = 0; i < MAX_SIZE; i++) {
        if (D[i] != EMPTY && D[i] != DELETED) {
            count++;
        }
    }
    #elif defined(OPEN_HASHING_IMPL)
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

// Helper function to assert test results
void assertTest(const char* testName, bool condition) {
    testStats.totalTests++;
    if (condition) {
        testStats.passedTests++;
        printf("%s[PASS]%s %s\n", COLOR_GREEN, COLOR_RESET, testName);
    } else {
        testStats.failedTests++;
        printf("%s[FAIL]%s %s\n", COLOR_RED, COLOR_RESET, testName);
    }
}

// ==================== TEST CASES ====================

// Test 1: Basic Insert and Search
void test_BasicInsertSearch() {
    printf("\n%s===== TEST 1: Basic Insert and Search =====%s\n", COLOR_YELLOW, COLOR_RESET);
    DICT_TYPE D;
    INIT_DICT(D);

    INSERT(D, 'A');
    assertTest("Insert 'A' and search finds it", SEARCH(D, 'A') == true);
    assertTest("Search for non-existent 'Z' returns false", SEARCH(D, 'Z') == false);
}

// Test 2: Multiple Insertions
void test_MultipleInsertions() {
    printf("\n%s===== TEST 2: Multiple Insertions =====%s\n", COLOR_YELLOW, COLOR_RESET);
    DICT_TYPE D;
    INIT_DICT(D);

    char elements[] = {'A', 'B', 'C', 'D', 'E'};
    int count = 5;

    printf("  Inserting: ");
    for (int i = 0; i < count; i++) {
        printf("%c ", elements[i]);
        INSERT(D, elements[i]);
    }
    printf("\n");

    bool allFound = true;
    for (int i = 0; i < count; i++) {
        if (!SEARCH(D, elements[i])) {
            printf("  %s[X]%s Failed to find '%c'\n", COLOR_RED, COLOR_RESET, elements[i]);
            allFound = false;
        }
    }

    assertTest("All 5 inserted elements are searchable", allFound);
}

// Test 3: Duplicate Insertion Prevention
void test_DuplicateInsertion() {
    printf("\n%s===== TEST 3: Duplicate Insertion Prevention =====%s\n", COLOR_YELLOW, COLOR_RESET);
    DICT_TYPE D;
    INIT_DICT(D);

    INSERT(D, 'A');
    int countBefore = countElements(D);
    printf("  Count after first insert: %d\n", countBefore);

    INSERT(D, 'A');  // Try inserting duplicate
    int countAfter = countElements(D);
    printf("  Count after duplicate insert: %d\n", countAfter);

    assertTest("Duplicate insertion doesn't increase count", countBefore == countAfter && countAfter == 1);
    assertTest("Element still searchable after duplicate attempt", SEARCH(D, 'A') == true);
}

// Test 4: Delete Operation
void test_DeleteOperation() {
    printf("\n%s===== TEST 4: Delete Operation =====%s\n", COLOR_YELLOW, COLOR_RESET);
    DICT_TYPE D;
    INIT_DICT(D);

    char elements[] = {'A', 'B', 'C'};
    printf("  Inserting A, B, C...\n");
    for (int i = 0; i < 3; i++) {
        INSERT(D, elements[i]);
    }

    printf("  Deleting 'B'...\n");
    DELETE(D, 'B');

    assertTest("Deleted element 'B' not found", SEARCH(D, 'B') == false);
    assertTest("Non-deleted element 'A' still found", SEARCH(D, 'A') == true);
    assertTest("Non-deleted element 'C' still found", SEARCH(D, 'C') == true);
    assertTest("Count reduced by 1 after delete", countElements(D) == 2);
}

// Test 5: Collision Handling
void test_CollisionHandling() {
    printf("\n%s===== TEST 5: Collision Handling =====%s\n", COLOR_YELLOW, COLOR_RESET);
    DICT_TYPE D;
    INIT_DICT(D);

    // Insert elements that will collide (same hash value modulo MAX_SIZE)
    char elem1 = 'A';  // ASCII 65
    char elem2 = 65 + MAX_SIZE;  // Will have same hash as 'A'

    printf("  Inserting '%c' (ASCII %d)...\n", elem1, (int)elem1);
    INSERT(D, elem1);
    printf("  Inserting '%c' (ASCII %d)...\n", elem2, (int)elem2);
    INSERT(D, elem2);

    assertTest("First colliding element found", SEARCH(D, elem1) == true);
    assertTest("Second colliding element found", SEARCH(D, elem2) == true);

    printf("  Element '%c' at index: %d\n", elem1, GET_INDEX(D, elem1));
    printf("  Element '%c' at index: %d\n", elem2, GET_INDEX(D, elem2));
}

// Test 6: Empty Dictionary Operations
void test_EmptyDictionary() {
    printf("\n%s===== TEST 6: Empty Dictionary Operations =====%s\n", COLOR_YELLOW, COLOR_RESET);
    DICT_TYPE D;
    INIT_DICT(D);

    assertTest("Search in empty dictionary returns false", SEARCH(D, 'A') == false);
    assertTest("Empty dictionary has 0 elements", countElements(D) == 0);

    // Delete from empty should not crash
    printf("  Attempting delete from empty dictionary...\n");
    DELETE(D, 'A');
    assertTest("Delete from empty dictionary doesn't crash", true);
}

// Test 7: Insert-Delete-Insert Sequence
void test_InsertDeleteInsert() {
    printf("\n%s===== TEST 7: Insert-Delete-Insert Sequence =====%s\n", COLOR_YELLOW, COLOR_RESET);
    DICT_TYPE D;
    INIT_DICT(D);

    printf("  Phase 1: Insert 'X'\n");
    INSERT(D, 'X');
    assertTest("Phase 1: 'X' inserted and found", SEARCH(D, 'X') == true);

    printf("  Phase 2: Delete 'X'\n");
    DELETE(D, 'X');
    assertTest("Phase 2: 'X' deleted and not found", SEARCH(D, 'X') == false);

    printf("  Phase 3: Re-insert 'X'\n");
    INSERT(D, 'X');
    assertTest("Phase 3: 'X' re-inserted and found", SEARCH(D, 'X') == true);
}

// Test 8: Comprehensive CRUD Cycle
void test_ComprehensiveCycle() {
    printf("\n%s===== TEST 8: Comprehensive CRUD Cycle =====%s\n", COLOR_YELLOW, COLOR_RESET);
    DICT_TYPE D;
    INIT_DICT(D);

    // Create
    printf("  CREATE: Inserting X, Y, Z\n");
    char phase1[] = {'X', 'Y', 'Z'};
    for (int i = 0; i < 3; i++) INSERT(D, phase1[i]);
    assertTest("Create: All 3 elements inserted", countElements(D) == 3);

    // Read
    printf("  READ: Searching for all elements\n");
    assertTest("Read: All elements searchable",
               SEARCH(D, 'X') && SEARCH(D, 'Y') && SEARCH(D, 'Z'));

    // Update (Delete Y + Insert M)
    printf("  UPDATE: Deleting Y, inserting M\n");
    DELETE(D, 'Y');
    INSERT(D, 'M');
    assertTest("Update: Old element 'Y' deleted", SEARCH(D, 'Y') == false);
    assertTest("Update: New element 'M' inserted", SEARCH(D, 'M') == true);

    // Final state verification
    bool finalCheck = SEARCH(D, 'X') && SEARCH(D, 'Z') &&
                      SEARCH(D, 'M') && !SEARCH(D, 'Y');
    assertTest("Final state: X, Z, M present; Y absent", finalCheck);

    printf("  Final dictionary contents:\n");
    PRINT_DICT(D);
}

// Test 9: Batch Operations
void test_BatchOperations() {
    printf("\n%s===== TEST 9: Batch Populate Operations =====%s\n", COLOR_YELLOW, COLOR_RESET);
    DICT_TYPE D;
    INIT_DICT(D);

    // Batch insert "HELLOWORLD" - duplicates should be ignored
    printf("  Batch inserting: HELLOWORLD\n");
    char elements[] = {'H', 'E', 'L', 'L', 'O', 'W', 'O', 'R', 'L', 'D'};
    for (int i = 0; i < 10; i++) {
        INSERT(D, elements[i]);
    }

    // Unique elements: H, E, L, O, W, R, D = 7 unique
    int elemCount = countElements(D);
    printf("  Expected unique count: 7, Actual: %d\n", elemCount);
    assertTest("Batch insert: Correct unique count (7)", elemCount == 7);

    // Verify all unique elements are present
    char unique[] = {'H', 'E', 'L', 'O', 'W', 'R', 'D'};
    bool allFound = true;
    for (int i = 0; i < 7; i++) {
        if (!SEARCH(D, unique[i])) {
            printf("  %s[X]%s Failed to find '%c'\n", COLOR_RED, COLOR_RESET, unique[i]);
            allFound = false;
        }
    }
    assertTest("Batch search: All unique elements found", allFound);
}

// Test 10: Delete Multiple Elements
void test_DeleteMultiple() {
    printf("\n%s===== TEST 10: Delete Multiple Elements =====%s\n", COLOR_YELLOW, COLOR_RESET);
    DICT_TYPE D;
    INIT_DICT(D);

    // Insert 5 elements
    char elements[] = {'A', 'B', 'C', 'D', 'E'};
    printf("  Inserting A, B, C, D, E\n");
    for (int i = 0; i < 5; i++) {
        INSERT(D, elements[i]);
    }

    int initialCount = countElements(D);
    printf("  Initial count: %d\n", initialCount);

    // Delete 3 elements
    printf("  Deleting B, D\n");
    DELETE(D, 'B');
    DELETE(D, 'D');

    int afterCount = countElements(D);
    printf("  Count after deletions: %d\n", afterCount);

    assertTest("Count reduced by 2 after deletions", afterCount == initialCount - 2);
    assertTest("Deleted elements not found", !SEARCH(D, 'B') && !SEARCH(D, 'D'));
    assertTest("Remaining elements found", SEARCH(D, 'A') && SEARCH(D, 'C') && SEARCH(D, 'E'));
}

// Test 11: Stress Test - Many Elements
void test_StressFill() {
    printf("\n%s===== TEST 11: Stress Test - Large Insertions =====%s\n", COLOR_YELLOW, COLOR_RESET);
    DICT_TYPE D;
    INIT_DICT(D);

    int insertAttempts = 0;

    printf("  Inserting uppercase A-Z...\n");
    for (char c = 'A'; c <= 'Z'; c++) {
        #ifdef CLOSED_HASHING_IMPL
        if (countElements(D) >= MAX_SIZE) break;
        #endif
        INSERT(D, c);
        insertAttempts++;
    }

    printf("  Inserting lowercase a-z...\n");
    for (char c = 'a'; c <= 'z'; c++) {
        #ifdef CLOSED_HASHING_IMPL
        if (countElements(D) >= MAX_SIZE) break;
        #endif
        INSERT(D, c);
        insertAttempts++;
    }

    printf("  Inserting digits 0-9...\n");
    for (char c = '0'; c <= '9'; c++) {
        #ifdef CLOSED_HASHING_IMPL
        if (countElements(D) >= MAX_SIZE) break;
        #endif
        INSERT(D, c);
        insertAttempts++;
    }

    int finalCount = countElements(D);
    printf("  Attempted insertions: %d\n", insertAttempts);
    printf("  Final element count: %d\n", finalCount);

    assertTest("Stress test: Dictionary contains elements", finalCount > 0);

    #ifdef CLOSED_HASHING_IMPL
    assertTest("Closed hashing: Doesn't exceed capacity", finalCount <= MAX_SIZE);
    printf("  Load factor: %.2f%%\n", (finalCount * 100.0) / MAX_SIZE);
    #else
    assertTest("Open hashing: All elements inserted", finalCount == insertAttempts);
    #endif
}

// Test 12: Search Non-Existent After Deletions
void test_SearchAfterDeletions() {
    printf("\n%s===== TEST 12: Search After Deletions =====%s\n", COLOR_YELLOW, COLOR_RESET);
    DICT_TYPE D;
    INIT_DICT(D);

    // Insert A, C, E
    printf("  Inserting A, C, E\n");
    INSERT(D, 'A');
    INSERT(D, 'C');
    INSERT(D, 'E');

    // Search for B, D (never inserted)
    assertTest("Search for never-inserted 'B' returns false", SEARCH(D, 'B') == false);
    assertTest("Search for never-inserted 'D' returns false", SEARCH(D, 'D') == false);

    // Delete C
    printf("  Deleting C\n");
    DELETE(D, 'C');

    // Search again
    assertTest("Search for deleted 'C' returns false", SEARCH(D, 'C') == false);
    assertTest("Search for existing 'A' still returns true", SEARCH(D, 'A') == true);
    assertTest("Search for existing 'E' still returns true", SEARCH(D, 'E') == true);
}

// Test 13: Boundary Test - Hash Index Validation
void test_HashIndexBoundary() {
    printf("\n%s===== TEST 13: Hash Index Boundary Test =====%s\n", COLOR_YELLOW, COLOR_RESET);
    DICT_TYPE D;
    INIT_DICT(D);

    // Insert various ASCII characters
    char testChars[] = {' ', '!', '0', '9', 'A', 'Z', 'a', 'z', '~'};
    int numChars = sizeof(testChars) / sizeof(testChars[0]);

    printf("  Testing hash indices for boundary characters:\n");
    bool allIndicesValid = true;

    for (int i = 0; i < numChars; i++) {
        #ifdef CLOSED_HASHING_IMPL
        if (countElements(D) >= MAX_SIZE) break;
        #endif

        char c = testChars[i];
        INSERT(D, c);
        int idx = GET_INDEX(D, c);
        printf("  '%c' (ASCII %d) -> index %d\n", c, (int)c, idx);

        if (idx < 0 || idx >= MAX_SIZE) {
            allIndicesValid = false;
            printf("    %s[ERROR]%s Index out of bounds!\n", COLOR_RED, COLOR_RESET);
        }
    }

    assertTest("All hash indices within valid range [0, MAX_SIZE)", allIndicesValid);
}

// Test 14: Random Batch Insert-Delete Cycle
void test_RandomBatchCycle() {
    printf("\n%s===== TEST 14: Random Batch Insert-Delete Cycle =====%s\n", COLOR_YELLOW, COLOR_RESET);
    DICT_TYPE D;
    INIT_DICT(D);

    srand((unsigned int)time(NULL));

    // Insert 10 random elements
    printf("  Inserting 10 random characters...\n");
    char inserted[10];
    for (int i = 0; i < 10; i++) {
        #ifdef CLOSED_HASHING_IMPL
        if (countElements(D) >= MAX_SIZE) break;
        #endif

        inserted[i] = 'A' + (rand() % 26);
        INSERT(D, inserted[i]);
        printf("    Inserted '%c'\n", inserted[i]);
    }

    int midCount = countElements(D);
    printf("  Count after insertions: %d\n", midCount);

    // Delete 5 random elements from what we inserted
    printf("  Deleting 5 random elements...\n");
    for (int i = 0; i < 5; i++) {
        int idx = rand() % 10;
        DELETE(D, inserted[idx]);
        printf("    Deleted '%c'\n", inserted[idx]);
    }

    int finalCount = countElements(D);
    printf("  Count after deletions: %d\n", finalCount);

    assertTest("Count decreased or stayed same after deletions", finalCount <= midCount);
}

// ==================== TEST RUNNER ====================

void runAllTests() {
    printf("\n");
    printf("========================================\n");
    printf("  HASH DICTIONARY AUTOMATED TEST SUITE\n");
    printf("  Implementation: %s\n", IMPL_NAME);
    printf("  Dictionary Size: %d\n", MAX_SIZE);
    printf("========================================\n");

    // Reset test statistics
    testStats.totalTests = 0;
    testStats.passedTests = 0;
    testStats.failedTests = 0;

    // Run all tests
    test_BasicInsertSearch();
    test_MultipleInsertions();
    test_DuplicateInsertion();
    test_DeleteOperation();
    test_CollisionHandling();
    test_EmptyDictionary();
    test_InsertDeleteInsert();
    test_ComprehensiveCycle();
    test_BatchOperations();
    test_DeleteMultiple();
    test_StressFill();
    test_SearchAfterDeletions();
    test_HashIndexBoundary();
    test_RandomBatchCycle();

    // Print final statistics
    printf("\n");
    printf("========================================\n");
    printf("          TEST RESULTS SUMMARY\n");
    printf("========================================\n");
    printf("Total Tests:  %d\n", testStats.totalTests);
    printf("%sPassed Tests: %d%s\n", COLOR_GREEN, testStats.passedTests, COLOR_RESET);
    if (testStats.failedTests > 0) {
        printf("%sFailed Tests: %d%s\n", COLOR_RED, testStats.failedTests, COLOR_RESET);
    } else {
        printf("Failed Tests: 0\n");
    }

    double passRate = (testStats.totalTests > 0) ? (100.0 * testStats.passedTests / testStats.totalTests) : 0.0;

    if (passRate == 100.0) {
        printf("Pass Rate:    %s%.2f%%%s\n", COLOR_GREEN, passRate, COLOR_RESET);
    } else if (passRate >= 80.0) {
        printf("Pass Rate:    %s%.2f%%%s\n", COLOR_YELLOW, passRate, COLOR_RESET);
    } else {
        printf("Pass Rate:    %s%.2f%%%s\n", COLOR_RED, passRate, COLOR_RESET);
    }

    printf("========================================\n");

    if (testStats.failedTests == 0) {
        printf("%s\n   ALL TESTS PASSED!\n", COLOR_GREEN);
        printf("   Implementation is CORRECT.%s\n\n", COLOR_RESET);
    } else {
        printf("%s\n   SOME TESTS FAILED!\n", COLOR_RED);
        printf("   Please review the implementation.%s\n\n", COLOR_RESET);
    }
}

int main() {
    printf("\n");
    printf("%s========================================%s\n", COLOR_CYAN, COLOR_RESET);
    printf("%s   HASH DICTIONARY TEST SUITE%s\n", COLOR_CYAN, COLOR_RESET);
    printf("%s========================================%s\n", COLOR_CYAN, COLOR_RESET);

    runAllTests();

    return 0;
}
