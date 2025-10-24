# Hash Dictionary Testing Suite

## Overview
This directory contains comprehensive testing drivers for both **Open Hashing (Separate Chaining)** and **Closed Hashing (Linear Probing)** implementations.

## Files
- `open_hashing.c/.h` - Open hashing implementation
- `closed_hashing.c/.h` - Closed hashing implementation
- `main.c` - Interactive driver program with manual testing capabilities
- `test_suite.c` - **Automated test suite with 14 comprehensive tests**

## Test Suite Features

The `test_suite.c` file provides:

### Automated Tests (14 total)
1. **Basic Insert and Search** - Fundamental operations
2. **Multiple Insertions** - Batch insertion verification
3. **Duplicate Insertion Prevention** - Ensures no duplicates
4. **Delete Operation** - Single deletion correctness
5. **Collision Handling** - Tests hash collision resolution
6. **Empty Dictionary Operations** - Edge case testing
7. **Insert-Delete-Insert Sequence** - State management
8. **Comprehensive CRUD Cycle** - Full lifecycle testing
9. **Batch Populate Operations** - Large batch insertions (e.g., "HELLOWORLD")
10. **Delete Multiple Elements** - Sequential deletions
11. **Stress Test** - Insert A-Z, a-z, 0-9 (62 characters)
12. **Search After Deletions** - Verify search correctness post-delete
13. **Hash Index Boundary Test** - Validate hash function output
14. **Random Batch Insert-Delete Cycle** - Randomized operations

### Features
- Color-coded output (PASS/FAIL indicators)
- Detailed test statistics (pass rate, total/passed/failed)
- Comprehensive assertions for each test case
- Verbose output showing intermediate steps
- Easy switching between implementations

## Manual Testing Driver (main.c)

The existing `main.c` provides an interactive menu with:
- Manual insert/delete/search operations
- Batch populate with random or predefined strings
- Delete random elements
- Hash function testing
- Stress testing (A-Z insertion)
- Statistics display (load factor, chain lengths, etc.)

## Known Issues Found During Testing

### Open Hashing (open_hashing.c)
- **Line 46**: `search()` function has `return;` instead of `return false;`
  - Missing return value will cause compilation error
  - **Location**: `open_hashing.c:46`

### Closed Hashing (closed_hashing.c)
- **Missing include**: `#include <stdio.h>` needed for `printf()` in `printDictionary()`
  - Currently causes implicit declaration warning
  - **Location**: `closed_hashing.c:51`

## Compilation Instructions

### For Interactive Driver (main.c)

**After fixing the bugs above**, compile with:

```bash
# For Open Hashing
gcc -o main_open main.c open_hashing.c -DOPEN_HASHING_IMPL

# For Closed Hashing
gcc -o main_closed main.c closed_hashing.c -DCLOSED_HASHING_IMPL
```

### For Automated Test Suite (test_suite.c)

**After fixing the bugs above**, compile with:

```bash
# For Open Hashing Tests
gcc -o test_open test_suite.c open_hashing.c -DOPEN_HASHING_IMPL

# For Closed Hashing Tests
gcc -o test_closed test_suite.c closed_hashing.c -DCLOSED_HASHING_IMPL
```

Then run:
```bash
./test_open     # Run all tests for open hashing
./test_closed   # Run all tests for closed hashing
```

## Switching Between Implementations

In both `main.c` and `test_suite.c`, uncomment the desired implementation at the top:

```c
// Choose implementation: uncomment one
// #define CLOSED_HASHING_IMPL
#define OPEN_HASHING_IMPL
```

## Test Suite Output Example

```
========================================
  HASH DICTIONARY AUTOMATED TEST SUITE
  Implementation: Open Hashing (Chaining)
  Dictionary Size: 11
========================================

===== TEST 1: Basic Insert and Search =====
[PASS] Insert 'A' and search finds it
[PASS] Search for non-existent 'Z' returns false

===== TEST 2: Multiple Insertions =====
  Inserting: A B C D E
[PASS] All 5 inserted elements are searchable

...

========================================
          TEST RESULTS SUMMARY
========================================
Total Tests:  42
Passed Tests: 42
Failed Tests: 0
Pass Rate:    100.00%
========================================

   ALL TESTS PASSED!
   Implementation is CORRECT.
```

## Batch Operations Available

### In main.c:
- **Populate with Random Characters** - Insert N random chars (A-Z, a-z, 0-9)
- **Populate with Predefined String** - Insert chars from a string
- **Delete Random Elements** - Delete N random existing elements
- **Stress Test** - Insert entire alphabet A-Z

### In test_suite.c:
- Automated batch tests are built into test cases
- Test 9: Batch inserts "HELLOWORLD" and verifies unique count
- Test 11: Stress test inserts A-Z, a-z, 0-9
- Test 14: Random batch insert-delete cycle

## Implementation Details

### Open Hashing
- Uses separate chaining with linked lists
- No fixed capacity (chains grow dynamically)
- Handles collisions by chaining elements

### Closed Hashing
- Uses linear probing for collision resolution
- Fixed capacity (MAX = 11)
- Uses EMPTY ('*') and DELETED ('?') markers

## Notes
- Both implementations use `char` as the element type
- Hash function: `hash(elem) = elem % MAX_SIZE`
- All tests are designed to work with both implementations
- The test suite validates correctness, collision handling, and edge cases

## Recommendations for Future Testing

1. **Fix the compilation bugs** listed above
2. Run the automated test suite on both implementations
3. Use the interactive driver for manual exploration
4. Consider adding more stress tests with larger datasets
5. Test with different MAX_SIZE values to observe collision behavior

## Bug Report Summary

| File | Line | Issue | Severity |
|------|------|-------|----------|
| open_hashing.c | 46 | Missing return value in `search()` | **Critical** - Prevents compilation |
| closed_hashing.c | 51 | Missing `#include <stdio.h>` | **Medium** - Causes warnings, may link successfully |

Both bugs must be fixed before the test suite can run successfully.
