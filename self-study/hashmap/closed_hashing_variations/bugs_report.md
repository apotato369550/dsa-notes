# Bug Report - Closed Hashing Variations

## double_hashing.c

### Bug 1
**Function:** `getIndex`
**Line:** 49
**Type:** Logical Bug
**Issue:** The condition `D[i] != EMPTY == false` is incorrect operator precedence. This evaluates as `(D[i] != EMPTY) == false` which means it continues when the slot IS empty, which is backwards.
**Fix:** Change to `D[i] != EMPTY` or add explicit parentheses: `(D[i] != EMPTY) == false` should be `!(D[i] == EMPTY)` or simply `D[i] != EMPTY`

---

## quadratic_hashing.c

### Bug 1
**Function:** `getIndex`
**Line:** 40
**Type:** Logical Bug
**Issue:** Same as double_hashing.c - the condition `D[i] != EMPTY == false` has incorrect operator precedence.
**Fix:** Change to `D[i] != EMPTY` or `!(D[i] == EMPTY)`

---

## key_based.c

### Bug 1
**Function:** `getIndex`
**Line:** 76
**Type:** Syntax Bug
**Issue:** Missing return value. Function is declared to return `int` but the return statement has no value.
**Fix:** Change `return;` to `return -1;` (to indicate element not found)

### Bug 2
**Function:** `search`
**Line:** 85-87
**Type:** Logical Bug
**Issue:** The function doesn't check if the element is at the hashed position itself (in `D.Elem[hashed].data`). It only searches the linked chain, missing elements stored directly in the hash table.
**Fix:** Add a check before traversing: `if (D.Elem[hashed].data == elem) return true;`

### Bug 3
**Function:** `getIndex`
**Line:** 78-80
**Type:** Logical Bug
**Issue:** Same as search - doesn't check if the element is at the hashed position itself before traversing the chain.
**Fix:** Add a check: `if (D.Elem[hashed].data == elem) return hashed;` before the traversal loop

---

## synonym_list.c

### Bug 1
**Function:** `insert`
**Line:** 17
**Type:** Logical Bug
**Issue:** Condition check is backwards. It says `if ((*D).last < MAX)` but `last` is initialized to `MAX` and should grow beyond `MAX`. The check should be `< MAX * 2` to match the array size.
**Fix:** Change `if ((*D).last < MAX)` to `if ((*D).last < MAX * 2)`

### Bug 2
**Function:** `deleteElem`
**Line:** 39
**Type:** Logical Bug
**Issue:** Wrong condition check. After searching in the synonym area (indices >= MAX), it checks `if (i < MAX)` which would never be true since `i` starts at `MAX`.
**Fix:** Change `if (i < MAX)` to `if (i < (*D).last)`

---
