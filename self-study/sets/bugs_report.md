# Bug Report - Multi-Word Set Implementation

## multi_word.c

### Bug 1
**Function:** `displaySet`
**Line:** 14
**Type:** Logical Bug
**Issue:** The mask calculation uses `i` (the word index) instead of `j` (the bit position). This will always check the same bit position for each bit in a word.
**Fix:** Change `WORD mask = 1 << i;` to `WORD mask = 1 << j;`

### Bug 2
**Function:** `insert`
**Line:** 24
**Type:** Logical Bug
**Issue:** Division by wrong value. Should divide by `N_BITS` (bits per word) not `N_WORDS` (number of words).
**Fix:** Change `A[floor(elem / N_WORDS)]` to `A[floor(elem / N_BITS)]` (appears twice on lines 24 and 26)

### Bug 3
**Function:** `insert`
**Line:** 25
**Type:** Logical Bug
**Issue:** Modulo by wrong value. Should use `N_BITS` not `N_WORDS`.
**Fix:** Change `1 << (elem % N_WORDS)` to `1 << (elem % N_BITS)`

### Bug 4
**Function:** `isMember`
**Line:** 30
**Type:** Logical Bug
**Issue:** Division by wrong value - same as insert.
**Fix:** Change `A[floor(elem / N_WORDS)]` to `A[floor(elem / N_BITS)]`

### Bug 5
**Function:** `isMember`
**Line:** 31
**Type:** Logical Bug
**Issue:** Modulo by wrong value - same as insert.
**Fix:** Change `1 << (elem % N_WORDS)` to `1 << (elem % N_BITS)`

### Bug 6
**Function:** `deleteElem`
**Line:** 36
**Type:** Logical Bug
**Issue:** Division by wrong value - same as insert.
**Fix:** Change `A[floor(elem / N_WORDS)]` to `A[floor(elem / N_BITS)]` (appears twice on lines 36 and 38)

### Bug 7
**Function:** `deleteElem`
**Line:** 37
**Type:** Logical Bug
**Issue:** Modulo by wrong value - same as insert.
**Fix:** Change `1 << (elem % N_WORDS)` to `1 << (elem % N_BITS)`

### Bug 8
**Function:** `deleteElem`
**Line:** 38
**Type:** Logical Bug
**Issue:** Wrong bitwise operation. To delete an element, you need to use AND with the complement of the mask (NOT just AND with the mask).
**Fix:** Change `A[floor(elem / N_WORDS)] = word & mask;` to `A[floor(elem / N_BITS)] = word & ~mask;`

---

## Notes
The multi_word.c file has a systematic issue where `N_WORDS` and `N_BITS` are confused throughout. Remember:
- `N_BITS` = bits per word (32 in this case for unsigned int)
- `N_WORDS` = number of words in the set array (4)
- To find which word: `elem / N_BITS`
- To find which bit in that word: `elem % N_BITS`
